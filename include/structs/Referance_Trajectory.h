//
//  Reference_Trajectory.h
//  Reference_Trajectory
//
//  Created by Seth on 11/24/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#ifndef REFERENCE_TRAJECTORY_H
#define REFERENCE_TRAJECTORY_H


#include <vector>
struct Reference_Trajectory {
    std::vector<double> time;
    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> Z;
    std::vector<double> VX;
    std::vector<double> VY;
    std::vector<double> VZ;
};

#endif
