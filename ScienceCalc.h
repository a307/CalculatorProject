#pragma once
#include "BasicCalc.h"

class ScienceCalc : public BasicCalc {

public:
	ScienceCalc();
	~ScienceCalc();

	// accessors and mutators
	void setResult(double r);

	double getResult();

	// virtual scientific prototypes override from base class

	// factorial n!
	double fact(double n) override;

	// trig functions

	// sin
	double sinTrig(double n) override;

	// cos
	double cosTrig(double n) override;

	// tan
	double tanTrig(double n) override;

	// pi
	double pie() override;

	// pow 
	double opPower(double x, double y) override;

	// e
	double e() override;

private:
	double result;

};