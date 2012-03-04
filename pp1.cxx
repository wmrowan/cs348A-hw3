/*********************************************************************************/
/* Programming Project 1: Sample program to visualize a sphere in OpenGL         */
/*********************************************************************************/

#include <GL/gl.h>
#include <GL/glu.h>
#include "pp1.h"
#include "pp1_ui.h"
#include <stdlib.h>

#define VIEW_X_DEFAULT          5.0       /* default x position of the viewpoint */
#define VIEW_X_DEFAULT_MIN      -8.0      /* min and max values of x position */
#define VIEW_X_DEFAULT_MAX      8.0 

#define VIEW_Y_DEFAULT          5.0       /* default y position of the viewpoint */
#define VIEW_Y_DEFAULT_MIN      -8.0      /* min and max values of y position */
#define VIEW_Y_DEFAULT_MAX      8.0

#define VIEW_Z_DEFAULT          5.0       /* default z position of the viewpoint */
#define VIEW_Z_DEFAULT_MIN      -8.0      /* min and max values of z position */
#define VIEW_Z_DEFAULT_MAX      8.0 

GLfloat KNOTS[6] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0}; 

class Torus {
public:
    Torus() {
        theNurb = gluNewNurbsRenderer();
        gluNurbsProperty(theNurb, GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
        gluNurbsProperty(theNurb, GLU_U_STEP, 15);
        gluNurbsProperty(theNurb, GLU_V_STEP, 15);

        gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);

        gluNurbsCallback(theNurb, GLU_ERROR, (_GLUfuncptr)nurbsError);

        R = 0;
        r = 0;

        initLimits(0,1);
        calcCtrlPts();

        memcpy(knots, KNOTS, sizeof(KNOTS));
    }

    void draw() {
        gluBeginSurface(theNurb);
        gluNurbsSurface(theNurb,
                        6, knots, 6, knots,
                        3*4,4, &ctrlpoints[0][0][0],
                        3,3, GL_MAP2_VERTEX_4);
        gluEndSurface(theNurb);
    }

    void setR(GLdouble val) {
        R = val;
        calcCtrlPts();
        canvas->redraw();
        canvas2->redraw();
    }

    void setr(GLdouble val) {
        r = val;
        calcCtrlPts();
        canvas->redraw();
        canvas2->redraw();
    }

private:
    static void nurbsError(GLenum err) {
        printf("Nurbs error: %s\n", gluErrorString(err));
    };

    void initLimits(GLfloat low,GLfloat up) {
        for(int u = 0; u < 3; u++) {
            for(int v = 0; v < 3; v++) {
                if(u < 2) limits[u][v][0] = low;
                else      limits[u][v][0] = up;
                if(u < 1) limits[u][v][1] = low;
                else      limits[u][v][1] = up;

                if(v < 2) limits[u][v][2] = low;
                else      limits[u][v][2] = up;
                if(v < 1) limits[u][v][3] = low;
                else      limits[u][v][3] = up;
            }
        }
    }

    void calcCtrlPts() {
        for(int u = 0; u < 3; u++) {
            for (int v = 0; v < 3; v++) {
                evalPt(u,v, &ctrlpoints[u][v][0]);
            }
        }
    }

    GLfloat x(GLfloat Q1, GLfloat Q2, GLfloat T1, GLfloat T2) {
        return R*(1 + Q1*Q2 - T1*T2 - Q1*Q2*T1*T2) + r*(1 - T1*T2 - Q1*Q2 + T1*T2*Q1*Q2);
    }

    GLfloat y(GLfloat Q1, GLfloat Q2, GLfloat T1, GLfloat T2) {
        return R*(T1 + T2 + T1*Q1*Q2 + T2*Q1*Q2) + r*(T1 + T2 - T1*Q1*Q2 - T2*Q1*Q2);
    }

    GLfloat z(GLfloat Q1, GLfloat Q2, GLfloat T1, GLfloat T2) {
        return r*(Q1 + Q2 + Q1*T1*T2 + Q2*T1*T2);
    }

    GLfloat w(GLfloat Q1, GLfloat Q2, GLfloat T1, GLfloat T2) {
        return 1 + Q1*Q2 + T1*T2 + Q1*Q2*T1*T2;
    }

    void evalPt(int u, int v, GLfloat *p) {
        GLfloat Q1 = limits[u][v][0];
        GLfloat Q2 = limits[u][v][1];
        GLfloat T1 = limits[u][v][2];
        GLfloat T2 = limits[u][v][3];

        p[0] = x(Q1,T1,Q2,T2);
        p[1] = y(Q1,T1,Q2,T2);
        p[2] = z(Q1,T1,Q2,T2);
        p[3] = w(Q1,T1,Q2,T2);
    }
     
    GLfloat R;
    GLfloat r;

    GLUnurbs *theNurb;
    GLfloat limits[3][3][4];
    GLfloat ctrlpoints[3][3][4];
    GLfloat knots[8];
};

GLdouble viewX, viewY, viewZ;             /* view point */
Torus torus;

void DrawScene(){
    torus.draw();
}

// Callback for the slider that defines viewpoint x
void ViewPointXCallback(Fl_Value_Slider *ob, long data){
	viewX = ob->value();
	canvas->redraw();
	canvas2->redraw();
}

