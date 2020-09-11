/*
   Copyright 2020 Colin Deane

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
	ray.h
	This class is for the ray themselves. Stores important variables like the origin and direction of the ray

	This code is an edited version of Peter Shirley's Ray Tracing in One Weekend. Available at: https://raytracing.github.io/books/RayTracingInOneWeekend.html
*/
#pragma once
#ifndef RAY_H
#define RAY_H

#include "gpro-math/gproVector.h"

class ray {
	public:
		ray(){} // Default ctor
		ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}; // Ctor with values

		point3 origin() const { return orig; }	// Get the origin
		vec3 direction() const { return dir; }	// Get the direction

		// Think of the function P(t) = A + tb
		point3 at(float t) const {
			return orig + (dir * t);
		}

		point3 orig;	// Origin of the ray
		vec3 dir;		// Direction of the ray	
};

#endif