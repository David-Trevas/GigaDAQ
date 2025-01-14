//
//  DAQControls.cpp
//  GigaDAQ
//
//  Created by David A. Trevas on 1/8/25.
//

#include "DAQControls.h"


Button::Button(){
    type = BUTTON;
    name = "";
    w = 0;
    h = 0;
    this->buttonUp = nullptr;
}
Button::Button(String nm, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c1,  unsigned int c2){
    name = nm;
    type = BUTTON;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    fgColor = c1;
    bgColor = c2;
    this->buttonUp = nullptr;
}
void Button::setButtonUp(void (*du)()){
	this->buttonUp = du;
}
void Button::release(){
	if(buttonUp != nullptr){
		(*buttonUp)();
	}
}

Slider::Slider(){
    type = SLIDER;
    name = "";
    w = 0;
    h = 0;
    mode = HORIZONTAL;
    minX = 0.0;
    maxX = 1.0;
    minY = 0.0;
    maxY = 1.0;
    posX = 0.5;
    posY = 0.5;
    this->slide = nullptr;
}
Slider::Slider(String nm, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c1,  unsigned int c2){
    name = nm;
    type = SLIDER;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    fgColor = c1;
    bgColor = c2;
    mode = HORIZONTAL;
    minX = 0.0;
    maxX = 1.0;
    minY = 0.0;
    maxY = 1.0;
    posX = 0.5;
    posY = 0.5;
    this->slide = nullptr;
}
void Slider::setXlimits(float minimumX, float maximumX){
    minX = minimumX;
    maxX = maximumX;
}
void Slider::setYlimits(float minimumY, float maximumY){
    minY = minimumY;
    maxY = maximumY;
}
void Slider::setPosition(float px, float py){
	posX = px;
	posY = py;
}
void Slider::setMode(int md){
	mode = md;
}
void Slider::setSlideAction(void(*sf)()){
	this->slide = sf;
}
void Slider::sliderMotion(){
	if(slide != nullptr){
		(*slide)();
	}
}
    
Textbox::Textbox(){
    type = TEXTBOX;
    name = "";
    w = 0;
    h = 0;
}
Textbox::Textbox(String nm, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c1,  unsigned int c2){
    name = nm;
    type = TEXTBOX;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    fgColor = c1;
    bgColor = c2;
}
