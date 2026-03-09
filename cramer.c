#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "determinant.h"

int main()
{
    int n=3;
    srand(time(NULL));

    double **A, **Ai;
    double *B;
    double detA;

    FILE *f1=fopen("equation.txt","w");
    FILE *f2=fopen("solution.txt","w");

    A=(double**)malloc(n*sizeof(double*));
    Ai=(double**)malloc(n*sizeof(double*));
    B=(double*)malloc(n*sizeof(double));

    for(int i=0;i<n;i++)
    {
        A[i]=(double*)malloc(n*sizeof(double));
        Ai[i]=(double*)malloc(n*sizeof(double));
    }

    printf("Matrix A:\n");

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            A[i][j]=rand()%10+1;
            fprintf(f1,"%lf ",A[i][j]);
            printf("%5.2lf ",A[i][j]);
        }

        B[i]=rand()%10+1;
        fprintf(f1,"| %lf\n",B[i]);
        printf("| %5.2lf\n",B[i]);
    }

    detA=determinant(A,n);

    if(detA==0)
    {
        printf("No unique solution\n");
        return 0;
    }

    printf("\nSolutions:\n");

    for(int k=0;k<n;k++)
    {
        pid_t pid=fork();

        if(pid==0)
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(j==k)
                        Ai[i][j]=B[i];
                    else
                        Ai[i][j]=A[i][j];
                }
            }

            double detAi=determinant(Ai,n);
            double x=detAi/detA;

            printf("x%d = %lf\n",k+1,x);
            fprintf(f2,"x%d = %lf\n",k+1,x);

            exit(0);
        }
    }

    for(int i=0;i<n;i++)
        wait(NULL);

    fclose(f1);
    fclose(f2);

    for(int i=0;i<n;i++)
    {
        free(A[i]);
        free(Ai[i]);
    }

    free(A);
    free(Ai);
    free(B);

    return 0;
}
