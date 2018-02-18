#pragma once
#include "gVector.h"

class Mesh
{
private:                                        
	float snowCapHeight = 0.0;
	float rows;
	float cols;
	float width;
	float depth;
public:                    
	Mesh(int rows, int cols, float width, float depth);
	virtual ~Mesh();
	int getRows() const;
	int getCols() const;
	float getWidth()const;
	float getDepth()const;
	float getSnowHeight() const;
	void setSnowHeight(float height);
	Mesh* fractalize() const;
	Mesh* subDivide() const;
	gVector getVertexSelected(int row, int col) const;
	//gVector getVertex(int value);
	//void returnVertex(int value, gVector newVertex);
	void setHeight(int row,int col, float height);                                                         
	void setVertex(int row, int col, gVector newVertex);
	void manipulateVertex(int value, float h);
	

	std::vector<std::vector<gVector>*>* meshVertices;  //vector of mesh vertices


};