// Callback for the slider that defines viewpoint y
void ViewPointYCallback(Fl_Value_Slider *ob, long data){
	viewY = ob->value();
	canvas->redraw();
	canvas2->redraw();
}

// Callback for the slider that defines viewpoint z
void ViewPointZCallback(Fl_Value_Slider *ob, long data){
	viewZ = ob->value();
	canvas->redraw();
	canvas2->redraw();
}

void TorusParamRCallback(Fl_Value_Slider *ob, long data) {
    torus.setR(ob->value());
}

void TorusParamrCallback(Fl_Value_Slider *ob, long data) {
    torus.setr(ob->value());
}

// Callback for the button that controls the exit of the program
void QuitProgram(Fl_Button *ob, long data){
	exit(0);
}

// Define the default values of the interface
void InitInterfaceDefaults(void){
	ViewPointXSlider->bounds(VIEW_X_DEFAULT_MIN, VIEW_X_DEFAULT_MAX);
	ViewPointXSlider->value(VIEW_X_DEFAULT);

	ViewPointYSlider->bounds(VIEW_Y_DEFAULT_MIN, VIEW_Y_DEFAULT_MAX);
	ViewPointYSlider->value(VIEW_Y_DEFAULT);

	ViewPointZSlider->bounds(VIEW_Z_DEFAULT_MIN, VIEW_Z_DEFAULT_MAX);
	ViewPointZSlider->value(VIEW_Z_DEFAULT);
  
	viewX      = VIEW_X_DEFAULT ;
	viewY      = VIEW_Y_DEFAULT ;
	viewZ      = VIEW_Z_DEFAULT ;
}

void MyInit(void){
}


int main(int argc, char *argv[]){
	Fl_Double_Window *ui = create_the_forms();
	Fl::visual(FL_DOUBLE|FL_INDEX);
	ui->label("Torus");
	ui->show(argc, argv);

	InitInterfaceDefaults();

	ViewPointXSlider->redraw();
	ViewPointYSlider->redraw();
	ViewPointZSlider->redraw();
	MyInit();

	Fl::run();
	return 0;
}

///////////////////////////////////////////////////////////////////////
/////////// You should not need to edit anything below here ///////////
///////////////////////////////////////////////////////////////////////

// Define viewpoint of main window
void DefineViewPointMain(){
	glLoadIdentity();
	gluLookAt(
		viewX, viewY, viewZ,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
}

// Define viewpoint of the secondary window
void DefineViewPointSecondary(){
	glLoadIdentity();
	gluLookAt(
		6.0, 10.0, 13.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
}

// Create the axes
void DrawAxes(void){
	glDisable(GL_LIGHTING);
	glLineWidth(3.0);
	glBegin (GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f( 0.0, 0.0, 0.0 );   glVertex3f( 0.0, 0.0, 10.0 );
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f( 0.0, 0.0, 0.0 );   glVertex3f( 0.0, 10.0, 0.0 );
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f( 0.0, 0.0, 0.0 );   glVertex3f( 10.0, 0.0, 0.0 );
	glEnd();
	glEnable(GL_LIGHTING);
}

// Create the viewpoint lines and spheres
void DrawViewpoint(void){
	glDisable(GL_LIGHTING);
	glLineWidth(3.0);
	glColor3f(1.0, 1.0, 1.0);

	glBegin (GL_LINES);
	glVertex3f( 0.0, 0.0, 0.0 ); glVertex3f( viewX, viewY, viewZ );
	glEnd();
	glTranslatef(viewX, viewY, viewZ);
	glEnable(GL_LIGHTING);
	//gluSphere(theQuadric, 0.5, 10, 10);
}

// Define the light sources
void DefineLight(void){
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); 
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); 

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
}

// Define the material
void DefineMaterial(void){
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

MainCanvas::MainCanvas(int X, int Y, int W, int H)
 : Fl_Gl_Window(X, Y, W, H, "")
{
}

int MainCanvas::handle(int event){
	return Fl_Gl_Window::handle(event);
}
void MainCanvas::draw(){
	if (!valid()) {
		glViewport(0,0, (GLint)w(), (GLint)h());
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective (75.0, (GLdouble)w()/(GLdouble)h(), 0.1, 20.0);
		glMatrixMode( GL_MODELVIEW );
		DefineLight();
		DefineMaterial();
	}
	/* Draw in the main window */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineViewPointMain();

	DrawScene();
}

CameraPositionCanvas::CameraPositionCanvas(int X, int Y, int W, int H)
 : Fl_Gl_Window(X, Y, W, H, "")
{
}

int CameraPositionCanvas::handle(int event){
	return Fl_Gl_Window::handle(event);
}
void CameraPositionCanvas::draw(){
	if (!valid()) {
		glViewport(0,0, (GLint)w(), (GLint)h());
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective (75.0, (GLdouble)w()/(GLdouble)h(), 0.1, 20.0);
		glMatrixMode( GL_MODELVIEW );
		DefineLight();
		DefineMaterial();
	}
	/* Draw in the secondary window */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DefineViewPointSecondary();

	DrawScene();
	
	DrawAxes();
	DrawViewpoint();
}
