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
	sphere.h
	A header which stores a sphere class. Has a center point a radius so it can be placed in a 3d plane
	Uses discriminant and the quadratic formula to calculate hit points

	This code is an edited version of Peter Shirley's Ray Tracing in One Weekend. Available at: https://raytracing.github.io/books/RayTracingInOneWeekend.html
*/
#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "gpro-math/gproVector.h"

class Sphere : public Hittable {
	public:
		Sphere() { radius = 0; }; // Default ctor
		Sphere(point3 cen, float r) : center(cen), radius(r) {}; // Ctor with values

		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override; // Override the hit function from Hittable

		point3 center;	// Center of the sphere
		float radius;	// Radius of the sphere
};

// Check to see if a ray hit a sphere object
bool Sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
	// Calculate the discriminate from the ray
	vec3 oc = r.origin() - center;
	float a = r.direction().length_squared();
	float half_b = dot(oc, r.direction());
	float c = oc.length_squared() - radius * radius;
	float discriminant = half_b * half_b - a * c;

	// If the discriminant is positive (2 real solutions)
	if (discriminant > 0)
	{
		// Use the quadratic formula to find points of interesection
		float root = sqrt(discriminant);
		float temp = (-half_b - root) / a;
		if (temp < tmax && temp > tmin) // If the answer to the quadratic formula is within acceptable hit bounds
		{
			//Gather information about the hit
			rec.t = temp;										// t in P(t) = A + tb
			rec.p = r.at(rec.t);								// Get the point of collision 
			vec3 outward_normal = (rec.p - center) / radius;	// Calculate the normal
			rec.set_face_normal(r, outward_normal);				// See if it is intersecting from inside or outside
			return true;
		}

		temp = (-half_b + root) / a;
		if (temp < tmax && temp > tmin) // If the answer to the quadratic formula is within acceptable hit bounds
		{
			//Gather information about the hit
			rec.t = temp;										// t in P(t) = A + tb
			rec.p = r.at(rec.t);								// Get the point of collision 
			vec3 outward_normal = (rec.p - center) / radius;	// Calculate the normal
			rec.set_face_normal(r, outward_normal);				// See if it is intersecting from inside or outside
			return true;
		}
	}
	return false;
}

#endif