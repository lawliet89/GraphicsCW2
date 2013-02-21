#include "raycast.h"

// Constructor for a group of n objects.
Group::Group(int n) {

  // Resize to create n empty objects
	objects.resize(n);
}

// Destructor.
Group::~Group() {

  for (vector<Object3D*>::iterator it = objects.begin(); it != objects.end(); it++){
	  delete *it;
  }
  // the vector will be destroyed via its destructor
}

// Insert an object into the array.
void Group::addObject(int index, Object3D *obj) {
	objects.at(index) = obj;
}

bool Group::intersect(const Ray &r, Hit &h)
{
	// TODO: Group::intersect
	bool result = false;

	// Let's create a temporary Hit object to get the minimum hit
	Hit temp;

	// Parameters of h to keep track of
	float t = INFINITY;
	Vec3f colour;

	for (vector<Object3D*>::iterator it = objects.begin(); it != objects.end(); it++){
		bool test = (*it) -> intersect(r,temp);
		if (test){	// Intersection found!
			result = true;
			t = min(temp.getT(), t);
			colour = temp.getColor();
		}
	}

	if (result)
		h.set(t, colour);

	return result;

}
