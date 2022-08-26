#include <iostream>
#include <vector>
#include <cmath>
#include<string>
#include <pcl/io/pcd_io.h>

#include "figures.hpp"
#include "circle_regression.hpp"
#include "visualisation.hpp"
#include "FunctionsSearchIntersection.hpp"

/*** Example of solution to compute the intersection between a cylinder and a plane transformed according to an angle. ***/

#define CASE 0 //Put 1, if we want to compute the radius evolution according to the angle
#define display 1 //Put 1, if we want to visualise the 3D intersection
//the cylinder radius is fixed to 1. We can change, but we will need to change also the size of plan data generated.
#define radius_cylindre 1
#define angle_degree 20 //Start 1° if we want to plot radius according to the angle, else start 0.01° => not 0°
#define axe_z 2 //the higher of the cylinder
#define axe_xy 2 // the size of the plan within the plan Oxy
#define nb_iter 10000 //number of iteration for the descente of gradient. We avoid to have different radius for each execution with 10000

using namespace std;

string name_figure = "Intersection_circle_fitting";
string name_fi = "intersection_circle";

//Function to compute the evolution of the radius circle fitting according to the angle.
void evolution_radius_angle(float angle, int stop);

pcl::PointCloud<pcl::PointXYZ>::Ptr cylindre;
pcl::PointCloud<pcl::PointXYZ>::Ptr plan;
pcl::PointCloud<pcl::PointXYZ>::Ptr plan_transformed;
pcl::PointCloud<pcl::PointXYZ>::Ptr p_intersection;
vector<cv::Point3f> p_plane;
vector<double> xx, yy, x_estim, y_estim;
vector<double> r_init, r_finale, prediction;
double erreur; double rayon;

int main(){
    	int rouge[3] = {1, 0, 0}; int bleu[3] = {0, 0, 1};
    	vector<double> xc(1,0), yc(1,0);
    
	if(CASE == 1){
		evolution_radius_angle(angle_degree, 45);
	}else{
		cylindre = cylinder(radius_cylindre, axe_z);
		plan = plane(axe_xy);
		plan_transformed = matrix_transformation(plan, (angle_degree*M_PI)/180);
		p_plane = points_plan(plan_transformed);
		p_intersection = intersection_points(p_plane,radius_cylindre);
		xx = points_x(p_intersection);
		yy = points_y(p_intersection);
		plot(xx, yy, rouge, L"cercle d'intersection", L"X axis", L"Y axis", name_fi);
		r_init = random_randn(xx.size(), 0,1);
		//erreur = cost_function(xx, r_init, yy);
		//cout << "error: " << erreur << endl;
		r_finale = gradient_desc(xx, r_init, yy, nb_iter);
    		prediction = circle_model(xx, r_finale);
    		rayon = sqrt((xx[20]*xx[20]) + (prediction[20]*prediction[20]))/2;
    		generateCircleData(0,0,rayon,50,x_estim,y_estim);
		xc[0] = 0; yc[0] = 0;
		cout << "x_centre: " << xc[0] << endl;
		cout << "y_centre: " << yc[0] << endl;
		cout << "radius_estimated: " << rayon << endl;
		plot3(xx, yy, x_estim, y_estim, xc, yc, bleu, rouge, L"Circle Intersection and circle fitting", L"X axis", L"Y axis", name_figure);
  		if (display == 1) visualization_cylinder_plan_intersection(cylindre, plan_transformed, p_intersection);
  	}
	return 0;
}

void evolution_radius_angle(float angle, int stop){
	vector<double> angle_degre, radius;
	int vert[3] = {0, 1, 0};
	cylindre = cylinder(radius_cylindre, axe_z);
	plan = plane(axe_xy);
	int cpt(0);
	angle_degre.push_back(0);
	radius.push_back(1);
	for(float i=angle;i<=stop;i=i+1){
		plan_transformed = matrix_transformation(plan, (i*M_PI)/180);
		p_plane = points_plan(plan_transformed);
		p_intersection = intersection_points(p_plane,radius_cylindre);
		xx = points_x(p_intersection);
		yy = points_y(p_intersection);
		r_init = random_randn(xx.size(), 0,1);
		r_finale = gradient_desc(xx, r_init, yy, 10000);
    		prediction = circle_model(xx, r_finale);
    		rayon = sqrt((xx[20]*xx[20]) + (prediction[20]*prediction[20]))/2;
		angle_degre.push_back(i);
		radius.push_back(rayon);
		cpt++;
		cout << "iteration: " << cpt << endl;
		cout << "radius_estimated: " << rayon << endl;
	}
	plot(angle_degre, radius, vert, L"Radius evolution in function of the angle", L"Angle (degree)", L"Radius(micro metre)", "radius_angle");
}



