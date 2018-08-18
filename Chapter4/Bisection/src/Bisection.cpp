//============================================================================
// Name        : Bisection.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : A bisection algorithm as discussed in 4.2
//============================================================================

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>
//#include <limits>

using std::cout; using std::endl;
using std::fabs; using std::pow;
using std::setprecision;
using std::setw; using std::scientific;
//using std::numeric_limits;

enum STATUS {SUCCESS, BAD_FUNC, BAD_BRACKET};
STATUS bisect(double (*func)(double), double a, double b, size_t N, double tol, double& root);
double f_4_2_1(double);
double f_4_2_2(double);
double f_4_2_3(double);
double f_4_2_4(double);
double f_4_2_5(double);

int main(int argc, char* argv[])
{
	static const double PI = 3.141592654;
	double a;
	double b;
	const size_t N = 100;
	const double tol = 1e-4;
	double root;
	STATUS result;
	double (*f)(double)  = f_4_2_5;
	cout << "BISECTION..." << endl;
	int imin = 0;
	int imax = 0;
	for (int i = imin; i < imax; ++i)
		{
		//a = i;
		//b = i+1;
		//cout << "i = " << i << endl;
		if((result = bisect(f, a, b, N, tol, root)) == SUCCESS)
			{
			cout << "root = " << root/PI << "PI\n"
				 << "f(root) = " << f(root)
				 << endl;
			}
		else
			{
			cout << "STATUS was: ";
			switch (result)
				{
			case BAD_FUNC:
				cout << "BAD_FUNC";
				break;
			case BAD_BRACKET:
				cout << "BAD_BRACKET";
				break;
			default:
				cout << "unknown";
				break;
				}
			cout << endl;
			}
		cout << endl;
		}

	return EXIT_SUCCESS;
}

STATUS bisect(double (*func)(double), double a, double b, size_t N, double tol, double& root)
	{
	if (!func) return BAD_FUNC;
	if (func(a)*func(b) > 0.) return BAD_BRACKET;

	if (a > b)
		{
		double tmp = a;
		a = b;
		b = tmp;
		}

	size_t steps = 0;
	double mp;
	do {
		++steps;
		mp = (a+b)/2.;

		// debug
		cout << scientific
			 << "steps = " << steps << "\n"
			 << "a = " << a << "\n"
			 << "b = " << b << "\n"
			 << "mp = " << mp << "\n"
			 << "residual = " << func(mp) << "\n"
			 << endl;

		if (func(a)*func(mp) > 0.)
			a = mp;
		else
			b = mp;
		}
	//while (steps < N && fabs(func(mp)) > tol);
	while (steps < N && fabs(a - b) > tol);

	root = mp;

	return SUCCESS;
	}

double f_4_2_1(double x)
{
	return pow(x,3.0) - 5.;
}

double f_4_2_2(double x)
{
	return pow(x,2.0) - 3*x + 1.;
}

double f_4_2_3(double x)
{
	return pow(x, 4.) +2*pow(x, 3.) - 10018.01*pow(x, 2.) +2*x - 10019.01;
}

double f_4_2_4(double x)
{
	return cos(x) - cos(3.1*x);
}

double f_4_2_5(double x)
{
	return tan(x) - x;
}
