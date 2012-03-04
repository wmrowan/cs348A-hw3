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

        //gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);

        gluNurbsCallback(theNurb, GLU_ERROR, (_GLUfuncptr)nurbsError);

        R = 2;
        r = 1;

        initLimits();
        calcCtrlPts();


        memcpy(knots, KNOTS, sizeof(KNOTS));
    }

    
    void draw() {
        glPushMatrix();
            quarterSurface();
            glRotatef(180., 0,1,0);
            quarterSurface();
            glRotatef(180., 1,0,0);
            quarterSurface();
            glRotatef(180., 0,1,0);
            quarterSurface();
        glPopMatrix();
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

    void quarterSurface() {
        gluBeginSurface(theNurb);
            gluNurbsSurface(theNurb,
                            6, knots, 6, knots,
                            3*4,4, &ctrlpoints[0][0][0],
                            3,3, GL_MAP2_VERTEX_4);
        gluEndSurface(theNurb);
    }

    void initLimits() {
        for(int u = 0; u < 3; u++) {
            for(int v = 0; v < 3; v++) {
                if(v < 2){limits[u][v][4] = 1;limits[u][v][5] = 0;}
                else     {limits[u][v][4] = 0;limits[u][v][5] = 1;}
                if(v < 1){limits[u][v][6] = 1;limits[u][v][7] = 0;}
                else     {limits[u][v][6] = 0;limits[u][v][7] = 1;}

                if(u < 2){limits[u][v][0] = 1;limits[u][v][1] = 0;}
                else     {limits[u][v][0] = 0;limits[u][v][1] = 1;}
                if(u < 1){limits[u][v][2] = 1;limits[u][v][3] = 0;}
                else     {limits[u][v][2] = 0;limits[u][v][3] = 1;}
            }
        }

        printLimits();
    }

    void calcCtrlPts() {
        for(int u = 0; u < 3; u++) {
            for (int v = 0; v < 3; v++) {
                evalPt(u,v, &ctrlpoints[u][v][0]);
            }
        }

        printCtrlPts();
    }

    void printLimits() {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                printf("[(%f; %f), (%f; %f), (%f; %f), (%f; %f)]\n", limits[i][j][0], limits[i][j][1], limits[i][j][2], limits[i][j][3],
                                                                    limits[i][j][4], limits[i][j][5], limits[i][j][6], limits[i][j][7]);
            }
            printf("\n");
        }
        printf("\n");
    }

    void printCtrlPts() {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                printf("[%f; %f, %f, %f] ", ctrlpoints[i][j][3], ctrlpoints[i][j][0], ctrlpoints[i][j][1], ctrlpoints[i][j][2]);
            }
            printf("\n");
        }
        printf("\n");
    }


    // Don't ask
    GLfloat qq(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return s1*s2*q1*q2;
    }

    GLfloat tt(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return p1*p2*t1*t2;
    }

    GLfloat qqtt(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return q1*q2*t1*t2;
    }

    GLfloat T1(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return p1*p2*s2*t1;
    }

    GLfloat T2(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return p1*p2*s2*t1;
    }

    GLfloat t1qq(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return s2*t1*q1*q2;
    }

    GLfloat t2qq(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return s1*t2*q1*q2;
    }

    GLfloat Q1(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return s1*s2*p2*q1;
    }

    GLfloat Q2(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return s1*s2*p2*q1;
    }

    GLfloat q1tt(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return p2*q1*t1*t2;
    }

    GLfloat q2tt(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return p1*q2*t1*t2;
    }


    // Really, please
    GLfloat x(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return R*(p1*p2*s1*s2 + qq(q1,p1,q2,p2,t1,s1,t2,s2) - tt(q1,p1,q2,p2,t1,s1,t2,s2) - qqtt(q1,p1,q2,p2,t1,s1,t2,s2)) + r*(p1*p2*s1*s2 - tt(q1,p1,q2,p2,t1,s1,t2,s2) - qq(q1,p1,q2,p2,t1,s1,t2,s2) + qqtt(q1,p1,q2,p2,t1,s1,t2,s2));
    }

    GLfloat y(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return R*(T1(q1,p1,q2,p2,t1,s1,t2,s2) + T2(q1,p1,q2,p2,t1,s1,t2,s2) + t1qq(q1,p1,q2,p2,t1,s1,t2,s2) + t2qq(q1,p1,q2,p2,t1,s1,t2,s2)) + r*(T1(q1,p1,q2,p2,t1,s1,t2,s2) + T2(q1,p1,q2,p2,t1,s1,t2,s2) - t1qq(q1,p1,q2,p2,t1,s1,t2,s2) - t2qq(q1,p1,q2,p2,t1,s1,t2,s2));
    }

    GLfloat z(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return r*(Q1(q1,p1,q2,p2,t1,s1,t2,s2) + Q2(q1,p1,q2,p2,t1,s1,t2,s2) + q1tt(q1,p1,q2,p2,t1,s1,t2,s2) + q2tt(q1,p1,q2,p2,t1,s1,t2,s2));
    }

    GLfloat w(GLfloat q1, GLfloat p1, GLfloat q2, GLfloat p2, GLfloat t1, GLfloat s1, GLfloat t2, GLfloat s2) {
        return p1*p2*s1*s2 + qq(q1,p1,q2,p2,t1,s1,t2,s2) + tt(q1,p1,q2,p2,t1,s1,t2,s2) + qqtt(q1,p1,q2,p2,t1,s1,t2,s2);
    }

    void evalPt(int u, int v, GLfloat *p) {
        GLfloat q1 = limits[u][v][0];
        GLfloat p1 = limits[u][v][1];
        GLfloat q2 = limits[u][v][2];
        GLfloat p2 = limits[u][v][3];
        GLfloat t1 = limits[u][v][4];
        GLfloat s1 = limits[u][v][5];
        GLfloat t2 = limits[u][v][6];
        GLfloat s2 = limits[u][v][7];

        p[0] = x(q1,p1,q2,p2,t1,s1,t2,s2);
        p[1] = y(q1,p1,q2,p2,t1,s1,t2,s2);
        p[2] = z(q1,p1,q2,p2,t1,s1,t2,s2);
        p[3] = w(q1,p1,q2,p2,t1,s1,t2,s2);
    }
     
    GLfloat R;
    GLfloat r;

    GLUnurbs *theNurb;
    GLfloat limits[3][3][8];
    GLfloat ctrlpoints[3][3][4];
    GLfloat knots[6];
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
