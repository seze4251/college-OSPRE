//
//  mainGNC.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>

#include "GNC.h"

int main(int, char**) {
    int serverPort = 9000;
    std::string host("localhost");
    
    std::cout << "GNC Application Starting\n";
    GNC gnc(host, serverPort);
    
    try {
        gnc.open();
        std::cout << "GNC Initalized\n";
        gnc.run();
        
    } catch (const char* exception) {
        std::cerr << "GNC: Error: " << exception << std::endl;
        
    } catch(std::exception &exception) {
        std::cerr << "GNC: Standard exception: " << exception.what() << '\n';
        
    } catch (...) {
        std::cout << "GNC: Exception of unknown type caught" << std::endl;
        throw;
    }
    
    std::cout << "GNC Application Terminating\n";
    return 0;
}
