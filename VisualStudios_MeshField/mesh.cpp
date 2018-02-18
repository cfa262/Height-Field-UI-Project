#include "mesh.h"

Mesh::Mesh(int r, int c, float w, float d)
{	
	this->meshVertices = new std::vector<std::vector<gVector>*>();

	for (int i = 0; i <= r; i++)
	{
		std::vector<gVector>* vec1 = new std::vector<gVector>();
		float depth = d/2.0f;
		float row = r*1.0f;
		float z = d*(i/(row))-(depth);
		for (int j = 0; j <= c; j++)
		{
			float y = 0;
			float u = 0.0;
			float width = w/2.0f;
			float col = c*1.0f;
			float x = w*(j/(col))-(width);
			vec1->push_back(gVector(x, y, z, u));
		}
		this->meshVertices->push_back(vec1);
	}
	this->width = w;
	this->depth = d;
}

Mesh::~Mesh()
{
}

int Mesh::getRows() const
{
	return this->meshVertices->size();
}

int Mesh::getCols() const
{
	return this->meshVertices->at(0)->size();
}

float Mesh::getWidth()const
{
	return this->width;
}

float Mesh::getDepth()const
{
	return this->depth;
}

float Mesh::getSnowHeight() const
{
	return this->snowCapHeight;
}

void Mesh::setSnowHeight(float height)
{
	this->snowCapHeight = height;
}


gVector Mesh::getVertexSelected(int row, int col) const
{
	return this->meshVertices->at(row)->at(col);
}

void Mesh::setHeight(int row, int col, float h)
{
	this->meshVertices->at(row)->at(col)[1] = h;
}

void Mesh::setVertex(int row, int col, gVector vert)
{
	this->meshVertices->at(row)->at(col) = vert;
}
void Mesh::manipulateVertex(int value, float h) {
	//changes the value from vertexSlider in window
	int t = this->getRows()*this->getCols();
	
	int row = 0;
	int col = 0;
	if (value != 0) {
		row = t%value;
		col = t/value;
	}
	setHeight(row, col, h);
}

//gVector Mesh::getVertex(int value) 
//{
//	//returns vector using int value from list Widget
//	/*int row = depth%value;
//	int col = depth/value;*/
//	//return getVertexSelected(row, col);
//	return ;
//}
//void Mesh::returnVertex(int value, gVector vert) {
//	//place vertex back into vectorList
//	/*int row = depth%value;
//	int col = depth/value;*/
//	//setVertex(row, col, vert);
//}

Mesh* Mesh::fractalize() const
{
	int newMeshRow = (this->getRows()*2)-2;
	int newMeshCol = (this->getCols()*2)-2;
	Mesh* fractalMesh = new Mesh(newMeshRow, newMeshCol, this->getWidth(), this->getDepth());
	//for loop to get all the vertices from this mesh to new fractalMesh
	for (int i = 0, thisRow = 0; i < fractalMesh->getRows(); i += 2, thisRow++)
	{
		for (int j = 0, thisCol = 0; j < fractalMesh->getCols(); j += 2, thisCol++)
		{
			gVector newVert = this->getVertexSelected(thisRow, thisCol);
			fractalMesh->setVertex(i, j, newVert);
		}
	}

	gVector vec1 = this->getVertexSelected(0, 0);
	gVector vec2 = this->getVertexSelected(0, 1);
	float x = vec2[0]-vec1[0];
	float y = vec2[2]-vec1[2];
	float z = sqrt(x*x + y*y);

	//creates new mesh values and gives random height
	for (int i = 0; i < fractalMesh->getRows(); i += 2)
	{
		for (int j = 1; j < fractalMesh->getCols(); j += 2)
		{
			float translate = ((float)rand()/(float)RAND_MAX)*z-(z/2.0f);
			gVector v1 = fractalMesh->getVertexSelected(i, j-1);
			gVector v2 = fractalMesh->getVertexSelected(i, j+1);
			fractalMesh->setVertex(i, j, gVector((v1[0] + v2[0])/2.0f,(v1[1] + v2[1])/2.0f +translate, (v1[2] + v2[2])/2.0f, 1.0));
		}
	}
	for (int i = 1; i < fractalMesh->getRows(); i += 2)
	{
		for (int j = 0; j < fractalMesh->getCols(); j++)
		{
			float translate = ((float)rand()/(float)RAND_MAX)*z-(z/2.0f);
			gVector v1 = fractalMesh->getVertexSelected(i-1, j);
			gVector v2 = fractalMesh->getVertexSelected(i+1, j);
			fractalMesh->setVertex(i, j, gVector((v1[0] + v2[0])/2.0f, (v1[1] + v2[1])/2.0f +translate, (v1[2] + v2[2])/2.0f, 1.0));
		}
	}
	return fractalMesh;
}

