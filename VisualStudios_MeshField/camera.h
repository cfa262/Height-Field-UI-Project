#include <math.h>
#include "gMatrix.h"
#include "gVector.h"
#include <iostream>

// A class for storing camera transforms
class Camera{

	private:
		gMatrix rot;			
		float phi;				
		float theta;			
		gVector up;				
		gVector eye;			
	public:
		Camera(float r, float phi, float theta); 
		void increasePhi(float inc);		// increase the phi angle
		void increaseTheta(float inc);		// increase the theta angle
		void increaseRad(float inc);		// increase the radius
		const gVector getEye();		// get the current eye position
		const gVector getUp();		// get the current up vector
};