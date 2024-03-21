#include <stdio.h>
#include <omp.h>

double func(double y) {
    return 1 / (1 + y + y*y + y*y*y*y);
}

double trapezoidal_rule(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; ++i) {
        result += func(a + i * h);
    }
    result *= h;
    return result;
}

int main() {
    double start_time, end_time;
    start_time = omp_get_wtime();

    double a = 5.0;
    double b = 10.0;
    int n = 1000;  //Number of intervals for accuracy

    double integral_value = trapezoidal_rule(func, a, b, n);

    end_time = omp_get_wtime();

    printf("Approximate value of the integral: %lf\n", integral_value);
    printf("Time taken: %lf seconds\n", end_time - start_time);
    return 0;
}
