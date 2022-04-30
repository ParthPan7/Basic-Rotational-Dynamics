#include "RotationalMechanics.h"
#include <math.h>

#define PI 3.14159265

float RotationalMechanics::calculatingTorque(float r, float f, float pHI)
{
	return r * f * sin(pHI * PI/180);
}

float RotationalMechanics::momentOfInertia(float m, float r)
{
	return m * r * r;
}

float RotationalMechanics::computeConstantAngularAcceleration(float I, float T)
{
	return T / (float) I;
}

float RotationalMechanics::computeAngularVelocity(float omega0, float alpha, float t)
{
	return omega0 + alpha * t;
}

float RotationalMechanics::computeAngularDisplacement(float thetha0, float Omega0, float alpha, float t)
{
	return thetha0 + Omega0 * t + (1 / (float)2) * alpha * t * t;
}

Coordinates3D RotationalMechanics::computeNextObjectPositionAlongCircularPath(float theta0, float r, Coordinates3D centre)
{
	Coordinates3D newPositionalCoordinate;
	float updatedXCoordinate = centre.x + r * cos(theta0);
	float updatedYCoordinate = centre.y + r * sin(theta0);
	newPositionalCoordinate.x = updatedXCoordinate;
	newPositionalCoordinate.y = updatedYCoordinate;
	return newPositionalCoordinate;
}