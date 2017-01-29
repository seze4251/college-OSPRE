//
//  Builder.cpp
//  Builder
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "External_Builder.h"
#include <iostream>

External_Builder::External_Builder(ByteBuffer& bufParam) : buf(bufParam) {
    std::cout << "External_Builder Constructor" << std::endl;
}

External_Builder::~External_Builder() {
    
}

// *******************************
//
// TODO: IMPLEMENT METHODS BELOW
//
// ********************************
void External_Builder::buildExternal_DataMessage(External_DataMessage &msg) {
    
}

void External_Builder::buildExternal_OSPREStatus(External_OSPREStatus &msg) {
    
}

void External_Builder::buildExternal_PointingRequest(External_PointingRequest &msg) {
    
}


void External_Builder::buildExternal_SolutionMessage(External_SolutionMessage &msg) {
    
}

