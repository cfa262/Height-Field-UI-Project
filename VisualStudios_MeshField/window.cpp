
#include <iostream>
#include <sstream>
#include <string>
#include "window.h"
#include "ui_window.h"
#include "myglwidget.h"


Window::Window(QWidget *parent) :  // Window constructor
    QWidget(parent),
    ui(new Ui::Window)
{
	ui->setupUi(this);				// Standard Qt stuff

	
	//list Widget
	connect(ui->listWidget, &QListWidget::currentRowChanged, this, &Window::on_listWidget_currentItemChanged);

	//buttons
	connect(ui->createButton, &QPushButton::clicked, this, &Window::createMesh);
	connect(ui->topViewButton, &QPushButton::clicked, this, &Window::topButtonPushed);
	connect(ui->sideViewButton, &QPushButton::clicked, this, &Window::sideButtonPushed);
	connect(ui->fractalizeButton, &QPushButton::clicked, this, &Window::fractalizeButtonPushed);
	connect(ui->smoothButton, &QPushButton::clicked, this, &Window::smoothButtonPushed);
	connect(ui->randomFieldButton, &QPushButton::clicked, this, &Window::randomFieldPushed);
	//connect(ui->snowButton, &QPushButton::clicked, this, &Window::snowButtonPushed);

	//translider
	ui->translateSlider->setMaximum(10); ui->translateSlider->setMinimum(0); ui->translateSlider->setSingleStep(1);
	connect(ui->translateSlider, &QSlider::valueChanged, this, &Window::changeTransSlider);
	//ui->translateSlider->setValue(0);
	//color/snow sliders
	ui->snowSlider->setMaximum(20); ui->snowSlider->setMinimum(0); ui->snowSlider->setSingleStep(1);
	ui->red_slider->setMaximum(255); ui->red_slider->setMinimum(0);  ui->red_slider->setSingleStep(5);
	ui->green_slider->setMaximum(255); ui->green_slider->setMinimum(0);  ui->green_slider->setSingleStep(5);
	ui->blue_slider->setMaximum(255); ui->blue_slider->setMinimum(0);  ui->blue_slider->setSingleStep(5);
	connect(ui->snowSlider, &QSlider::valueChanged, this, &Window::changeSnowHeight);
	connect(ui->red_slider, &QSlider::valueChanged, this, &Window::changeColorRed);
	connect(ui->green_slider, &QSlider::valueChanged, this, &Window::changeColorGreen);
	connect(ui->blue_slider, &QSlider::valueChanged, this, &Window::changeColorBlue);

	//start slider values
	ui->blue_slider->setValue(255);
	ui->green_slider->setValue(255);
	ui->red_slider->setValue(255);

	//wireframe
	connect(ui->wireFrameCheckBox, &QCheckBox::clicked, this, &Window::wireFrameChecked);
	
	//creates new mesh
	this->meshField = new Mesh(0, 0, 0, 0);

	ui->myGLWidget->update();
}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *e)  // If the user hits esc, close the program. 
{
    if (e->key() == Qt::Key_Escape)
        close();
	else if (e->key() == Qt::Key_A)
	{
		ui->myGLWidget->cam->increasePhi(-7);
		ui->myGLWidget->update();
	}
	else if (e->key() == Qt::Key_D)
	{
		ui->myGLWidget->cam->increasePhi(7);
		ui->myGLWidget->update();
	}
	else if (e->key() == Qt::Key_W)
	{
		ui->myGLWidget->cam->increaseTheta(-7);
		ui->myGLWidget->update();
	}
	else if (e->key() == Qt::Key_S)
	{
		ui->myGLWidget->cam->increaseTheta(7);
		ui->myGLWidget->update();
	}
	else if (e->key() == Qt::Key_E)
	{
		ui->myGLWidget->cam->increaseRad(-0.5);
		ui->myGLWidget->update();
	}
	else if (e->key() == Qt::Key_F)
	{
		ui->myGLWidget->cam->increaseRad(0.5);
		ui->myGLWidget->update();
	}
    else
        QWidget::keyPressEvent(e);
}
void Window::mousePressEvent(QMouseEvent* event)
{
	lastPos = event->pos();
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
	int a = event->x()-lastPos.x();
	int b = event->y()-lastPos.y();
	if (event->buttons() & Qt::LeftButton) 
	{
		ui->myGLWidget->cam->increasePhi(a);
		ui->myGLWidget->cam->increaseTheta(b);
	}
	else if (event->buttons() & Qt::RightButton) 
	{
		ui->myGLWidget->cam->increasePhi(a);
		ui->myGLWidget->cam->increaseTheta(b);
	}
	lastPos = event->pos();
}

void Window::setController(Controller* c)
{
	this->controller = c; 
}

//Controller* Window::getController()
//{
//	return this->controller->getController();
//}

