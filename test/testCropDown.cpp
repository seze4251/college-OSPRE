//
//  testCropDown.cpp
//  testCropDown
//
//  Created by Anthony on 4/11/2017.
//  Copyright � 2017 Anthony. All rights reserved.
//
 
#include <iostream>
#include <unistd.h>
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
#include <iomanip>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Namespaces
using namespace cv;

// Define common values
#define MOON_RADIUS 1736.0
#define EARTH_RADIUS 6371.0
#define DOWN_SAMPLE_SIZE 2
#define CROP_SIZE 400

// Global variables
Mat imIn, dst, tmp, imGray, imGrayDS;
string window_name = "Downsampling and Image Finding Example";


/***
Main Function
*/
int main(int argc, char* argv[]){
	std::cout << std::scientific << std::setprecision(6) << std::endl;

	std::cout << "Reading image" << std::endl;
	imIn = imread("test/TestImages/Full_Moon_Test_Iteration_One-01.jpg");
	// imIn = imread("test/TestImages/blueMoon.jpg");
	if(!imIn.data){
		printf("Could not read image");
		return -1;
	}
	namedWindow("Original", WINDOW_NORMAL);
	imshow("Original", imIn);
	resizeWindow("Original", 800, 800);
	waitKey(0);

	tmp = imIn;
	dst = tmp;

	cvtColor(imIn, imGray, CV_BGR2GRAY);
	// smooth image to improve finding accuracy and time
	GaussianBlur(imGray, imGray, Size(9,9), 2, 2);

	// Downsample image
	// pyrDown(imGray, imGrayDS, Size(imGray.cols/DOWN_SAMPLE_SIZE, imGray.rows/DOWN_SAMPLE_SIZE));
	cv::threshold(imGray, imGray, 64, 255, THRESH_BINARY);
	namedWindow("Threshold", WINDOW_NORMAL);
	imshow("Threshold", imGray);
	resizeWindow("Threshold", 800, 800);
	waitKey(0);

	// Find circle in downsampled image and time
	clock_t startFind = clock();
	vector<Vec3f> circles;
	std::cout << "Calling HoughCircles" << std::endl;

	HoughCircles(imGray, circles, CV_HOUGH_GRADIENT, 2, imIn.rows/2, 200, 50);
	clock_t endFind = clock();
	double elapsedTime = (endFind - startFind)/CLOCKS_PER_SEC;
	std::cout << "Elapsed time = " << elapsedTime << std::endl;

	if(circles.size() == 0 || !circles.size()){
		std::cout << "No circles found!" << std::endl;
		return -1;
	} else {
		std::cout << "Found " << circles.size() << " circles" << std::endl;
		std::cout << "(x, y) = (" << circles[0][0] << ", " << circles[0][1] << ")" << std::endl;
		std::cout << "" << std::endl;
	}

	// int CROP_SIZE = 3*DOWN_SAMPLE_SIZE*cvRound(circles[0][2]);

	// Create crop area around found moon
	std::cout << "Creating crop area" << std::endl;
	int rectX = cvRound(circles[0][0]) - CROP_SIZE/2;
	int rectY = cvRound(circles[0][1]) - CROP_SIZE/2;

	std::cout << "rectX = " << rectX << "\trectY = " << rectY << std::endl;

	cv::Rect myROI(rectX, //x
				   rectY, //y
				   CROP_SIZE, CROP_SIZE);

	std::cout << "Creating cropped image" << std::endl;
	cv::Mat croppedImage = imIn(myROI);

	double convHeight = imIn.rows/CROP_SIZE;
	double convWidth = imIn.cols/CROP_SIZE;

	/**
	--- Drawing function not working currently ---
	*/
	// for(int i=0; i < circles.size(); i++){
	// 	Point center(cvRound(convHeight*circles[0][0]), cvRound(2*circles[0][1]));
	// 	int radius = cvRound(convWidth*circles[0][2]);
	// 	// Draw found circles
	// 	circle(croppedImage, center, 3, Scalar(0,255,0), -1, 8, 0); // Centerpoint
	// 	circle(croppedImage, center, radius, Scalar(0,0,255), 3, 8, 0);
	// }

	// Create window for display
	//namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	std::cout << "Showing cropped image" << std::endl;
	namedWindow(window_name, WINDOW_NORMAL);
	imshow(window_name, croppedImage);
	resizeWindow(window_name, 600, 600);
	waitKey(0);



	return 0;
}
