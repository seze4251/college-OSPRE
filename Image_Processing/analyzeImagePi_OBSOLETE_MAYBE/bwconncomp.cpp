//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bwconncomp.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "bwconncomp.h"
#include "analyzeImage_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_boolean_T *varargin_1
//                double *CC_Connectivity
//                double CC_ImageSize[2]
//                double *CC_NumObjects
//                emxArray_real_T *CC_RegionIndices
//                emxArray_int32_T *CC_RegionLengths
// Return Type  : void
//
void bwconncomp(const emxArray_boolean_T *varargin_1, double *CC_Connectivity,
                double CC_ImageSize[2], double *CC_NumObjects, emxArray_real_T
                *CC_RegionIndices, emxArray_int32_T *CC_RegionLengths)
{
  int numRuns;
  int firstRunOnPreviousColumn;
  int lastRunOnPreviousColumn;
  emxArray_int32_T *regionLengths;
  emxArray_int32_T *startRow;
  emxArray_int32_T *endRow;
  int firstRunOnThisColumn;
  emxArray_int32_T *startCol;
  int nextLabel;
  int k;
  int runCounter;
  double numComponents;
  emxArray_int32_T *labelsRenumbered;
  int p;
  int root_k;
  int root_p;
  double y;
  emxArray_real_T *pixelIdxList;
  emxArray_int32_T *x;
  emxArray_int32_T *idxCount;
  numRuns = 0;
  firstRunOnPreviousColumn = varargin_1->size[0];
  if ((varargin_1->size[0] != 0) && (varargin_1->size[1] != 0)) {
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < varargin_1->
         size[1]; lastRunOnPreviousColumn++) {
      firstRunOnThisColumn = lastRunOnPreviousColumn * firstRunOnPreviousColumn;
      if (varargin_1->data[firstRunOnThisColumn]) {
        numRuns++;
      }

      nextLabel = (firstRunOnPreviousColumn + firstRunOnThisColumn) -
        firstRunOnThisColumn;
      for (k = 0; k <= nextLabel - 2; k++) {
        runCounter = firstRunOnThisColumn + k;
        if (varargin_1->data[runCounter + 1] && (!varargin_1->data[runCounter]))
        {
          numRuns++;
        }
      }
    }
  }

  emxInit_int32_T(&regionLengths, 1);
  emxInit_int32_T(&startRow, 1);
  emxInit_int32_T(&endRow, 1);
  emxInit_int32_T(&startCol, 1);
  if (numRuns == 0) {
    nextLabel = startRow->size[0];
    startRow->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)startRow, nextLabel, sizeof(int));
    nextLabel = endRow->size[0];
    endRow->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)endRow, nextLabel, sizeof(int));
    nextLabel = startCol->size[0];
    startCol->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)startCol, nextLabel, sizeof(int));
    nextLabel = regionLengths->size[0];
    regionLengths->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)regionLengths, nextLabel, sizeof(int));
    for (nextLabel = 0; nextLabel < 2; nextLabel++) {
      CC_ImageSize[nextLabel] = varargin_1->size[nextLabel];
    }

    numComponents = 0.0;
    nextLabel = CC_RegionIndices->size[0];
    CC_RegionIndices->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)CC_RegionIndices, nextLabel, sizeof
                      (double));
    nextLabel = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)CC_RegionLengths, nextLabel, sizeof
                      (int));
    CC_RegionLengths->data[0] = 0;
  } else {
    nextLabel = startRow->size[0];
    startRow->size[0] = numRuns;
    emxEnsureCapacity((emxArray__common *)startRow, nextLabel, sizeof(int));
    nextLabel = endRow->size[0];
    endRow->size[0] = numRuns;
    emxEnsureCapacity((emxArray__common *)endRow, nextLabel, sizeof(int));
    nextLabel = startCol->size[0];
    startCol->size[0] = numRuns;
    emxEnsureCapacity((emxArray__common *)startCol, nextLabel, sizeof(int));
    firstRunOnPreviousColumn = varargin_1->size[0];
    runCounter = 0;
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < varargin_1->
         size[1]; lastRunOnPreviousColumn++) {
      firstRunOnThisColumn = lastRunOnPreviousColumn * firstRunOnPreviousColumn
        - 1;
      nextLabel = 1;
      while (nextLabel <= firstRunOnPreviousColumn) {
        while ((nextLabel <= firstRunOnPreviousColumn) && (!varargin_1->
                data[nextLabel + firstRunOnThisColumn])) {
          nextLabel++;
        }

        if ((nextLabel <= firstRunOnPreviousColumn) && varargin_1->
            data[nextLabel + firstRunOnThisColumn]) {
          startCol->data[runCounter] = lastRunOnPreviousColumn + 1;
          startRow->data[runCounter] = nextLabel;
          while ((nextLabel <= firstRunOnPreviousColumn) && varargin_1->
                 data[nextLabel + firstRunOnThisColumn]) {
            nextLabel++;
          }

          endRow->data[runCounter] = nextLabel - 1;
          runCounter++;
        }
      }
    }

    nextLabel = regionLengths->size[0];
    regionLengths->size[0] = numRuns;
    emxEnsureCapacity((emxArray__common *)regionLengths, nextLabel, sizeof(int));
    for (nextLabel = 0; nextLabel < numRuns; nextLabel++) {
      regionLengths->data[nextLabel] = 0;
    }

    k = 0;
    runCounter = 1;
    nextLabel = 1;
    firstRunOnPreviousColumn = -1;
    lastRunOnPreviousColumn = -1;
    firstRunOnThisColumn = 0;
    while (k + 1 <= numRuns) {
      if (startCol->data[k] == runCounter + 1) {
        firstRunOnPreviousColumn = firstRunOnThisColumn + 1;
        firstRunOnThisColumn = k;
        lastRunOnPreviousColumn = k;
        runCounter = startCol->data[k];
      } else {
        if (startCol->data[k] > runCounter + 1) {
          firstRunOnPreviousColumn = -1;
          lastRunOnPreviousColumn = -1;
          firstRunOnThisColumn = k;
          runCounter = startCol->data[k];
        }
      }

      if (firstRunOnPreviousColumn >= 0) {
        for (p = firstRunOnPreviousColumn - 1; p + 1 <= lastRunOnPreviousColumn;
             p++) {
          if ((endRow->data[k] >= startRow->data[p] - 1) && (startRow->data[k] <=
               endRow->data[p] + 1)) {
            if (regionLengths->data[k] == 0) {
              regionLengths->data[k] = regionLengths->data[p];
              nextLabel++;
            } else {
              if (regionLengths->data[k] != regionLengths->data[p]) {
                for (root_k = k; root_k + 1 != regionLengths->data[root_k];
                     root_k = regionLengths->data[root_k] - 1) {
                  regionLengths->data[root_k] = regionLengths->
                    data[regionLengths->data[root_k] - 1];
                }

                for (root_p = p; root_p + 1 != regionLengths->data[root_p];
                     root_p = regionLengths->data[root_p] - 1) {
                  regionLengths->data[root_p] = regionLengths->
                    data[regionLengths->data[root_p] - 1];
                }

                if (root_k + 1 != root_p + 1) {
                  if (root_p + 1 < root_k + 1) {
                    regionLengths->data[root_k] = root_p + 1;
                    regionLengths->data[k] = root_p + 1;
                  } else {
                    regionLengths->data[root_p] = root_k + 1;
                    regionLengths->data[p] = root_k + 1;
                  }
                }
              }
            }
          }
        }
      }

      if (regionLengths->data[k] == 0) {
        regionLengths->data[k] = nextLabel;
        nextLabel++;
      }

      k++;
    }

    emxInit_int32_T(&labelsRenumbered, 1);
    nextLabel = labelsRenumbered->size[0];
    labelsRenumbered->size[0] = regionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)labelsRenumbered, nextLabel, sizeof
                      (int));
    numComponents = 0.0;
    for (k = 0; k + 1 <= numRuns; k++) {
      if (regionLengths->data[k] == k + 1) {
        numComponents++;
        labelsRenumbered->data[k] = (int)numComponents;
      }

      labelsRenumbered->data[k] = labelsRenumbered->data[regionLengths->data[k]
        - 1];
    }

    nextLabel = regionLengths->size[0];
    regionLengths->size[0] = (int)numComponents;
    emxEnsureCapacity((emxArray__common *)regionLengths, nextLabel, sizeof(int));
    runCounter = (int)numComponents;
    for (nextLabel = 0; nextLabel < runCounter; nextLabel++) {
      regionLengths->data[nextLabel] = 0;
    }

    for (k = 0; k + 1 <= numRuns; k++) {
      if (labelsRenumbered->data[k] > 0) {
        regionLengths->data[labelsRenumbered->data[k] - 1] =
          ((regionLengths->data[labelsRenumbered->data[k] - 1] + endRow->data[k])
           - startRow->data[k]) + 1;
      }
    }

    if (regionLengths->size[0] == 0) {
      y = 0.0;
    } else {
      y = regionLengths->data[0];
      for (k = 2; k <= regionLengths->size[0]; k++) {
        y += (double)regionLengths->data[k - 1];
      }
    }

    emxInit_real_T1(&pixelIdxList, 1);
    emxInit_int32_T(&x, 1);
    nextLabel = pixelIdxList->size[0];
    pixelIdxList->size[0] = (int)y;
    emxEnsureCapacity((emxArray__common *)pixelIdxList, nextLabel, sizeof(double));
    nextLabel = x->size[0];
    x->size[0] = regionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)x, nextLabel, sizeof(int));
    runCounter = regionLengths->size[0];
    for (nextLabel = 0; nextLabel < runCounter; nextLabel++) {
      x->data[nextLabel] = regionLengths->data[nextLabel];
    }

    runCounter = 2;
    if (regionLengths->size[0] != 1) {
      runCounter = 1;
    }

    if (runCounter <= 1) {
      nextLabel = regionLengths->size[0];
    } else {
      nextLabel = 1;
    }

    if ((!(regionLengths->size[0] == 0)) && (nextLabel > 1)) {
      firstRunOnPreviousColumn = 1;
      k = 1;
      while (k <= runCounter - 1) {
        firstRunOnPreviousColumn *= regionLengths->size[0];
        k = 2;
      }

      for (runCounter = 0; runCounter + 1 <= firstRunOnPreviousColumn;
           runCounter++) {
        for (k = 1; k < nextLabel; k++) {
          x->data[runCounter + k * firstRunOnPreviousColumn] += x->
            data[runCounter + (k - 1) * firstRunOnPreviousColumn];
        }
      }
    }

    emxInit_int32_T(&idxCount, 1);
    nextLabel = idxCount->size[0];
    idxCount->size[0] = 1 + x->size[0];
    emxEnsureCapacity((emxArray__common *)idxCount, nextLabel, sizeof(int));
    idxCount->data[0] = 0;
    runCounter = x->size[0];
    for (nextLabel = 0; nextLabel < runCounter; nextLabel++) {
      idxCount->data[nextLabel + 1] = x->data[nextLabel];
    }

    emxFree_int32_T(&x);
    for (k = 0; k + 1 <= numRuns; k++) {
      runCounter = (startCol->data[k] - 1) * varargin_1->size[0];
      nextLabel = labelsRenumbered->data[k] - 1;
      if (labelsRenumbered->data[k] > 0) {
        for (firstRunOnPreviousColumn = startRow->data[k];
             firstRunOnPreviousColumn <= endRow->data[k];
             firstRunOnPreviousColumn++) {
          idxCount->data[nextLabel]++;
          pixelIdxList->data[idxCount->data[nextLabel] - 1] =
            firstRunOnPreviousColumn + runCounter;
        }
      }
    }

    emxFree_int32_T(&idxCount);
    emxFree_int32_T(&labelsRenumbered);
    for (nextLabel = 0; nextLabel < 2; nextLabel++) {
      CC_ImageSize[nextLabel] = varargin_1->size[nextLabel];
    }

    nextLabel = CC_RegionIndices->size[0];
    CC_RegionIndices->size[0] = pixelIdxList->size[0];
    emxEnsureCapacity((emxArray__common *)CC_RegionIndices, nextLabel, sizeof
                      (double));
    runCounter = pixelIdxList->size[0];
    for (nextLabel = 0; nextLabel < runCounter; nextLabel++) {
      CC_RegionIndices->data[nextLabel] = pixelIdxList->data[nextLabel];
    }

    emxFree_real_T(&pixelIdxList);
    nextLabel = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = regionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)CC_RegionLengths, nextLabel, sizeof
                      (int));
    runCounter = regionLengths->size[0];
    for (nextLabel = 0; nextLabel < runCounter; nextLabel++) {
      CC_RegionLengths->data[nextLabel] = regionLengths->data[nextLabel];
    }
  }

  emxFree_int32_T(&startCol);
  emxFree_int32_T(&endRow);
  emxFree_int32_T(&startRow);
  emxFree_int32_T(&regionLengths);
  *CC_Connectivity = 8.0;
  *CC_NumObjects = numComponents;
}

//
// File trailer for bwconncomp.cpp
//
// [EOF]
//
