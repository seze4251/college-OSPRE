//
//  ImageNameReader.cpp
//  ImageNameReader
//
//  Created by Seth on 03/27/2017.
//  Copyright © 2017 Seth. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Server.h"
#include "ImageNameReader.h"

ImageNameReader::ImageNameReader() : count(0) {}

std::string ImageNameReader::getNextImageName() {
    std::string result;
    try {
        result = data.at(count);
        count++;
        
    } catch ( std::out_of_range e) {
        result = std::string();
    }
    
    return result;
}

void ImageNameReader::loadImageNames(std::string testDir) {
    std::string fileName = testDir + "/Test_Images/" + "Image_Order.txt";
    std::ifstream file(fileName);
    
    if (!file) {
        fprintf(Server::getAppl()->getLogFileID(), "Error: reading Image_Order.txt: %s could not be opened for reading\n", fileName.c_str());
        throw "CameraController read Image File names Could Not Be Opened for Reading";
    }
    
    std::string line;
    while(file) {
        std::getline(file, line);
        if (line.empty() == false) {
            data.push_back(testDir + "/Test_Images/" + line);
        }
    }
}







