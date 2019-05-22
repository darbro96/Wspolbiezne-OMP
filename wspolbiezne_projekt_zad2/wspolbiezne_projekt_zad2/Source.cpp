#include <iostream>
#include <omp.h>
#include <ctime>
#include <conio.h>

using namespace std;

double f(double x, double y) { return (cos(pow(x, 2) + x * y)) / (sqrt(pow(x, 2) + pow(y, 2) + 6)); }

int main()
{
	int n = 10000;
	double tab[100];
	double xp = 0, xk = 5, s = 0, dx, yp = 0, yk = 1, x, y, dy;
	dx = (xk - xp) / n;
	dy = (yk - yp) / n;
	int k, i;
	clock_t start = clock();
#pragma omp parallel for reduction(+:s) private(k,i,x,y) firstprivate(xp,yp,dy,dx)
	for (k = 1; k <= n; k++) {
		x = xp;
		y = yp + k * dy;
		for (i = 1; i <= n; i++) {
			s += f(xp + i * dx, y)* (dy*dx);
		}
	}

	clock_t stop = clock() - start;
	cout << s << endl << "Czas: " << stop / 1000 << " s";
	_getch();
	return 0;

}