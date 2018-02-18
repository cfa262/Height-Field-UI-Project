// Implementation of the MyGLWidget class
// Your scene graph will be created and called from here and OpenGL calls to display it. 

#include <QtWidgets>
#include <QtOpenGL>  // Note that some of the OpenGL calls are Qt specific and not standard OpenGL

#include "myglwidget.h"
#include "window.h"
#include <GL/glu.h>

MyGLWidget::MyGLWidget(QWidget *parent)					 // Constructor 
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)   // Call to parent constructor
{
	win = (Window*)parent;  // casting parent to type Window (which it is)

	cam = new Camera(4, 0, 0); // Create the 3D camera
	cam->increaseTheta(-90);	//set as top view 
	this->wireFrame = FALSE;
}

MyGLWidget::~MyGLWidget()	// Destructor
{
	delete this->cam;
}

////////////////////////////////////////////////////////////////////////////
// A few more Qt methods that you don't need to worry about yet. 
QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}
///////////////////////////////////////////////////////////////////////////////


// Initializing OpenGL
void MyGLWidget::initializeGL()
{
	qglClearColor(Qt::darkBlue);	// Set the background color. Note this isn't standard OpenGL. It's Qt. 

}

// This method gets called whenever the widget needs updating. 
void MyGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the window using the background color set in initialization
 
    draw();

}

// YOUR CODE GOES IN THIS DRAW METHOD
// Actual code for drawing the primitives
void MyGLWidget::draw()
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	gluLookAt(cam->getEye()[0], cam->getEye()[1], cam->getEye()[2],
		0.0, 0.0, 0.0,
		cam->getUp()[0], cam->getUp()[1], cam->getUp()[2]);

	//for each row and coloumn in meshVertices, a nested for loop is needed
	for (int i = 0; i < win->meshField->meshVertices->size()-1; i++)
	{
		for (int j = 0; j < win->meshField->meshVertices->at(0)->size()-1; j++)
		{
			//this makes sure I get every single vertex in the vectorList
			std::vector<gVector>* vec1 = win->meshField->meshVertices->at(i);
			std::vector<gVector>* vec2 = win->meshField->meshVertices->at(i+1);

			//if wireframe is checked
			//draw wireframe
			if (wireFrame)
			{
				glBegin(GL_LINE_LOOP);
				//glColor3f(1,1,1);
				glColor3f(red, green, blue);

				//draws first traingle
				glBegin(GL_LINE_LOOP);
				glVertex3f(vec1->at(j)[0], vec1->at(j)[1], vec1->at(j)[2]);
				glVertex3f(vec2->at(j + 1)[0], vec2->at(j + 1)[1], vec2->at(j + 1)[2]);
				glVertex3f(vec2->at(j)[0], vec2->at(j)[1], vec2->at(j)[2]);
				glEnd();

				//draws second triangle
				glBegin(GL_LINE_LOOP);
				glVertex3f(vec1->at(j)[0], vec1->at(j)[1], vec1->at(j)[2]);
				glVertex3f(vec1->at(j + 1)[0], vec1->at(j + 1)[1], vec1->at(j + 1)[2]);
				glVertex3f(vec2->at(j + 1)[0], vec2->at(j + 1)[1], vec2->at(j + 1)[2]);
				glEnd();

			}
			else {
				//draws surface

				glBegin(GL_POLYGON);

				//draws first triangle

				//1st vertex
				if (vec1->at(j)[1] >= win->meshField->getSnowHeight())
					{ glColor3f(1, 1, 1); }
				else { glColor3f(red, green, blue); }
				
				glVertex3f(vec1->at(j)[0], vec1->at(j)[1], vec1->at(j)[2]);

				//2nd vertex
				if (vec1->at(j)[1] >= win->meshField->getSnowHeight())
				{ glColor3f(1, 1, 1); }
				else {
					glColor3f(red, green, blue);
				}
				glVertex3f(vec2->at(j + 1)[0], vec2->at(j + 1)[1], vec2->at(j + 1)[2]);

				//3rd vertex
				if (vec2->at(j)[1] >= win->meshField->getSnowHeight())
					{ glColor3f(1, 1, 1); }
				else { glColor3f(red, green, blue); }
				glVertex3f(vec2->at(j)[0], vec2->at(j)[1], vec2->at(j)[2]);
				glEnd();

				//draws second Triangle

				glBegin(GL_POLYGON);
				//glColor3f(red, green, blue);

				// 1st Vertex
				if (vec1->at(j)[1] >= win->meshField->getSnowHeight())
				{ glColor3f(1, 1, 1); }
				else { glColor3f(red, green, blue); }
				glVertex3f(vec1->at(j)[0], vec1->at(j)[1], vec1->at(j)[2]);

				// 2nd Vertex
				if (vec1->at(j+1)[1] >= win->meshField->getSnowHeight())
				{ glColor3f(1, 1, 1); }
				else { glColor3f(red, green, blue); }
				glVertex3f(vec1->at(j + 1)[0], vec1->at(j + 1)[1], vec1->at(j + 1)[2]);

				// 3rd Vertex
				if (vec2->at(j+1)[1] >= win->meshField->getSnowHeight())
				{ glColor3f(1, 1, 1); }
				else { glColor3f(red, green, blue); }
				glVertex3f(vec2->at(j + 1)[0], vec2->at(j + 1)[1], vec2->at(j + 1)[2]);
				glEnd();
			}

		}
	}
}


/////////////////////////////////////////////////////////////////
// More Qt methods that you do not have to worry about just now
void MyGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, -5, 5);  // left, right, bottom, top, near, far
	gluPerspective(90, 1, 0.1, 10);		// experiment with these settings to see their effects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
   
}



//////////////////////////////////////////////////////////////////////////
