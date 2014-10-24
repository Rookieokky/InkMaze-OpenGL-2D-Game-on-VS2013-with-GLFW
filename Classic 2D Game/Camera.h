#pragma once

#include <cmath>
#include "Constant.h"
#include <Box2D/Box2D.h>

class Vector3 {

public:
	// vars
	float x, y, z;

	// constructors
	Vector3() {}

	Vector3(float x1, float y1, float z1) {
		x = x1; y = y1; z = z1;
	}

	// vector ops
	void Normalize() {
		float fTemp = 1 / Length();

		x *= fTemp;
		y *= fTemp;
		z *= fTemp;

	}

	inline double Length() const {
		return(sqrt((x * x) + (y * y) + (z * z)));
	}

	//  operators
	Vector3 operator + (const Vector3 & rhs) const {
		return(Vector3(x + rhs.x, y + rhs.y, z + rhs.z));
	}

	Vector3 operator - (const Vector3 & rhs) const {
		return(Vector3(x - rhs.x, y - rhs.y, z - rhs.z));
	}

	Vector3 operator / (float k) const {
		return(Vector3(x / k, y / k, z / k));
	}

	float operator * (const Vector3 & rhs) const {
		// dot product
		return((x * rhs.x) + (y * rhs.y) + (z * rhs.z));
	}

	Vector3 operator *= (const float k) {
		x *= k;
		y *= k;
		z *= k;

		return(*this);
	}

	float & operator [] (int n) {
		// access like an array
		switch (n) {

			case 0: return(x);
			case 1: return(y);
			case 2: return(z);
			default: /* bug out */;

		}
	}

}; // end class


class Camera
{
public:
	Camera(float posX, float posY, float posZ,
		   float viewX, float viewY, float viewZ,
		   float upX, float upY, float upZ);
	~Camera() {}

	// co-ordinates
	Vector3 up, view, pos;

	// movement functions
	void Rotate(float x, float y, float z);
	void Move(float speed);
	void Strafe(float speed);

	// initialize / change the camera's position and view
	void Position(float posX, float posY, float posZ,
				  float viewX, float viewY, float viewZ,
				  float upX, float upY, float upZ);

	b2Vec2 GetPosition2()
	{
		return b2Vec2(pos.x, pos.y);
	}

	void toPosition(b2Vec2 position)
	{
		pos.x = position.x;
		pos.y = position.y;
		view.x = pos.x;
		view.y = pos.y;
	}

	void moveHorizeon(float step)
	{
		pos.x += step;
		view.x += step;
	}

	void moveVertical(float step)
	{
		pos.y += step;
		view.y += step;
	}



	// call glulookat
	void Update();
};

