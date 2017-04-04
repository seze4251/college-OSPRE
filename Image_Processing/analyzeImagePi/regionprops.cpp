//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: regionprops.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "regionprops.h"
#include "analyzeImage_emxutil.h"
#include "sum.h"
#include "bwconncomp.h"
#include "analyzeImage_rtwutil.h"

// Function Definitions

//
// Arguments    : const emxArray_boolean_T *varargin_1
//                const emxArray_real_T *varargin_2
//                emxArray_struct_T *outstats
// Return Type  : void
//
void regionprops(const emxArray_boolean_T *varargin_1, const emxArray_real_T
                 *varargin_2, emxArray_struct_T *outstats)
{
  emxArray_real_T *CC_RegionIndices;
  emxArray_int32_T *CC_RegionLengths;
  double sumIntensity;
  double wc[2];
  double CC_NumObjects;
  int i29;
  struct_T statsOneObj;
  int loop_ub;
  b_struct_T b_statsOneObj;
  b_emxArray_struct_T *stats;
  emxArray_int32_T *regionLengths;
  emxArray_int32_T *idxCount;
  int k;
  int i30;
  emxArray_real_T *Intensity;
  emxArray_real_T *b_stats;
  int vstride;
  emxInit_real_T1(&CC_RegionIndices, 1);
  emxInit_int32_T(&CC_RegionLengths, 1);
  bwconncomp(varargin_1, &sumIntensity, wc, &CC_NumObjects, CC_RegionIndices,
             CC_RegionLengths);
  for (i29 = 0; i29 < 2; i29++) {
    statsOneObj.WeightedCentroid[i29] = 0.0;
  }

  i29 = outstats->size[0];
  outstats->size[0] = (int)CC_NumObjects;
  emxEnsureCapacity((emxArray__common *)outstats, i29, sizeof(struct_T));
  loop_ub = (int)CC_NumObjects;
  for (i29 = 0; i29 < loop_ub; i29++) {
    outstats->data[i29] = statsOneObj;
  }

  emxInitStruct_struct_T(&b_statsOneObj);
  b_statsOneObj.Area = 0.0;
  for (i29 = 0; i29 < 2; i29++) {
    b_statsOneObj.Centroid[i29] = 0.0;
  }

  for (i29 = 0; i29 < 4; i29++) {
    b_statsOneObj.BoundingBox[i29] = 0.0;
  }

  b_statsOneObj.MajorAxisLength = 0.0;
  b_statsOneObj.MinorAxisLength = 0.0;
  b_statsOneObj.Eccentricity = 0.0;
  b_statsOneObj.Orientation = 0.0;
  b_statsOneObj.Image.size[0] = 0;
  b_statsOneObj.Image.size[1] = 0;
  b_statsOneObj.FilledImage.size[0] = 0;
  b_statsOneObj.FilledImage.size[1] = 0;
  b_statsOneObj.FilledArea = 0.0;
  b_statsOneObj.EulerNumber = 0.0;
  memset(&b_statsOneObj.Extrema[0], 0, sizeof(double) << 4);
  b_statsOneObj.EquivDiameter = 0.0;
  b_statsOneObj.Extent = 0.0;
  i29 = b_statsOneObj.PixelIdxList->size[0];
  b_statsOneObj.PixelIdxList->size[0] = 0;
  emxEnsureCapacity((emxArray__common *)b_statsOneObj.PixelIdxList, i29, sizeof
                    (double));
  i29 = b_statsOneObj.PixelList->size[0] * b_statsOneObj.PixelList->size[1];
  b_statsOneObj.PixelList->size[0] = 0;
  b_statsOneObj.PixelList->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_statsOneObj.PixelList, i29, sizeof
                    (double));
  b_statsOneObj.Perimeter = 0.0;
  b_statsOneObj.PixelValues.size[0] = 0;
  b_statsOneObj.MeanIntensity = 0.0;
  b_statsOneObj.MinIntensity = 0.0;
  b_statsOneObj.MaxIntensity = 0.0;
  b_statsOneObj.SubarrayIdx.size[0] = 1;
  b_statsOneObj.SubarrayIdx.size[1] = 0;
  for (i29 = 0; i29 < 2; i29++) {
    b_statsOneObj.WeightedCentroid[i29] = 0.0;
    b_statsOneObj.SubarrayIdxLengths[i29] = 0.0;
  }

  emxInit_struct_T1(&stats, 1);
  i29 = stats->size[0];
  stats->size[0] = (int)CC_NumObjects;
  emxEnsureCapacity_struct_T(stats, i29);
  loop_ub = (int)CC_NumObjects;
  for (i29 = 0; i29 < loop_ub; i29++) {
    emxCopyStruct_struct_T(&stats->data[i29], &b_statsOneObj);
  }

  emxFreeStruct_struct_T(&b_statsOneObj);
  emxInit_int32_T(&regionLengths, 1);
  emxInit_int32_T(&idxCount, 1);
  if (CC_NumObjects != 0.0) {
    i29 = regionLengths->size[0];
    regionLengths->size[0] = CC_RegionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)regionLengths, i29, sizeof(int));
    loop_ub = CC_RegionLengths->size[0];
    for (i29 = 0; i29 < loop_ub; i29++) {
      regionLengths->data[i29] = CC_RegionLengths->data[i29];
    }

    loop_ub = 2;
    if (CC_RegionLengths->size[0] != 1) {
      loop_ub = 1;
    }

    if (loop_ub <= 1) {
      i29 = CC_RegionLengths->size[0];
    } else {
      i29 = 1;
    }

    if ((!(CC_RegionLengths->size[0] == 0)) && (i29 > 1)) {
      vstride = 1;
      k = 1;
      while (k <= loop_ub - 1) {
        vstride *= CC_RegionLengths->size[0];
        k = 2;
      }

      for (loop_ub = 0; loop_ub + 1 <= vstride; loop_ub++) {
        for (k = 1; k < i29; k++) {
          regionLengths->data[loop_ub + k * vstride] += regionLengths->
            data[loop_ub + (k - 1) * vstride];
        }
      }
    }

    i29 = idxCount->size[0];
    idxCount->size[0] = 1 + regionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)idxCount, i29, sizeof(int));
    idxCount->data[0] = 0;
    loop_ub = regionLengths->size[0];
    for (i29 = 0; i29 < loop_ub; i29++) {
      idxCount->data[i29 + 1] = regionLengths->data[i29];
    }

    for (k = 0; k < (int)CC_NumObjects; k++) {
      if (idxCount->data[k] + 1 > idxCount->data[(int)((1.0 + (double)k) + 1.0)
          - 1]) {
        i29 = 1;
        i30 = 0;
      } else {
        i29 = idxCount->data[k] + 1;
        i30 = idxCount->data[(int)((1.0 + (double)k) + 1.0) - 1];
      }

      loop_ub = stats->data[k].PixelIdxList->size[0];
      stats->data[k].PixelIdxList->size[0] = (i30 - i29) + 1;
      emxEnsureCapacity((emxArray__common *)stats->data[k].PixelIdxList, loop_ub,
                        sizeof(double));
      loop_ub = (i30 - i29) + 1;
      for (i30 = 0; i30 < loop_ub; i30++) {
        stats->data[k].PixelIdxList->data[i30] = CC_RegionIndices->data[(i29 +
          i30) - 1];
      }
    }
  }

  emxFree_int32_T(&CC_RegionLengths);
  emxFree_real_T(&CC_RegionIndices);
  i29 = stats->size[0];
  for (k = 0; k < i29; k++) {
    if (!(stats->data[k].PixelIdxList->size[0] == 0)) {
      i30 = regionLengths->size[0];
      regionLengths->size[0] = stats->data[k].PixelIdxList->size[0];
      emxEnsureCapacity((emxArray__common *)regionLengths, i30, sizeof(int));
      loop_ub = stats->data[k].PixelIdxList->size[0];
      for (i30 = 0; i30 < loop_ub; i30++) {
        regionLengths->data[i30] = (int)stats->data[k].PixelIdxList->data[i30];
      }

      i30 = regionLengths->size[0];
      emxEnsureCapacity((emxArray__common *)regionLengths, i30, sizeof(int));
      loop_ub = regionLengths->size[0];
      for (i30 = 0; i30 < loop_ub; i30++) {
        regionLengths->data[i30]--;
      }

      i30 = idxCount->size[0];
      idxCount->size[0] = regionLengths->size[0];
      emxEnsureCapacity((emxArray__common *)idxCount, i30, sizeof(int));
      loop_ub = regionLengths->size[0];
      for (i30 = 0; i30 < loop_ub; i30++) {
        idxCount->data[i30] = div_s32(regionLengths->data[i30], (int)wc[0]);
      }

      i30 = regionLengths->size[0];
      emxEnsureCapacity((emxArray__common *)regionLengths, i30, sizeof(int));
      loop_ub = regionLengths->size[0];
      for (i30 = 0; i30 < loop_ub; i30++) {
        regionLengths->data[i30] -= idxCount->data[i30] * (int)wc[0];
      }

      i30 = stats->data[k].PixelList->size[0] * stats->data[k].PixelList->size[1];
      stats->data[k].PixelList->size[0] = idxCount->size[0];
      stats->data[k].PixelList->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)stats->data[k].PixelList, i30,
                        sizeof(double));
      loop_ub = idxCount->size[0];
      for (i30 = 0; i30 < loop_ub; i30++) {
        stats->data[k].PixelList->data[i30] = idxCount->data[i30] + 1;
      }

      loop_ub = regionLengths->size[0];
      for (i30 = 0; i30 < loop_ub; i30++) {
        stats->data[k].PixelList->data[i30 + stats->data[k].PixelList->size[0]] =
          regionLengths->data[i30] + 1;
      }
    } else {
      i30 = stats->data[k].PixelList->size[0] * stats->data[k].PixelList->size[1];
      stats->data[k].PixelList->size[0] = 0;
      stats->data[k].PixelList->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)stats->data[k].PixelList, i30,
                        sizeof(double));
    }
  }

  emxFree_int32_T(&idxCount);
  emxFree_int32_T(&regionLengths);
  i29 = stats->size[0];
  k = 0;
  emxInit_real_T1(&Intensity, 1);
  emxInit_real_T1(&b_stats, 1);
  while (k <= i29 - 1) {
    i30 = Intensity->size[0];
    Intensity->size[0] = stats->data[k].PixelIdxList->size[0];
    emxEnsureCapacity((emxArray__common *)Intensity, i30, sizeof(double));
    loop_ub = stats->data[k].PixelIdxList->size[0];
    for (i30 = 0; i30 < loop_ub; i30++) {
      Intensity->data[i30] = varargin_2->data[(int)stats->data[k]
        .PixelIdxList->data[i30] - 1];
    }

    sumIntensity = c_sum(Intensity);
    for (vstride = 0; vstride < 2; vstride++) {
      loop_ub = stats->data[k].PixelList->size[0];
      i30 = b_stats->size[0];
      b_stats->size[0] = loop_ub;
      emxEnsureCapacity((emxArray__common *)b_stats, i30, sizeof(double));
      for (i30 = 0; i30 < loop_ub; i30++) {
        b_stats->data[i30] = stats->data[k].PixelList->data[i30 + stats->data[k]
          .PixelList->size[0] * vstride] * Intensity->data[i30];
      }

      CC_NumObjects = c_sum(b_stats);
      wc[vstride] = CC_NumObjects / sumIntensity;
    }

    for (i30 = 0; i30 < 2; i30++) {
      stats->data[k].WeightedCentroid[i30] = wc[i30];
    }

    k++;
  }

  emxFree_real_T(&b_stats);
  emxFree_real_T(&Intensity);
  for (k = 0; k < stats->size[0]; k++) {
    for (loop_ub = 0; loop_ub < 2; loop_ub++) {
      outstats->data[k].WeightedCentroid[loop_ub] = stats->data[k].
        WeightedCentroid[loop_ub];
    }
  }

  emxFree_struct_T1(&stats);
}

//
// File trailer for regionprops.cpp
//
// [EOF]
//
