#include "ray.h"
#include "material.h"
#include "light.h"

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
vec3f Material::shade( Scene *scene, const ray& r, const isect& i ) const
{
	// YOUR CODE HERE

	// For now, this method just returns the diffuse color of the object.
	// This gives a single matte color for every distinct surface in the
	// scene, and that's it.  Simple, but enough to get you started.
	// (It's also inconsistent with the phong model...)

	// Your mission is to fill in this method with the rest of the phong
	// shading model, including the contributions of all the light sources.
    // You will need to call both distanceAttenuation() and shadowAttenuation()
    // somewhere in your code in order to compute shadows and light falloff.
	vec3f P = r.getPosition() + r.getDirection() * i.t;
	vec3f Ia;
	for (list<Light*>::const_iterator iter = scene->beginLights(); iter != scene->endLights(); iter++) {
		int id = (*iter)->id();
		if (id == 2) {
			Ia = (*iter)->getColor(P);
			break;
		}
	}
	double ns = shininess * 128;
	vec3f Iphong = ke + vec3f(ka[0]*Ia[0], ka[1]*Ia[1], ka[2]*Ia[2]);
	for (list<Light*>::const_iterator iter = scene->beginLights(); iter != scene->endLights(); iter++) {
		int id = (*iter)->id();
		vec3f intensity = (*iter)->getColor(P);
		if (id != 2) {
			vec3f Idiffuse = prod(kd, intensity);// vec3f(kd[0] * intensity[0], kd[1] * intensity[1], kd[2] * intensity[2]);
			double nl = i.N.dot((*iter)->getDirection(P).normalize());
			if (nl < 0)
				nl = 0;
			Idiffuse *= nl;
			
			vec3f Ispecular = prod(ks, intensity);// vec3f(ks[0] * intensity[0], ks[1] * intensity[1], ks[2] * intensity[2]);
			vec3f Ldir = ((*iter)->getDirection(P)).normalize();
			double LN = Ldir.dot(i.N) * 2;
			vec3f LNN = i.N;
			LNN *= LN;
			vec3f R = LNN - Ldir;
			vec3f V = -r.getDirection().normalize();
			double VR = V.dot(R);
			if (VR < 0)
				VR = 0;
			double VRns = pow(VR, ns);
			Ispecular *= VRns;

			vec3f disatte = (Idiffuse + Ispecular) * ((*iter)->distanceAttenuation(P));
			vec3f shaatte = (*iter)->shadowAttenuation(P);
			Iphong = Iphong + prod(disatte, shaatte);
		}
	}
	return Iphong;
}
