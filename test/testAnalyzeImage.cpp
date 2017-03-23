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



	//rawtime = time(0);
	//timeinfo = localtime(&rawtime);
	//strftime(buffer, 80, "./log/ImageProcessorLog_%d-%m-%Y.log", timeinfo);

	//// Open Log File
	//logFile = fopen(buffer, "a+");

	//// Log Application Starting
	//fprintf(logFile, "Image Processor Application Started, Time = %ld\n", time(0));

	//// Set Timeout to 1 minute
	//setTimeoutTime(60, 0);

}

// *******************************
//
// Application Functionality:
//
// ********************************
void setImageParameters(PointEarthMoon point, double* pix_deg, double* estPos, double* moonEphem) {
	// estimated Position is a double[3] km, ECI frame
	// Need to Set Variables:
	// double sensitivity;
	// double pxDeg[2]; // Pixel Per Degree
	// double dv3[2]; //Pixel Radius Guess from estimated Position

	if (point == PEM_Earth) {
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
		calcRadGuess(moonPxDiam, estPos, point, dv3);

		// Get analysis sensitivity
		sensitivity = calcSens(moonPxDiam, estPos, point); // This function needs to be emperically determined

	}
	else if (point == PEM_Moon) {
		// Evaluate on the assumption that we're pointing at the Moon

		double dist = sqrt(pow(estPos[0], 2) + pow(estPos[1], 2) + pow(estPos[2], 2));
		double angDiam = atan(EARTH_RADIUS / dist) * 180 / M_PI * 2; // [deg]
		double earthPxDiam[2] = { angDiam*pix_deg[0], angDiam*pix_deg[1] }; // [px], diam of Earth in height and width

		calcRadGuess(earthPxDiam, estPos, point, dv3);

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


void processImage(void) {
	setImageParameters(msg->point, msg->pix_deg, msg->estimatedPosition, msg->moonEphem);


	fprintf(logFile, "Analyze Image: Starting Call to Analyze Image\n");
	fprintf(logFile, "Analyze Image Inputs:\n");

	fprintf(logFile, "dv3 = %f  %f, sens = %f, \npix_deg %f  %f, camera Width %d  camera height %d\n", dv3[0], dv3[1], sensitivity, msg->pix_deg[0], msg->pix_deg[1], msg->cameraWidth, msg->cameraHeight);

	analyzeImage((unsigned char*)msg->getImagePointer(), dv3, sensitivity, centerPt_data, centerPt_size, &radius, &numCirc, &alpha, &beta, &theta, msg->pix_deg, msg->cameraWidth, msg->cameraHeight);

	fprintf(logFile, "Analyze Image: Ended Call to Analyze Image\n");

	if (numCirc) {
		fprintf(logFile, "Analyze Image: BODY HAS BEEN FOUND!!!!\n");
		fprintf(logFile, "Found %1.2f Object(s)\n", numCirc);
		fprintf(logFile, "Center (%f,%f)\n ", centerPt_data[0], centerPt_data[1]);
		fprintf(logFile, "Radius %f\n", radius);
		fprintf(logFile, "Alpha = %f, Beta = %f,  Theta = %f\n", alpha, beta, theta); \
	}


	// TEMP
	pixel_error = 0;
	// Update ProcessedImageMessage
	processedImageMessage->update(alpha, beta, theta, pixel_error, msg->point, msg->timeStamp);
}

void readImage(std::string imgFilename) {
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
	unsigned char* imIn = (unsigned char*)imageMessage->getImagePointer(); // <--- Change this to be compatible with msg
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
