#pragma once
#include <math.h>
#include "Coordinates3D.h"
class RotationalMechanics
{
public:
	/*
		Known
		r = lever Arm - positional point where force will be applied ; This should be different from Actual Radius Covering Circular Motion Path
		pHI = angle at which force is applied to lever Arm
		f = magnitude of force being applied to lever Arm

		Unknown
		τ  = calculating Torque  ( returned by formulated function )
	*/
	float calculatingTorque(float r,float f,float pHI);
	
	/*
		Known
		m = mass of an object
		r = radius : length from pivot to centre

		Unknown
		I = moment of Inertia ( returned by formulated function )
	*/
	float momentOfInertia(float m, float r);

	/*
		Known
		I = Moment of Interia
		τ = Torque ; T
		
		Unknown
		α = constant angular acceleration ( returned by formulated function )
	*/
	float computeConstantAngularAcceleration(float I, float T);

	/*
		Known 
		Omega0 = Initial / Previous angular velocity
		α = constant angular acceleration ; alpha
		t = delta time

		Unknown
		Omega = current angular velocity ( returned by formulated function )
	*/
	float computeAngularVelocity(float omega0,float alpha,float t);

	/*
	Known
	thetha0 = Initial / Previous angular displacement
	Omega0 = Initial or Previous angular velocity
	α = constant angular acceleration ; alpha
	t = delta time 

	Unknown
	theta = current angular displacement ( returned by formulated function )
	*/
	float computeAngularDisplacement(float thetha0,float Omega0, float alpha, float t);

	/*
	Known
	thetha0  = angular displacement in radians
	r = radius ; fix length radius covering circular motion path
	centreOfMotion = (X,Y,0) cordinates pair describing centre around which object rotates technically
	
	Unknown
	updatedObjectPosition = (X,Y,0) latest position computed coordinate  
	*/
	Coordinates3D computeNextObjectPositionAlongCircularPath(float theta0, float r, Coordinates3D centre);
};

