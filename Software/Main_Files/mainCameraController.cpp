//
//  mainCameraController.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>

#include "CameraController.h"

int main(int argc, char **argv) {
    int serverPort = 10000;
    bool readImageFile = true;
    std::string host("localhost");
    
    std::cout << "CameraController Application Starting\n";
    CameraController controller(host, serverPort, readImageFile);
    
    std::cout << "CameraController Initalized\n";
    controller.open();
    controller.run();
    std::cout << "CameraController Application Terminating\n";
    return 0;
}
