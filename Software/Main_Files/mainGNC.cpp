//
//  mainGNC.cpp
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <unistd.h>
#include <iostream>

int main(int argc, char **argv) {
    for (int i = 0; i<2; i++) {
        std::cout << "GNC Main is actually being used ... YAY!" << std::endl;
        sleep(10);
    }
    return 0;
}
