// generated by Fast Light User Interface Designer (fluid) version 1.0300

#ifndef pp1_ui_h
#define pp1_ui_h
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.h>

class MainCanvas : public Fl_Gl_Window {
public:
  MainCanvas(int X, int Y, int W, int H);
  int handle(int event);
  void draw();
};

class CameraPositionCanvas : public Fl_Gl_Window {
public:
  CameraPositionCanvas(int X, int Y, int W, int H);
  int handle(int event);
  void draw();
};
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *assgn1_ui;
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
extern void QuitProgram(Fl_Button*, long);
extern Fl_Button *ExitButton;
extern Fl_Button *All;
#include <FL/Fl_Value_Slider.H>
extern void ViewPointXCallback(Fl_Value_Slider*, long);
extern Fl_Value_Slider *ViewPointXSlider;
extern void ViewPointYCallback(Fl_Value_Slider*, long);
extern Fl_Value_Slider *ViewPointYSlider;
extern void ViewPointZCallback(Fl_Value_Slider*, long);
extern Fl_Value_Slider *ViewPointZSlider;
extern MainCanvas *canvas;
extern CameraPositionCanvas *canvas2;
extern void TorusParamRCallback(Fl_Value_Slider*, long);
extern Fl_Value_Slider *TorusParamRSlider;
extern void TorusParamrCallback(Fl_Value_Slider*, long);
extern Fl_Value_Slider *TorusParamrSlider;
extern void TorusParamMCallback(Fl_Value_Slider*, long);
extern Fl_Value_Slider *TorusParamMSlider;
Fl_Double_Window* create_the_forms();
#endif
