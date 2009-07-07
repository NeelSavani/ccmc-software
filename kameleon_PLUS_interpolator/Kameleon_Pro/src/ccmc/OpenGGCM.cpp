/*
 * OpenGGCM.cpp
 *
 *  Created on: Jun 2, 2009
 *      Author: David Berrios
 */

#include "OpenGGCM.h"
#include "Point.h"
#include "Cell3D.h"
#include "Vector.h"
#include "OpenGGCMInterpolator.h"

/**
 * Default constructor
 */
OpenGGCM::OpenGGCM()
{
	// TODO Auto-generated constructor stub


	x_string = "x";
	y_string = "y";
	z_string = "z";
	previous_x = missingValue;
	previous_y = missingValue;
	previous_z = missingValue;

}

/**
 * @param filename
 * @return
 */
long OpenGGCM::open(const std::string& filename)
{
	long status;
	status = openFile(filename);

	loadVariable(x_string);
	loadVariable(y_string);
	loadVariable(z_string);
	initializeSIUnits();
	initializeConversionFactorsToSI();



	cout << "testing open in OpenGGCM class" << endl;
	return status;
}

Interpolator * OpenGGCM::createNewInterpolator()
{
	Interpolator * interpolator = new OpenGGCMInterpolator(this);

	return interpolator;
}

void OpenGGCM::initializeConversionFactorsToSI()
{
	std::cout << "OpenGGCM::initializeConversionFactorsToSI()" << std::endl;
	conversionFactorsToSI["bx1"] = 1e-9f;
	conversionFactorsToSI["by1"] = 1e-9f;
	conversionFactorsToSI["bz1"] = 1e-9f;
	conversionFactorsToSI["bx"] = 1e-9f;
	conversionFactorsToSI["by"] = 1e-9f;
	conversionFactorsToSI["bz"] = 1e-9f;
	conversionFactorsToSI["ux"] = 1e3f;
	conversionFactorsToSI["uy"] = 1e3f;
	conversionFactorsToSI["uz"] = 1e3f;
	conversionFactorsToSI["jx"] = 1e3f;
	conversionFactorsToSI["jy"] = 1e3f;
	conversionFactorsToSI["jz"] = 1e3f;
	conversionFactorsToSI["rho"] = 1e6f;
	conversionFactorsToSI["p"] = 1e-12f;



}

void OpenGGCM::initializeSIUnits()
{

	variableSIUnits["bx1"] = "T";
	variableSIUnits["by1"] = "T";
	variableSIUnits["bz1"] = "T";
	variableSIUnits["bx"] = "T";
	variableSIUnits["by"] = "T";
	variableSIUnits["bz"] = "T";
	variableSIUnits["ux"] = "m/s";
	variableSIUnits["uy"] = "m/s";
	variableSIUnits["uz"] = "m/s";
	variableSIUnits["jx"] = "A/m^2";
	variableSIUnits["jy"] = "A/m^2";
	variableSIUnits["jz"] = "A/m^2";
	variableSIUnits["rho"] = "m^-3";
	variableSIUnits["p"] = "Pa";
}




OpenGGCM::~OpenGGCM()
{
	// TODO Auto-generated destructor stub
}