//
//  DAQControls.h
//  GigaDAQ
//
//  Created by David A. Trevas on 1/8/25.
//

#ifndef _DAQ_CONTROLS_INCLUDE_
#define _DAQ_CONTROLS_INCLUDE_

#include <stdio.h>
#include "Control.h"

//Slider modes - Horizontal is X, Vertical is Y, Trackpad is both

#define HORIZONTAL 	0
#define VERTICAL	1
#define TRACKPAD	2

struct Button : Control {
    void (*buttonUp)(void);
    Button();
    Button(String nm, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c1,  unsigned int c2);
    void setButtonUp(void (*du)());
    void release();
};

struct Slider : Control {
	int mode;
    float minX;
    float maxX;
    float minY;
    float maxY;
    float posX;
    float posY;
    void (*slide)();
    Slider();
    Slider(String nm, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c1,  unsigned int c2);
    void setXlimits(float minimumX, float maximumX);
    void setYlimits(float minimumY, float maximumY);
    void setPosition(float px, float py);
    void setMode(int md);
    void setSlideAction(void(*sf)());
    void sliderMotion();
};

struct Textbox : Control {
    
    Textbox();
    Textbox(String nm, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c1,  unsigned int c2);
};
#endif /* _DAQ_CONTROLS_INCLUDE_ */
