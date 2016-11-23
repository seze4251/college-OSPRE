//
//  Matrix.h
//  Matrix
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//


#ifndef MATRIX_H
#def MATRIX_H

#include "ErrorCode.h"

class Matrix {
public:
    //Constructor
    Matrix();
    
    //Destructor
    ~Matrix();
    
    // Methods
    void randomizeMatrix();
    void constMatrix(double value);
    void printMatrix();
    Matrix copyMatrix();
    int subtractMatrix(Matrix *b);
    int matrixProduct(Matrix *b);
    void zeroMatrix();

private:
    int rows;
    int cols;
    double * data;
};



#endif
