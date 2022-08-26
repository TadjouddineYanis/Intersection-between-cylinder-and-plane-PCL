#include <pcl/io/pcd_io.h>
#include <opencv2/core/types.hpp>
pcl::PointCloud<pcl::PointXYZ>::Ptr cylinder(float radius, float z_long);
pcl::PointCloud<pcl::PointXYZ>::Ptr plane(float taille_xy);
pcl::PointCloud<pcl::PointXYZ>::Ptr matrix_transformation(pcl::PointCloud<pcl::PointXYZ>::ConstPtr plann, float theta);
std::vector<cv::Point3f> points_plan(pcl::PointCloud<pcl::PointXYZ>::ConstPtr plan);
pcl::PointCloud<pcl::PointXYZ>::Ptr droite_plan(std::vector<cv::Point3f> plan, int val);
pcl::PointCloud<pcl::PointXYZ>::Ptr intersection_points(std::vector<cv::Point3f> p_plan, float radius);
std::vector<double> points_x(pcl::PointCloud<pcl::PointXYZ>::ConstPtr p_inter);
std::vector<double> points_y(pcl::PointCloud<pcl::PointXYZ>::ConstPtr p_inter);
void generateCircleData(const double cx, const double cy, const double r, int nbPts, std::vector<double> &x, std::vector<double> &y);
void generated_ellipse(const double cx, const double cy, double a, double b, int nb_point, std::vector<double> &x, std::vector<double> &y);
