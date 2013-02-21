#include "raycast.h"

// TODO: sphere class

// Sphere intersection: http://www.csee.umbc.edu/~olano/435f02/ray-sphere.html

Sphere::Sphere(): radius(0)
{

}



Sphere::Sphere(Vec3f centre, float radius, Vec3f colour):
		centre(centre), radius(radius), colour(colour)
{

}
bool Sphere::intersect(const Ray &r, Hit &h)
{
	// See notes Lecture 10 slide 12 for the "normalised" version of the equation we are solving
	// The quadratic equation is t^2 + bt + c
	float b,c;	// the coefficients for the quadratic equation we are trying to solve
	Vec3f delta = r.getOrigin()-centre;
	// Now let's calculate the coefficients
	// a = 1.f;
	b = r.getDirection().Dot3( delta );
	c = delta.Length() * delta.Length() - radius*radius;

	// Now let's calculate the determinant
	float determinant = b*b-c;

	// No real roots = no intersection
	if (determinant < 0)
		return false;

	//Real roots? Find intersection -- we want the smaller one, but still positive
	float t1 = (-1*b + sqrt(determinant));
	float t2 = (-1*b - sqrt(determinant));

	if (t1 < 0 ) t1 = INFINITY;	// behind camera plane
	if (t2 < 0 ) t2 = INFINITY;	// behind camera plane

	if (t1 == INFINITY && t2 == INFINITY)
		return false;	// sphere is completely behind camera plane

	h.set( min (t1, t2) , colour);

	return true;
}

// Getters and Setters
const Vec3f& Sphere::getCentre() const {
	return centre;
}

void Sphere::setCentre(const Vec3f& centre) {
	this->centre = centre;
}

const Vec3f& Sphere::getColour() const {
	return colour;
}

void Sphere::setColour(const Vec3f& colour) {
	this->colour = colour;
}

float Sphere::getRadius() const {
	return radius;
}

void Sphere::setRadius(float radius) {
	this->radius = radius;
}

