//
//  Control.cpp
//  GigaDAQ
//
//  Created by David A. Trevas on 1/8/25.
//

#include "Control.h"

Control::Control(){}
void Control::setDisplayText(String txt){
    prevDispText = dispText;
    dispText = txt;
}

Event::Event(){
    type = NOTHING;
    name = "";
    x = 0;
    y = 0;
    t = 0;
}
