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
	Modified because: Completing the Graphics 1 Lab
*/


#include <stdio.h>
#include <stdlib.h>


#include "gpro/gpro-math/gproVector.h"
#include "gpro/color.h"
#include "gpro/ray.h"


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

color ray_color(const ray& r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (1.0f + unit_direction.y);
	return (color(1.0f,1.0f,1.0f) * (1 - t) + color(0.5f, 0.7f, 1.0f) * t);
	
}

int main(int const argc, char const* const argv[])
{
	//testVector();

	//printf("\n\n");

	// Image 

	const float aspect_ratio = 16.0f / 9.0f;
	const int image_width = 256;
	const int image_height = 256;

	// Camera
	float viewport_height = 2.0;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0;
	
	point3 origin = point3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0);
	point3 lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);

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
			float u = float(i) / (image_width - 1);
			float v = float(j) / (image_height - 1);
			ray r(origin, lower_left_corner + (horizontal * u) + (vertical * v) - origin);
			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);


			// Create a color for each pixel. The first input is R, the second input is G, the third input is B 
			//color pixel_color(float(i) / (image_width - 1), float(j) / (image_height - 1), 0.25);
			//write_color(std::cout, pixel_color);
			
			// The code below is equivalent to the code above
			
			/*float r = float(i) / (image_width - 1);
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
