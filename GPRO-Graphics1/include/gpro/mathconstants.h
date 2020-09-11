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
    mathconstants.h
    This header is important math constants and headers needed for the project to run

    This code is an edited version of Peter Shirley's Ray Tracing in One Weekend. Available at: https://raytracing.github.io/books/RayTracingInOneWeekend.html
*/
#pragma once
#ifndef MATHCONSTANTS_H
#define MATHCONSTANTS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

//Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = float(3.1415926535897932385);

// Utility functions

// This function can turn a number in degrees into radians
inline float degrees_to_radians(float degrees)
{
	return degrees * pi / 180.0f;
}

// Common headers

#include "ray.h"
#include "gpro-math/gproVector.h"

#endif