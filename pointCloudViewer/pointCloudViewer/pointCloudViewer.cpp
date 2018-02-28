// pointCloudViewer.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2/viz.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void help()
{
	cout
		<< "--------------------------------------------------------------------------" << endl
		<< "This program shows how to visualize a cube rotated around (1,1,1) and shifted "
		<< "using Rodrigues vector." << endl
		<< "Usage:" << endl
		<< "./widget_pose" << endl
		<< endl;
}
int main()
{
	help();
	viz::Viz3d myWindow("Coordinate Frame");
	myWindow.showWidget("Coordinate Widget", viz::WCoordinateSystem());
	//viz::WLine axis(Point3f(-1.0f, -1.0f, -1.0f), Point3f(1.0f, 1.0f, 1.0f));
	//axis.setRenderingProperty(viz::LINE_WIDTH, 4.0);
	//myWindow.showWidget("Line Widget", axis);
	viz::WCube cube_widget(Point3f(0.5, 0.5, 0.0), Point3f(0.0, 0.0, -0.5), true, viz::Color::blue());

	//viz::WText3D textX("x", Point3d(1, 0, 0), 0.1);
	//viz::WText3D textY("y", Point3d(0, 1, 0), 0.1);
	//viz::WText3D textZ("z", Point3d(0, 0, 1), 0.1);
	//myWindow.showWidget("textX Widget", textX);
	//myWindow.showWidget("textY Widget", textY);
	//myWindow.showWidget("textZ Widget", textZ);

	cube_widget.setRenderingProperty(viz::LINE_WIDTH, 4.0);
	myWindow.showWidget("Cube Widget", cube_widget);
	Mat rot_vec = Mat::zeros(1, 3, CV_32F);
	float translation_phase = 0.0, translation = 0.0;
	while (!myWindow.wasStopped())
	{
		/* Rotation using rodrigues */
		rot_vec.at<float>(0, 0) += CV_PI * 0.01f;
		rot_vec.at<float>(0, 1) += CV_PI * 0.01f;
		rot_vec.at<float>(0, 2) += CV_PI * 0.01f;
		translation_phase += CV_PI * 0.01f;
		translation = sin(translation_phase);
		Mat rot_mat;
		Rodrigues(rot_vec, rot_mat);
		Affine3f pose(rot_mat, Vec3f(translation, translation, translation));
		myWindow.setWidgetPose("Cube Widget", pose);
		myWindow.spinOnce(1, true);
	}
	return 0;
}



