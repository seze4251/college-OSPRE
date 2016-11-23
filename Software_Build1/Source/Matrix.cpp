//
//  Matrix.cpp
//  Matrix
//
//  Created by Seth on 11/10/2016.
//  Copyright © 2016 Seth. All rights reserved.
//

#include "Matrix.h"


void matrixInit() {
    srand((unsigned int) time(NULL));
}



void randomizeMatrix() {
    
}

void randomizeMatrix(const matrix * mtx) {
    int i, j;
    
    for ( i = 0; i < mtx -> rows; i++) {
        for ( j = 0; j < mtx -> cols; j++) {
            ELEM(mtx,i,j) = rand();
        }
    }
}


void constMatrix(double value) {
    
}

void constMatrix(const matrix * mtx, const double value) {
    int i, j;
    if( !mtx) {
        printf("ConstantMatrix: mtx points to NULL");
    }
    for ( i = 0; i < mtx -> rows; i++) {
        for ( j = 0; j < mtx -> cols; j++) {
            ELEM(mtx,i,j) = value;
        }
    }
}



void printMatrix() {
    
}
// Prints the matrix
void printMatrix(const matrix * mtx) {
    printf("\n");
    if (!mtx) {
        printf("printMatrix: mtx points to null");
    }
    int i, j;
    for ( i = 0; i < mtx -> rows; i++) {
        for ( j = 0; j < mtx -> cols ; j++) {
            printf("%11.2f", ELEM(mtx,i,j));
        }
        printf("\n");
    }
}

Matrix copyMatrix() {
    
}

/*
matrix * copyMatrix(const matrix * mtx) {
    matrix * copy = newMatrix(mtx -> rows, mtx -> cols);
    int i, j;
    for ( i = 0; i < mtx -> rows; i++) {
        for ( j = 0; j < mtx -> cols; j++) {
            ELEM(copy,i,j) = ELEM(mtx,i,j);
        }
    }
    return copy;
}
*/

int subtractMatrix(Matrix *b) {
    
}
/*
int subtractMatrix(const matrix * mtx1, const matrix * mtx2) {
    int i, j;
    if (!mtx1 || !mtx2) {
        printf("subtractMatrix: mtx1 or mtx2 point to null\n");
    }
    
    if ( mtx1 -> cols != mtx2 -> cols || mtx1 -> rows != mtx2 -> rows ) {
        printf("Mtx1 and Mtx2 must be the same size\n");
        return -2;
    }
    
    for ( i = 0; i < mtx1 -> rows; i++) {
        for ( j = 0; j < mtx2 -> cols; j++) {
            if (ELEM(mtx1,i,j) - ELEM(mtx2,i,j) != 0) {
                return -3;
            }
        }
    }
    return 0;
}
*/


void zeroMatrix() {
    
}

void zeroMatrix(const matrix * mtx) {
    int i, j;
    
    for ( i = 0; i < mtx -> rows; i++) {
        for ( j = 0; j < mtx -> cols; j++) {
            ELEM(mtx,i,j) = 0;
        }
    }
}



int matrixProduct(Matrix *b) {
    
}

/*
int matrixProduct(const matrix * mtxA, const matrix * mtxB, matrix * mtxC) {
    // If mtxA, mtxB, mtxC is NULL, return -1
    if (!mtxA || !mtxB) {
        return -1;
    }
    
    // If mtxA and mtxB are not the correct size, return -2
    if (mtxA -> cols != mtxB -> rows) {
        printf("Matrix A cols must equal Matrix B rows");
        return -2;
    }
    
    // If mtxC is not the correct size, return -3
    if (mtxC -> rows != mtxA -> rows || mtxC -> cols != mtxB -> cols ) {
        printf("Matrix C must be the correct size");
        return -3;
    }
    
    int i, j, k;
    
    // Perform the matrix multiplication
    for (i = 0; i < mtxA -> rows; i++) {
        for ( j = 0; j < mtxB -> cols ; j++) {
            for ( k = 0; k < mtxA -> cols ; k++) {
                ELEM(mtxC,i,j) += ELEM(mtxA,i,k) * ELEM(mtxB,k,j);
            }
        }
    }
    
    // Return True
    return 0;
    
}

int matrixProductCacheObliv(const matrix * mtxA, const matrix * mtxB, matrix * mtxC, int startRA, int endRA, int startM, int endM, int startCB, int endCB) {
    
    const int maxDim = 20;
    
    // If mtxA, mtxB, mtxC is NULL, return -1
    if (!mtxA || !mtxB) {
        return -1;
    }
    
    // If mtxA and mtxB are not the correct size, return -2
    if (mtxA -> cols != mtxB -> rows) {
        printf("Matrix A cols must equal Matrix B rows\n");
        return -2;
    }
    
    // If mtxC is not the correct size, return -3
    if (mtxC -> rows != mtxA -> rows || mtxC -> cols != mtxB -> cols ) {
        printf("Matrix C must be the correct size\n");
        return -3;
    }
    
    if ( ((endRA - startRA) < maxDim) && ((endM - startM) < maxDim) && ((endCB -startCB) < maxDim) ) {
        int i, j, k;
        
        // Perform the matrix multiplication
        for (i = startRA; i < endRA; i++) {
            for ( k = startM; k < endM ; k++) {
                for ( j = startCB; j < endCB ; j++) {
                    ELEM(mtxC,i,j) +=  ELEM(mtxA,i,k) * ELEM(mtxB,k,j);
                }
            }
        }
        
        return 0;
        
    } else {
        
        if ( max( (endRA - startRA), (endM - startM), (endCB -startCB) ) ==  (endRA - startRA)) {
            // Split A horizonally
            
            int c = startRA + (endRA - startRA) /2; // integers automatically floor in C
            matrixProductCacheObliv(mtxA, mtxB, mtxC, startRA, c, startM, endM, startCB, endCB);
            matrixProductCacheObliv(mtxA, mtxB, mtxC, c, endRA, startM, endM, startCB, endCB);
            return 0;
            
        } else if (max( (endRA - startRA), (endM - startM), (endCB -startCB) ) ==  (endCB -startCB)) {
            // Split B Vertically
            
            int c = startCB + (endCB -startCB) /2;
            matrixProductCacheObliv(mtxA, mtxB, mtxC, startRA, endRA, startM, endM, startCB, c);
            matrixProductCacheObliv(mtxA, mtxB, mtxC, startRA, endRA, startM, endM, c, endCB);
            return 0;
            
        } else {
            
            // Split the Columns in A and the Rows in B
            int c = startM + (endM - startM) /2;
            matrixProductCacheObliv(mtxA, mtxB, mtxC, startRA, endRA, startM, c, startCB, endCB);
            matrixProductCacheObliv(mtxA, mtxB, mtxC, startRA, endRA, c, endM, startCB, endCB);
            return 0;
        }
    }
}
*/
