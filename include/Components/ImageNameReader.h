//
//  ImageNameReader.h
//  ImageNameReader
//
//  Created by Seth on 03/27/2017.
//  Copyright © 2017 Seth. All rights reserved.
//


#ifndef IMAGENAMEREADER_H
#define IMAGENAMEREADER_H

#include <vector>
#include <string>

class ImageNameReader {
public:
    ImageNameReader();
    
    std::string getNextImageName();
    
    void loadImageNames(std::string testDir);
    
private:
    std::vector<std::string> data;
    int count;
};

#endif
