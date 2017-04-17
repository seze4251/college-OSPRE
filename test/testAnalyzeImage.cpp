//
//  testAnalyzeImage.cpp
//  testAnalyzeImage
//
//  Created by Anthony on 3/21/2017.
//  Copyright � 2017 Anthony. All rights reserved.
//
/**
TODO:
 - Merge newly generated analyzeImage code that deals with 13MP images
**/
 
#include <iostream>
#include <unistd.h>
#include <exception>
#include <stdio.h>
#include <string>
#include <cmath>
#include <time.h>
 #include <iomanip>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
#define CROP_SIZE 400

// Pre Declare Functions:
void readImage(std::string imgFilename, unsigned char* imIn);
void calcRadGuess(double* pxDiam, double* estPos, PointEarthMoon point, double* ans);
int testNominal(bool vOut);

/***
Main Function
*/
int main(int argc, char* argv[]){
	int nomCase = 1;

	bool vOut = 0; // Verbose output

	nomCase = testNominal(vOut);
}

/***
Nominal Test Case

13MP image, 4160 x 3120
67 px diameter moon in center
*/
int testNominal(bool vOut) {
	if(vOut){
		std::cout << "Starting nominal case" << std::endl;
	}

	std::cout << std::scientific << std::setprecision(6) << std::endl;

	bool testFailed = 0;
	//Setup time
	time_t rawtime;
	struct tm * timinfo;

	// double radiusRangeGuess[2] = {157, 167};
	double radiusRangeGuess[2] = {58, 63};
	double pix_deg[2] = {67, 67};
	double centerPt_data[2];
	int centerPt_size[2];
	double radius;
	double numCirc;
	double alpha;
	double beta;
	double theta;
	//double sensitivity = 0.99;
	double sensitivity = 0.97;

	//double imgWidth = 1100; double imgHeight = 736;
	double imgWidth = 4160; double imgHeight = 3120;
	

	// Initialize function 'analyzeImage' input arguments.
	// Load image with OpenCV
	if(vOut){
		std::cout << "Reading image with OpenCV" << std::endl;
	}
    
    cv::Mat imageTmp, imGray, imGrayDS;

    if(vOut){
    	std::cout << "Starting Image Read" << std::endl;
    }
    imageTmp = imread("test/TestImages/nomTest.jpg");
    // imageTmp = imread("test/TestImages/blueMoon.jpg", IMREAD_COLOR);
    if(vOut){
    	std::cout << "Finished Image Read" << std::endl;
    }
    
	if(!imageTmp.data){
		std::cout << "Could not read image" << std::endl;
		return -1;
	}

	// Downsample and crop
	cvtColor(imageTmp, imGray, CV_BGR2GRAY);
	// smooth image to improve finding accuracy and time
	GaussianBlur(imGray, imGray, Size(9,9), 2, 2);

	// Downsample image
	pyrDown(imGray, imGrayDS, Size(imGray.cols/DOWN_SAMPLE_SIZE, imGray.rows/DOWN_SAMPLE_SIZE));

	// Find circle in downsampled image and time
	vector<Vec3f> circles;
	HoughCircles(imGrayDS, circles, CV_HOUGH_GRADIENT, 2, imageTmp.rows/2, 200, 100);

	if(circles.size() == 0 || !circles.size()){
		std::cout << "No circles found!" << std::endl;
		return -1;
	}

	// int CROP_SIZE = 3*DOWN_SAMPLE_SIZE*cvRound(circles[0][2]);

	// Create crop area around found moon
	int rectX = cvRound(DOWN_SAMPLE_SIZE*circles[0][0]) - CROP_SIZE/2;
	int rectY = cvRound(DOWN_SAMPLE_SIZE*circles[0][1]) - CROP_SIZE/2;
	int rectCoords[2] = {rectX, rectY};
	cv::Rect myROI(rectX, //x
				   rectY, //y
				   CROP_SIZE, CROP_SIZE);

	cv::Mat image = imageTmp(myROI);

	// namedWindow("Cropped", WINDOW_NORMAL);
	// imshow("Cropped", image);
	// resizeWindow("Cropped", 600, 600);
	// cv::waitKey(0);

	emxArray_uint8_T *I;
	emxInitArray_uint8_T(&I, 3);
	cv::Vec3b intensity;
	int sizeimage, counter;
	int rows = image.rows;
	int cols = image.cols;
	sizeimage = rows*cols;
    I->size[0] = rows;
	I->size[1] = cols;
	I->size[2] = 3;

	if(vOut){
		std::cout << "Image rows = " << rows << "\tImage cols = " << cols << std::endl;
    	std::cout << "Starting Conversion to EMX array" << std::endl;
    }
	// Convert image into emxArray
	emxEnsureCapacity((emxArray__common *)I, 0, (int)sizeof(unsigned char));
    try{
		counter = 0;
		for (int i=0; i < cols; i++){
		  for (int j=0; j < rows; j++){
		    intensity = image.at<Vec3b>(j,i); 
	        uchar blue = intensity.val[0];
	        uchar green = intensity.val[1];
	        uchar red = intensity.val[2];
	        *(I->data + counter) = red;
	        *(I->data + counter + sizeimage) = green;
	        *(I->data + counter + 2*sizeimage) = blue;
	        counter++;
		  }
		}
	} catch(...) {
		std::cout << "Image conversion failed" << std::endl;
		return 0;
	}
    
    if(vOut){
    	std::cout << "Finished Conversion to EMX array" << std::endl;
    	std::cout << "Starting call to analyze image" << std::endl;
    }

	clock_t startFind = clock();
	try{
		analyzeImage( I, radiusRangeGuess, sensitivity,
                  pix_deg, imgWidth, imgHeight, centerPt_data,
                  centerPt_size, &radius, &numCirc,
                  &alpha, &beta, &theta, rectCoords);
	} catch (const char*){
		std::cout << "Call to analyzeImage failed" << std::endl;
		return -1;
	}
	clock_t endFind = clock();
	double timeElapsed = (endFind - startFind)/CLOCKS_PER_SEC;

	if(vOut){
	    std::cout << "Finished call to analyze image" << std::endl;
	    std::cout << "Time elapsed = " << timeElapsed << std::endl;
	    std::cout << "" << std::endl;
	}

    // ----------- Convert output back -------------
    double radius_Tmp = radius;
    // double centerPt_data_Tmp[2] = {centerPt_data[0], centerPt_data[1]};

    // radius = radius_Tmp;

    // std::cout << "Found x = " << centerPt_data[0] << std::endl;
    // std::cout << "Found y = " << centerPt_data[1] << std::endl;
    // std::cout << "rectX = " << rectX << "\trectY = " << rectY << std::endl;
    // std::cout << "" << std::endl;

    // centerPt_data[0] = centerPt_data[0] + rectX;
    // centerPt_data[1] = centerPt_data[1] + rectY;

    // alpha = (centerPt_data[0] - imgWidth / 2.0) / pix_deg[0];
    // beta = (centerPt_data[1] - imgHeight / 2.0) / pix_deg[1];

	// Test that radius is within acceptable range
	if(radius<(59.8545-2e-2) || radius>(59.8545+2e-2)){
		if(vOut){
			std::cout << "Calculated radius is incorrect." << std::endl;
			std::cout << "Expected 59.8545 +/- 0.02, but instead found: " << radius << std::endl;
		}
		testFailed = 1;
	}

	// Test the calculated center point
	if(centerPt_data[0] < (2078.8762-6e-2) || centerPt_data[0] > (2078.8762+6e-2)){
		if(vOut){
			std::cout << "Calculated X center point is incorrect" << std::endl;
			std::cout << "Expected 2078.8762 +/- 0.06 but instead found: " << centerPt_data[0] << std::endl;
		}
		testFailed = 1;
	}
	if(centerPt_data[1] < (1559.0764-6e-2) || centerPt_data[1] > (1559.0764+6e-2)){
		if(vOut){
			std::cout << "Calculated Y center point is incorrect" << std::endl;
			std::cout << "Expected 1559.0764 +/- 0.06 but instead found: " << centerPt_data[1] << std::endl;
		}
		testFailed = 1;
	}

	//Test alpha, beta, theta
	if(alpha < (-0.0168-1e-3) || alpha > (-0.0168+1e-3)){
		if(vOut){
			std::cout << "Calculated alpha is incorrect" << std::endl;
			std::cout << "Expected -0.0168 +/- 1e-3 but instead found: " << alpha << std::endl;
		}
		testFailed = 1;
	}
	if(beta < (-0.0138-1e-3) || beta > (-0.0138+1e-3)){
		if(vOut){
			std::cout << "Calculated beta is incorrect" << std::endl;
			std::cout << "Expected -0.0138 +/- 1e-3 but instead found: " << beta << std::endl;
		}
		testFailed = 1;
	}
	if(theta < (1.7867-1e-3) || beta > (1.7867+1e-3)){
		if(vOut){
			std::cout << "Calculated theta is incorrect" << std::endl;
			std::cout << "Expected 1.7867 +/- 1e-3 but instead found: " << theta << std::endl;
		}
		testFailed = 1;
	}

	if(testFailed){
        std::cout << "analyzeImage: Test has failed" << std::endl;
		return 0;
	} else {
        std::cout << "analyzeImage: Test has Passed" << std::endl;
		return 1;
	}
    return 1;
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


/***
--- OUTDATED ---
readImage
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
            //imIn[counter] = red;
            //imIn[counter + 13431200] = green;
            //imIn[counter + 2 * 13431200] = blue;
            *(imIn + counter) = red;
            *(imIn + counter + 13431200) = green;
            *(imIn + counter + 2*13431200) = blue;
            counter++;
        }
    }

    //cv::imshow("Display window", imIn);

	//imageMessage->currentImageSize = 2428800;
	printf("Read Image: Finished Image Read\n");
}
