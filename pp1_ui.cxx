// generated by Fast Light User Interface Designer (fluid) version 1.0300

#include "pp1_ui.h"

Fl_Double_Window *assgn1_ui=(Fl_Double_Window *)0;

Fl_Button *ExitButton=(Fl_Button *)0;

Fl_Button *All=(Fl_Button *)0;

Fl_Value_Slider *ViewPointXSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *ViewPointYSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *ViewPointZSlider=(Fl_Value_Slider *)0;

MainCanvas *canvas=(MainCanvas *)0;

CameraPositionCanvas *canvas2=(CameraPositionCanvas *)0;

Fl_Value_Slider *TorusParamRSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *TorusParamrSlider=(Fl_Value_Slider *)0;

Fl_Value_Slider *TorusParamMSlider=(Fl_Value_Slider *)0;

Fl_Double_Window* create_the_forms() {
  { assgn1_ui = new Fl_Double_Window(870, 810, "assgn1_ui");
    assgn1_ui->box(FL_NO_BOX);
    { Fl_Box* o = new Fl_Box(-10, 0, 880, 825, "R");
      o->box(FL_UP_BOX);
      o->labelcolor(FL_BLACK);
    } // Fl_Box* o
    { ExitButton = new Fl_Button(770, 780, 80, 20, "Exit");
      ExitButton->box(FL_SHADOW_BOX);
      ExitButton->labelfont(1);
      ExitButton->callback((Fl_Callback*)QuitProgram, (void*)(0));
    } // Fl_Button* ExitButton
    { All = new Fl_Button(0, 0, 0, 0);
      All->box(FL_NO_BOX);
      All->color((Fl_Color)1027423549);
      All->selection_color((Fl_Color)1027423549);
      All->labelcolor(FL_BLACK);
    } // Fl_Button* All
    { Fl_Box* o = new Fl_Box(470, 570, 290, 20, "Viewpoint Position");
      o->labelfont(1);
      o->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
    } // Fl_Box* o
    { ViewPointXSlider = new Fl_Value_Slider(420, 600, 400, 20, "X");
      ViewPointXSlider->type(1);
      ViewPointXSlider->color(FL_CYAN);
      ViewPointXSlider->labelcolor(FL_BLACK);
      ViewPointXSlider->callback((Fl_Callback*)ViewPointXCallback, (void*)(0));
      ViewPointXSlider->align(Fl_Align(FL_ALIGN_LEFT));
    } // Fl_Value_Slider* ViewPointXSlider
    { ViewPointYSlider = new Fl_Value_Slider(420, 630, 400, 20, "Y");
      ViewPointYSlider->type(1);
      ViewPointYSlider->color(FL_GREEN);
      ViewPointYSlider->labelcolor(FL_BLACK);
      ViewPointYSlider->callback((Fl_Callback*)ViewPointYCallback, (void*)(0));
      ViewPointYSlider->align(Fl_Align(FL_ALIGN_LEFT));
    } // Fl_Value_Slider* ViewPointYSlider
    { ViewPointZSlider = new Fl_Value_Slider(420, 660, 400, 20, "Z");
      ViewPointZSlider->type(1);
      ViewPointZSlider->color(FL_RED);
      ViewPointZSlider->labelcolor(FL_BLACK);
      ViewPointZSlider->callback((Fl_Callback*)ViewPointZCallback, (void*)(0));
      ViewPointZSlider->align(Fl_Align(FL_ALIGN_LEFT));
    } // Fl_Value_Slider* ViewPointZSlider
    { Fl_Button* o = new Fl_Button(0, 0, 0, 0);
      o->box(FL_NO_BOX);
      o->color((Fl_Color)1651472442);
      o->selection_color((Fl_Color)1651472442);
      o->labelcolor(FL_BLACK);
    } // Fl_Button* o
    { canvas = new MainCanvas(20, 40, 800, 510);
      canvas->box(FL_DOWN_BOX);
      canvas->color(FL_BACKGROUND_COLOR);
      canvas->selection_color(FL_BACKGROUND_COLOR);
      canvas->labeltype(FL_NORMAL_LABEL);
      canvas->labelfont(0);
      canvas->labelsize(14);
      canvas->labelcolor(FL_BLACK);
      canvas->user_data((void*)(0));
      canvas->align(Fl_Align(FL_ALIGN_CENTER));
      canvas->when(FL_WHEN_RELEASE);
    } // MainCanvas* canvas
    { Fl_Box* o = new Fl_Box(280, 10, 290, 20, "Sphere View");
      o->labelfont(1);
      o->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
    } // Fl_Box* o
    { canvas2 = new CameraPositionCanvas(20, 570, 360, 220);
      canvas2->box(FL_DOWN_BOX);
      canvas2->color(FL_BACKGROUND_COLOR);
      canvas2->selection_color(FL_BACKGROUND_COLOR);
      canvas2->labeltype(FL_NORMAL_LABEL);
      canvas2->labelfont(0);
      canvas2->labelsize(14);
      canvas2->labelcolor(FL_BLACK);
      canvas2->user_data((void*)(0));
      canvas2->align(Fl_Align(FL_ALIGN_CENTER));
      canvas2->when(FL_WHEN_RELEASE);
    } // CameraPositionCanvas* canvas2
    { TorusParamRSlider = new Fl_Value_Slider(420, 690, 400, 20, "R");
      TorusParamRSlider->type(1);
      TorusParamRSlider->color((Fl_Color)186);
      TorusParamRSlider->labelcolor(FL_BLACK);
      TorusParamRSlider->minimum(-5);
      TorusParamRSlider->maximum(5);
      TorusParamRSlider->step(0.1);
      TorusParamRSlider->callback((Fl_Callback*)TorusParamRCallback, (void*)(0));
      TorusParamRSlider->align(Fl_Align(FL_ALIGN_LEFT));
    } // Fl_Value_Slider* TorusParamRSlider
    { TorusParamrSlider = new Fl_Value_Slider(420, 720, 400, 20, "r");
      TorusParamrSlider->type(1);
      TorusParamrSlider->color((Fl_Color)161);
      TorusParamrSlider->labelcolor(FL_BLACK);
      TorusParamrSlider->minimum(-5);
      TorusParamrSlider->maximum(5);
      TorusParamrSlider->step(0.1);
      TorusParamrSlider->callback((Fl_Callback*)TorusParamrCallback, (void*)(0));
      TorusParamrSlider->align(Fl_Align(FL_ALIGN_LEFT));
    } // Fl_Value_Slider* TorusParamrSlider
    { TorusParamMSlider = new Fl_Value_Slider(420, 750, 400, 20, "m");
      TorusParamMSlider->type(1);
      TorusParamMSlider->color((Fl_Color)139);
      TorusParamMSlider->labelcolor(FL_BLACK);
      TorusParamMSlider->minimum(-5);
      TorusParamMSlider->maximum(5);
      TorusParamMSlider->step(0.1);
      TorusParamMSlider->callback((Fl_Callback*)TorusParamMCallback, (void*)(0));
      TorusParamMSlider->align(Fl_Align(FL_ALIGN_LEFT));
    } // Fl_Value_Slider* TorusParamMSlider
    assgn1_ui->end();
  } // Fl_Double_Window* assgn1_ui
  return assgn1_ui;
}
