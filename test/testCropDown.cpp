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
#include <string>
#include <cmath>
#include <time.h>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// analyzeImage helpers
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "analyzeImage_terminate.h"
#include "analyzeImage_initialize.h"
#include "analyzeImage_emxAPI.h"
#include "analyzeImage_emxutil.h"

// OSPRE helpers
#include "PointEarthMoon.h"

// Namespaces
using namespace cv;

// Define common values
#define MOON_RADIUS 1736.0
#define EARTH_RADIUS 6371.0
#define DOWN_SAMPLE_SIZE 2

// Global variables
Mat imIn, dst, tmp, imGray, imGrayDS;
char* window_name = "Downsampling and Image Finding Example";


/***
Main Function
*/
int main(int argc, char* argv[]){
	imIn = imread("test/TestImages/nomTest.jpg");
	if(!imIn.data){
		printf("Could not read image");
		return -1;
	}

	tmp = imIn;
	dst = tmp;

	// Find circle and time
	clock_t startFind = clock();
	cvtColor(imIn, imGray, CV_BGR2GRAY);
	// smooth image to improve finding accuracy and time
	GaussianBlur(imGray, imGray, Size(9,9), 2, 2);

	// Downsample image
	pyrDown(imGray, imGrayDS, Size(imGray.cols/DOWN_SAMPLE_SIZE, imGray.cols/DOWN_SAMPLE_SIZE));
	vector<Vec3f> circles;
	HoughCircles(imGrayDS, circles, CV_HOUGH_GRADIENT, 2, imIn.rows/2, 200, 100);

	for(int i=0; i < circles.size(); i++){
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// Draw found circles
		circle(imIn, center, 3, Scalar(0,255,0), -1, 8, 0); // Centerpoint
		circle(imIn, center, radius, Scalar(0,0,255), 3, 8, 0);
	}


	// Create window for display
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
	imshow(window_name, dst);


}
