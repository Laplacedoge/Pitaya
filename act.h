#ifndef __ACT_H__
#define __ACT_H__

#include "matrix.h"
#include <assert.h>

void vActReLU(Mat *mat, Mat *dst);
void vActReLU_(Mat *mat);

#define actLEAKYRELU_ALPHA 0.01F
void vActLeakyReLU(Mat *mat, Mat *dst);
void vActLeakyReLU_(Mat *mat);

#endif


