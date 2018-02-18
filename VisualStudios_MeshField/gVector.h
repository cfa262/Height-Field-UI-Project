#ifndef G_VECTOR
#define G_VECTOR

#include <assert.h>
#include <math.h>
#include <vector>

/********************************************
*   VECTOR CLASS
*   - Note.  Error check to make sure the
*     operations make sense.  (ie. checking
*     vectors have the same length)
*********************************************/

class gVector{
	private:
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Instance Variables (1pt).
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		std::vector<double> data;			/// stores the values of the vector 
	public:
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Constructor/Destructor (4pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		gVector(){}
		gVector(int size);										/// Creates gVectors of a specified size(1pt)
		gVector(double d1, double d2);							/// Creates gVectors of size 2			(1pt)
		gVector(double d1, double d2, double d3);				/// Creates gVectors of size 3			(1pt)
		gVector(double d1, double d2, double d3, double d4);	/// Creates gVectors of size 4			(1pt)
		~gVector(){}											/// Destructor							(Leave Empty)
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Getters/Setters (7pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		int size() const;							/// Returns the number of elements in the vector	(1pt)
		double length() const;						/// Calculates the length of the vector				(2pt)
		double get(int index) const;				/// Returns the value at the index of the vector	(1pt)
		void set(int index, double value);			/// Sets the specified index in the vector to value	(1pt)
		double& operator[] (int index);				/// Returns a reference to the specified index.		(1pt)
		double operator[] (int index) const;		/// Returns the value at the specified index.		(1pt)
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//  Boolean friends functions (5pt)
		//  Use the equality testing algorithms discussed in the reading/lecture						(3pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		friend bool operator== (const gVector& v1, const gVector& v2);		/// Tests v1[i] == v2[i]	(1pt)
		friend bool operator!= (const gVector& v1, const gVector& v2);		/// Tests v1[i] != v2[i]	(1pt)
		
		/// /////////////////////////////////////////////////////////////////////////////////////////////////////
		// Vector math functions (13pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		friend gVector operator+ (const gVector& v1, const gVector& v2);	/// Vector Addition			(2pt)
		friend gVector operator- (const gVector& v1, const gVector& v2);	/// Vector Subtraction		(2pt)
		friend double  operator* (const gVector& v1, const gVector& v2);	/// Dot Product				(2pt)
		friend gVector operator* (const gVector& v,  const double d);		/// Scalar Multiplication	(1pt)
		friend gVector operator* (const double d,    const gVector& v);		/// Scalar Multiplication	(1pt)
		friend gVector operator/ (const gVector& v,  const double d);		/// Scalar Division			(1pt)
		friend gVector operator^ (const gVector& v1, const gVector& v2);	/// Cross Product			(4pt)
};

#endif

