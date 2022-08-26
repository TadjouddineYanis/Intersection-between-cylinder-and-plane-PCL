#include <iostream>
#include<vector>
#include <cmath>
#include <Eigen/Dense>
#include <pcl/io/pcd_io.h>
#include <pcl/common/angles.h>
#include <pcl/features/normal_3d.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <opencv2/core/types.hpp>

using namespace std;

//Function to generate a cylinder => Oxyz
pcl::PointCloud<pcl::PointXYZ>::Ptr cylinder(float radius, float z_long){
	pcl::PointCloud<pcl::PointXYZ>::Ptr points_cylindre (new pcl::PointCloud<pcl::PointXYZ>);
	for (float z=-z_long; z <= z_long; z += 0.05){
		for (float angle=0.0;angle<=360.0; angle+=4.5){
			pcl::PointXYZ point;
			point.x = radius * cos(pcl::deg2rad(angle));
			point.y = radius * sin(pcl::deg2rad(angle));
			point.z = z;
			points_cylindre->points.push_back(point);
		}	 
	}
	return (points_cylindre);
}
//Function to generate a plane => Oxy
pcl::PointCloud<pcl::PointXYZ>::Ptr plane(float taille_xy) {
	pcl::PointCloud<pcl::PointXYZ>::Ptr points_plan (new pcl::PointCloud<pcl::PointXYZ>);
	for(float y=-taille_xy;y<=taille_xy;y=y+0.05){
		for(float x=-taille_xy;x<=taille_xy;x=x+0.05){
			pcl::PointXYZ p;
			p.x = x;
			p.y = y;
			p.z = 0;
			points_plan -> points.push_back(p);
		}
	}
	return points_plan;
}
//Function to tranform the plane generated, according to an angle theta
pcl::PointCloud<pcl::PointXYZ>::Ptr matrix_transformation(pcl::PointCloud<pcl::PointXYZ>::ConstPtr plann, float theta){
	pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_points (new pcl::PointCloud<pcl::PointXYZ> ());
	Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
	transform (0,0) = cos(theta);
  	transform (0,2) = sin(theta);
  	transform (2,0) = -sin(theta);
  	transform (2,2) = cos(theta);
  	pcl::transformPointCloud(*plann, *transformed_points, transform);
  	return transformed_points;
}
//Function to stock the 3D XYZ points of the transformed plane, to another format in order to manipulate them
vector<cv::Point3f> points_plan(pcl::PointCloud<pcl::PointXYZ>::ConstPtr plan){
	vector<cv::Point3f> data_plan;
	for(const auto& point_plan: *plan){
  		data_plan.push_back(cv::Point3f(point_plan.x, point_plan.y, point_plan.z));
  	}
  	return data_plan;
}
//Function to extract or to access the lines who composed the plane. It will be easier to have the intersection.
//Indeed, we are looking for the intersection between a line of the plane and the cylinder. We must have two intersection points all the time.
pcl::PointCloud<pcl::PointXYZ>::Ptr droite_plan(vector<cv::Point3f> plan, int val){
	int compteur(0);
	pcl::PointCloud<pcl::PointXYZ>::Ptr droite (new pcl::PointCloud<pcl::PointXYZ>);
	for(size_t j=0; j<plan.size()-1; j++){
  		if(plan[j].y != plan[j+1].y){
  			compteur++;
  		}else{
  			compteur = compteur;
  		}
  		if(compteur == val){
  			pcl::PointXYZ p;
  			p.x = plan[j].x;
  			p.y = plan[j].y;
  			p.z = plan[j].z;
  			droite -> points.push_back(p);
  		}
  	}
  	return droite;
}
//Function to compute the intersection between the cylinder and the plane.
//plane equation (y=theta and z=ax+b); cylinder equation (x^2 + y^2 = r^2 and z=val).
//we are looking for an intersection point I (x, y, z). And to find it, we need to compute a relation between the two equations.
//We found this equation after calculation : z^2 - 2bz + b^2 - a^2(r^2 - theta^2) = 0. We have to compute Delta and we will have z with only when Delta > 0.
//Then, x = (z - b)/a and y = theta (will be any point among the y points of the straight lines of the plane)
pcl::PointCloud<pcl::PointXYZ>::Ptr intersection_points(vector<cv::Point3f> p_plan, float radius){
	double a, b;
	double delta, z1, z2, x1, x2;
	pcl::PointCloud<pcl::PointXYZ>::Ptr p_inter (new pcl::PointCloud<pcl::PointXYZ>);
	vector<cv::Point3f> inter_plan;
	pcl::PointCloud<pcl::PointXYZ>::Ptr d_plan;
	pcl::PointXYZ center;
	center.x = 0;
	center.y = 0;
	center.z = 0;
	p_inter -> points.push_back(center);
	for(int i=0;i<=80;i++){
		d_plan = droite_plan(p_plan, i);
		inter_plan = points_plan(d_plan);
		a = (inter_plan[40].z - inter_plan[10].z)/(inter_plan[40].x - inter_plan[10].x);
		b = inter_plan[40].z - (a*inter_plan[40].x);
		delta = pow((-2*b),2) - 4*(pow(b,2) - pow(a,2)*(pow(radius, 2) - pow(inter_plan[0].y,2)));
		if(delta > 0.0){
			z1 = (2*b - sqrt(delta))/2;
			z2 = (2*b + sqrt(delta))/2;
			x1 = (z1 - b)/a;
			x2 = (z2 - b)/a;
			pcl::PointXYZ p1;
			p1.x = x1;
			p1.y = inter_plan[0].y;
			p1.z = z1;
			pcl::PointXYZ p2;
			p2.x = x2;
			p2.y = inter_plan[0].y;
			p2.z = z2;
			p_inter -> points.push_back(p1);
			p_inter -> points.push_back(p2);	
		}
	}
	return p_inter;
}
//Function to extract the x points of the intersection found in order to plot them according to a 2D space
vector<double> points_x(pcl::PointCloud<pcl::PointXYZ>::ConstPtr p_inter){
	vector<double> x;
	for(const auto& point_x: *p_inter){
  		x.push_back(point_x.x - point_x.z);
  	}
  	return x;
}
//Function to extract the y points of the intersection found in order to plot them according to a 2D space
vector<double> points_y(pcl::PointCloud<pcl::PointXYZ>::ConstPtr p_inter){
	vector<double> y;
	for(const auto& point_y: *p_inter){
  		y.push_back(point_y.y);
  	}
  	return y;
}
//Function to generate a circle according to a center(cx, cy) and a r radius : (x-cx)^2 + (y-cy)^2 = r^2
void generateCircleData(const double cx, const double cy, const double r, int nbPts, vector<double> & x, vector<double> & y){
    	for(double i = 0 ; i < nbPts ; i += (2.0 * M_PI)/nbPts){
        	x.push_back(r*cos(i) + cx);
        	y.push_back(r*sin(i) + cy);
    	}
}
//Function to generate an ellipse according to a center (cx, cy) and the constant a and b of an ellipse equation : (x-cx)^2/a^2 + (y-cy)^2/b^2 = 1
void generated_ellipse(const double cx, const double cy, double a, double b, int nb_point, vector<double> &x, vector<double> &y){
	for(double t=0.0; t<nb_point; t=t+(2.0 * M_PI)/nb_point){
		x.push_back(a*cos(t) + cx);
		y.push_back(b*sin(t) + cy);
	}
}
