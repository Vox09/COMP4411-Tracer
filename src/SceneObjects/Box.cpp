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
	double t1 = 0;
	double t2 = 0;
	if (pointst.empty()) {
		return false;
	}
	else {
		t2 = *(pointst.begin());
		for (list<double>::iterator iter = pointst.begin(); iter != pointst.end(); iter++) {
			if ((*iter) <= t2)
				t1 = *iter;
			else {
				t1 = t2;
				t2 = *iter;
			}
		}
	}

	if (t2 <= RAY_EPSILON) {
		return false;
	}
	else {
		vec3f point;
		if (t1 > RAY_EPSILON) {
			i.obj = this;
			i.t = t1;
			point = r.at(t1);
		}
		else {
			i.obj = this;
			i.t = t2;
			point = r.at(t2);
		}
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
