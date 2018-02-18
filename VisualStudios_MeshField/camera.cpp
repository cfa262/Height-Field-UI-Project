#include "camera.h"

Camera::Camera(float r, float newPhi, float newTheta)
{
	up = gVector(0, 1, 0, 0);
	eye = gVector(0, 0, r, 1);
	phi = newPhi;
	theta = newTheta;
	rot = gMatrix::identityMatrix(4);	
	
	gMatrix thetaRot = 
		gMatrix::rotationMatrix(gVector(0.0, 1.0, 0.0), theta);
	gMatrix phiRot = 
		gMatrix::rotationMatrix(gVector(1.0, 0.0, 0.0), phi);
	rot = thetaRot*phiRot;
}

void Camera::increasePhi(float inc)
{
	phi += inc;
	gMatrix thetaRot = 
		gMatrix::rotationMatrix(gVector(1.0, 0.0, 0.0), theta);
	gMatrix phiRot = 
		gMatrix::rotationMatrix(gVector(0.0, 1.0, 0.0), phi);
	rot = thetaRot*phiRot;
}

void Camera::increaseTheta(float inc)
{
	theta += inc;
	gMatrix thetaRot = 
		gMatrix::rotationMatrix(gVector(1.0, 0.0, 0.0), theta);
	gMatrix phiRot = 
		gMatrix::rotationMatrix(gVector(0.0, 1.0, 0.0), phi);
	rot = thetaRot*phiRot;
}

void Camera::increaseRad(float inc)
{
	eye[2] += inc;
}

const gVector Camera::getEye(){
	return rot * eye;
}

const gVector Camera::getUp(){
	return rot * up;
}