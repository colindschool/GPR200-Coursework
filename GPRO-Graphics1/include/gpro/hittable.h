#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
	point3 p;
	vec3 normal;
	float t;
	bool front_face;

	inline void set_face_normal(const ray& r, const vec3& outward_normal) 
	{
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

class hittable {
	public:
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif