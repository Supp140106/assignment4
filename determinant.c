#include <stdio.h>
#include <stdlib.h>
#include "determinant.h"

double determinant(double **a, int n)
{
    double det = 0;
    double **temp;
    int sign = 1;

    if (n == 1)
        return a[0][0];

    temp = (double**)malloc((n-1)*sizeof(double*));
    for(int i=0;i<n-1;i++)
        temp[i]=(double*)malloc((n-1)*sizeof(double));

    for(int f=0; f<n; f++)
    {
        int subi=0;

        for(int i=1;i<n;i++)
        {
            int subj=0;

            for(int j=0;j<n;j++)
            {
                if(j==f) continue;

                temp[subi][subj]=a[i][j];
                subj++;
            }
            subi++;
        }

        det += sign * a[0][f] * determinant(temp,n-1);
        sign = -sign;
    }

    for(int i=0;i<n-1;i++)
        free(temp[i]);
    free(temp);

    return det;
}
