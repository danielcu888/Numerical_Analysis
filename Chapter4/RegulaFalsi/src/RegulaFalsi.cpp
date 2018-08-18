//============================================================================
// Name        : RegulaFalsi.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <iostream>
#include <cmath>

using std::cout; using std::endl;
using std::fabs;

enum STATUS {SUCCESS, BAD_FUNC, BAD_BRACKET};
STATUS regfal(double (*func)(double), double a, double b, size_t N, double tol, double& root);
double f_4_2_1(double);
double f_4_2_2(double);
double f_4_2_3(double);

int main(int argc, char* argv[])
	{
	const double a = 1;
	const double b = 3;
	const size_t N = 6;
	const double tol = 0.;
	double root;
	STATUS result;
	double (*f)(double) = f_4_2_2;
	cout << "REGULA FALSI..." << endl;
	if((result = regfal(f, a, b, N, tol, root)) == SUCCESS)
		{
		cout << "root = " << root << "\n"
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

		return EXIT_FAILURE;
		}

	return EXIT_SUCCESS;
	}

STATUS regfal(double (*func)(double), double a, double b, size_t N, double tol, double& root)
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
	double p;
	do {
		++steps;
		if (fabs(func(a)) < tol)
			{
			root = a;
			break;
			}
		if (fabs(func(b)) < tol)
			{
			root = b;
			break;
			}
		p = (b*func(a) - a*func(b))/(func(a) - func(b));

		// debug
		cout << "steps = " << steps << "\n"
			 << "a = " << a << "\n"
			 << "b = " << b << "\n"
			 << "p = " << p << "\n"
			 << "residual = " << func(p) << "\n"
			 << endl;

		if (func(a)*func(p) > 0.)
			a = p;
		else
			b = p;

	} while (steps < N && fabs(func(p)) > tol);

	root = p;
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
