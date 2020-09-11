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
	color.h
	A header which stores a function to write out a color

	This code is an edited version of Peter Shirley's Ray Tracing in One Weekend. Available at: https://raytracing.github.io/books/RayTracingInOneWeekend.html
*/
#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "gpro/gpro-math/gproVector.h"

#include <iostream>

void write_color(std::ostream& out, color pixel_color)
{
	//Write the translated [0, 255] value of each color component.
	out << static_cast<int>(255.99 * pixel_color.x) << ' '
		<< static_cast<int>(255.99 * pixel_color.y) << ' '
		<< static_cast<int>(255.99 * pixel_color.z) << '\n';
}

#endif