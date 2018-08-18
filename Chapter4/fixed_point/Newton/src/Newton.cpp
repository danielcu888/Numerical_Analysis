//============================================================================
// Name        : Newton.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <float.h>
#include <cmath>
#include <numeric>
#include <iostream>

using std::fabs;
using std::pow;
using std::numeric_limits;
using std::cout; using std::endl;
using std::cerr;
using std::scientific;

enum STATUS {SUCCEEDED, NOT_CONVERGED, BAD_FUNCTION, BAD_BRACKET, BAD_START};
STATUS NewtonBisection(double (*f)(double), double (*dfdx)(double), double x0, double a, double b, unsigned int max_steps,
		double xtol, double ftol, double& result, unsigned int& steps, bool allow_bisect = false);
double generator(double x, double (*f)(double), double (*dfdx)(double));

//double func(double x);
//double dfuncdx(double x);

//double func1(double x);
//double dfuncdx1(double x);

//double func3(double x);
//double dfuncdx3(double x);

//double func4(double);
//double dfuncdx4(double);

//double func5(double);
//double dfuncdx5(double);

double func10(double);
double dfuncdx10(double);

const double PI = 3.141592654;
const unsigned int max_bisect_count = 2;

int main(int argc, char *argv[])
	{
	const unsigned int max_steps = 25;
	const double xtol = 1e-6;
	const double ftol = 1e-6;
	double result = numeric_limits<double>::max();
	unsigned int steps = 0;

	const double x_0 = PI/4;
	const double a = -1.5;
	const double b = 0.5;
	STATUS stat = NewtonBisection(func10, dfuncdx10, x_0, a, b, max_steps, xtol, ftol, result, steps, false);
	switch (stat)
		{
	case SUCCEEDED:
		cout << "Solved to result = " << result/(PI/4) << " PI/4, in " << steps << " steps." << endl;
		break;
	case NOT_CONVERGED:
		cout << "****Did not converge*** result = " << result << ", after " << max_steps << " steps." << endl;
		break;
	case BAD_FUNCTION:
		cerr << "***Error: Bad function." << endl;
		break;
	case BAD_BRACKET:
		cerr << "***Error: Bad bracket." << endl;
		break;
	case BAD_START:
		cerr << "***Error: Initial guess resides outside bracket." << endl;
		break;
	default:
		cerr << "***Unrecognized STATUS***" << endl;
		break;
		}

	cout << "check: f(result) = " << func10(result) << endl;

	return EXIT_SUCCESS;
	}

STATUS NewtonBisection(double (*f)(double), double (*dfdx)(double), double x0, double a, double b, unsigned int max_steps,
		double xtol, double ftol, double& result, unsigned int& steps, bool allow_bisect)
	{
	if (!f || !dfdx) return BAD_FUNCTION;
	if (allow_bisect && f(a)*f(b) > 0.) return BAD_BRACKET;
	if (allow_bisect && ((b>=a && x0 > b) || (b<=a && x0 < b))) return BAD_START;

	if(allow_bisect && fabs(a - b) < xtol)
		{
		result = a;
		return SUCCEEDED;
		}

	bool bisect = false;

	steps = 0;
	double x_prev, x_next;
	double f_prev, g_next;
	do
		{
		if(!bisect)
			{
			if (steps == 0)
				{
				x_prev = x0;
				x_next = generator(x_prev, f, dfdx);
				}
			else
				{
				x_prev = x_next;
				x_next = g_next;
				}
			f_prev = f(x_prev);
			g_next = generator(x_next, f, dfdx);

			// Check next x resides within current bracket
			if ((b >= a && (x_next > b || x_next < a)) || (b <= a && (x_next < b || x_next > a)))
				{
				if (allow_bisect)
					bisect = true;
				else
					{
					++steps;
					}
				}
			else
				++steps;
			}
		else
			{
			static unsigned int bisect_count = 0;
			if (bisect_count < max_bisect_count)
				{
				const double mp = (a+b)/2.;
				const double fmp = f(mp);

				// check if current bracket has converged
				if(fabs(a - b) < xtol || fabs(fmp) < ftol)
					{
					x_prev = x_next;
					x_next = mp;
					f_prev = fmp;
					break;
					}

				if (f(a)*fmp < 0.)
					b = mp;
				else
					a = mp;

				if (bisect_count == 0)
					{
					// on first bisection we merely want new x_next, maintaining old x_prev
					x_next = mp;
					}
				else if (bisect_count > 0)
					{
					// on final bisection we update both x_prev, x_next and f_next
					x_prev = x_next;
					x_next = mp;
					if(bisect_count+1 == max_bisect_count)
						g_next = generator(x_next, f, dfdx);
					}

				if (bisect_count > 0)
					++steps;
				++bisect_count;
				}
			else
				{
				bisect_count = 0;
				bisect = false;
				}
			}
		//**********DEBUG OUTPUT*************
		cout << scientific
				<< "x_" << steps-1 << " = " << x_prev/(PI/4) << " PI/4"
				<< ",\t\tf(x_" << steps-1 << ") = " << (f_prev = f(x_prev))
				<< ", x_" << steps << " = " << x_next/(PI/4) << " PI/4"
				<< ",\t\tf(x_" << steps << ") = " << g_next
				//<< ",\tbisect = " << bisect
				<< endl;
		//***********************************
		}
	while (steps < max_steps && fabs(x_prev - x_next) > xtol && fabs(f_prev) > ftol);

	result = x_next;
	if(bisect) ++steps;
	return steps >= max_steps ? NOT_CONVERGED : SUCCEEDED;
	}

double generator(double x, double (*f)(double), double (*dfdx)(double))
	{
	return x - f(x)/dfdx(x);
	}

/*
double func(double x)
	{
	return pow(x, 2.) - 2.;
	}

double dfuncdx(double x)
	{
	return 2.*x;
	}

double func1(double x)
	{
	return pow(x,3.) - 2*pow(x,2.) + 2*x - 1.;
	}

double dfuncdx1(double x)
	{
	return 3*pow(x,2.) - 4*x + 2;
	}

double func3(double x)
	{
	return pow(x,4.) - 4*pow(x,3.) + 6*pow(x,2.) - 4*x + 1.;
	}

double dfuncdx3(double x)
	{
	return 4*pow(x,3.) - 12*pow(x,2.) + 12*x - 4;
	}

double func4(double x)
	{
	return sin(15*x) - 0.5*sin(14*x);
	}

double dfuncdx4(double x)
	{
	return 15*cos(15*x) - 7*cos(14*x);
	}

double func5(double x)
	{
	return 1. - x*x;
	}

double dfuncdx5(double x)
	{
	return -2.*x;
	}
*/

double func10(double x)
	{
	//return tan(x) - 2*x;
	if (x >= PI/2) return 1;
	if (x <= -PI/2) return -1;
	return sin(x);
	}

double dfuncdx10(double x)
	{
	//return pow(cos(x), 2.) - 2.;
	if ((x >= PI/2) || (x <= -PI/2)) return 0;
	return cos(x);
	}
