#include <math.h>
#include <stdio.h>

int main() {
    double number, result;

    printf("Enter a number to find its square root: ");
    scanf("%lf", &number);

    if (number < 0) {
        printf("Cannot compute the square root of a negative number.\n");
        return 1;
    }

    result = sqrt(number);
    printf("The square root of %.2f is %.2f\n", number, result);
    return 0;
}
