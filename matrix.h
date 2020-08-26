#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef float matParam_t;               // 普通参数类型
typedef const float matRoParam_t;       // 只读参数类型
typedef unsigned short matMatSize_t;    // 矩阵尺寸类型
typedef unsigned int matMatEleNum_t;    // 矩阵元素数量类型


// 矩阵类型
typedef struct _Mat {
    matMatSize_t rowNum;    // 矩阵的行数
    matMatSize_t colNum;    // 矩阵的列数
    matParam_t *base;       // 矩阵数据首元素地址
}Mat;

unsigned char ucGetIntPartLen(float num);
void vMatInit(Mat *mat, matMatSize_t rowNum, matMatSize_t colNum, matParam_t *base);
void vMatReshape(Mat *mat, matMatSize_t rowNum, matMatSize_t colNum);

#define MATSHOW_DECIMAL_PART_LEN 3U     // 小数部分显示位数
void vMatShow(Mat *mat);
void vMatAdd(Mat *matL, Mat *matR, Mat *dst);
void vMatAdd_(Mat *matL, Mat *matR);
void vMatScalarAdd(Mat *mat, matParam_t scal, Mat *dst);
void vMatScalarAdd_(Mat *mat, matParam_t scal);
#define vMatScalarSub(mat, scal, dst) vMatScalarAdd(mat, -scal, dst)
#define vMatScalarSub_(mat, scal) vMatScalarAdd_(mat, -scal)

void vMatSub(Mat *matL, Mat *matR, Mat *dst);
void vMatSub_(Mat *matL, Mat *matR);
void vMatDotMul(Mat *matL, Mat *matR, Mat *dst);
void vMatDotMul_(Mat *matL, Mat *matR);
void vMatMul(Mat *matL, Mat *matR, Mat *dst);

void vMatTrs(Mat *mat, Mat *dst);
// void vMatTrs_(Mat *mat);

matParam_t vGetMatTotalMin(Mat *mat);
matParam_t vGetMatTotalMax(Mat *mat);

#endif


