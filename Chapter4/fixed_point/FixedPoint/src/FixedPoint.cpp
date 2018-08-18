//============================================================================
// Name        : FixedPoint.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <limits>

using std::pow; using std::fabs; using std::cout;
using std::endl; using std::scientific;
using std::numeric_limits;

enum STATUS {SUCCESS, INVALID_GENERATOR, UNCONVERGED};
static const double tol = 1e-8; // termination tolerance involving previous and current x's
static const unsigned int N = 10; // max number of iterations
//static const double c = 7.0;
static const double root = 1.;

STATUS fixed_point(double (*g)(double x), double x_0, double tolerance, unsigned int max_steps, double& result,
		unsigned int& nsteps, bool use_aitken = false);

// generaqting functions
//double generator_a(double x);
//double generator_d(double x);
//double generator_4_3_1_4(double x);
//double generator_4_3_1_6(double x);
//double generator_4_3_1_10(double x);
//double generator_4_3_2_1(double x);
double generator_4_3_2_4(double x);

int main(int argc, char* argv[]) {
	//const double root = pow(c, 0.5);
	//const double delta = 1e-5;
	double result;
	unsigned int nsteps;

	//for(unsigned int i = 1; i < 2; ++i) {
		const double x_0 = 1000; // starting value
		cout  << "x_0 = " << x_0 << endl;
		switch(fixed_point(generator_4_3_2_4, x_0, tol, N, result, nsteps, true)) {
		case SUCCESS:
			cout << "successful convergence: result = " << result << " in " << nsteps << " steps." << endl;
			break;
		case INVALID_GENERATOR:
			cout << "invalid g(x)" << endl;
			break;
		case UNCONVERGED:
			cout << "solution did not converge." << endl;
			break;
		default:
			cout << "***ERROR! - unrecognized STATUS***" << endl;
			break;
		}
	//}

	return EXIT_SUCCESS;
}

STATUS fixed_point(double (*g)(double x), double x_0, double tolerance, unsigned int max_steps, double& result,
		unsigned int& nsteps, bool use_aitken) {
	if (!g) return INVALID_GENERATOR;
	nsteps = 0;
	double x_1, x_2, x_0_aitken;
	do {
		if (nsteps > 0)
			x_0 = x_1; // else if we are on the first step we just use the argument value
		x_1 = g(x_0);
		x_2 = g(x_1);
		if (use_aitken) { // calculate corresponding x_0 using aitken delta^2 extrapolation
			const double delta_x_0 = x_1 - x_0;
			const double delta_sq_x_0 = x_2 - 2*x_1 + x_0;
			x_0_aitken = x_0 - ((delta_x_0*delta_x_0)/(delta_sq_x_0));
		}
		++nsteps;

		// debug
		 cout << scientific << "\tstep = " << nsteps << "\tx_0 = " << x_0
			  << "\tx_0_aitken = " << x_0_aitken
			  << "\te_i_aitken/e_i = " << (x_0_aitken - root)/(x_0 - root) << endl;
		//	  << "\t|error| = " << fabs(7.390851e-01 - x_1)
		//	  << "\t|e_n| = " << fabs(pow(sin(1), static_cast<double>(nsteps))/(1 - sin(1)) * (x_cached - x_0)) << endl;
		//	  << "\te_step = " << x_1 - root << "\te_step/e_{step - 1} = " << (x_1 - root)/(x_0 - root) << endl;
		// end debug

	} while (nsteps < max_steps && fabs(x_0 - x_1) > tol);

	result = x_1;

	return ((nsteps < max_steps) && (result < numeric_limits<double>::max())) ? SUCCESS : UNCONVERGED;
}

/*
double generator_a(double x) {
	return (pow(x, 3.) + 18.)/13.;
}

double generator_d(double x) {
	return pow(x, 3.) - 12.*x + 18.;
}

double generator_4_3_1_4(double x) {
	return (x*x + c)/(2*x);
}


double generator_4_3_1_6(double x) {
	return pow(6 + x, 1./3.);
}

double generator_4_3_1_10(double x) {
	return cos(x);
}

double generator_4_3_2_1(double x) {
	return (x*x - 4*x + 7)/4;
}
*/

double generator_4_3_2_4(double x) {
	return 5 - 6./x;
}
