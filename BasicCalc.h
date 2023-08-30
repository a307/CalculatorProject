#pragma once
class BasicCalc {

public:
	BasicCalc(); // constructor for basic calculator
	virtual ~BasicCalc(); // destructor for basic calculator

	// prototypes

	//accessor and mutator
	void setResult(double r);

	double getResult();

	// addition function
	double add(double num1, double num2);

	// subtraction function
	double subtract(double num1, double num2);

	// multiplication function
	double multiply(double num1, double num2);

	// division function
	double divide(double num1, double num2);

	// square root function
	double squareRoot(double n);

	// sqaure function
	double square(double n);

	// virtual scientific prototypes

	// factorial n!
	virtual double fact(double n);

	// trig functions

	// sin
	virtual double sinTrig(double n);

	// cos
	virtual double cosTrig(double n);

	// tan
	virtual double tanTrig(double n);

	// pi
	virtual double pie();

	// pow 
	virtual double opPower(double x, double y);

	// e
	virtual double e();

private:
	double result;

};