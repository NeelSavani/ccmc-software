/*
 * ENLILInterpolator.cpp
 *
 *  Created on: Jul 9, 2009
 *      Author: dberrios
 */

#include "ENLILInterpolator.h"
#include "Constants.h"
#include "StringConstants.h"
#include "Utils.h"
#include <iostream>

namespace ccmc
{
	/**
	 * @param model
	 */
	ENLILInterpolator::ENLILInterpolator(Model * model)
	{
		// TODO Auto-generated constructor stub
		this->modelReader = model;
		this->setMissingValue(this->modelReader->getMissingValue());
		//the model open should have done the proper error checks, so we
		//just check the first component name to see which set to use
		if (this->modelReader->doesVariableExist("r"))
		{
			r_string = ccmc::strings::variables::r_;
			lat_string = ccmc::strings::variables::phi_;
			lon_string = ccmc::strings::variables::theta_;

		} else
		{
			r_string = ccmc::strings::variables::x_;
			lat_string = ccmc::strings::variables::y_;
			lon_string = ccmc::strings::variables::z_;

		}


		//TODO: fix the phi/theta issue to correspond to the actual
		//lat lon
		r_data = modelReader->getVariableData(r_string);
		lat_data = modelReader->getVariableData(lat_string);
		lon_data = modelReader->getVariableData(lon_string);
		nr = r_data->size();
		nlat = lat_data->size();
		nlon = lon_data->size();

		previous_r = missingValue;
		previous_lon = missingValue;
		previous_lat = missingValue;


	}

	/**
	 * @param variable
	 * @param r
	 * @param lat
	 * @param lon
	 * @return
	 */
	float ENLILInterpolator::interpolate(const std::string& variable, const float& r, const float& lat,
			const float& lon)
	{
		long variable_id = modelReader->getVariableID(variable);
		float dc0, dc1, dc2;
		return interpolate(variable_id, r, lat, lon, dc0, dc1, dc2);

	}

	/**
	 * @param variable
	 * @param r
	 * @param lat
	 * @param lon
	 * @param dr
	 * @param dlat
	 * @param dlon
	 * @return
	 */
	float ENLILInterpolator::interpolate(const std::string& variable, const float& r, const float& lat,
			const float& lon, float& dr, float& dlat, float& dlon)
	{
		long variable_id = modelReader->getVariableID(variable);

		return interpolate(variable_id, r, lat, lon, dr, dlat, dlon);

	}

	/**
	 * @param variableID
	 * @param r
	 * @param lat
	 * @param lon
	 * @param dr
	 * @param dlat
	 * @param dlon
	 * @return
	 */
	float ENLILInterpolator::interpolate(long variableID, const float& r, const float& lat,
			const float& lon, float& dr, float& dlat, float& dlon)
	{

		int change_sign_flag = 0;


		//Convert radius to meters
		float r_converted = r * ccmc::constants::AU_in_meters;

		/* 1 *//*local_y = Z - ( pow( pi, 2 ) / 2 );*//** convert from latitude -60 to 60 to radians ...*/
		/* 2 *//*local_y = Z - ( pi / 2 );  *//** convert from latitude -60 to 60 to radians ...*/

		/*local_y = ( Z/radian_in_degrees ) + ( pi/2 );*//** convert from latitude -60...60 to 30...150 range in degress and then to radians...*/

		/*********** 3 ***********/

		float lat_converted = -lat/ccmc::constants::Radian_in_degrees + ccmc::constants::Pi/2.f;

		/** convert degrees ( 0 - 360 longitude ) to radiadns **/
		//first check to see if the degrees are between 0 and 360

		/** correct for longitude angles less than 0 or having a magnitude greater
		 * than 360.f
		 */
		float lon_converted = lon;

		if (lon_converted < 0.f)
		{
			lon_converted = -lon_converted;
			while(lon_converted > 360.f)
				lon_converted = lon_converted - 360.f;
			lon_converted = 360.f - lon_converted;

		} else if (lon_converted > 360.f)
		{
			while(lon_converted > 360.f)
				lon_converted = lon_converted - 360.f;

		}

		lon_converted = lon_converted / ccmc::constants::Radian_in_degrees;
		int ir, ilat, ilon;
		if (previous_r == r && previous_lon == lon && previous_lat == lat)
		{
			ir = previous_ir;
			ilat = previous_ilat;
			ilon = previous_ilon;
		} else
		{
			//first, find the cell
			ir = Utils<float>::binary_search(*r_data, 0, (*r_data).size() - 1, r_converted);
			ilat = Utils<float>::binary_search(*lat_data, 0, (*lat_data).size() - 1, lat_converted);
			ilon = Utils<float>::binary_search(*lon_data, 0, (*lon_data).size() - 1, lon_converted);
		}

		float value;
		if ((ir < 0) || (ir >= nr - 1) || (ilat < 0) || (ilat >= nlat - 1))
		{
			value = this->missingValue;
//			std::cerr << "returning missing value" << std::endl;
		} else
		{
//cout << "about to enter interpolate_in_block_enlil" << endl;
			value = interpolate_in_block_enlil(r_converted, lat_converted, lon_converted, ir, ilat, ilon,
					variableID, dr, dlat, dlon);

			/****** we need to change the sign of any y vector component ... *********/

			if (change_sign_flag) /*** this flag is set when cdf_varNum is set above ***/
			{
				value = value * (-1.0);
			}

			/*printf("DEBUG:\tcall to interpolate_in_block complete\n");*/

			/*return interpolated_value;*/



		}

		previous_ir = ir;
		previous_ilon = ilon;
		previous_ilat = ilat;
		previous_r = r;
		previous_lon = lon;
		previous_lat = lat;
		return value;
	}

