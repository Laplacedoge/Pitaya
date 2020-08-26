#include "matrix.h"

/*!
 * @brief 获取一个float的整数部分的位长
 * @param num       待操作的单精度浮点数
 * */
unsigned char ucGetIntPartLen(float num) {
    unsigned char len = 0, negFlag = 0;
    unsigned int _num;
    if(num < 0) {
        negFlag = 1;
        num = -num;
    } else if(num == 0) {
        return 1U;
    }
    _num = (unsigned int)num;
    do {
        _num = _num / 10;
        len++;
    } while(_num != 0);
    return len + negFlag;
}

/*!
 * @brief 初始化矩阵
 * @param mat       待初始化矩阵的Mat结构体地址
 * @param rowNum    指定的矩阵行数
 * @param colNum    指定的矩阵列数
 * @param base      指定的矩阵数据存放地址
 * */
void vMatInit(Mat *mat, matMatSize_t rowNum, matMatSize_t colNum, matParam_t *base) {
    mat->rowNum = rowNum;
    mat->colNum = colNum;
    mat->base = base;
}

void vMatReshape(Mat *mat, matMatSize_t rowNum, matMatSize_t colNum) {
    // 当rowNum与colNum全部为0时
    assert(!(rowNum == 0 && colNum == 0));

    // 在rowNum与colNum皆不为0的情况下, rowNum与colNum相乘的结果不等于原本矩阵拥有的元素数量
    assert(((rowNum != 0 && colNum != 0) && (rowNum * colNum == mat->rowNum * mat->colNum)) || (rowNum == 0 || colNum == 0));

    // 在rowNum与colNum其中一个为0的情况下, 无法根据现有的维度信息去推算出另一个维度的信息时
    assert(((rowNum == 0 || colNum == 0) && (rowNum == 0 && (mat->rowNum * mat->colNum % colNum == 0) || colNum == 0 && (mat->rowNum * mat->colNum % rowNum == 0))) || (rowNum != 0 && colNum != 0));
    
    unsigned int eleNum = mat->rowNum * mat->colNum;
    if(rowNum == 0) {
        mat->colNum = colNum;
        mat->rowNum = eleNum / colNum;
    } else if(colNum == 0) {
        mat->rowNum = rowNum;
        mat->colNum = eleNum / rowNum;
    } else {
        mat->rowNum = rowNum;
        mat->colNum = colNum;
    }
}

/*!
 * @brief 显示矩阵
 * @param mat 待显示的矩阵
 * */
void vMatShow(Mat *mat) {
    assert(mat != NULL);
    assert(mat->base != NULL);

    char buff[8];
    matMatSize_t rowNum, colNum;

    sprintf((char *)buff, "%%%u.3f", ucGetIntPartLen(vGetMatTotalMax(mat)) + MATSHOW_DECIMAL_PART_LEN + 1U);

    printf("\nMat[%u][%u] = [\n", mat->rowNum, mat->colNum);
    for(rowNum = 0; rowNum < mat->rowNum; rowNum++) {
        printf("  [ ");
        for(colNum = 0; colNum < mat->colNum; colNum++) {
            // printf("%9.3f", *((float *)(mat->base) + rowNum * mat->colNum + colNum));
            printf((const char *)buff, *((float *)(mat->base) + rowNum * mat->colNum + colNum));
            if(colNum == mat->colNum - 1) printf(" ");
            else printf(", ");
        }
        printf("]\n");
    }
    printf("]\n\n");
}

/*!
 * @brief 两矩阵相加
 * @param matL  左矩阵
 * @param matR  右矩阵
 * @param dst   存放结果的矩阵
 * */
void vMatAdd(Mat *matL, Mat *matR, Mat *dst) {
    assert(matL->rowNum == matR->rowNum && matL->colNum == matR->colNum);
    assert(matL != NULL && matR != NULL && dst != NULL);
    assert(matL->base != NULL && matR->base != NULL && dst->base != NULL);

    unsigned int num = matL->rowNum * matL->colNum;
    matParam_t *p = matL->base, *q = matR->base, *t = dst->base;
    while(num--) *(t++) = *(p++) + *(q++);
}

