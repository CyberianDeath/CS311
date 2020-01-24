#include <iomanip>
#include <iostream>

typedef double F(double,double);

/*
Approximates y(t) in y'(t)=f(t,y) with y(a)=y0 and
t=a..b and the step size h.
*/
void euler(double y0, double a, double b, double h)
{
    double y = y0;
    for (double t = a; t < b; t += h)
    {
        std::cout << std::fixed << std::setprecision(3) << t << " " << y << "\n";
        y += h * f(t, y);
    }
    std::cout << "done\n";
}

int main()
{
    euler(100, 0, 100,  2);
    euler( 100, 0, 100,  5);
    euler( 100, 0, 100, 10);
}
