//
//  mainCameraController.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <exception>

#include "CameraController.h"

int main(int, char**) {
    int serverPort = 10000;
    bool readImageFile = true;
    std::string host("localhost");
    
    std::cout << "CameraController Application Starting\n";
    CameraController controller(host, serverPort, readImageFile);
    
    try {
        controller.open();
        std::cout << "CameraController Initalized\n";
        controller.run();
        
    } catch (const char* exception) {
        std::cerr << "CameraController: Error: " << exception << std::endl;
        
    } catch(std::exception &exception) {
        std::cerr << "CameraController: Standard exception: " << exception.what() << '\n';
        
    } catch (...) {
        std::cout << "CameraController: Exception of unknown type caught" << std::endl;
        throw;
    }
    
    std::cout << "CameraController Application Terminating\n";
    return 0;
}
