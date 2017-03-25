//
//  SpacecraftDataReader
//  SpacecraftDataReader.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "SpacecraftDataReader.h"
#include "Server.h"

SpacecraftDataReader::SpacecraftDataReader(unsigned int applicationProcessID) : messageNum(0) {}

External_DataMessage* SpacecraftDataReader::getNextDataMessage() {
    External_DataMessage* msg = &data.at(messageNum);
    messageNum++;
    return msg;
}

void SpacecraftDataReader::readDataFile(std::string fileName) {
    std::ifstream file(fileName);
    
    if (!file) {
        fprintf(Server::getAppl()->getLogFileID(), "Error: read Config File: %s could not be opened for reading\n", fileName.c_str());
        throw "Spacecraft Data File Could Not Be Opened for Reading";
    }
    
    std::string line;
    // Get rid of comments
    std::getline(file, line);
    std::getline(file, line);
    
    double number;
    int column = 1;
    External_DataMessage tempMessage(applicationProcessID);
    
    while(file){
        file >> number;

        if(column == 1) {
            tempMessage.satTime = number;
            column++;
        } else if(column == 2){
            tempMessage.quat[0] = number;
            column++;
        } else if(column == 3){
            tempMessage.quat[1] = number;
            column++;
        } else if(column == 4){
            tempMessage.quat[2] = number;
            column++;
        } else if(column == 5){
            tempMessage.quat[3] = number;
            column++;
        } else if(column == 6){
            tempMessage.angularVelocity[0] = number;
            column++;
        } else if(column == 7){
            tempMessage.angularVelocity[1] = number;
            column++;
        } else if(column == 8){
            tempMessage.angularVelocity[2] = number;
            column++;
        } else if(column == 9){
            // This Spot is for angular velocity magnitude which I do not care about so I am ignoring
            column++;
        } else if(column == 10){
            tempMessage.sunAngle[0] = number;
            column++;
        } else if(column == 11){
            tempMessage.sunAngle[1] = number;
            column++;
        } else if(column == 12){
            tempMessage.sunAngle[2] = number;
            column++;
        } else if(column == 13){
            tempMessage.ephem[0] = number;
            column++;
        } else if(column == 14){
            tempMessage.ephem[1] = number;
            column++;
        } else if(column == 15){
            tempMessage.ephem[2] = number;
            data.push_back(tempMessage);
            column = 1;
        }
    }
    
}
