#pragma once

#include <vector>
#include <iostream>
#include "face.h"
//#include "vertex.h"
#include "myglwidget.h"
#include "gMatrix.h"
#include "window.h"

void parser(const char* file, std::vector<Face*> *faces); // A function for loading faces from a file

class Controller{
	private:
		std::vector<Face*> faces;	// Store all of the faces/polygons in the scene

		//std::vector<gVector*> vertices;   //stores all the vertices
		//std::vector<vertex*> vertices;

		std::vector<gMatrix*> matrices;  //stores all the matrices 

		int selected;				// Which face is currently selected
		int vertexSelected;		//which vertex is currently selected
		int matrixSelected;   //which matrix is currently selected

		Window* win;				// A pointer to the display mechanisms
	public:
		Controller(Window* win); 
		~Controller();

		Controller* getController();

		void addVertex(gVector * v);
		//void addVertex(gVector v);
		//std::vector<vertex*>vertices; //stores all the vertices in scene
		//std::vector<gVector*>vertices; //stores all the vertices in scene

		const int numPolys();				// Get the number of faces
		void addMatrix(gMatrix * m);
		const int numVertices();
		const gMatrix getPoly(int i);		// Get a certain face
		const gVector getVertex(int i);
		//const int numVertices();
		//const gVector getVertex(int i);     //Get a cetain vertex
		const int getSelected();			// Get which face has been selected
		const int getVertexSelected();
		//const int getVertexSelected();		//get which vertex has been selected
		void select(int i);					// Set the selected face
		void vertexSelect(int i);
		//void vertexSelect(int i);
		void extrudeSelected(float depth);	// Perform an extrusion
};