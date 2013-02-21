
// Class to represent a collection of objects in a scene.

#ifndef GROUP_H_
#define GROUP_H_

#include "raycast.h"
#include <vector>

class Group : public Object3D{

  // A vector of pointers to objects
  vector<Object3D*> objects;


public:

  // Default constructor.
  Group(){}

  // Constructor for a group of n objects.
  Group(int n);

  // Destructor.
  ~Group();

  // Insert an object into the array.
  void addObject(int index, Object3D *obj);

  bool intersect(const Ray &r, Hit &h);

};

#endif /* GROUP_H_ */