	/**
	 * @param variableID
	 * @param r
	 * @param lat
	 * @param lon
	 * @return
	 */
	float ENLILInterpolator::interpolate(long variableID, const float& r, const float& lat, const float& lon)
	{
		float dc0, dc1, dc2;
		return interpolate(variableID, r, lat, lon, dc0, dc1, dc2);

	}

	/**
	 *
	 */
	ENLILInterpolator::~ENLILInterpolator()
	{
		// TODO Auto-generated destructor stub
	}

	/**
	 * @param r
	 * @param lat
	 * @param lon
	 * @param ir
	 * @param ilat
	 * @param ilon
	 * @param variableID
	 * @param dr
	 * @param dlat
	 * @param dlon
	 * @return
	 */
	float ENLILInterpolator::interpolate_in_block_enlil(float r, float lat, float lon, int ir, int ilat, int ilon,
			long variableID, float& dr, float& dlat, float& dlon)
	{
//		cout << "ir: " << ir << " ilon: " << ilon << " ilat: " << ilat << endl;

		//x y z = r lat lon = r phi theta
		bool main_memory_flag = true;
		const std::vector<float> * vData = modelReader->getVariableDataByID(variableID);
		if (vData == NULL)
			main_memory_flag = false;
//std::cout << "variable_id: " << variableID << " main_memory_flag: " << main_memory_flag << std::endl;
		float value;
		float dr_blk, dlat_blk, dlon_blk, m_r, m_lat, m_lon, two_pi = 4 * asin(1.);

		/*int ix, iy, iz;*/
		int NV_blk = nr * nlat, ilon1 = -1;

		/* int first_cell_in_block = found_block_index * nx * ny * nz; */

		/*printf("interpolating block %d\n", found_block_index );*/

		/*find_in_block( x, y, z, found_block_index, &ix, &iy, &iz, &data_ix, &data_iy, &data_iz );*/

		dr_blk = (*r_data)[ir + 1] - (*r_data)[ir];
		dlat_blk = (*lat_data)[ilat + 1] - (*lat_data)[ilat];

		/* periodic boundary */
		if ((ilon == (nlon - 1)) || (ilon == -1))
		{
			ilon = nlon - 1;
			ilon1 = 0;
			dlon_blk = ((*lon_data)[ilon1] - (*lon_data)[ilon] + two_pi);
			m_lon = (lon - (*lon_data)[nlon - 1] + ((*lon_data)[0] > lon) * two_pi) / dlon_blk;
		} else
		{
			ilon1 = ilon + 1;
			dlon_blk = (*lon_data)[ilon + 1] - (*lon_data)[ilon];
			m_lon = (lon - (*lon_data)[ilon]) / dlon_blk;
		}

		dr = dr_blk; /* return values to caller */
		dlat = dlat_blk;
		dlon = dlon_blk;

		m_r = (r - (*r_data)[ir]) / dr_blk;
		m_lat = (lat - (*lat_data)[ilat]) / dlat_blk;

		double data[8];
		int indices[8];
		indices[0] = (ir + ilat * nr + ilon * NV_blk);
		indices[1] = (ir + 1 + ilat * nr + ilon * NV_blk);
		indices[2] = (ir + (ilat + 1) * nr + ilon * NV_blk);
		indices[3] = (ir + 1 + (ilat + 1) * nr + ilon * NV_blk);
		indices[4] = (ir + ilat * nr + (ilon1) * NV_blk);
		indices[5] = (ir + 1 + ilat * nr + (ilon1) * NV_blk);
		indices[6] = (ir + (ilat + 1) * nr + (ilon1) * NV_blk);
		indices[7] = (ir + 1 + (ilat + 1) * nr + (ilon1) * NV_blk);
		if (!main_memory_flag)
		{

			for (int i = 0; i < 8; i++)
			{
				data[i] = modelReader->getVariableAtIndexByID(variableID, indices[i]);
			}

		} else
		{

			for (int i = 0; i < 8; i++)
			{
				data[i] = (*vData)[indices[i]];
			}

		}

		/* printf("DEBUG\tdata 1..8 = %g %g %g %g %g %g %g this should be data_8-->%g<--\n", data_1, data_2, data_3, data_4, data_5, data_6, data_7, data_8 ); */

		value = (1 - m_lon) * ((1 - m_lat) * ((1 - m_r) * data[0] + m_r * data[1]) + m_lat * (+(1 - m_r) * data[2] + m_r
				* data[3])) + m_lon * ((1 - m_lat) * (+(1 - m_r) * data[4] + m_r * data[5]) + m_lat * (+(1 - m_r) * data[6] + m_r
				* data[7]));

		return (value);

	}
}
