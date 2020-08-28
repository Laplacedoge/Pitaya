#include "act.h"

/*!
 * @brief ReLU函数(矩阵使用) ReLU function applied to matrix.
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
 * @brief ReLU函数(矩阵使用, 结果覆盖矩阵自身) ReLU function applied to matrix(The result will override the matrix itself).
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

/*!
 * @brief Leaky ReLU函数(矩阵使用) Leaky ReLU function applied to matrix.
 * @param mat   待使用Leaky ReLU的矩阵 Matrix for applying leaeky ReLU.
 * @param dst   待存放结果的矩阵 Matrix that storing result.
 * */
void vActLeakyReLU(Mat *mat, Mat *dst) {
    assert(mat != NULL && dst != NULL && mat->base != NULL && dst->base != NULL);

    matMatEleNum_t tmp = mat->rowNum * mat->colNum;
    matParam_t *p = mat->base, *q = dst->base;
    while(tmp--) {
        if(*p > 0) *q = *p;
        else *q = *p * actLEAKYRELU_ALPHA;
        p++;
        q++;
    }
}

/*!
 * @brief Leaky ReLU函数(矩阵使用, 结果覆盖矩阵自身) Leaky ReLU function applied to matrix(The result will override the matrix itself).
 * @param mat   待使用Leaky ReLU的矩阵 Matrix for applying leaeky ReLU.
 * */
void vActLeakyReLU_(Mat *mat) {
    assert(mat != NULL &&  mat->base != NULL);

    matMatEleNum_t tmp = mat->rowNum * mat->colNum;
    matParam_t *p = mat->base;
    while(tmp--) {
        if(*p < 0) *p = *p * actLEAKYRELU_ALPHA;
        p++;
    }
}