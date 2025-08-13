#include <math.h>
#include <stdio.h>

int main() {
    double radius, area;

    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);

    area = M_PI * radius * radius;  // Calculate area using the formula πr²

    printf("The area of the circle with radius %.2f is %.2f\n", radius, area);
    return 0;
}
