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
	hittable.h
	A header which stores a class which hittable objects need. It stores important variables like if the ray is intersecting from the inside or outside of an object.
	Also stores a abstract function for if something is hit, which is overriden by various other classes

	This code is an edited version of Peter Shirley's Ray Tracing in One Weekend. Available at: https://raytracing.github.io/books/RayTracingInOneWeekend.html
*/
#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
	point3 p;					// Point of intersenction
	vec3 normal;				// Vector that is perpendicular to the surface at the point of intersection
	float t = 0.0f;				// the variable t in the function P(t) = A + tb
	bool front_face = false;	// Whether the ray is hitting the front face

	inline void set_face_normal(const ray& r, const vec3& outward_normal) 
	{
		// Uses dot to determine if the front face is outward from the surface
		front_face = dot(r.direction(), outward_normal) < 0;
		if (front_face)
		{
			normal = outward_normal;
		}
		else
		{
			vec3 zero(0.0f, 0.0f, 0.0f);
			normal =  zero-outward_normal;
		}
	}
};

// Set up the abstract hit function
class Hittable {
	public:
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif