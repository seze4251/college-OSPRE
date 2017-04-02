//
//  testAnalyzeImage.cpp
//  testAnalyzeImage
//
//  Created by Anthony on 3/21/2017.
//  Copyright � 2017 Anthony. All rights reserved.
//
#include <iostream>
#include <unistd.h>
#include <exception>
#include <stdio.h>
#include <string>
#include <cmath>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "analyzeImage_terminate.h"
#include "analyzeImage_initialize.h"
#include "PointEarthMoon.h"

#define MOON_RADIUS 1736.0
#define EARTH_RADIUS 6371.0

// Pre Declare Functions:
void readImage(std::string imgFilename, unsigned char* imIn);
//double calcSens(double* moonPxDiam, double* estimatedPosition, PointEarthMoon point);
void calcRadGuess(double* pxDiam, double* estPos, PointEarthMoon point, double* ans);

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

	unsigned char imIn[2428800];

	readImage("test/TestImages/moonTest.jpeg", imIn);

	//Output variables
	double centerPt_data[2];
	int centerPt_size[2];
	double radius;
	double numCirc;
	double alpha, beta, theta;
	double cameraWidth = 4120.0;
	double cameraHeight = 3260.0;

	try{
		analyzeImage(imIn, radGuessIn, sensitivity, centerPt_data, centerPt_size, 
			&radius, &numCirc, &alpha, &beta, &theta, pix_deg, cameraWidth, cameraHeight);
	} catch (const char*){
		std::cout << "Call to analyzeImage failed" << std::endl;
		return -1;
	}

	// Test that radius is within acceptable range
	if(radius<(59.8545-1e-4) || radius>(59.8545+1e-4)){
		std::cout << "Calculated radius is incorrect." << std::endl;
		std::cout << "Expected 59.8545 +/- 1e-4, but instead found: " << radius << std::endl;
	}

	// Test the calculated center point
	if(centerPt_data[0] < (2078.8762-1e-4) || centerPt_data[0] > (2078.8762+1e-4)){
		std::cout << "Calculated X center point is incorrect" << std::endl;
		std::cout << "Expected 2078.8762 +/- 1e-4 but instead found: " << centerPt_data[0] << std::endl;
	}
	if(centerPt_data[1] < (1559.0764-1e-4) || centerPt_data[1] > (1559.0764+1e-4)){
		std::cout << "Calculated Y center point is incorrect" << std::endl;
		std::cout << "Expected 1559.0764 +/- 1e-4 but instead found: " << centerPt_data[0] << std::endl;
	}

	//Test alpha, beta, theta
	if(alpha < (-0.0168-1e-4) || alpha > (-0.0168+1e-4)){
		std::cout << "Calculated alpha is incorrect" << std::endl;
		std::cout << "Expected -0.0168 +/- 1e-4 but instead found: " << alpha << std::endl;
	}
	if(beta < (-0.0138-1e-4) || beta > (-0.0138+1e-4)){
		std::cout << "Calculated beta is incorrect" << std::endl;
		std::cout << "Expected -0.0138 +/- 1e-4 but instead found: " << beta << std::endl;
	}
	if(theta < (1.7867-1e-4) || beta > (1.7867+1e-4)){
		std::cout << "Calculated theta is incorrect" << std::endl;
		std::cout << "Expected 1.7867 +/- 1e-4 but instead found: " << theta << std::endl;
	}
}

// *******************************
//
// Application Functionality:
//
// ********************************
/*
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
*/
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

/*double calcSens(double* moonPxDiam, double* estimatedPosition, PointEarthMoon point) {
	return (double) 0.99;

} */


/*
fprintf(logFile, "Read Image: Starting Image Read\n");

if (imgFilename.empty() == true) {
    fprintf(logFile, "Read Image: Input is empty string, all images have been read and processed in current test directory\n");
    throw "CameraController::readImage(), image name empty, no more images to read";
} else {
    fprintf(logFile, "Read Image: Input String: %s\n", imgFilename.c_str());
}

cv::Mat image;
image = cv::imread(imgFilename, cv::IMREAD_COLOR);


if(!image.data){
    fprintf(logFile, "Read Image ERROR: Could not open or find the image\n");
    throw InvalidFileName("ReadImage() no Image Name in directory");
} else {
    fprintf(logFile, "Read Image: Image Name Valid\n");
}

// Allocate variables
unsigned char* imIn = (unsigned char*) imageMessage->getImagePointer(); // <--- Change this to be compatible with msg
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

imageMessage -> currentImageSize = 2428800;
fprintf(logFile, "Read Image: Finished Image Read\n");
*/


void readImage(std::string imgFilename, unsigned char* imIn) {
	// Get image
	printf("Read Image: Starting Image Read\n");
	cv::Mat image;
	image = cv::imread(imgFilename, cv::IMREAD_COLOR);


	if (!image.data) {
		printf("Read Image ERROR: Could not open or find the image, Image Name: %s \n", imgFilename.c_str());
		return;
	}
	else {
		printf("Read Image: Image Name Valid, Image Name: %s\n", imgFilename.c_str());
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


	//imageMessage->currentImageSize = 2428800;
	printf("Read Image: Finished Image Read\n");
}
