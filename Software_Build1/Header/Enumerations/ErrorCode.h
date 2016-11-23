//
//  ErrorCode.h
//  ErrorCode
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef ERRORCODE_H
#def ERRORCODE_H

enum ErrorCode {
    SUCCESS = 0;
    E_INVALID_INPUT = -1;
    E_GETADDRINFO = -2;
    E_BIND_UNSUCCESSFUL = -3;
    E_LISTEN_FAILURE = -4;
    E_CONNECTION_FAILURE = -5;
};

void handleError(ErrorCode error);
#endif
