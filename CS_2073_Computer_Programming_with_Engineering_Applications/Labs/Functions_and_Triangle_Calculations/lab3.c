#include <stdio.h>
#include <math.h> // needed for the square root function

double calc_area(double a, double b){
    
    return (.5 * (a*b));
}

double calc_perimeter(double a, double b){
    double c;
    c = sqrt((a*a) + (b*b));
    
    return a + b + c;
}

int main()
{
    double a, b;
    double perimeter, area;
    
    
    printf("Input base length of triangle:\n");
    scanf("%lf", &a);
    printf("Input height of triangle:\n");
    scanf("%lf", &b);
    
    perimeter = calc_perimeter(a,b);
    area = calc_area(a,b);
    
    printf("The perimeter of the triangle is: %lf\n", perimeter);
    printf("The area of the triangle is: %lf\n", area);
    
    return 0;
}
