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
	GPRO-Graphics1-TestConsole-main.c/.cpp
	Main entry point source file for a Windows console application.

	Modified by: Colin Deane
	Modified because: Completing the Graphics 1 Lab. Displays two spheres with a gradient background

	Contains code that is an edited version of Peter Shirley's Ray Tracing in One Weekend. Available at: https://raytracing.github.io/books/RayTracingInOneWeekend.html
	Special thanks to Dan Bucketin for providing the framework for the vectors
*/


#include <stdio.h>
#include <stdlib.h>


#include "gpro/mathconstants.h" //Also includes other common headers (e.g. ray.h and gproVector.h)
#include "gpro/hittable_list.h"
#include "gpro/color.h"
#include "gpro/sphere.h"


void testVector()
{
	// test array vector initializers and functions
	float3 av, bv, cv, dv;
	vec3default(av);								// -> a = (0, 0, 0)
	vec3init(bv, 1.0f, 2.0f, 3.0f);					// -> b = (1, 2, 3)
	vec3copy(dv, vec3init(cv, 4.0f, 5.0f, 6.0f));	// -> d = c = (4, 5, 6)
	vec3copy(av, dv);								// a = d			-> a = (4, 5, 6)
	vec3add(dv, bv);								// d += b			-> d = (4 + 1, 5 + 2, 6 + 3) = (5, 7, 9)
	vec3sum(dv, bv, bv);							// d = b + b		-> d = (1 + 1, 2 + 2, 3 + 3) = (2, 4, 6)
	vec3add(vec3sum(dv, cv, bv), av);				// d = c + b + a	-> d = (4 + 1 + 4, 5 + 2 + 5, 6 + 3 + 6) = (9, 12, 15)

#ifdef __cplusplus
	// test all constructors and operators
	vec3 a, b(1.0f, 2.0f, 3.0f), c(cv), d(c);		// default; init; copy array; copy
	a = d;											// assign						-> a = (4, 5, 6)
	d += b;											// add assign					-> d = (5, 7, 9)
	d = b + b;										// sum, init, assign			-> d = (2, 4, 6)
	d = c + b + a;									// sum, init, sum, init, assign	-> d = (9, 12, 15)
#endif	// __cplusplus
}

#include <iostream>


// Gets the color of the ray based on any collisions
color ray_color(const ray& r, const Hittable& world)
{
	//Creates a hit_record to store the hit
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) // If there is a collision
	{
		// Get the normal and white to it then multiply by half
		return (rec.normal + color(1, 1, 1)) * 0.5f;
	}
	//Create the gradient in the background
	vec3 unit_direction = unit_vector(r.direction());
	float t = (unit_direction.y + 1.0f) * 0.5f;
	return (color(1.0f, 1.0f, 1.0f) * (1.0f - t) + (color(0.5f, 0.7f, 1.0f) * t));
	
	
}

int main(int const argc, char const* const argv[])
{
	// Image 

	const float aspect_ratio = 16.0f / 9.0f; // 16:9 aspect ratio
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio); //Maintains aspect ratio

	// World
	Hittable_list world;
	world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5f));			// Create a small sphere at the center of the viewport with a radius of .5
	world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100.0f));	// Create a large sphere super far outside the viewport (-100 y) with a radius of 100

	// Camera
	float viewport_height = 2.0;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0; //Distance between the project plane and the projection point
	
	point3 origin = point3(0, 0, 0);					// Origin of the camera
	vec3 horizontal = vec3(viewport_width, 0, 0);		// Vector for tracking horizontal movement
	vec3 vertical = vec3(0, viewport_height, 0);		// Vector for tracking vertical movement
	point3 lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length); // Calculate the lower left corner of the image

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	// Use this loop to create RGB values for individual pixels going from left-to-right and top-to-bottom
	// R will always be 0 at the far left and 255 at the far right 
	// G will always be 255 at the top and 0 at the bottom
	// B will always be 63 (it is not affected by the loop)
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush; //Report the progress
		for (int i = 0; i < image_width; ++i)
		{
			float u = float(i) / (image_width - 1);									// 'u' will vary from 0 to 1
			float v = float(j) / (image_height - 1);								// 'v' will vary from 0 to 1
			ray r(origin, lower_left_corner + (horizontal * u) + (vertical * v));	// Create a ray that has its origin at the camera origin and it's direction based from the lower left corner
			color pixel_color = ray_color(r, world);								// Color the pixel based on the calculated ray color
			write_color(std::cout, pixel_color);									// Write the color to the screen

			/*OLDER ITERATIONS

			// Create a color for each pixel. The first input is R, the second input is G, the third input is B 
			//color pixel_color(float(i) / (image_width - 1), float(j) / (image_height - 1), 0.25);
			//write_color(std::cout, pixel_color);
			
			// The code below is equivalent to the code above
			
			float r = float(i) / (image_width - 1);
			float g = float(j) / (image_height - 1);
			float b = 0.25;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n'; */
			
		}
	}

	std::cerr << "\nDone.\n";
	system("pause");
}
