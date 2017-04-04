//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: regionprops.cpp
//
// MATLAB Coder version            : 3.2
// C/C++ source code generated on  : 14-Feb-2017 14:49:57
//

// Include Files
#include "rt_nonfinite.h"
#include "analyzeImage.h"
#include "regionprops.h"
#include "analyzeImage_emxutil.h"
#include "sum.h"
#include "bwconncomp.h"

// Function Definitions

//
// Arguments    : const boolean_T varargin_1[809600]
//                const double varargin_2[809600]
//                emxArray_struct_T *outstats
// Return Type  : void
//
void regionprops(const boolean_T varargin_1[809600], const double varargin_2
                 [809600], emxArray_struct_T *outstats)
{
  emxArray_real_T *CC_RegionIndices;
  emxArray_int32_T *CC_RegionLengths;
  double sumIntensity;
  double wc[2];
  double CC_NumObjects;
  struct_T statsOneObj;
  int i13;
  b_struct_T b_statsOneObj;
  b_emxArray_struct_T *stats;
  int loop_ub;
  emxArray_int32_T *idxCount;
  emxArray_int32_T *idx;
  int dim;
  b_emxArray_struct_T *b_stats;
  int k;
  int vstride;
  emxArray_real_T *Intensity;
  emxArray_real_T *c_stats;
  double A;
  emxInit_real_T1(&CC_RegionIndices, 1);
  emxInit_int32_T(&CC_RegionLengths, 1);
  bwconncomp(varargin_1, &sumIntensity, wc, &CC_NumObjects, CC_RegionIndices,
             CC_RegionLengths);
  for (i13 = 0; i13 < 2; i13++) {
    statsOneObj.WeightedCentroid[i13] = 0.0;
  }

  emxInitStruct_struct_T(&b_statsOneObj);
  b_statsOneObj.Area = 0.0;
  for (i13 = 0; i13 < 2; i13++) {
    b_statsOneObj.Centroid[i13] = 0.0;
  }

  for (i13 = 0; i13 < 4; i13++) {
    b_statsOneObj.BoundingBox[i13] = 0.0;
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
  i13 = b_statsOneObj.PixelIdxList->size[0];
  b_statsOneObj.PixelIdxList->size[0] = 0;
  emxEnsureCapacity((emxArray__common *)b_statsOneObj.PixelIdxList, i13, (int)
                    sizeof(double));
  i13 = b_statsOneObj.PixelList->size[0] * b_statsOneObj.PixelList->size[1];
  b_statsOneObj.PixelList->size[0] = 0;
  b_statsOneObj.PixelList->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_statsOneObj.PixelList, i13, (int)
                    sizeof(double));
  b_statsOneObj.Perimeter = 0.0;
  b_statsOneObj.PixelValues.size[0] = 0;
  for (i13 = 0; i13 < 2; i13++) {
    b_statsOneObj.WeightedCentroid[i13] = 0.0;
  }

  b_statsOneObj.MeanIntensity = 0.0;
  b_statsOneObj.MinIntensity = 0.0;
  b_statsOneObj.MaxIntensity = 0.0;
  b_statsOneObj.SubarrayIdx.size[0] = 1;
  b_statsOneObj.SubarrayIdx.size[1] = 0;
  for (i13 = 0; i13 < 2; i13++) {
    b_statsOneObj.SubarrayIdxLengths[i13] = 0.0;
  }

  emxInit_struct_T1(&stats, 1);
  i13 = stats->size[0];
  stats->size[0] = (int)CC_NumObjects;
  emxEnsureCapacity_struct_T(stats, i13);
  loop_ub = (int)CC_NumObjects;
  for (i13 = 0; i13 < loop_ub; i13++) {
    emxCopyStruct_struct_T(&stats->data[i13], &b_statsOneObj);
  }

  emxFreeStruct_struct_T(&b_statsOneObj);
  emxInit_int32_T(&idxCount, 1);
  emxInit_int32_T(&idx, 1);
  if (CC_NumObjects != 0.0) {
    dim = 2;
    if (CC_RegionLengths->size[0] != 1) {
      dim = 1;
    }

    i13 = idx->size[0];
    idx->size[0] = CC_RegionLengths->size[0];
    emxEnsureCapacity((emxArray__common *)idx, i13, (int)sizeof(int));
    loop_ub = CC_RegionLengths->size[0];
    for (i13 = 0; i13 < loop_ub; i13++) {
      idx->data[i13] = CC_RegionLengths->data[i13];
    }

    if (dim <= 1) {
      i13 = CC_RegionLengths->size[0];
    } else {
      i13 = 1;
    }

    if ((!(CC_RegionLengths->size[0] == 0)) && (i13 > 1)) {
      vstride = 1;
      k = 1;
      while (k <= dim - 1) {
        vstride *= CC_RegionLengths->size[0];
        k = 2;
      }

      for (dim = 0; dim + 1 <= vstride; dim++) {
        for (k = 1; k < i13; k++) {
          idx->data[dim + k * vstride] += idx->data[dim + (k - 1) * vstride];
        }
      }
    }

    i13 = idxCount->size[0];
    idxCount->size[0] = 1 + idx->size[0];
    emxEnsureCapacity((emxArray__common *)idxCount, i13, (int)sizeof(int));
    idxCount->data[0] = 0;
    loop_ub = idx->size[0];
    for (i13 = 0; i13 < loop_ub; i13++) {
      idxCount->data[i13 + 1] = idx->data[i13];
    }

    for (k = 0; k < (int)CC_NumObjects; k++) {
      if (idxCount->data[k] + 1 > idxCount->data[(int)((1.0 + (double)k) + 1.0)
          - 1]) {
        i13 = 1;
        vstride = 0;
      } else {
        i13 = idxCount->data[k] + 1;
        vstride = idxCount->data[(int)((1.0 + (double)k) + 1.0) - 1];
      }

      dim = stats->data[k].PixelIdxList->size[0];
      stats->data[k].PixelIdxList->size[0] = (vstride - i13) + 1;
      emxEnsureCapacity((emxArray__common *)stats->data[k].PixelIdxList, dim,
                        (int)sizeof(double));
      loop_ub = (vstride - i13) + 1;
      for (vstride = 0; vstride < loop_ub; vstride++) {
        stats->data[k].PixelIdxList->data[vstride] = CC_RegionIndices->data[(i13
          + vstride) - 1];
      }
    }
  }

  emxFree_int32_T(&CC_RegionLengths);
  emxFree_real_T(&CC_RegionIndices);
  emxInit_struct_T1(&b_stats, 1);
  i13 = b_stats->size[0];
  b_stats->size[0] = stats->size[0];
  emxEnsureCapacity_struct_T(b_stats, i13);
  loop_ub = stats->size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    emxCopyStruct_struct_T(&b_stats->data[i13], &stats->data[i13]);
  }

  for (k = 0; k < stats->size[0]; k++) {
    if (!(b_stats->data[k].PixelIdxList->size[0] == 0)) {
      i13 = idx->size[0];
      idx->size[0] = b_stats->data[k].PixelIdxList->size[0];
      emxEnsureCapacity((emxArray__common *)idx, i13, (int)sizeof(int));
      loop_ub = b_stats->data[k].PixelIdxList->size[0];
      for (i13 = 0; i13 < loop_ub; i13++) {
        idx->data[i13] = (int)b_stats->data[k].PixelIdxList->data[i13];
      }

      i13 = idx->size[0];
      emxEnsureCapacity((emxArray__common *)idx, i13, (int)sizeof(int));
      loop_ub = idx->size[0];
      for (i13 = 0; i13 < loop_ub; i13++) {
        idx->data[i13]--;
      }

      i13 = idxCount->size[0];
      idxCount->size[0] = idx->size[0];
      emxEnsureCapacity((emxArray__common *)idxCount, i13, (int)sizeof(int));
      loop_ub = idx->size[0];
      for (i13 = 0; i13 < loop_ub; i13++) {
        idxCount->data[i13] = idx->data[i13] / 736;
      }

      i13 = idx->size[0];
      emxEnsureCapacity((emxArray__common *)idx, i13, (int)sizeof(int));
      loop_ub = idx->size[0];
      for (i13 = 0; i13 < loop_ub; i13++) {
        idx->data[i13] -= idxCount->data[i13] * 736;
      }

      i13 = b_stats->data[k].PixelList->size[0] * b_stats->data[k]
        .PixelList->size[1];
      b_stats->data[k].PixelList->size[0] = idxCount->size[0];
      b_stats->data[k].PixelList->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)b_stats->data[k].PixelList, i13,
                        (int)sizeof(double));
      loop_ub = idxCount->size[0];
      for (i13 = 0; i13 < loop_ub; i13++) {
        b_stats->data[k].PixelList->data[i13] = idxCount->data[i13] + 1;
      }

      loop_ub = idx->size[0];
      for (i13 = 0; i13 < loop_ub; i13++) {
        b_stats->data[k].PixelList->data[i13 + b_stats->data[k].PixelList->size
          [0]] = idx->data[i13] + 1;
      }
    } else {
      i13 = b_stats->data[k].PixelList->size[0] * b_stats->data[k]
        .PixelList->size[1];
      b_stats->data[k].PixelList->size[0] = 0;
      b_stats->data[k].PixelList->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)b_stats->data[k].PixelList, i13,
                        (int)sizeof(double));
    }
  }

  emxFree_int32_T(&idx);
  emxFree_int32_T(&idxCount);
  i13 = stats->size[0];
  stats->size[0] = b_stats->size[0];
  emxEnsureCapacity_struct_T(stats, i13);
  loop_ub = b_stats->size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    emxCopyStruct_struct_T(&stats->data[i13], &b_stats->data[i13]);
  }

  k = 0;
  emxInit_real_T1(&Intensity, 1);
  emxInit_real_T1(&c_stats, 1);
  while (k <= b_stats->size[0] - 1) {
    i13 = Intensity->size[0];
    Intensity->size[0] = stats->data[k].PixelIdxList->size[0];
    emxEnsureCapacity((emxArray__common *)Intensity, i13, (int)sizeof(double));
    loop_ub = stats->data[k].PixelIdxList->size[0];
    for (i13 = 0; i13 < loop_ub; i13++) {
      Intensity->data[i13] = varargin_2[(int)stats->data[k].PixelIdxList->
        data[i13] - 1];
    }

    sumIntensity = c_sum(Intensity);
    for (dim = 0; dim < 2; dim++) {
      loop_ub = stats->data[k].PixelList->size[0];
      i13 = c_stats->size[0];
      c_stats->size[0] = loop_ub;
      emxEnsureCapacity((emxArray__common *)c_stats, i13, (int)sizeof(double));
      for (i13 = 0; i13 < loop_ub; i13++) {
        c_stats->data[i13] = stats->data[k].PixelList->data[i13 + stats->data[k]
          .PixelList->size[0] * dim] * Intensity->data[i13];
      }

      A = c_sum(c_stats);
      wc[dim] = A / sumIntensity;
    }

    for (i13 = 0; i13 < 2; i13++) {
      stats->data[k].WeightedCentroid[i13] = wc[i13];
    }

    k++;
  }

  emxFree_real_T(&c_stats);
  emxFree_struct_T1(&b_stats);
  emxFree_real_T(&Intensity);
  i13 = outstats->size[0];
  outstats->size[0] = (int)CC_NumObjects;
  emxEnsureCapacity((emxArray__common *)outstats, i13, (int)sizeof(struct_T));
  loop_ub = (int)CC_NumObjects;
  for (i13 = 0; i13 < loop_ub; i13++) {
    outstats->data[i13] = statsOneObj;
  }

  for (k = 0; k < stats->size[0]; k++) {
    for (dim = 0; dim < 2; dim++) {
      outstats->data[k].WeightedCentroid[dim] = stats->data[k]
        .WeightedCentroid[dim];
    }
  }

  emxFree_struct_T1(&stats);
}

//
// File trailer for regionprops.cpp
//
// [EOF]
//
