#pragma once

#include "gVector.h"
#include "gMatrix.h"

// Simple class for hold face data
class Face{
	private:
		gMatrix points;
	public:
		Face(const gVector& v1, const gVector& v2, const gVector& v3, const gVector& v4):points(3, 4){
			points[0][0] = v1[0];
			points[1][0] = v1[1];
			points[2][0] = v1[2];
			points[0][1] = v2[0];
			points[1][1] = v2[1];
			points[2][1] = v2[2];
			points[0][2] = v3[0];
			points[1][2] = v3[1];
			points[2][2] = v3[2];
			points[0][3] = v4[0];
			points[1][3] = v4[1];
			points[2][3] = v4[2];
		}
		const gMatrix getPoints(){
			return points;
		}

		const void setPoints(gMatrix newPoints)
		{
			points = newPoints;
		}
		const gVector getNormal(){
			gVector r = -1*(points.getCol(1)-points.getCol(0))^(points.getCol(2)-points.getCol(1));
			return r/r.length();
	}
};