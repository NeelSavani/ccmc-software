/*
 * ENLILInterpolator.h
 *
 *  Created on: Jul 9, 2009
 *      Author: dberrios
 */

#ifndef ENLILINTERPOLATOR_H_
#define ENLILINTERPOLATOR_H_

#include "Interpolator.h"
#include "Model.h"
#include <string>

namespace ccmc
{
	/**
	 * @class ENLILInterpolator ENLILInterpolator.h ccmc/ENLILInterpolator.h
	 * @brief TODO: Brief description of ENLILInterpolator class
	 *
	 * TODO: Full description of ENLILInteprolator class
	 */
	class ENLILInterpolator: public Interpolator
	{
		public:
			ENLILInterpolator(Model * model);
			float interpolate(const std::string& variable, const float& r, const float& lat, const float& lon);
			float interpolate(const std::string& variable, const float& r, const float& lat, const float& lon,
					float& dr, float& dlat, float& dlon);
			float interpolate(long variableID, const float& r, const float& lat, const float& lon);
			float interpolate(long variableID, const float& r, const float& lat, const float& lon,
					float& dr, float& dlat, float& dlon);


			virtual ~ENLILInterpolator();

		private:
			const std::vector<float> * r_data;
			const std::vector<float> * lat_data; //phi
			const std::vector<float> * lon_data; //theta
			std::string r_string;
			std::string lat_string;
			std::string lon_string;
			int nr;
			int nlat;
			int nlon;
			float interpolate_in_block_enlil(float r, float lon, float lat, int ir, int ilat, int ilon,
								long variableID, float& dr, float& dlat, float& dlon);
			float previous_r;
			float previous_lon;
			float previous_lat;
			int previous_ir;
			int previous_ilon;
			int previous_ilat;
	};
}

#endif /* ENLILINTERPOLATOR_H_ */