void Window::updateBrowser()// update the face browser
{
	//clears the tree widget(browser)
	ui->listWidget->clear();

	//creates the tree widget(browser)
	for (int i = 0; i < this->meshField->getRows(); i++) {
		for (int j = 0; j < this->meshField->getCols(); j++) {
			//int count = 0;
			std::string a = std::to_string(i);
			std::string b = std::to_string((this->meshField->meshVertices->at(i)->at(j)[1]));
			std::string c = std::to_string(j);
			std::string finalString = "(" + a + " , " + b + " , " + c +") vertex";
			const char *v = finalString.c_str();
			//select(count);
			ui->listWidget->addItem(v);
		}
	}
}

void Window::select(int selected)// set the selection
{

	QListWidgetItem *it = ui->listWidget->item(selected);
	ui->listWidget->setCurrentItem(it);

}

void Window::updateDrawing()// redraw the OpenGL window
{
	ui->myGLWidget->update(); 
}


const int Window::getSelected()
{
	return this->selected;
}
void Window::changeTransSlider(float translate) {
	ui->vertexLabel->setNum(translate);
	//gVector vert = this->meshField->getVertex(this->selected);
	float newTrans = translate*0.01f;
	this->meshField->manipulateVertex(this->selected, newTrans);
	this->updateBrowser();
	ui->myGLWidget->update();
}
void Window::on_listWidget_currentItemChanged(int value)
{
	selected = value;

}

void Window::fractalizeButtonPushed() {
	//int count = 0;	
	for (int count = 0; count < ui->fractalSpinBox->value(); count++) {

		this->meshField = meshField->fractalize();
	}
	this->updateBrowser();
	ui->myGLWidget->update();
	
}
void Window::smoothButtonPushed() {
	
	for (int count = 0; count < ui->smoothSpinBox->value(); count++) {

		this->meshField = meshField->subDivide();
	}
	this->updateBrowser();
	ui->myGLWidget->update();

}
void Window::topButtonPushed() {
	ui->myGLWidget->cam = new Camera(4,0,0);
	ui->myGLWidget->cam->increaseTheta(-90);
	ui->myGLWidget->update();
}
void Window::sideButtonPushed() {
	ui->myGLWidget->cam = new Camera(4,0,0);
	//ui->myGLWidget->cam->increaseTheta(0);
	ui->myGLWidget->update();
}
void Window::randomFieldPushed() {
	
	//get the values from previous mesh rows and cols
	int r = this->meshField->meshVertices->size()/2;
	int c = this->meshField->meshVertices->at(0)->size()/2;
	float w = this->meshField->getWidth();
	float d = this->meshField->getDepth();

	//create a new mesh
	this->meshField = new Mesh(r, c, w, d);

	//fractalize the new mesh
	this->meshField = meshField->fractalize();
	this->updateBrowser();
	ui->myGLWidget->update();

}

//when Create Mesh button is pressed, it will create the mesh
void Window::createMesh() {

	ui->myGLWidget->rows = ui->rowSpinBox->value();   
	ui->myGLWidget->cols = ui->columnSpinBox->value();
	ui->myGLWidget->depth = ui->depthSpinBox->value();
	ui->myGLWidget->width = ui->widthSpinBox->value();

	this->meshField = new Mesh(ui->myGLWidget->rows, ui->myGLWidget->cols, ui->myGLWidget->depth+1, ui->myGLWidget->width+1);

	this->updateBrowser();
	ui->myGLWidget->update();
}

void Window::wireFrameChecked() {
	if (ui->wireFrameCheckBox->checkState()) {
		ui->wireFrameCheckBox->setChecked(1);
		ui->myGLWidget->wireFrame = TRUE;
	}
	else {
		ui->myGLWidget->wireFrame = FALSE;
	}
	ui->myGLWidget->update();

}

void Window::changeSnowHeight(float snowHeight) {
	float thisSnow = snowHeight*0.01f;
	this->meshField->setSnowHeight(thisSnow);
	ui->snowLabel->setNum(snowHeight);
	ui->myGLWidget->update();
}

void Window::changeColorRed(float red)
{
	//changes shape to red
	ui->myGLWidget->red = red/255;
	ui->redLabel->setNum(red);
	ui->myGLWidget->update();
}
void Window::changeColorGreen(float green)
{
	//changes shape to green
	ui->myGLWidget->green = green/255;
	ui->greenLabel->setNum(green);
	ui->myGLWidget->update();
}
void Window::changeColorBlue(float blue)
{
	//changes shape to blue
	ui->myGLWidget->blue = blue/255;
	ui->blueLabel->setNum(blue);
	ui->myGLWidget->update();
}
//void Window::snowButtonPushed() {
//	this->mesh->snowCapHeight = 
//}


