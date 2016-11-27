//
//  ErrorCode.cpp
//  ErrorCode
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include <iostream>
#include "ErrorCode.h"

void handleError(ErrorCode error) {
    switch (error)
    {
        case SUCCESS:
            break;
        case E_INVALID_INPUT:
            std::cout << "Error: Invalid Input\n";
            break;
        case E_GETADDRINFO:
            std::cout << "Error: Call to getaddrinfo() failure\n";
            //fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            break;
        case E_BIND_UNSUCCESSFUL:
            std::cout << "Error: Bind Unsuccessful\n";
            break;
        case E_LISTEN_FAILURE:
            std::cout << "Error: Failure to Listen on Socket\n";
            break;
        default:
            std::cout << "Error: Unknown Error Code";
            break;
    }
}
