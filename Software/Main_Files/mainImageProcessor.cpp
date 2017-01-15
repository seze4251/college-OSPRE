//
//  mainImageProcessor.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>

#include "ImageProcessor.h"

int main(int argc, char **argv) {
    int serverPort = 8000;
    int watchDogPort = 5000;
    std::string host("localhost");
    
    std::cout << "ImageProcessor Application Starting\n";
    ImageProcessor proc(host, serverPort, watchDogPort);
    
    std::cout << "ImageProcessor Initalized\n";
    proc.open();
    proc.run();
    std::cout << "ImageProcessor Application Terminating\n";
    return 0;
}
