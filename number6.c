#include <stdio.h>
#include <math.h>


double trapezia(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double res = (func(a) + func(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        res += func(x);
    }
    res *= h;

    return res;

}

double integral(double (*func)(double), double a, double b, double eps) {
    int n = 10;

    int iter = 0;
    double prev = trapezia(func, a, b, n);
    n *= 2;
    double res = trapezia(func, a, b, n);
    
    while (fabs(prev - res) > eps) {
        prev = res;
        n *= 2;
        res = trapezia(func, a, b, n);
        iter++;
        if (iter > 20) break;
    }

    return res;
}

double f_a(double x) {
    if (fabs(x) < 1e-15) {
        return 1.0;
    }
    return log(1.0 + x) / x;
}

double f_b(double x) {
    double e = exp(1.0);
    return pow(e, -(x * x) / 2.0);
}

double f_c(double x) {

   if (x > 0.999999) {
        return 1000.0;
    }

    return -log(1.0 - x);
}

double f_d(double x) {
    if (fabs(x) < 1e-15) {
        return 1.0;
    }
    return pow(x, x);
}

int main() {
    double eps;
    scanf("%lf", &eps);
    double a = 0.0;
    double b = 1.0;

    printf("%f\n", integral(f_a, a, b, eps));
    printf("%f\n", integral(f_b, a, b, eps));
    printf("%f\n", integral(f_c, a, b, eps));
    printf("%f\n", integral(f_d, a, b, eps));



    return 0;
}