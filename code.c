#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
long long baseToDecimal(const char *value, int base) {
    long long result = 0;
    int len = strlen(value);
    for (int i = 0; i < len; i++) {
        char digit = value[i];
        int num = (digit >= '0' && digit <= '9') ? (digit - '0') : (digit - 'A' + 10);
        result = result * base + num;
    }
    return result;
}
double lagrangeInterpolation(int x[], long long y[], int k) {
    double c = 0;
    for (int i = 0; i < k; i++) {
        double term = y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term = term * (0 - x[j]) / (x[i] - x[j]);
            }
        }
        c += term;
    }
    return c;
}
int isPointValid(double c, int x[], long long y[], int k) {
    for (int i = 0; i < k; i++) {
        if (fabs(lagrangeInterpolation(x, y, k) - y[i]) > 1e-6) {
            return 0; 
        }
    }
    return 1;
}

int main() {
    int n1 = 4, k1 = 3;
    char *values1[4] = {"4", "111", "12", "213"};
    int bases1[4] = {10, 2, 10, 4};
    int x1[] = {1, 2, 3, 6};
    long long y1[4];

    for (int i = 0; i < n1; i++) {
        y1[i] = baseToDecimal(values1[i], bases1[i]);
    }

    double secret1 = lagrangeInterpolation(x1, y1, k1);
    printf("First Test Case Secret (c): %.0lf\n", secret1);

    int n2 = 9, k2 = 6;
    char *values2[9] = {
        "28735619723837", "1A228867F0CA", "32811A4AA0B7B", "917978721331A",
        "1A22886782E1", "28735619654702", "71AB5070CC4B", "122662581541670", "642121030037605"
    };
    int bases2[9] = {10, 16, 12, 11, 16, 10, 14, 9, 8};
    int x2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    long long y2[9];

    for (int i = 0; i < n2; i++) {
        y2[i] = baseToDecimal(values2[i], bases2[i]);
    }

    double secret2 = lagrangeInterpolation(x2, y2, k2);
    printf("Second Test Case Secret (c): %.0lf\n", secret2);

    printf("Wrong Points: ");
    for (int i = 0; i < n2; i++) {
        if (!isPointValid(secret2, x2, y2, k2)) {
            printf("(%d, %lld) ", x2[i], y2[i]);
        }
    }

    printf("\n");

    return 0;
}
