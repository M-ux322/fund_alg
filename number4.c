#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

double ln_fact(int n) {
    if (n <= 1) return 0.0;
    double res = 0.0;
    for (int i = 2; i <= n; i++) {
        res += log(i);
    }
    return res;
}

double e_lim(double eps) {
    int n = 1;
    double prev = pow(1.0 + 1.0/n, n);
    n++;
    double a = pow(1.0 + 1.0/n, n);

    while (fabs(a - prev) > eps) {
        prev = a;
        n *= 2;
        a = pow(1.0 + 1.0/n, n);
    }
    return a;
}

double e_sum(double eps) {
    double sum = 1.0;
    int n = 1;
    double x = 1.0 / n;

    while(x > eps) {
        sum += x;
        n++;
        x /=  n;
    }

    sum += x;

    return sum;
}

double e_ur(double eps) {
    double a = 2.0;
    double b = 3.0;

    while (fabs(a - b) > eps) {
        double x = (a + b) / 2;

        double f_1 = log(a) - 1;
        double f_2 = log(x) - 1;
        if (f_1 * f_2 < 0) {
            b = x;
        } else a = x;
    }

    return a;
}

// ln(π) = 4[n×ln(2) + ln(n!)] - [ln(n) + 2×ln((2n)!)]
double pi_lim(double eps) {
    int n = 1;
    double prev = exp(4.0 * (n * log(2.0) + ln_fact(n)) - (log(n) + 2.0 * ln_fact(2 * n)));
    n++;
    double a = exp(4.0 * (n * log(2.0) + ln_fact(n)) - (log(n) + 2.0 * ln_fact(2 * n)));

    while (fabs(a - prev) > eps) {
        prev = a;
        n *= 2;
        a = exp(4.0 * (n * log(2.0) + ln_fact(n)) - (log(n) + 2.0 * ln_fact(2 * n)));
    }
    return a;
}

double pi_sum(double eps) {
    double sum = 0.0;
    int n = 1;
    double x = pow(-1, n - 1) / (2 * n - 1);

    while (fabs(x) > eps) {
        x = pow(-1, n - 1) / (2 * n - 1);
        sum += x;
        n++;
    }
    return 4 * sum;
}

double pi_ur(double eps) {
    double a = 3.0;
    double b = 4.0;
    
    while (fabs(a - b) > eps) {
       double x = (a + b) / 2; 
        
        double f1 = cos(a) + 1;
        double f2 = cos(b) + 1;
        
        if (f1 < f2) {
            b = x;
        } else {
            a = x;
        }
    }
    
    return (a + b) / 2;
}

double lim_ln(double eps) {
    int n = 1;
    double prev = n * (pow(2, 1.0/n) - 1);
    n++;
    double a = n * (pow(2, 1.0/n) - 1);

    while (fabs(a - prev) > eps) {
        prev = a;
        n *= 2;
        a = n * (pow(2, 1.0/n) - 1);
    }
    return a;
}

double ln_sum(double eps) {
    int n = 1;
    double sum = 0.0;
    double x = pow(-1, n - 1) / n;

    while (fabs(x) > eps) {
        x = pow(-1, n - 1) / n;
        sum += x;
        n++;
    }
    return sum;
}

double ln_ur(double eps) {
    double a = 0.0;
    double b = 1.0;
    double e = exp(1.0);

    while (fabs(a - b) > eps) {
        double x = (a + b) / 2;
        double f_1 = pow(e, a) - 2;
        double f_2 = pow(e, x) - 2;
        if (f_1 * f_2 < 0) {
            b = x;
        } else a = x;
    }
    return (a + b) / 2;
}

double two_lim(double eps) {
    int n = 1;
    double prev = -0.5 - (-0.5) * (-0.5) / 2 + 1;
    n++;
    double a = prev - prev * prev / 2 + 1;

    while (fabs(a - prev) > eps) {
        prev = a;
        n++;
        a = prev - prev * prev / 2 + 1;
    }
    return a;
}

