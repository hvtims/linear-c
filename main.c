#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("check args\n");
        return 1;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("error reading file\n");
        return 1;
    }

    double *y = NULL;
    size_t size = 0;
    double value;

    // Read values from the file
    while (fscanf(file, "%lf", &value) == 1) {
        y = realloc(y, (size + 1) * sizeof(double));
        if (!y) {
            printf("Memory allocation failed\n");
            fclose(file);
            return 1;
        }
        y[size++] = value;
    }
    fclose(file);

    double N = (double)size;
    if (N == 0) {
        printf("no data\n");
        free(y);
        return 1;
    }

    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0, sumY2 = 0.0;

    // Calculate summations
    for (int x = 0; x < size; x++) {
        sumX += (double)x;
        sumY += y[x];
        sumXY += (double)x * y[x];
        sumX2 += (double)x * x;
        sumY2 += y[x] * y[x];
    }

    // Calculate slope (m) and intercept (b)
    double m = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
    double b = (sumY - m * sumX) / N;

    // Calculate Pearson Correlation Coefficient (r)
    double r = (N * sumXY - sumX * sumY) / sqrt((N * sumX2 - sumX * sumX) * (N * sumY2 - sumY * sumY));

    printf("Linear Regression Line: y = %.6fx + %.6f\n", m, b);
    printf("Pearson Correlation Coefficient: %.10f\n", r);

    free(y);
    return 0;
}
