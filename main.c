#include <stdio.h>
#include "matrix.h"

#define NDEBUG

matParam_t mat1_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
// matParam_t mat1_data[] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
// matParam_t mat1_data[] = {12, 11, 9, 7, 4, 2, 1, 3, 5, 6, 8, 10};

int main(int argc, char *argv) {
    Mat mat1;
    vMatInit(&mat1, 1, 12, (matParam_t *)&mat1_data);
    vMatShow(&mat1);
    vMatReshape(&mat1, 0, 6);
    vMatShow(&mat1);
    vMatScalarAdd_(&mat1, 5);
    vMatShow(&mat1);
}