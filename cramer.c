#include <stdio.h>

void cramer(double a[10][10], double b[10], double x[10], int n) {
    double d = 1; // Determinant
    double d1, d2, temp;

    // Calculate the determinant
    for (int i = 0; i < n; i++) {
        d *= a[i][i];
        for (int j = i + 1; j < n; j++) {
            temp = a[j][i] / a[i][i];
            for (int k = i; k < n; k++) {
                a[j][k] -= temp * a[i][k];
            }
        }
    }

    // Calculate x values
    for (int i = 0; i < n; i++) {
        d1 = d;
        for (int j = 0; j < n; j++) {
            if (j == i) {
                d1 *= b[j];
            } else {
                d1 *= a[j][j];
            }
        }
        x[i] = d1 / d;
    }
}

int main() {
    double a[10][10], b[10], x[10];
    int n;
    printf("Enter number of equations: ");
    scanf("%d", &n);
    printf("Enter coefficients of the equations (matrix A):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }
    printf("Enter constants of the equations (vector B):\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }
    cramer(a, b, x, n);
    printf("Solutions:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%%d] = %%lf\n", i, x[i]);
    }
    return 0;
}