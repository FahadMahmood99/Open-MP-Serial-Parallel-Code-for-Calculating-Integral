#include <stdio.h>
#include <omp.h>

double func(double y) {
    return 1 / (1 + y + y*y + y*y*y*y);
}

double trapezoidal_rule(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));
    int i;
    #pragma omp parallel private(i) shared(result)
    {
        double local_result = 0.0;
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        for (i = 1 + thread_id; i < n; i += num_threads) {
            local_result += func(a + i * h);
        }
        #pragma omp critical
        result += local_result;
    }
    result *= h;
    return result;
}

int main() {
    double start_time, end_time;
    start_time = omp_get_wtime();

    double a = 5.0;
    double b = 10.0;
    int n = 1000;  // Number of intervals for accuracy

    double integral_value = trapezoidal_rule(func, a, b, n);

    end_time = omp_get_wtime();

    printf("Approximate value of the integral: %lf\n", integral_value);
    printf("Time taken: %lf seconds\n", end_time - start_time);
    return 0;
}
