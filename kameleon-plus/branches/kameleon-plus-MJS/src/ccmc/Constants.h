/*
 * Constants.h
 *
 *  Created on: Jul 2, 2009
 *      Author: dberrios
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//TODO: Finish adding constants.
//TODO: Put \mainpage in one of hte source files
//TODO: Fix the conversionFactors
//TODO: Figure out some way of threading the problem.  Also figure out
//      How to improve the performance if the previous variable always changes.
//TODO: Keep previously requested variable, and a queue of the base variables!
namespace ccmc
{
	namespace constants
	{
		static float Boltzmann = 1.3806503e-23f;
		static float Avogadro = 6.0221415e23f;
		static float Pi = 3.14159265;
		static float AU_in_meters = 1.49598e11;
		static float Meters_to_AU = 6.68458134e-12;
		static float RadiansToDegrees = 57.2957795;
		static float DegreesToRadians = 0.0174532925;

	}

	namespace defaults
	{
		static float missingValue = -256.*-256.*-256.*-256.*-256.;
	}
}


#endif /* CONSTANTS_H_ */
