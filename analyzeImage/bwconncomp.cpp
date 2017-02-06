//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bwconncomp.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 25-Jan-2017 16:02:21
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "bwconncomp.h"
#include "analyzeImage_emxutil.h"

// Function Definitions

//
// Arguments    : const boolean_T varargin_1[809600]
//                double *CC_Connectivity
//                double CC_ImageSize[2]
//                double *CC_NumObjects
//                emxArray_real_T *CC_RegionIndices
//                emxArray_int32_T *CC_RegionLengths
// Return Type  : void
//
void bwconncomp(const boolean_T varargin_1[809600], double *CC_Connectivity,
                double CC_ImageSize[2], double *CC_NumObjects, emxArray_real_T
                *CC_RegionIndices, emxArray_int32_T *CC_RegionLengths)
{
  int numRuns;
  int firstRunOnPreviousColumn;
  emxArray_int32_T *regionLengths;
  int lastRunOnPreviousColumn;
  emxArray_int32_T *startRow;
  emxArray_int32_T *endRow;
  emxArray_int32_T *startCol;
  int k;
  int runCounter;
  int nextLabel;
  int firstRunOnThisColumn;
  emxArray_int32_T *labelsRenumbered;
  double numComponents;
  int p;
  int parent_k;
  int parent_p;
  double y;
  emxArray_real_T *pixelIdxList;
  emxArray_int32_T *x;
  emxArray_int32_T *idxCount;
  numRuns = 0;
  for (firstRunOnPreviousColumn = 0; firstRunOnPreviousColumn < 1100;
       firstRunOnPreviousColumn++) {
    lastRunOnPreviousColumn = firstRunOnPreviousColumn * 736;
    if (varargin_1[lastRunOnPreviousColumn]) {
      numRuns++;
    }

    for (k = 0; k < 735; k++) {
      runCounter = lastRunOnPreviousColumn + k;
      if (varargin_1[runCounter + 1] && (!varargin_1[runCounter])) {
        numRuns++;
      }
    }
  }

  emxInit_int32_T(&regionLengths, 1);
  emxInit_int32_T(&startRow, 1);
  emxInit_int32_T(&endRow, 1);
  emxInit_int32_T(&startCol, 1);
  if (numRuns == 0) {
    lastRunOnPreviousColumn = startRow->size[0];
    startRow->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)startRow, lastRunOnPreviousColumn,
                      (int)sizeof(int));
    lastRunOnPreviousColumn = endRow->size[0];
    endRow->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)endRow, lastRunOnPreviousColumn, (int)
                      sizeof(int));
    lastRunOnPreviousColumn = startCol->size[0];
    startCol->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)startCol, lastRunOnPreviousColumn,
                      (int)sizeof(int));
    lastRunOnPreviousColumn = regionLengths->size[0];
    regionLengths->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)regionLengths, lastRunOnPreviousColumn,
                      (int)sizeof(int));
    *CC_Connectivity = 8.0;
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < 2;
         lastRunOnPreviousColumn++) {
      CC_ImageSize[lastRunOnPreviousColumn] = 736.0 + 364.0 * (double)
        lastRunOnPreviousColumn;
    }

    *CC_NumObjects = 0.0;
    lastRunOnPreviousColumn = CC_RegionIndices->size[0];
    CC_RegionIndices->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)CC_RegionIndices,
                      lastRunOnPreviousColumn, (int)sizeof(double));
    lastRunOnPreviousColumn = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)CC_RegionLengths,
                      lastRunOnPreviousColumn, (int)sizeof(int));
    CC_RegionLengths->data[0] = 0;
  } else {
    lastRunOnPreviousColumn = startRow->size[0];
    startRow->size[0] = numRuns;
    emxEnsureCapacity((emxArray__common *)startRow, lastRunOnPreviousColumn,
                      (int)sizeof(int));
    lastRunOnPreviousColumn = endRow->size[0];
    endRow->size[0] = numRuns;
    emxEnsureCapacity((emxArray__common *)endRow, lastRunOnPreviousColumn, (int)
                      sizeof(int));
    lastRunOnPreviousColumn = startCol->size[0];
    startCol->size[0] = numRuns;
    emxEnsureCapacity((emxArray__common *)startCol, lastRunOnPreviousColumn,
                      (int)sizeof(int));
    runCounter = 0;
    for (firstRunOnPreviousColumn = 0; firstRunOnPreviousColumn < 1100;
         firstRunOnPreviousColumn++) {
      lastRunOnPreviousColumn = firstRunOnPreviousColumn * 736 - 1;
      nextLabel = 1;
      while (nextLabel <= 736) {
        while ((nextLabel <= 736) && (!varargin_1[nextLabel +
                lastRunOnPreviousColumn])) {
          nextLabel++;
        }

        if ((nextLabel <= 736) && varargin_1[nextLabel + lastRunOnPreviousColumn])
        {
          startCol->data[runCounter] = firstRunOnPreviousColumn + 1;
          startRow->data[runCounter] = nextLabel;
          while ((nextLabel <= 736) && varargin_1[nextLabel +
                 lastRunOnPreviousColumn]) {
            nextLabel++;
          }

          endRow->data[runCounter] = nextLabel - 1;
          runCounter++;
        }
      }
    }

    lastRunOnPreviousColumn = regionLengths->size[0];
    regionLengths->size[0] = numRuns;
    emxEnsureCapacity((emxArray__common *)regionLengths, lastRunOnPreviousColumn,
                      (int)sizeof(int));
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < numRuns;
         lastRunOnPreviousColumn++) {
      regionLengths->data[lastRunOnPreviousColumn] = 0;
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
                if (k + 1 != regionLengths->data[k]) {
                  regionLengths->data[k] = regionLengths->data
                    [regionLengths->data[k] - 1];
                  parent_k = regionLengths->data[k];
                } else {
                  parent_k = k + 1;
                }

                if (p + 1 != regionLengths->data[p]) {
                  regionLengths->data[p] = regionLengths->data
                    [regionLengths->data[p] - 1];
                  parent_p = regionLengths->data[p];
                } else {
                  parent_p = p + 1;
                }

                if (parent_k != parent_p) {
                  if (parent_p < parent_k) {
                    regionLengths->data[parent_k - 1] = parent_p;
                    regionLengths->data[k] = parent_p;
                  } else {
                    regionLengths->data[parent_p - 1] = parent_k;
                    regionLengths->data[p] = parent_k;
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
    lastRunOnPreviousColumn = labelsRenumbered->size[0];
    labelsRenumbered->size[0] = regionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)labelsRenumbered,
                      lastRunOnPreviousColumn, (int)sizeof(int));
    numComponents = 0.0;
    for (k = 0; k + 1 <= numRuns; k++) {
      if (regionLengths->data[k] == k + 1) {
        numComponents++;
        labelsRenumbered->data[k] = (int)numComponents;
      }

      labelsRenumbered->data[k] = labelsRenumbered->data[regionLengths->data[k]
        - 1];
    }

    lastRunOnPreviousColumn = regionLengths->size[0];
    regionLengths->size[0] = (int)numComponents;
    emxEnsureCapacity((emxArray__common *)regionLengths, lastRunOnPreviousColumn,
                      (int)sizeof(int));
    runCounter = (int)numComponents;
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < runCounter;
         lastRunOnPreviousColumn++) {
      regionLengths->data[lastRunOnPreviousColumn] = 0;
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
    lastRunOnPreviousColumn = pixelIdxList->size[0];
    pixelIdxList->size[0] = (int)y;
    emxEnsureCapacity((emxArray__common *)pixelIdxList, lastRunOnPreviousColumn,
                      (int)sizeof(double));
    nextLabel = 2;
    if (regionLengths->size[0] != 1) {
      nextLabel = 1;
    }

    emxInit_int32_T(&x, 1);
    lastRunOnPreviousColumn = x->size[0];
    x->size[0] = regionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)x, lastRunOnPreviousColumn, (int)
                      sizeof(int));
    runCounter = regionLengths->size[0];
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < runCounter;
         lastRunOnPreviousColumn++) {
      x->data[lastRunOnPreviousColumn] = regionLengths->
        data[lastRunOnPreviousColumn];
    }

    if (nextLabel <= 1) {
      lastRunOnPreviousColumn = regionLengths->size[0];
    } else {
      lastRunOnPreviousColumn = 1;
    }

    if ((!(regionLengths->size[0] == 0)) && (lastRunOnPreviousColumn > 1)) {
      firstRunOnPreviousColumn = 1;
      k = 1;
      while (k <= nextLabel - 1) {
        firstRunOnPreviousColumn *= regionLengths->size[0];
        k = 2;
      }

      for (runCounter = 0; runCounter + 1 <= firstRunOnPreviousColumn;
           runCounter++) {
        for (k = 1; k < lastRunOnPreviousColumn; k++) {
          x->data[runCounter + k * firstRunOnPreviousColumn] += x->
            data[runCounter + (k - 1) * firstRunOnPreviousColumn];
        }
      }
    }

    emxInit_int32_T(&idxCount, 1);
    lastRunOnPreviousColumn = idxCount->size[0];
    idxCount->size[0] = 1 + x->size[0];
    emxEnsureCapacity((emxArray__common *)idxCount, lastRunOnPreviousColumn,
                      (int)sizeof(int));
    idxCount->data[0] = 0;
    runCounter = x->size[0];
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < runCounter;
         lastRunOnPreviousColumn++) {
      idxCount->data[lastRunOnPreviousColumn + 1] = x->
        data[lastRunOnPreviousColumn];
    }

    emxFree_int32_T(&x);
    for (k = 0; k + 1 <= numRuns; k++) {
      runCounter = (startCol->data[k] - 1) * 736;
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
    *CC_Connectivity = 8.0;
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < 2;
         lastRunOnPreviousColumn++) {
      CC_ImageSize[lastRunOnPreviousColumn] = 736.0 + 364.0 * (double)
        lastRunOnPreviousColumn;
    }

    *CC_NumObjects = numComponents;
    lastRunOnPreviousColumn = CC_RegionIndices->size[0];
    CC_RegionIndices->size[0] = pixelIdxList->size[0];
    emxEnsureCapacity((emxArray__common *)CC_RegionIndices,
                      lastRunOnPreviousColumn, (int)sizeof(double));
    runCounter = pixelIdxList->size[0];
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < runCounter;
         lastRunOnPreviousColumn++) {
      CC_RegionIndices->data[lastRunOnPreviousColumn] = pixelIdxList->
        data[lastRunOnPreviousColumn];
    }

    emxFree_real_T(&pixelIdxList);
    lastRunOnPreviousColumn = CC_RegionLengths->size[0];
    CC_RegionLengths->size[0] = regionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)CC_RegionLengths,
                      lastRunOnPreviousColumn, (int)sizeof(int));
    runCounter = regionLengths->size[0];
    for (lastRunOnPreviousColumn = 0; lastRunOnPreviousColumn < runCounter;
         lastRunOnPreviousColumn++) {
      CC_RegionLengths->data[lastRunOnPreviousColumn] = regionLengths->
        data[lastRunOnPreviousColumn];
    }
  }

  emxFree_int32_T(&startCol);
  emxFree_int32_T(&endRow);
  emxFree_int32_T(&startRow);
  emxFree_int32_T(&regionLengths);
}

//
// File trailer for bwconncomp.cpp
//
// [EOF]
//
