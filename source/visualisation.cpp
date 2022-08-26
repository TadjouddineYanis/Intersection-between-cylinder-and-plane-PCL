#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>


//Function to visualize the cylinder, the tranformed plane and the points represented the intersection between the two in 3D.
void visualization_cylinder_plan_intersection(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cylindre, pcl::PointCloud<pcl::PointXYZ>::ConstPtr plan_transformed, pcl::PointCloud<pcl::PointXYZ>::ConstPtr intersection){
	pcl::visualization::PCLVisualizer viewer ("3D Viewer");
  	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cylindre_color_handler (cylindre, 0, 255, 0);
  	viewer.addPointCloud(cylindre, cylindre_color_handler, "cylinder");
  	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> plan_transformed_color_handler (plan_transformed, 0, 0, 255);
  	viewer.addPointCloud (plan_transformed, plan_transformed_color_handler, "plan_transformed");
  	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> intersection_color_handler (intersection, 255, 0, 0);
  	viewer.addPointCloud(intersection, intersection_color_handler, "intersection");
  	viewer.addCoordinateSystem (1.0, "cloud", 0);
  	viewer.setBackgroundColor(1, 1, 1);
  	viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cylinder");
  	viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "plan_transformed");
  	viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "intersection");
	while (!viewer.wasStopped ()){
		viewer.spinOnce (100);
	}
}
