#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "linalg.h"

#define float3 linalg::aliases::float3
#define float3x3 linalg::aliases::float3x3
// using namespace linalg::aliases;

int main()
{
    float mx = 28.061972;
    float my = 9.909383;
    float mz = -52.645428;

    float3 magData{mx, my, mz};

    float3x3 A{{1.002979, 0.039343, -0.014713},
               {0.039343, 1.019943, -0.006826},
               {-0.014713, -0.006826, 1.014517}};

    float3 b{7.977849, 3.137438, -5.371644};

    float3 magb = magData - b;
    float3 magC = linalg::mul(A, magData - b);

    printf("Calibrated magData: %f, %f, %f\n", magb[0], magb[1], magb[2]);
    printf("Calibrated magData: %f, %f, %f", magC[0], magC[1], magC[2]);

    return 0;
};