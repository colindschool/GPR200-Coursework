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
	hittable_list.h
	This class is for keeping track of hittable objects. It uses shared pointers to keep track of all the objects in the program

	This code is an edited version of Peter Shirley's Ray Tracing in One Weekend. Available at: https://raytracing.github.io/books/RayTracingInOneWeekend.html
*/
#pragma once
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Hittable_list : public Hittable {
	public:
		Hittable_list() {};	// Default ctor
		Hittable_list(shared_ptr<Hittable>object) { add(object); } // Ctor that adds to the vector

		void clear() { objects.clear(); }	// Clear the object vector
		void add(shared_ptr<Hittable> object) { objects.push_back(object); } //Add an object to the object vector

		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;	// Override the hit function from Hittable

		std::vector<shared_ptr<Hittable>> objects;	// Vector for storing hittable objects
};

// Check to see if a ray hit something in the hittable list
bool Hittable_list::hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
	hit_record temp_rec;	// Create a temporary hit_record
	bool hit_anything = false;
	float closest_so_far = tmax;	// Closest object so far

	// Loop through all the objects in the Hittable_list
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->hit(r, tmin, closest_so_far, temp_rec)) // See if the ray hit that object
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	// Return true/false based on if it hit anything
	return hit_anything;
}

#endif