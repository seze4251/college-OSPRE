//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: analyzeImage_types.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-Apr-2017 22:04:47
//
#ifndef ANALYZEIMAGE_TYPES_H
#define ANALYZEIMAGE_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
#ifndef struct_emxArray_boolean_T_0x0
#define struct_emxArray_boolean_T_0x0

struct emxArray_boolean_T_0x0
{
  int size[2];
};

#endif                                 //struct_emxArray_boolean_T_0x0

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_real_T

#ifndef struct_emxArray_real_T_0
#define struct_emxArray_real_T_0

struct emxArray_real_T_0
{
  int size[1];
};

#endif                                 //struct_emxArray_real_T_0

#ifndef struct_emxArray_real_T_1x0
#define struct_emxArray_real_T_1x0

struct emxArray_real_T_1x0
{
  int size[2];
};

#endif                                 //struct_emxArray_real_T_1x0

#ifndef struct_sIDhrNAaM1gFltZvsygdTzB
#define struct_sIDhrNAaM1gFltZvsygdTzB

struct sIDhrNAaM1gFltZvsygdTzB
{
  double Area;
  double Centroid[2];
  double BoundingBox[4];
  double MajorAxisLength;
  double MinorAxisLength;
  double Eccentricity;
  double Orientation;
  emxArray_boolean_T_0x0 Image;
  emxArray_boolean_T_0x0 FilledImage;
  double FilledArea;
  double EulerNumber;
  double Extrema[16];
  double EquivDiameter;
  double Extent;
  emxArray_real_T *PixelIdxList;
  emxArray_real_T *PixelList;
  double Perimeter;
  emxArray_real_T_0 PixelValues;
  double WeightedCentroid[2];
  double MeanIntensity;
  double MinIntensity;
  double MaxIntensity;
  emxArray_real_T_1x0 SubarrayIdx;
  double SubarrayIdxLengths[2];
};

#endif                                 //struct_sIDhrNAaM1gFltZvsygdTzB

typedef sIDhrNAaM1gFltZvsygdTzB b_struct_T;

#ifndef struct_c_emxArray_sIDhrNAaM1gFltZvsygd
#define struct_c_emxArray_sIDhrNAaM1gFltZvsygd

struct c_emxArray_sIDhrNAaM1gFltZvsygd
{
  b_struct_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_c_emxArray_sIDhrNAaM1gFltZvsygd

typedef c_emxArray_sIDhrNAaM1gFltZvsygd b_emxArray_struct_T;

#ifndef struct_emxArray__common
#define struct_emxArray__common

struct emxArray__common
{
  void *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray__common

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_boolean_T

#ifndef struct_emxArray_creal_T
#define struct_emxArray_creal_T

struct emxArray_creal_T
{
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_creal_T

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_int32_T

#ifndef struct_emxArray_int8_T
#define struct_emxArray_int8_T

struct emxArray_int8_T
{
  signed char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_int8_T

#ifndef struct_emxArray_real32_T
#define struct_emxArray_real32_T

struct emxArray_real32_T
{
  float *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_real32_T

typedef struct {
  double WeightedCentroid[2];
} struct_T;

#ifndef struct_emxArray_struct_T
#define struct_emxArray_struct_T

struct emxArray_struct_T
{
  struct_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_struct_T

#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T

struct emxArray_uint8_T
{
  unsigned char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_uint8_T
#endif

//
// File trailer for analyzeImage_types.h
//
// [EOF]
//
