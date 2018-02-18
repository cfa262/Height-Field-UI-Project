#include "gVector.h"

gVector::gVector(int size)
{
	data = std::vector<double>(size);
	for (std::vector<double>::size_type i = 0; i !=data.size(); i++)
	{
		data[i] = 0.0;
	}
}

gVector::gVector(double d1, double d2)
{
	data = std::vector<double>(2);
	data[0] = d1;
	data[1] = d2;
}

gVector::gVector(double d1, double d2, double d3)
{
	data = std::vector<double>(3);
	data[0] = d1;
	data[1] = d2;
	data[2] = d3;
}

gVector::gVector(double d1, double d2, double d3, double d4)
{
	data = std::vector<double>(4);
	data[0] = d1;
	data[1] = d2;
	data[2] = d3;
	data[3] = d4;
}

int gVector::size() const
{
	return data.size();
}

double gVector::length() const
{
	double squareLength = 0.0;
	for (std::vector<double>::size_type i = 0; i != data.size(); i++)
	{
		squareLength+=(data[i]*data[i]);
	}
	return sqrt(squareLength);
}

double gVector::get(int index) const
{
	assert((index < data.size()) && (index > -1));
	return data[index];

}

void gVector::set(int index, double value)
{
	assert((index < data.size()) && (index > -1));
	data[index] = value;
}

double & gVector::operator[](int index)
{
	//assert((index < data.size()) && (index > -1));
	return data[index];
}

double gVector::operator[](int index) const
{
	return data[index];
}

bool operator==(const gVector & v1, const gVector & v2)
{
	if (v1.size() != v2.size())												//Return false when the vector sizes are different.
		return false;

	bool equal = true;
	for (std::vector<double>::size_type i = 0; i != v1.size(); i++)
	{
		if (abs(v1[i] - v2[i]) > DBL_EPSILON)
			equal = false;
	}
	return equal;
}

bool operator!=(const gVector & v1, const gVector & v2)
{
	if (v1.size() != v2.size())												//Return true when the vector sizes are different.
		return true;

	bool equal = true;
	for (std::vector<double>::size_type i = 0; i != v1.size(); i++)
	{
		if (abs(v1[i] - v2[i]) > DBL_EPSILON)
			equal = false;
	}
	return !equal;
}

gVector operator+(const gVector & v1, const gVector & v2)
{
	assert(v1.size() == v2.size());
	gVector result = gVector(v1.size());
	for (std::vector<double>::size_type i = 0; i != v1.size(); i++)
	{
		result[i] = v1[i] + v2[i];
	}
	return result;
}

gVector operator-(const gVector & v1, const gVector & v2)
{
	assert(v1.size() == v2.size());
	gVector result = gVector(v1.size());
	for (std::vector<double>::size_type i = 0; i != v1.size(); i++)
	{
		result[i] = v1[i] - v2[i];
	}
	return result;
}

double operator*(const gVector & v1, const gVector & v2)
{
	assert(v1.size() == v2.size());
	double result = 0.0;
	for (std::vector<double>::size_type i = 0; i != v1.size(); i++)
	{
		result += v1[i] * v2[i];
	}
	return result;
}

gVector operator*(const gVector & v, const double d)
{
	gVector result = gVector(v.size());
	for (std::vector<double>::size_type i = 0; i != v.size(); i++)
	{
		result[i] = v[i] * d;
	}
	return result;
}

gVector operator*(const double d, const gVector & v)
{
	gVector result = gVector(v.size());
	for (std::vector<double>::size_type i = 0; i != v.size(); i++)
	{
		result[i] = v[i] * d;
	}
	return result;
}

gVector operator/(const gVector & v, const double d)
{
	assert(abs(d) > DBL_EPSILON);
	gVector result = gVector(v.size());
	for (std::vector<double>::size_type i = 0; i != v.size(); i++)
	{
		result[i] = v[i] / d;
	}
	return result;
}

gVector operator^(const gVector & v1, const gVector & v2)
{
	assert(((v1.size() == 2) && (v2.size() == 2))||((v1.size() == 3)&&(v2.size()==3)));				
	if(v1.size()==3)
		return gVector((v1[1] * v2[2]) - (v1[2] * v2[1]), (v1[2] * v2[0]) - (v1[0] * v2[2]), (v1[0] * v2[1]) - (v1[1] * v2[0]));
	else return gVector(0.0, 0.0, (v1[0] * v2[1]) - (v1[1]*v2[0]));
}


