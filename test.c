/*------------------------------------------------------------------
* Function: Local_trap
* Purpose: Use trapezoidal rule to estimate part of a definite integral
* Input args:
* a: left endpoint
* b: right endpoint
* n: number of trapezoids
* Return val: estimate of integral from local_a to local_b
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    int a[5][5] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20,}, {21, 22, 23, 24, 25}};
    int n = 5, m = 5;

    for (int i = 1; i < n - 1; i++)
#pragma omp parallel for
        for (int j = 0; j < m; j++)
            a[i][j] = a[i - 1][j] + a[i + 1][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            printf("%d\n", a[i][j]);
   
    return 0;
} /* main */

