// The Window class has the main Qt components and links together the GUI with your scene graph

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QSlider>
#include "gMatrix.h"
#include "eController.h"

class Data;  
class Controller; 

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);

	~Window();
	void updateBrowser();											// update the browser
	void select(int selected);			// set the selection
	void updateDrawing();				// redraw the OpenGL window
	//int getVertex();
	const int getSelected();			// get the index of the face selected
	void changeTransSlider(float value);
	//const float getExtrude();
	void setController(Controller* c); 
	//Controller* getController();

	Mesh* meshField;	//used for creating a meshfield

	
protected:
    void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent *event);

	signals:
	
public slots :

	void on_listWidget_currentItemChanged(int value);  // Called when a different item in the tree view is selected. 
	//void setUpTreeView(QStandardItem *row);
	void createMesh();
	void wireFrameChecked();
	void changeSnowHeight(float snowHeight);
	void changeColorRed(float red);
	void changeColorGreen(float green);
	void changeColorBlue(float blue);
	void fractalizeButtonPushed();
	void smoothButtonPushed();
	void topButtonPushed();
	void sideButtonPushed();
	void randomFieldPushed();
		
private:
    Ui::Window *ui;				// A Qt internal mechanism
	Controller* controller;		// Pointer to the controller
	QPoint lastPos;				// For mouse movement

	QStandardItemModel* model;  // Links Qt with your scene graph 
	QStandardItem* tempItem;

	std::vector<gVector*>* verticesList;
	int selected;
};

#endif // WINDOW_H
