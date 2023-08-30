#include <stdio.h>
#include <iostream>
#include "ScienceCalc.h"
#include <math.h>

using namespace std;

ScienceCalc::ScienceCalc() : BasicCalc() {

	result = 0.0;

}

ScienceCalc::~ScienceCalc() {


}

//acessor and mutators

void ScienceCalc::setResult(double r) {

	result = r;

}

double ScienceCalc::getResult() {

	return result;

}

// operations

// factorial function
double ScienceCalc::fact(double n) {

	int r = 1;
	int m = (int)n;

	for (int i = 1; i <= m; i++) {
		r = multiply(r, i); // use inherited multiplcation function
		//r = r * i;
	}

	result = r;

	return result;

}

// trig functions

double ScienceCalc::sinTrig(double n) {

	result = sin(n);

	return result;

}

double ScienceCalc::cosTrig(double n) {

	result = cos(n);

	return result;

}

double ScienceCalc::tanTrig(double n) {

	result = tan(n);

	return result;

}


// pi
double ScienceCalc::pie() {

	return 3.14159265359;

}

// pow 
double ScienceCalc::opPower(double x, double y) {

	result = pow(x, y);

	return result;

}

// e
double ScienceCalc::e() {

	return 2.718281828459;

}