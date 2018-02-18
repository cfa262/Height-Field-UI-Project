#ifndef G_MATRIX
#define G_MATRIX
#define PI 3.14

#include <assert.h>
#include <vector>
#include "gVector.h"

using namespace std;

/********************************************
*   MATRIX CLASS
*   - Note.  Error check to make sure the
*     operations make sense.  (ie, comparing
*     the size of the rows and cols, where
*     appropriate.)
*********************************************/

class gMatrix{
	private:
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Instance Variables (1pt).
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector<gVector> data;				/// An array that stores the rows (or columns)						(1pt)
	public:
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Constructor/Destructor (2pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		gMatrix(){}
		gMatrix(int square);				/// Creates a square matrix of size 'square'						(1pt)
		gMatrix(int r, int c);				/// Creates a matrix with rows 'r' and columns 'c'					(1pt)
		~gMatrix();							/// Deconstructor (don't worry about)			
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Getters/Setters (9pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int rows() const;						/// returns:  the number of rows								(1pt)
		int cols() const;						/// returns:  the number of cols								(1pt)
		bool isSquare() const;					/// returns:  returns true if the matrix is square				(1pt)
		double get(int r, int c) const;			/// returns:  the cth value in the rth row.						(1pt)
		gVector getRow(int r) const;			/// returns:  a vector containing the 'r'th row values			(1pt)
		gVector getCol(int c) const;			/// returns:  a vector containing the 'c'th column values		(1pt)
		void set(int r, int c, double value);	/// sets the cell at (r, c) to value							(1pt)
		gVector& operator[] (int r);			/// returns a reference to the 'r'th row (or column)			(1pt)
		gVector operator[] (int r) const;		/// returns a copy of the 'r'th row (or column)					(1pt)
		

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Matrix Cell Operations (20pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		gMatrix transpose() const;							/// Returns the transpose of the current matrix		(4pt)
		gMatrix inverse() const;							/// Returns the inverse of the current matrix (if	(6pt)
															//	it's square and has 3 or less rows)
		gMatrix subMatrix(int r1, int c1, int r2, int c2);	/// Returns a subMatrix with spans from cell		(4pt)
															//	(r1,c1) to cell (r2,c2) inclusive
		double determinant() const;							/// Returns the determinanet of the current matrix	(6pt)
															//	(if it's square and has 3 or less rows)
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Boolean Friend Functions (2pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		friend bool operator== (const gMatrix& m1, const gMatrix& m2);		/// m1[i][j] == m2[i][j]			(1pt)
		friend bool operator!= (const gMatrix& m1, const gMatrix& m2);		/// m1[i][j] == m2[i][j]			(1pt)
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Matrix Math Operations (13pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		friend gMatrix operator+ (const gMatrix& m1, const gMatrix& m2);	/// matrix addition: m1 + m2		(2pt)
		friend gMatrix operator- (const gMatrix& m1, const gMatrix& m2);	/// matrix subtraction: m1 - m2		(2pt)
		friend gMatrix operator* (const gMatrix& m1, const gMatrix& m2);	/// dot product: m1 * m2			(2pt)
		friend gVector operator* (const gVector& v,  const gMatrix& m);		/// dot product: v * m				(2pt)
		friend gVector operator* (const gMatrix& m,  const gVector& v);		/// dot product: m * v				(2pt)
		friend gMatrix operator* (const gMatrix& m,  const double d);		/// scalar product: m * d			(1pt)
		friend gMatrix operator* (const double d,    const gMatrix& m);		/// scalar product: d * m			(1pt)
		friend gMatrix operator/ (const gMatrix& m,  const double d);		/// scalar division: m * d			(1pt)
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Static Matrix Generating Functions (13pt)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static gMatrix rotationMatrix(double rotate2D);						/// Returns a 2-D HOMOGENEOUS		(4pt)
																			//  rotation matrix	
		static gMatrix rotationMatrix(const gVector& v, double rotate3D);	/// Returns a 3-D HOMOGENEOUS		(4pt)
																			//  rotation matrix	around an axis v
		static gMatrix scaleMatrix(const gVector& v);						/// Returns a nxn scale matrix		(4pt)
																			//  determined by v.  v is a vector 
																			//  of scale coefficients
		static gMatrix translationMatrix(const gVector& v);					/// Returns a nxn translation matrix(4pt)
																			//  determined by v					
		static gMatrix identityMatrix(int size);							/// Returns a size x size identity	(2pt)
																			//  matrix
};

/// HELPER FUNCTIONS FOR ME.  NOT PROVIDED
double radToDeg(double rad);
double degToRad(double deg);

#endif