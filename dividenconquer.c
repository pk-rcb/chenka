#include <stdio.h>
#include <math.h>

int multiply(int x, int y) {
    if (x < 10 && y < 10)
        return x * y;

    int n = fmax((int)log10(x) + 1, (int)log10(y) + 1);
    int half = n / 2;

    int p = pow(10, half);

    int a = x / p;
    int b = x % p;
    int c = y / p;
    int d = y % p;

    int ac = multiply(a, c);
    int ad = multiply(a, d);
    int bc = multiply(b, c);
    int bd = multiply(b, d);

    return ac * pow(10, 2 * half) + (ad + bc) * p + bd;
}

int main() {
    int x, y;
    printf("Enter first number: ");
    scanf("%d", &x);
    printf("Enter second number: ");
    scanf("%d", &y);

    printf("Product = %d\n", multiply(x, y));
    return 0;
}