Mesh* Mesh::subDivide() const
{

	int newMeshRow = (this->getRows() * 2) - 2;
	int newMeshCol = (this->getCols() * 2) - 2;
	Mesh* subMesh = new Mesh(newMeshRow, newMeshCol, this->getWidth(), this->getDepth());
                 
	for (int i = 0, thisRow = 0; i < subMesh->getRows(); i += 2, thisRow++)
	{
		for (int j = 0, thisCol = 0; j < subMesh->getCols(); j += 2, thisCol++)
		{
			subMesh->setVertex(i, j, this->getVertexSelected(thisRow, thisCol));
		}
	}
	//new vertices are created
	for (int i = 1; i < subMesh->getRows(); i += 2)
	{
		for (int j = 1; j < subMesh->getCols(); j += 2)
		{
			float faces = 4.0f;
			gVector newVector;
			gVector a = subMesh->getVertexSelected(i - 1, j - 1);
			gVector b = subMesh->getVertexSelected(i + 1, j - 1);
			gVector c = subMesh->getVertexSelected(i + 1, j + 1);
			gVector d = subMesh->getVertexSelected(i - 1, j + 1);
			newVector = a;
			newVector = newVector + b;
			newVector = newVector + c;
			newVector = newVector + d;
			newVector = newVector / faces;
			subMesh->setVertex(i, j, newVector);
		}
	}

	//creates mesh vertices using mesh edges
	for (int i = 0; i < subMesh->getRows(); i += 2)
	{
		for (int j = 1; j < subMesh->getCols(); j += 2)
		{
			
			gVector newVector;
			newVector = subMesh->getVertexSelected(i, j-1);
			newVector = newVector + subMesh->getVertexSelected(i, j+1);

			float value = 2.0f;
			if (i > 0){
				newVector = newVector + subMesh->getVertexSelected(i-1, j);
				value++;
			}
			int highest = subMesh->getRows() - 1;
			if (i < highest){
				newVector = newVector + subMesh->getVertexSelected(i+1, j);
				value++;
			}
			newVector = newVector/value;
			subMesh->setVertex(i, j, newVector);
		}
	}

	for (int i = 1; i < subMesh->getRows(); i += 2)
	{
		for (int j = 0; j < subMesh->getCols(); j += 2)
		{
			
			gVector newVector;
			newVector = subMesh->getVertexSelected(i - 1, j);
			newVector = newVector + subMesh->getVertexSelected(i+1, j);

			float value = 2.0f;
			if (j > 0){
				newVector = newVector + subMesh->getVertexSelected(i, j-1);
				value++;
			}
			int highest = subMesh->getCols() - 1;
			if (j < highest){
				newVector = newVector + subMesh->getVertexSelected(i, j+1);
				value++;
			}
			newVector = newVector/value;
			subMesh->setVertex(i, j, newVector);
		}
	}

    //change updated vertices
	for (int i = 0, thisRow = 0; i < subMesh->getRows(); i += 2, thisRow++)
	{
		for (int j = 0, thisCol = 0; j < subMesh->getRows(); j += 2, thisCol++)
		{
			gVector vectorAvg = gVector(0, 0, 0, 0);
			int highestRow = subMesh->getRows() - 1;
			int highestCol = subMesh->getCols() - 1;
			float value = 0;
			if (i > 0 && j > 0){
				vectorAvg = vectorAvg + subMesh->getVertexSelected(i-1, j-1);
				value++;
			}

			if (i > 0 && j < highestCol){
				vectorAvg = vectorAvg + subMesh->getVertexSelected(i-1, j+1);
				value++;
			}
			if (i < highestRow && j > 0){
				vectorAvg = vectorAvg + subMesh->getVertexSelected(i+1, j-1);
				value++;
			}
			if (i < highestRow && j < highestCol){
				vectorAvg = vectorAvg + subMesh->getVertexSelected(i+1, j+1);
				value++;
			}
			vectorAvg = vectorAvg/value;
			float m = 2.0f;
			float val = 0.0;
			gVector vecE = gVector(0, 0, 0, 0);
			int highRow = subMesh->getRows() - 1;
			int highCol = subMesh->getCols() - 1;
			gVector mVector = this->getVertexSelected(thisRow, thisCol);
			if (i > 0) {
				gVector midPoint = (mVector + this->getVertexSelected(thisRow - 1, thisCol))/m;
				vecE = vecE + midPoint;
				val++;
			}
			if (i < highRow){
				gVector midPoint = (mVector + this->getVertexSelected(thisRow + 1, thisCol))/m;
				vecE = vecE + midPoint;
				val++;
			}
			if (j > 0){
				gVector midPoint = (mVector + this->getVertexSelected(thisRow, thisCol - 1))/m;
				vecE = vecE + midPoint;
				val++;
			}
			if (j < highCol){
				gVector midPoint = (mVector + this->getVertexSelected(thisRow, thisCol + 1))/m;
				vecE = vecE + midPoint;
				val++;
			}
			vecE = vecE/val;
			gVector thisVector = subMesh->getVertexSelected(i, j);
			val += value;

			gVector newVertex = (vectorAvg + (2*vecE) + (val-3)*thisVector)/val;
			subMesh->setVertex(i, j, newVertex);
		}
	}
	return subMesh;
}