double two_pr(double eps) {
    int k = 2;
    double pr_1 = 1.0;
    double pr_2 = pow(2, pow(2, -k));
    while (fabs(pr_1 - pr_2) > eps) {
        pr_1 = pr_2;
        k++;
        pr_2 *= pow(2, pow(2, -k));
    }
    return pr_2;
}

double two_ur(double eps) {
    double a = 1.0;
    double b = 2.0;

    while (fabs(a - b) > eps) {

        double x = (a + b) / 2;
        double f_1 = a * a - 2;
        double f_2 = x * x - 2;
        if (f_1 * f_2 < 0) {
            b = x;
        } else a = x;
    }
    return (a + b) / 2;
}

double binom(int n, int k) {
     double log_res = 0.0;
    for (int i = 0; i < k; i++) {
        log_res += log(n - i) - log(i + 1);
    }
    return log_res;
}

double sum_binom(int m) {

    double res = 0.0;
    for (int i = 1; i <= m; i++) {
        double log_x  = binom(m, i) + log(ln_fact(i)) - log(i);
        double x = exp(log_x);

        if (i % 2 == 1) res -= x;
        else res += x;
        //printf("%f\n", ln_fact(i));
    }
    return res;
}

double gamma_lim(double eps) {
    int m = 1;
    double prev = sum_binom(m);
    m++;
    double a = sum_binom(m);

    while (fabs(a - prev) > eps) {
        prev = a;
        m++;
        a = sum_binom(m);
    }
    return a;
}

double gamma_sum(double eps) {
    int k = 2;
    double pi = acos(-1.0);
    double sum = - (pi * pi) / 6;
    
    while (k <= 1000000) {
        double x = 1.0 / ((int)sqrt(k) * (int)sqrt(k)) - 1.0 / k;
        sum += x;
        
        if (fabs(x) < eps && k > 100000) {
            break;
        }
        k++;
    }
    
    return sum;
}

bool is_prime(int num) {
    int up = (int)sqrt(num) + 1;
    for (int i = 2; i < up; i++) {
        if (num % i == 0) {
            return false;
            break;
        }
    }
    if (num < 2) return false;
    return true;
}

double prime_pr(int t) {
    double pr = 1.0;
    for (int i = 2; i <= t; i++) {
        if (is_prime(i)) pr *= (double)(i - 1) / i;
    }
    return pr * log(t);
}

double lim_t(double eps) {
    int t = 1;
    double prev = prime_pr(t);
    t *= 2;
    double a = prime_pr(t);

    while(fabs(a - prev) > eps) {
        prev = a;
        t *= 3;
        a = prime_pr(t);
    }
    return a;
}

double gamma_ur(double eps) {
    double a = 0.0;
    double b = 1.0;
    double e = exp(1.0);
    double l = lim_t(eps);

    while (fabs(a - b) > eps) {
        double x = (a + b) / 2;
        double f_1 = pow(e, -a) - l;
        double f_2 = pow(e, -x) - l;

        if (f_1 * f_2 < 0) {
            b = x;
        } else a = x;
    }
    return (a + b) / 2;

}

int main() {
    double eps;
    scanf("%lf", &eps);
    printf("%lf, %lf, %lf\n", e_lim(eps), e_sum(eps), e_ur(eps));
    printf("%lf, %lf, %lf\n", pi_lim(eps), pi_sum(eps), pi_ur(eps));
    printf("%lf, %lf, %lf\n", lim_ln(eps), ln_sum(eps), ln_ur(eps));
    printf("%lf, %lf, %lf\n", two_lim(eps), two_pr(eps), two_ur(eps));
    printf("%lf, %lf, %lf\n", two_lim(eps), two_pr(eps), two_ur(eps));
    printf("%lf, %lf, %lf\n", gamma_lim(eps), gamma_sum(eps), gamma_ur(eps));

}