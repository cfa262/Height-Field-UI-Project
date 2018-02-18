
#include "gMatrix.h"

#define PI 3.14

gMatrix::gMatrix(int x)
{
	data = std::vector<gVector>(x);
	for (std::vector<gVector>::size_type i = 0; 
		i != data.size(); i++)
	{
		data[i] = gVector(x);
	}
}

gMatrix::gMatrix(int r, int c)
{
	data = std::vector<gVector>(r);
	for (std::vector<gVector>::size_type i = 0; 
		i != data.size(); i++)
	{
		data[i] = gVector(c);
	}
}

gMatrix::~gMatrix()
{
}

int gMatrix::rows() const
{
	return data.size();
}

int gMatrix::cols() const
{
	return data[0].size();
}

bool gMatrix::isSquare() const
{
	return (rows() == cols());
}

double gMatrix::get(int r, int c) const
{
	return data[r][c];
}

gVector gMatrix::getRow(int r) const
{
	return data[r];
}

gVector gMatrix::getCol(int c) const
{
	gVector v = gVector(data.size());
	for (std::vector<double>::size_type i = 0; 
		i != v.size(); i++)
	{
		v[i] = data[i][c];
	}
	return v;
}

void gMatrix::set(int r, int c, double value)
{
	data[r][c] = value;
}

gVector & gMatrix::operator[](int r)
{
	return data[r];
}

gVector gMatrix::operator[](int r) const
{
	return data[r];
}

gMatrix gMatrix::transpose() const
{
	gMatrix v = gMatrix(cols(), rows());
	for (std::vector<gVector>::size_type i = 0; i != v.rows(); i++)
	{
		v[i] = getCol(i);
	}
	return v;
}


gMatrix gMatrix::subMatrix(int r1, int c1, int r2, int c2)
{
	gMatrix v = gMatrix(r2 - r1 + 1, c2 - c1 + 1);
	for (int i = r1; i < r2 + 1; i++)
	{
		for (int j = c1; j < c2; j++)
		{
		v[i - r1][j - c1] = data[i][j];
		}
	}
	return v;
}



bool operator==(const gMatrix & m1, const gMatrix & m2)
{
	if ((m1.rows() != m2.rows()) || (m1.cols() != m2.cols()))
		return false;
	else 
	{
		bool v = false;
		for (int i = 0; i < m1.rows(); i++)
		{
			if (m1[i] != m2[i])
				v = false;
		}
		return v;
	}
}

bool operator!=(const gMatrix & m1, const gMatrix & m2)
{
	if (m1 == m2)
		return false;
	else
		return true;
}

gMatrix operator+(const gMatrix & m1, const gMatrix & m2)
{
	gMatrix v = gMatrix(m1.rows(), m1.cols());
	for (int i = 0; i < m1.rows(); i++)
	{
		v[i] = m1[i] + m2[i];
	}
	return v;
}

gMatrix operator-(const gMatrix & m1, const gMatrix & m2)
{
	gMatrix v = gMatrix(m1.rows(), m1.cols());
	for (int i = 0; i < m1.rows(); i++)
	{
		v[i] = m1[i] - m2[i];
	}
	return v;
}

gMatrix operator*(const gMatrix & m1, const gMatrix & m2)
{
	gMatrix v = gMatrix(m1.rows(), m2.cols());
	for (int i = 0; i < v.rows(); i++)
		for (int j = 0 ;j< v.cols(); j++)
			v[i][j] = m1[i] * m2.getCol(j);
	return v;
}

gVector operator*(const gVector & v, const gMatrix & m)
{
	gVector z = gVector(m.cols());
	for (int i = 0; i < v.size(); i++)
	{
		z[i] = v*m.getCol(i);
	}
	return z;
}

gVector operator*(const gMatrix & m, const gVector & v)
{
	gVector z = gVector(m.rows());
	for (int i = 0; i < v.size(); i++)
	{
		z[i] = v*m[i];
	}
	return z;
}

gMatrix operator*(const gMatrix & m, const double d)
{
	gMatrix v = m;
	for (int i = 0; i < m.rows(); i++)
	{
		v[i] = v[i] * d;
	}
	return v;
}

gMatrix operator*(const double d, const gMatrix & m)
{
	gMatrix v = m;
	for (int i = 0; i < m.rows(); i++)
	{
		v[i] = v[i] * d;
	}
	return v;
}

gMatrix operator/(const gMatrix & m, const double d)
{
	gMatrix v = m;
	for (int i = 0; i < m.rows(); i++)
	{
		v[i] = v[i] / d;
	}
	return v;
}

gMatrix gMatrix::rotationMatrix(double rotate2D)
{
	gMatrix v= gMatrix(3,3);
	v[0] = gVector(cos(degToRad(rotate2D)),-sin(degToRad(rotate2D)),0.0);
	v[1] = gVector(sin(degToRad(rotate2D)), cos(degToRad(rotate2D)), 0.0);
	v[2] = gVector(0.0, 0.0, 1.0);
	return v;
}

gMatrix gMatrix::rotationMatrix(const gVector & v, double rotate3D)
{
	gMatrix z = gMatrix(4);
	gVector normalized = v / v.length();
	double radAngle = degToRad(rotate3D);
	double sine = sin(radAngle);
	double cosine = cos(radAngle);
	double tangent = 1 - cosine;
	z[0] = gVector(tangent*normalized[0] * normalized[0] + cosine,tangent*normalized[0] * normalized[1] - sine*normalized[2],tangent*normalized[0] * normalized[2] + sine*normalized[1],0.0);
	z[1] = gVector(tangent*normalized[0] * normalized[1] + sine*normalized[2],tangent*normalized[1] * normalized[1] + cosine,tangent*normalized[1] * normalized[2] - sine*normalized[0],0.0);
	z[2] = gVector(tangent*normalized[0] * normalized[2] - sine*normalized[1],tangent*normalized[1] * normalized[2] + sine*normalized[0],tangent*normalized[2] * normalized[2] + cosine,0.0);
	z[3] = gVector(0, 0, 0, 1);
	return z;

}

gMatrix gMatrix::scaleMatrix(const gVector & v)
{
	gMatrix z = gMatrix(v.size()+1);
	for (int i = 0; i < v.size(); i++)
	{
		z[i][i] = v[i];
	}
	z[z.rows() - 1][z.cols() - 1] = 1.0;
	return z;
}

gMatrix gMatrix::translationMatrix(const gVector & v)
{
	gMatrix z = gMatrix(v.size() + 1);
	for (int i = 0; i < v.size(); i++)
	{
		z[i][z.cols()-1] = v[i];
	}
	z[z.rows() - 1][z.cols() - 1] = 1.0;
	return z;
}

gMatrix gMatrix::identityMatrix(int s)
{
	gMatrix v = gMatrix(s);
	for (int i = 0; i < s; i++)
	{
		v[i][i] = 1;
	}
	return v;
}


double radToDeg(double rad)
{
	return rad*180.0/PI;
}

double degToRad(double deg)
{
	return deg*PI/180.0;
}


