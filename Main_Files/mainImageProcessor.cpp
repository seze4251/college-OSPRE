//
//  mainImageProcessor.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include <exception>

#include "ImageProcessor.h"

int main(int, char**) {
    int serverPort = 8000;
    std::string host("localhost");
    
    std::cout << "ImageProcessor Application Starting\n";
    ImageProcessor proc(host, serverPort);
    
    try {
        proc.open();
        std::cout << "ImageProcessor Initalized\n";
        proc.run();
        
    } catch (const char* exception) {
        std::cerr << "ImageProcessor: Error: " << exception << std::endl;
        
    } catch(std::exception &exception) {
        std::cerr << "ImageProcessor: Standard exception: " << exception.what() << '\n';
        
    } catch (...) {
        std::cout << "ImageProcessor: Exception of unknown type caught" << std::endl;
        throw;
    }
    
    std::cout << "ImageProcessor Application Terminating\n";
    return 0;
}
