#include <cmath>
#include <assert.h>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	// YOUR CODE HERE:
    // Add box intersection code here.
	// it currently ignores all boxes and just returns false.
	vec3f pn1(0, 0, 1), pn2(0, 1, 0), pn3(1, 0, 0);
	list<vec3f> pnormal;
	pnormal.push_back(pn1);
	pnormal.push_back(pn2);
	pnormal.push_back(pn3);
	list<double> pointst;
	vec3f dir = r.getDirection();
	for (list<vec3f>::iterator iter = pnormal.begin(); iter != pnormal.end(); iter++) {
		vec3f pn = *iter;
		if (pn.dot(dir) != 0) {
			double t = -(pn.dot(r.getPosition()) + 0.5) / (pn.dot(dir));
			vec3f point = r.getPosition() + dir * t;
			if ((point[0] <= 0.5 + RAY_EPSILON) && (point[0] >= -0.5 - RAY_EPSILON) && (point[1] <= 0.5 + RAY_EPSILON) && (point[1] >= -0.5 - RAY_EPSILON) && (point[2] <= 0.5 + RAY_EPSILON) && (point[2] >= -0.5 - RAY_EPSILON)) {
				pointst.push_back(t);
			}
			t = -(pn.dot(r.getPosition()) - 0.5) / (pn.dot(dir));
			point = r.getPosition() + dir * t;
			if ((point[0] <= 0.5 + RAY_EPSILON) && (point[0] >= -0.5 - RAY_EPSILON) && (point[1] <= 0.5 + RAY_EPSILON) && (point[1] >= -0.5 - RAY_EPSILON) && (point[2] <= 0.5 + RAY_EPSILON) && (point[2] >= -0.5 - RAY_EPSILON)) {
				pointst.push_back(t);
			}
		}
	}
	double finalt = 0;
	if (pointst.empty()) {
		return false;
	}
	else {
		finalt = *(pointst.begin());
		for (list<double>::iterator iter = pointst.begin(); iter != pointst.end(); iter++) {
			if ((*iter) < finalt)
				finalt = *iter;
		}
	}

	if (finalt <= RAY_EPSILON) {
		return false;
	}
	else {
		i.obj = this;
		i.t = finalt;
		vec3f point = r.at(finalt);
		if (abs(point[0] - 0.5) < RAY_EPSILON) {
			vec3f temp(1, 0, 0);
			i.N = temp;
		}
		else if (abs(point[0] + 0.5) < RAY_EPSILON) {
			vec3f temp(-1, 0, 0);
			i.N = temp;
		}
		else if (abs(point[1] - 0.5) < RAY_EPSILON) {
			vec3f temp(0, 1, 0);
			i.N = temp;
		}
		else if (abs(point[1] + 0.5) < RAY_EPSILON) {
			vec3f temp(0, -1, 0);
			i.N = temp;
		}
		else if (abs(point[2] - 0.5) < RAY_EPSILON) {
			vec3f temp(0, 0, 1);
			i.N = temp;
		}
		else if (abs(point[2] + 0.5) < RAY_EPSILON) {
			vec3f temp(0, 0, -1);
			i.N = temp;
		}
	}
	return true;
}
