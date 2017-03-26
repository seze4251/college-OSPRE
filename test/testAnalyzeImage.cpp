//
//  testAnalyzeImage.cpp
//  testAnalyzeImage
//
//  Created by Anthony on 3/21/2017.
//  Copyright © 2017 Anthony. All rights reserved.
//
#include <iostream>
#include <unistd.h>
#include <exception>
#include <stdio.h>
#include <string>

#include <cmath>
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "analyzeImage_terminate.h"
#include "analyzeImage_initialize.h"
#include "ImageProcessor.h"
#include "Service.h"

#define MOON_RADIUS 1736.0
#define EARTH_RADIUS 6371.0

/***
MAIN SCRIPT
*/
int main(int argc, char **argv) {
	//Setup time
	time_t rawtime;
	struct tm * timinfo;

	// Set up analysis variables
	double pix_deg[2] = {72, 72};
	double estPos[3] = {21212.105392, 25545.913981, 7945.349932};
	double moonEphem[3] = {-20878.747372, 347641.764991, 132624.248850};
	PointEarthMoon emPt = PEM_Earth;

	double sensitivity = 0.97;
	double radGuessIn[2] = {58, 63};

	//setImageParameters(emPt, pix_deg, estPos, moonEphem, sensitivity, radGuessIn);

	unsigned char* imIn[2428800];

	readImage("TestImages/moonTest.jpg", imIn);

	//Output variables
	double centerPt_data[2];
	int centerPt_size[2];
	double radius;
	double numCirc;
	double alpha, beat, theta;
	double cameraWidth = 4120.0;
	double cameraHeight = 3260.0;

	analyzeImage(imIn, radGuessIn, sensitivity, centerPt_data, centerPt_size, 
		&radius, &numCirc, &alpha, &beta, &theta, pix_deg, cameraWidth, cameraHeight);

}

// *******************************
//
// Application Functionality:
//
// ********************************
void setImageParameters(PointEarthMoon point, double* pix_deg, double* estPos, double* moonEphem,
                        double* sensitivity, double* radGuessIn) {
	// estimated Position is a double[3] km, ECI frame
	// Need to Set Variables:
	// double sensitivity;
	// double pxDeg[2]; // Pixel Per Degree
	// double radGuessIn[2]; //Pixel Radius Guess from estimated Position

	if (point == PEM_Moon) {
		// Evaluate on the assumption that we're pointing at the Earth
		//
		// Need to take estimated position, calculate expected angular diameter of celestial body, use image properties to turn this value
		// into an estimated pixel radius
		//
		// Use emperically determined correlation function to determine the necessary sensitivity based on phase of moon and position
		//

		double dist = sqrt(pow((moonEphem[0] - estPos[0]), 2) + pow((moonEphem[1] - estPos[1]), 2) + pow((moonEphem[2] - estPos[2]), 2)); // km
		double angDiam = atan(MOON_RADIUS / dist) * 180 / M_PI * 2; // [deg]
		double moonPxDiam[2] = { angDiam*pix_deg[0], angDiam*pix_deg[1] }; // [px], diam of Moon in height and width

																		   // Get radius guess
		calcRadGuess(moonPxDiam, estPos, point, radGuessIn);

		// Get analysis sensitivity
		sensitivity = calcSens(moonPxDiam, estPos, point); // This function needs to be emperically determined

	}
	else if (point == PEM_Earth) {
		// Evaluate on the assumption that we're pointing at the Moon

		double dist = sqrt(pow(estPos[0], 2) + pow(estPos[1], 2) + pow(estPos[2], 2));
		double angDiam = atan(EARTH_RADIUS / dist) * 180 / M_PI * 2; // [deg]
		double earthPxDiam[2] = { angDiam*pix_deg[0], angDiam*pix_deg[1] }; // [px], diam of Earth in height and width

		calcRadGuess(earthPxDiam, estPos, point, radGuessIn);

		// Get analysis sensitivity
		sensitivity = calcSens(earthPxDiam, estPos, point); // This function needs to be emperically determined
	}
}

/**
HELPER FUNCTIONS
*/

/*
calcRadGuess
TODO:
- Create emperical function describing estimated radius
- */
void calcRadGuess(double* pxDiam, double* estPos, PointEarthMoon point, double* ans) {
	/*if (point == PEM_Earth) {
	// Plug in estimated position to Earth emperical function
	ans[0] = pxDiam[0] / 2 - 2;
	ans[1] = pxDiam[1] / 2 + 2;
	} else if (point == PEM_Moon) {
	// Plug in estimated position to Moon emperical function
	ans[0] = pxDiam[0] / 2 - 2;
	ans[1] = pxDiam[1] / 2 + 2;
	}*/

	ans[0] = pxDiam[0] / 2 - 2;
	ans[1] = pxDiam[1] / 2 + 2;

	/*
	ans[0] = 157;
	ans[1] = 167;
	*/

}

double calcSens(double* moonPxDiam, double* estimatedPosition, PointEarthMoon point) {
	return (double) 0.99;

}


void readImage(std::string imgFilename, unsigned char* imIn[2428800]) {
	// Get image
	fprintf(logFile, "Read Image: Starting Image Read\n");
	cv::Mat image;
	image = cv::imread(imgFilename, cv::IMREAD_COLOR);


	if (!image.data) {
		fprintf(logFile, "Read Image ERROR: Could not open or find the image\n");
		return;
	}
	else {
		fprintf(logFile, "Read Image: Image Name Valid\n");
	}

	// Allocate variables
	// TODO:
	// - Verify that this is correct
	//unsigned char* imIn = (unsigned char*)imageMessage->getImagePointer();
	cv::Vec3b intensity;

	int counter = 0;
	// Loop through image and convert
	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			intensity = image.at<cv::Vec3b>(j, i);
			uchar blue = intensity.val[0];
			uchar green = intensity.val[1];
			uchar red = intensity.val[2];
			imIn[counter] = red;
			imIn[counter + 809600] = green;
			imIn[counter + 2 * 809600] = blue;
			counter++;
		}
	}

	imageMessage->currentImageSize = 2428800;
	fprintf(logFile, "Read Image: Finished Image Read\n");
}
