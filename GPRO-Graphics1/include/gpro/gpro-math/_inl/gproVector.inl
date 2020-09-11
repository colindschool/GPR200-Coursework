/*
   Copyright 2020 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
	gproVector.h
	Interface for vectors. Sets an example for C and C++ compatible headers.

	Modified by: Colin Deane
	Modified because: Implementing more vector utility functions

	Contains code that is an edited version of Peter Shirley's Ray Tracing in One Weekend. Available at: https://raytracing.github.io/books/RayTracingInOneWeekend.html
	Special thanks to Dan Bucketin for providing the framework for the vectors
*/

#ifdef _GPRO_VECTOR_H_
#ifndef _GPRO_VECTOR_INL_
#define _GPRO_VECTOR_INL_


#ifdef __cplusplus
#include <math.h>

// Default ctor
inline vec3::vec3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}
// Ctor with variables 
inline vec3::vec3(float const xc, float const yc, float const zc)
	: x(xc), y(yc), z(zc)
{
}
// Copy ctor with a float3
inline vec3::vec3(float3 const vc)
	: x(vc[0]), y(vc[1]), z(vc[2])
{
}
// Copy ctor with a vector
inline vec3::vec3(vec3 const& rh)
	: x(rh.x), y(rh.y), z(rh.z)
{
}

// Calculates the length of the vector (using vector squared)
inline float vec3::length() const
{
	return float(sqrt(length_squared()));
}

// Calculates the length of the vector squared
inline float vec3::length_squared() const
{
	return ((x * x) + (y * y) + (z * z));
}

// Equals operator setting one vector equal to another
inline vec3& vec3::operator =(vec3 const& rh)
{
	x = rh.x;
	y = rh.y;
	z = rh.z;
	return *this;
}

// Adding another vector to a vector (changing the original)
inline vec3& vec3::operator +=(vec3 const& rh)
{
	x += rh.x;
	y += rh.y;
	z += rh.z;
	return *this;
}

// Multiplying a vector with a float (changing the original)
inline vec3& vec3::operator *=(float const rh)
{
	x *= rh;
	y *= rh;
	z *= rh;
	return *this;
}

// Multipling a vector with a float (not changing the original)
inline vec3 const vec3::operator *(float const rh) const
{
	return vec3((x * rh), (y * rh), (z * rh));
}

// Adding a vector to another (not changing the original)
inline vec3 const vec3::operator +(vec3 const& rh) const
{
	return vec3((x + rh.x), (y + rh.y), (z + rh.z));
}

// Diving a vector by a float (not changing the original)
inline vec3 const vec3::operator /(float rh) const
{
	return vec3((x / rh), (y / rh), (z / rh));
}

// Subtracting one vector from another (not changing the original)
inline vec3 const vec3::operator -(vec3 const& rh) const
{
	return vec3((x - rh.x), (y - rh.y), (z - rh.z));
}

#endif	// __cplusplus

// Functions for C that I did not use
inline floatv vec3default(float3 v_out)
{
	v_out[0] = v_out[1] = v_out[2] = 0.0f;
	return v_out;
}
inline floatv vec3init(float3 v_out, float const xc, float const yc, float const zc)
{
	v_out[0] = xc;
	v_out[1] = yc;
	v_out[2] = zc;
	return v_out;
}
inline floatv vec3copy(float3 v_out, float3 const v_rh)
{
	v_out[0] = v_rh[0];
	v_out[1] = v_rh[1];
	v_out[2] = v_rh[2];
	return v_out;
}

inline floatv vec3add(float3 v_lh_sum, float3 const v_rh)
{
	v_lh_sum[0] += v_rh[0];
	v_lh_sum[1] += v_rh[1];
	v_lh_sum[2] += v_rh[2];
	return v_lh_sum;
}

inline floatv vec3sum(float3 v_sum, float3 const v_lh, float3 const v_rh)
{
	return vec3init(v_sum, (v_lh[0] + v_rh[0]), (v_lh[1] + v_rh[1]), (v_lh[2] + v_rh[2]));
}

// Normalizes the vector into a unit vector
inline vec3 unit_vector(const vec3& rh)
{
	return rh / rh.length();
}

// Calculates the dot product
inline float dot(const vec3& u, const vec3& v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}


#endif	// !_GPRO_VECTOR_INL_
#endif	// _GPRO_VECTOR_H_