/*!
 * @brief 两矩阵相加(结果存放在左矩阵)
 * @param matL  左矩阵
 * @param matR  右矩阵
 * */
void vMatAdd_(Mat *matL, Mat *matR) {
    assert(matL->rowNum == matR->rowNum && matL->colNum == matR->colNum);
    assert(matL != NULL && matR != NULL);
    assert(matL->base != NULL && matR->base != NULL);

    unsigned int num = matL->rowNum * matL->colNum;
    matParam_t *p = matL->base, *q = matR->base;
    while(num--) {
        *p = *p + *q;
        p++;
        q++;
    }
}

/*!
 * @brief 矩阵与标量值相加
 * @param mat   矩阵
 * @param num   右矩阵
 * @param dst   存放结果的矩阵
 * */
void vMatScalarAdd(Mat *mat, matParam_t scal, Mat *dst) {
    assert(mat != NULL && dst != NULL && mat->base != NULL && dst->base != NULL);

    unsigned int num = mat->rowNum * mat->colNum;
    matParam_t *p = mat->base, *t = dst->base;
    while(num--) *(t++) = *(p++) + scal;
}

/*!
 * @brief 矩阵与标量值相加(结果存放在矩阵)
 * @param mat   矩阵
 * @param num   标量值
 * */
void vMatScalarAdd_(Mat *mat, matParam_t scal) {
    assert(mat != NULL && mat->base != NULL);

    unsigned int num = mat->rowNum * mat->colNum;
    matParam_t *p = mat->base;
    while(num--) {
        *p = *p + scal;
        p++;
    }
}

/*!
 * @brief 矩阵减法
 * @param matL  左矩阵(被减矩阵)
 * @param matR  右矩阵(减矩阵)
 * @param dst   存放结果的矩阵
 * */
void vMatSub(Mat *matL, Mat *matR, Mat *dst) {
    assert(matL->rowNum == matR->rowNum && matL->colNum == matR->colNum);
    assert(matL != NULL && matR != NULL && dst != NULL);
    assert(matL->base != NULL && matR->base != NULL && dst->base != NULL);

    unsigned int num = matL->rowNum * matL->colNum;
    matParam_t *p = matL->base, *q = matR->base, *t = dst->base;
    while(num--) *(t++) = *(p++) - *(q++);
}

/*!
 * @brief 矩阵减法(结果存放在左矩阵)
 * @param matL  左矩阵(被减矩阵)
 * @param matR  右矩阵(减矩阵)
 * */
void vMatSub_(Mat *matL, Mat *matR) {
    assert(matL->rowNum == matR->rowNum && matL->colNum == matR->colNum);
    assert(matL != NULL && matR != NULL);
    assert(matL->base != NULL && matR->base != NULL);

    unsigned int num = matL->rowNum * matL->colNum;
    matParam_t *p = matL->base, *q = matR->base;
    while(num--) {
        *p = *p - *q;
        p++;
        q++;
    }
}

/*!
 * @brief 矩阵点乘
 * @param matL  左矩阵
 * @param matR  右矩阵
 * @param dst   存放结果的矩阵
 * */
void vMatDotMul(Mat *matL, Mat *matR, Mat *dst) {
    assert(matL->rowNum == matR->rowNum && matL->colNum == matR->colNum);
    assert(matL != NULL && matR != NULL && dst != NULL);
    assert(matL->base != NULL && matR->base != NULL && dst->base != NULL);

    unsigned int num = matL->rowNum * matL->colNum;
    matParam_t *p = matL->base, *q = matR->base, *t = dst->base;
    while(num--) *(t++) = *(p++) * *(q++);
}

/*!
 * @brief 矩阵点乘(结果存放在左矩阵)
 * @param matL  左矩阵
 * @param matR  右矩阵
 * */
void vMatDotMul_(Mat *matL, Mat *matR) {
    assert(matL->rowNum == matR->rowNum && matL->colNum == matR->colNum);
    assert(matL != NULL && matR != NULL);
    assert(matL->base != NULL && matR->base != NULL);

    unsigned int num = matL->rowNum * matL->colNum;
    matParam_t *p = matL->base, *q = matR->base;
    while(num--) {
        *p = *p * *q;
        p++;
        q++;
    }
}

