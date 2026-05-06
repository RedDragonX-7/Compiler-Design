#include <stdio.h>

// Define PI as a macro constant
#define PI 3.14159

int main() {
    float radius, area;

    // Input radius
    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);

    // Calculate area
    area = PI * radius * radius;

    // Display result
    printf("Area of the circle = %.2f\n", area);

    return 0;
}