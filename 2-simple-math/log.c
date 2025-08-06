#include <math.h>
#include <stdio.h>

int main() {
    double number, result;

    printf("Enter a number to find its logarithm (base 10): ");
    scanf("%lf", &number);

    if (number <= 0) {
        printf("Cannot compute the logarithm of zero or a negative number.\n");
        return 1;
    }

    result = log10(number);
    printf("The logarithm (base 10) of %.2f is %.2f\n", number, result);
    return 0;
}
