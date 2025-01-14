//
//  Control.h
//  GigaDAQ
//
//  Created by David A. Trevas on 1/8/25.
//

#ifndef _CONTROL_INCLUDE_
#define _CONTROL_INCLUDE_

#include <stdio.h>
#include "Arduino.h"
#include <Arduino_GigaDisplay_GFX.h>
#include <Arduino_GigaDisplayTouch.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

#define CYAN    0x07FF
#define RED     0xf800
#define BLUE    0x001F
#define GREEN   0x07E0
#define MAGENTA 0xF81F
#define WHITE   0xffff
#define BLACK   0x0000
#define YELLOW  0xFFE0

#define NOTHING 0
#define BUTTON 1
#define SLIDER 2
#define TEXTBOX 3



struct Control {
    String name; 
    int type;
    unsigned int x;        //Must be in range 0 - 100
    unsigned int y;
    unsigned int w;
    unsigned int h;
    String dispText;   
    String prevDispText;
    unsigned int fgColor;
    unsigned int bgColor;
    Control();
    
    void setDisplayText(String txt);
};

struct Event {
    int type;
    String name;
    unsigned int x;
    unsigned int y;
    unsigned long t;
    Event();
};
#endif /* _CONTROL_INCLUDE_ */
