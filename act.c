#include "act.h"

/*!
 * @brief 矩阵使用的ReLU函数 ReLU function applied to matrix.
 * @param mat   待使用ReLU的矩阵 Matrix for applying ReLU.
 * @param dst   待存放结果的矩阵 Matrix that storing result.
 * */
void vActReLU(Mat *mat, Mat *dst) {
    assert(mat != NULL && dst != NULL && mat->base != NULL && dst->base != NULL);

    matMatEleNum_t tmp = mat->rowNum * mat->colNum;
    matParam_t *p = mat->base, *q = dst->base;
    while(tmp--) {
        if(*p > 0) *q = *p;
        else *q = 0;
        p++;
        q++;
    }
}

/*!
 * @brief 矩阵使用的ReLU函数(结果覆盖自身) ReLU function applied to matrix(The result will override the matrix itself).
 * @param mat   待使用ReLU的矩阵 Matrix for applying ReLU.
 * */
void vActReLU_(Mat *mat) {
    assert(mat != NULL &&  mat->base != NULL);

    matMatEleNum_t tmp = mat->rowNum * mat->colNum;
    matParam_t *p = mat->base;
    while(tmp--) {
        if(*p < 0) *p = 0;
        p++;
    }
}