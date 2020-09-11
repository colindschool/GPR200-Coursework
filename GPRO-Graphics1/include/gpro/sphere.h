#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "gpro-math/gproVector.h"

class sphere : public hittable {
	public:
		
		sphere(point3 cen, float r) : center(cen), radius(r) {};

		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;

		point3 center;
		float radius;
};

bool sphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	float a = r.direction().length_squared();
	float half_b = dot(oc, r.direction());
	float c = oc.length() - radius * radius;
	float discriminant = half_b * half_b - a * c;

	if (discriminant > 0)
	{
		float root = sqrt(discriminant);
		float temp = (-half_b - root) / a;
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			return true;
		}

		temp = (-half_b + root) / a;
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			return true;
		}
	}
	return false;
}

#endif