//
//  GigaDAQ.h
//  GigaDAQ
//
//  Created by David A. Trevas on 1/8/25.
//

#ifndef _GIGADAQ_INCLUDE_
#define _GIGADAQ_INCLUDE_

#include <stdio.h>
#include "DAQControls.h"

#define NUM_BUTTONS 		20
#define NUM_SLIDERS 		10
#define NUM_TEXTBOXES 		15

#define PORTRAIT_USBDOWN 	0
#define LANDSCAPE_USBRIGHT 	1
#define PORTRAIT_USBUP 		2
#define LANDSCAPE_USBLEFT 	3

#define GIGA_DS_WIDTH 		480
#define GIGA_DS_HEIGHT 		800

class GigaDAQ {
public:
    unsigned int screenW;
    unsigned int screenH;
    int rotation;
    Button button[NUM_BUTTONS];
    Slider slider[NUM_SLIDERS];
    Textbox textbox[NUM_TEXTBOXES];
    Event currentEvent;
    Event previousEvent;
    GigaDisplay_GFX graph;
	Arduino_GigaDisplayTouch touch;
    GigaDAQ();
    GigaDAQ(int rotation);
    GigaDAQ(unsigned int screenWidth, unsigned int screenHeight, int rotation);
    void begin(void);
    void drawAll();
    void drawButton(int num);
    void drawSlider(int num);
    void drawTextbox(int num);
    void locate(int touchX, int touchY);
    int arrayPosition(int type, String name);
    void takeAction(void);
    void handleInputs(void);
    void updateDisplays(void);
private:
	int maximizeFont(String dt, int boxW, int boxH, uint16_t *boundBoxW, uint16_t *boundBoxH);
};
#endif /* _GIGADAQ_INCLUDE_ */
