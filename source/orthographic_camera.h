// Orthographic camera class.

#ifndef ORTHOGRAPHIC_CAMERA_H_
#define ORTHOGRAPHIC_CAMERA_H_

#include "raycast.h"

class OrthographicCamera : public Camera{

	float size;
	Vec3f centre, direction, up, horizontal;

public:

  // Constructor.
  OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size);

  // Concrete implementation of pure virtual function in the
  // parent class.
  virtual Ray generateRay(Vec2f point);

};

#endif /* ORTHOGRAPHIC_CAMERA_H_ */
