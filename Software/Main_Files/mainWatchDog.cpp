//
//  main_WatchDog.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include "WatchDog.h"

int main(int argc, char **argv) {
    std::cout << "WatchDog Application Starting\n";
    WatchDog dog(5000);
    std::cout << "WatchDog Initalized\n";
    dog.open(std::string("localhost"), 5000);
    dog.run();
    std::cout << "WatchDog Application Terminating\n";
    return 0;
}
