#include "raycast.h"

// TODO: camera


// Constructor with parameters.
OrthographicCamera::OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size):
	centre(centre), direction(direction), size(size)
{
	// Normalise the direction
	this -> direction.Normalize();

	// normalise input up
	up.Normalize();

	cout << "Camera Stats:\nSize: " << size << "\n";
	cout << "Centre: " << this -> centre << "\n";
	cout << "Direction: " << this -> direction << "\n";
	cout << "Provided Up: " << up << "\n";

	// First, let's check if up and direction are normal
	float dotProduct = this->direction.Dot3(up);

	if (!dotProduct){
		cout << "Provided up is normal to direction";
		this -> up = up;	// No further processing required
	}
	else{
		// Consider a line from the centre in the projection direction,
		// and a right-angled triangle which consists of three vertices:
		// the centre, centre + normalised up vector, and a point from the centre in the direction vector
		// that will form the triangle.
		// Then we first calculate the coordinate of the third vertex

		// Note that direction.up (when both are unit) gives the cosine between the vector
		Vec3f base = centre + (this->direction) * ( dotProduct ) ;

		// Now let's find the centre + normalised up vector point
		Vec3f tip = centre + up;

		// Now we can finally find the up vector that is perpendicular to direction
		this -> up = (tip-base);
		this -> up.Normalize();

		cout << "Calculated up: " << this -> up << "\n";
		//cout << this->direction.Dot3(this -> up) << endl;

	}

	// calculate horizontal
	Vec3f::Cross3(horizontal, this -> up, this -> direction);
	horizontal.Normalize();
}


Ray OrthographicCamera::generateRay(Vec2f point)
{
	// Calculate origin on the camera plane
	Vec3f origin(centre);
	origin += horizontal * ( point.x() * size) ;
	origin += up * ( point.y() * size );

	return Ray(direction, origin);

}
