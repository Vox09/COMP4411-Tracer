#include <cmath>

#include "light.h"

double DirectionalLight::distanceAttenuation( const vec3f& P ) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


vec3f DirectionalLight::shadowAttenuation( const vec3f& P ) const
{
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.
	ray r(P, -orientation);
	isect i;
	vec3f rst(1, 1, 1);
	while (scene->intersect(r, i)) {
		rst[0] *= i.getMaterial().kt[0];
		rst[1] *= i.getMaterial().kt[1];
		rst[2] *= i.getMaterial().kt[2];
		if (rst == vec3f(0, 0, 0))
			return rst;
		r = ray(r.at(i.t), r.getDirection());
	}
    return rst;
}

vec3f DirectionalLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f DirectionalLight::getDirection( const vec3f& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation( const vec3f& P ) const
{
	// YOUR CODE HERE

	// You'll need to modify this method to attenuate the intensity 
	// of the light based on the distance between the source and the 
	// point P.  For now, I assume no attenuation and just return 1.0
	double a = constant_attenuation_coeff;
	double b = linear_attenuation_coeff;
	double c = quadratic_attenuation_coeff;
	double d = sqrt((position - P).dot(position - P));
	double fbottom = a + b * d + c * d * d;
	if (fbottom == 0)
		return 1.0;
	double f = 1 / fbottom;
	if (f > 1)
		f = 1.0;
	return f;
}

vec3f PointLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f PointLight::getDirection( const vec3f& P ) const
{
	return (position - P).normalize();
}


vec3f PointLight::shadowAttenuation(const vec3f& P) const
{
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.
	ray r(P, getDirection(P));
	isect i;
	vec3f rst(1, 1, 1);
	while (scene->intersect(r, i)) {
		rst[0] *= i.getMaterial().kt[0];
		rst[1] *= i.getMaterial().kt[1];
		rst[2] *= i.getMaterial().kt[2];
		if (rst == vec3f(0, 0, 0))
			return rst;
		r = ray(r.at(i.t), r.getDirection());
	}
    return rst;
}

double AmbientLight::distanceAttenuation(const vec3f& P) const
{
	return 1.0;
}


vec3f AmbientLight::shadowAttenuation(const vec3f& P) const
{
	return vec3f(1, 1, 1);
}

vec3f AmbientLight::getColor(const vec3f& P) const
{
	return color;
}

vec3f AmbientLight::getDirection(const vec3f& P) const
{
	return vec3f(0, 0, 0);
}