/*!
 * @brief 矩阵乘法
 * @param matL  左矩阵
 * @param matR  右矩阵
 * @param dst   存放结果的矩阵
 * */
void vMatMul(Mat *matL, Mat *matR, Mat *dst) {

    assert(matL->colNum == matR->rowNum);
    assert(matL != NULL && matR != NULL && dst != NULL);
    assert(matL->base != NULL && matR->base != NULL && dst->base != NULL);

    unsigned short row, col;
    unsigned short i = matL->colNum;

    // 左源矩阵与右源矩阵元素指针
    float *srcL = NULL;
    float *srcR = NULL;

    // 目标矩阵元素指针
    float *target = NULL;

    dst->rowNum = matL->rowNum;
    dst->colNum = matR->colNum;

    for(row = 0; row < matL->rowNum; row++) {
        for(col = 0; col < matR->colNum; col++) {
            i = matL->colNum;

            // 重新计算源矩阵元素指针
            srcL = (float *)(matL->base) + row * matL->colNum + i - 1;
            srcR = (float *)(matR->base) + (i - 1) * matR->colNum + col;

            // 重新计算目标矩阵元素指针
            target = (float *)(dst->base) + row * dst->colNum + col;
            *target = 0;
            while(i--) {
                *target += *srcL * *srcR;
                srcL--;
                srcR -= matR->colNum;
            }
        }
    }
}

/*!
 * @brief 矩阵转置
 * @param mat   待转置矩阵
 * @param dst   存放结果的矩阵
 * */
void vMatTrs(Mat *mat, Mat *dst) {
    assert((mat->rowNum + mat->colNum) != 0 && mat != NULL && mat->base != NULL && dst != NULL && dst->base != NULL);

    matMatEleNum_t totalEleNum = mat->rowNum * mat->colNum, tmp;
    if(mat->rowNum == 1 || mat->colNum == 1) {
        dst->rowNum = mat->colNum;
        dst->colNum = mat->rowNum;
        memcpy((void *)dst->base, (void *)mat->base, (int)(totalEleNum * 4));
        return;
    } else {
        dst->rowNum = mat->colNum;
        dst->colNum = mat->rowNum;
        for(tmp = 0; tmp < totalEleNum; tmp++) {
            *(dst->base + dst->colNum * (tmp % mat->colNum) + (tmp / mat->colNum)) = *(mat->base + tmp);
        }
    }
}

// void vMatTrs_(Mat *mat) {
//     assert((mat->rowNum + mat->colNum) != 0 && mat != NULL && mat->base != NULL);

//     matMatSize_t matSizeSwap;
//     matParam_t matParamSwap;
//     matMatEleNum_t totalEleNum = mat->rowNum * mat->colNum, row, col;

//     matSizeSwap = mat->colNum;
//     mat->colNum = mat->rowNum;
//     mat->rowNum = matSizeSwap;
//     if(mat->rowNum == 1 || mat->colNum == 1) return;
//     else {
//         for(row = 0; row < ) {
//             for() {

//             }
//         }
//     }
// }

// void vMatConv() {

// }

/*!
 * @brief 获取矩阵的唯一最小值
 * @param mat   待获取最小值的矩阵
 * */
matParam_t vGetMatTotalMin(Mat *mat) {
    assert(mat != NULL && mat->base != NULL);

    matMatEleNum_t len = mat->rowNum * mat->colNum;
    matParam_t min = 3.4028234663852886e38, *p = mat->base;
    if(len == 1) return *(mat->base);
    while(len--) {
        if(*p < min) min = *p;
        p++;
    }
    return min;
}

/*!
 * @brief 获取矩阵的唯一最大值
 * @param mat   待获取最大值的矩阵
 * */
matParam_t vGetMatTotalMax(Mat *mat) {
    assert(mat != NULL && mat->base != NULL);

    matMatEleNum_t len = mat->rowNum * mat->colNum;
    matParam_t max = -3.4028234663852886e38, *p = mat->base;
    if(len == 1) return *(mat->base);
    while(len--) {
        if(*p > max) max = *p;
        p++;
    }
    return max;
}
