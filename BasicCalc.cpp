#include <stdio.h>
#include <iostream>
#include "BasicCalc.h"
#include <math.h>

using namespace std;

BasicCalc::BasicCalc() {

	result = 0.0; // intialize to zero

}

// destructor
BasicCalc::~BasicCalc() {

}

// set result mutator
void BasicCalc::setResult(double r) {

	result = r;

}

// get result accessor
double BasicCalc::getResult() {

	return result;

}

// operation functions

double BasicCalc::add(double num1, double num2) {

	result = num1 + num2;

	return result;
}

double BasicCalc::subtract(double num1, double num2) {

	result = num1 - num2;

	return result;
}

double BasicCalc::multiply(double num1, double num2) {

	result = num1 * num2;

	return result;
}

double BasicCalc::divide(double num1, double num2) {

	result = num1 / num2;

	return result;
}

double BasicCalc::squareRoot(double n) {

	result = sqrt(n);

	return result;
}

double BasicCalc::square(double n) {

	result = pow(n, 2);

	return result;
}

// non impletmented science operations to be overridden

double BasicCalc::fact(double n) {

	return 0.0;

}

// trig functions

double BasicCalc::sinTrig(double n) {

	return 0.0;

}

double BasicCalc::cosTrig(double n) {

	return 0.0;

}

double BasicCalc::tanTrig(double n) {

	return 0.0;

}


// pi
double BasicCalc::pie() {

	return 0.0;

}

// pow 
double BasicCalc::opPower(double x, double y) {

	return 0.0;
}

// e
double BasicCalc::e() {

	return 0.0;

}