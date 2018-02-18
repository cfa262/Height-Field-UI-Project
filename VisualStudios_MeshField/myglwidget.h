// A Qt widget class for displaying OpenGL primitives
// You will need to connect your scene graph code to this class

#ifndef MYGLWIDGET_H // Similar to #pragma once. Used to handle circular dependences. 
#define MYGLWIDGET_H // #endif is at the end of the file. 
#include "camera.h"
#include "mesh.h"
#include <QGLWidget>

class Window; 
class MyGLWidget : public QGLWidget  // MyGLWidget is a sub-class of QGLWidget and inherits all of its functionality
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);	// Constructor: This might be where your animal (scene graph and primitves) get created?
    ~MyGLWidget();								// Destructor
	Camera* cam;	// A pointer to the 3D camera

	bool wireFrame;
	float red;
	float green;
	float blue;
	int rows;
	int cols;
	int depth;
	int width;
	
signals:			// Qt uses signals and slots to connect QUI elements. Don't worry about these right now. 
public slots:

protected:
    void initializeGL();						// OpenGL requires some initialization. 
    void paintGL();								// Called when the OpenGL window needs to be redrawn. It calls our draw method. 
    void resizeGL(int width, int height);		// Called when the window is resized. 
    QSize minimumSizeHint() const;				// Methods for handling resizing and mouse events. Don't worry about them now. 
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	
private:
	Window* win;	// Keep a pointer to the win
    void draw();	
};

#endif // MYGLWIDGET_H

