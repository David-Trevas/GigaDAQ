//
//  GigaDAQ.cpp
//  GigaDAQ
//
//  Created by David A. Trevas on 1/8/25.
//

#include "GigaDAQ.h"

const GFXfont *sansFont[] = {&FreeSans24pt7b, &FreeSans18pt7b, &FreeSans12pt7b, &FreeSans9pt7b};

GigaDAQ::GigaDAQ(){
    screenW = GIGA_DS_WIDTH;
    screenH = GIGA_DS_HEIGHT;
    rotation = PORTRAIT_USBDOWN;
    
}
GigaDAQ::GigaDAQ(int rotation){
    this->rotation = rotation;
    if(rotation == PORTRAIT_USBDOWN || rotation == PORTRAIT_USBUP){
        screenW = GIGA_DS_WIDTH;
        screenH = GIGA_DS_HEIGHT;
    }
    else{
        screenW = GIGA_DS_HEIGHT;
        screenH = GIGA_DS_WIDTH;
    }
}
GigaDAQ::GigaDAQ(unsigned int screenWidth, unsigned int screenHeight, int rotation){
    screenW = screenWidth;
    screenH = screenHeight;
    this->rotation = rotation;
}
void GigaDAQ::begin(void){
	graph.begin();
	touch.begin();
	graph.setRotation(rotation);
}
void GigaDAQ::drawButton(int num){
	int cw, ch, cx, cy;
	int fontNo;
	uint16_t bboxw, bboxh;
	cw = button[num].w * screenW / 100;
	ch = button[num].h * screenH / 100;
	
	if(cw > 0 && ch > 0){
		GFXcanvas16 canvas(cw, ch);
		cx = button[num].x * screenW / 100;
		cy = button[num].y * screenH / 100;
		
		canvas.fillScreen(0x0000);
		canvas.fillRect(0, 0, cw, ch, button[num].bgColor);
		canvas.setTextWrap(false);
		canvas.setTextColor(button[num].fgColor);
		
// 		fontNo = maximizeFont(button[num].dispText, cw, ch, &bboxw, &bboxh);
// 		canvas.setFont(sansFont[fontNo]);
// 		canvas.setCursor((cw - bboxw)/2, ch-(ch-bboxh)/2);

		canvas.setFont(&FreeSans18pt7b);
		canvas.setCursor(cw/10, ch-10);
		canvas.print(button[num].dispText);
		graph.drawRGBBitmap(cx, cy, canvas.getBuffer(), cw, ch);
		button[num].prevDispText = button[num].dispText;
	}
}
void GigaDAQ::drawSlider(int num){
	int cw, ch, cx, cy, smx, smy;
	float fracx, fracy;
	
	cw = slider[num].w * screenW / 100;
	ch = slider[num].h * screenH / 100;
	
	if(cw > 0 && ch > 0){
		GFXcanvas16 canvas(cw, ch);
		cx = slider[num].x * screenW / 100;
		cy = slider[num].y * screenH / 100;
		
		canvas.fillScreen(slider[num].bgColor);
		canvas.drawRect(0, 0, cw, ch, slider[num].fgColor);
		
		if(slider[num].mode == VERTICAL){
			fracx = 1.0;
		}
		else{
			fracx = (slider[num].posX - slider[num].minX)/(slider[num].maxX - slider[num].minX);
		}
		smx = (int)(fracx * cw);
		
		if(slider[num].mode == HORIZONTAL){
			fracy = 1.0;
		}
		else{
			fracy = (slider[num].posY - slider[num].minY)/(slider[num].maxY - slider[num].minY);
		}
		smy = (int)(fracy * ch);
		
		canvas.fillRect(0, ch-smy, smx, smy, slider[num].fgColor);
		
		
		graph.drawRGBBitmap(cx, cy, canvas.getBuffer(), cw, ch);
	}
}
void GigaDAQ::drawTextbox(int num){
	int cw, ch, cx, cy, fontNo;
	uint16_t bboxw, bboxh;
	cw = textbox[num].w * screenW / 100;
	ch = textbox[num].h * screenH / 100;
	
	if(cw > 0 && ch > 0){
		GFXcanvas16 canvas(cw, ch);
		cx = textbox[num].x * screenW / 100;
		cy = textbox[num].y * screenH / 100;
		
		canvas.fillScreen(0x0000);
		canvas.fillRect(0, 0, cw, ch, textbox[num].bgColor);
		canvas.setTextWrap(false);
		canvas.setTextColor(textbox[num].fgColor);
		
	// 	fontNo = maximizeFont(textbox[num].dispText, cw, ch, &bboxw, &bboxh);
// 		canvas.setFont(sansFont[fontNo]);
// 		canvas.setCursor((cw - bboxw)/2, ch-(ch-bboxh)/2);
		
		canvas.setFont(&FreeSans18pt7b);
		canvas.setCursor(cw/10, ch-10);
		canvas.print(textbox[num].dispText);
		graph.drawRGBBitmap(cx, cy, canvas.getBuffer(), cw, ch);
		textbox[num].prevDispText = textbox[num].dispText;
	}
}
void GigaDAQ::drawAll(){
    int i;
    
    graph.fillScreen(0x0000);
    
    for(i = 0; i < NUM_BUTTONS; i++){
        if(button[i].w > 0 && button[i].h > 0){
        	drawButton(i);
        }
    }
    
    for(i = 0; i < NUM_SLIDERS; i++){
        if(slider[i].w > 0 && slider[i].h > 0){
            drawSlider(i);
        }
    }
    
    for(i = 0; i < NUM_TEXTBOXES; i++){
        if(textbox[i].w > 0 && textbox[i].h > 0){
            drawTextbox(i);
        }
    }
}
void GigaDAQ::locate(int touchX, int touchY){
    unsigned px=0, py=0, cx, cy, cw, ch;
    float fracx, fracy, slidx, slidy;
    
    int i;
    bool matchFound = false;
    
    switch(rotation){
        case PORTRAIT_USBDOWN:
            px = touchX * 100 / screenW;
            py = touchY * 100 / screenH;
            break;
        case LANDSCAPE_USBRIGHT:
            px = touchY * 100 / screenW;
            py = (screenH - touchX) * 100 / screenH;
            break;
        case PORTRAIT_USBUP:
            px = (screenW - touchX) * 100 / screenW;
            py = (screenH - touchY) * 100 / screenH;
            break;
        case LANDSCAPE_USBLEFT:
            px = (screenW - touchY) * 100 / screenW;
            py = touchX * 100 / screenH;
            break;
    }
    
    i = 0;
    
    do{
        cw = button[i].w;
        ch = button[i].h;
        if(cw > 0 && ch > 0){
            cx = button[i].x;
            cy = button[i].y;
            if(cx < px && px <= cx+cw && cy < py && py <= cy+ch){
                matchFound = true;
                currentEvent.type = BUTTON;
                currentEvent.name = button[i].name;
                currentEvent.x = px;
                currentEvent.y = py;
                currentEvent.t = millis();
            }
        }
        i++;
    }while(i < NUM_BUTTONS && matchFound == false);
    
    if(matchFound == false){
        i = 0;
        do{
            cw = slider[i].w;
            ch = slider[i].h;
            if(cw > 0 && ch > 0){
                cx = slider[i].x;
                cy = slider[i].y;
                if(cx < px && px <= cx+cw && cy < py && py <= cy+ch){
                    matchFound = true;
                    currentEvent.type = SLIDER;
                    currentEvent.name = slider[i].name;
                    currentEvent.x = px;
                    currentEvent.y = py;
                    currentEvent.t = millis();
                    fracx = (float)(px - cx)/(float)cw;
                    slidx = slider[i].minX + fracx*(slider[i].maxX - slider[i].minX);
                    fracy = (float)((cy+ch)-py)/(float)ch;
                    slidy = slider[i].minY + fracy*(slider[i].maxY - slider[i].minY);
                    slider[i].posX = slidx;
                    slider[i].posY = slidy;
                    drawSlider(i);
                }
            }
            i++;
        }while(i < NUM_SLIDERS && matchFound == false);
    }
    
    if(matchFound == false){
        currentEvent.type = NOTHING;
        currentEvent.name = "";
        currentEvent.x = 0;
        currentEvent.y = 0;
        currentEvent.t = 0;
    }
    return;
}
int GigaDAQ::arrayPosition(int type, String name){
    int i, val=-1;
    bool matchFound = false;
    
    if(type == BUTTON){
        i = 0;
        do{
            if(button[i].name.equals(name)){
                matchFound = true;
                val = i;
            }
            i++;
        } while(i < NUM_BUTTONS && matchFound == false);
    }
    else if(type == SLIDER){
        i = 0;
        do{
            if(slider[i].name.equals(name)){
                matchFound = true;
                val = i;
            }
            i++;
        } while(i < NUM_SLIDERS && matchFound == false);
    }
    else if(type == TEXTBOX){
        i = 0;
        do{
            if(textbox[i].name.equals(name)){
                matchFound = true;
                val = i;
            }
            i++;
        } while(i < NUM_TEXTBOXES && matchFound == false);
    }
    
    return val;
}
void GigaDAQ::takeAction(void){
    int num;
    float fracx, fracy, slidx, slidy;
    
    //Button action when finger lifts from button
    if(previousEvent.type == BUTTON && currentEvent.type == NOTHING){
        num = arrayPosition(BUTTON, previousEvent.name);
        if(num >= 0){
            button[num].release();
        }
    }
    
    //Slider responds if finger stays in slider
    
    if(previousEvent.type == SLIDER && currentEvent.type == SLIDER && previousEvent.name == currentEvent.name){
        num = arrayPosition(SLIDER, currentEvent.name);
        if(num >= 0){
            slider[num].sliderMotion();
        }
    }
    
    //Other actions will go here
}
void GigaDAQ::handleInputs(void){
	uint8_t contacts;
	GDTpoint_t points[5];
	int tpx, tpy;
	
	contacts = touch.getTouchPoints(points);
	
	if(contacts > 0){
		tpx = points[0].x;
		tpy = points[0].y;
	}
	else{
		tpx = 0;
		tpy = 0;
	}
	locate(tpx, tpy);
	takeAction();
	previousEvent = currentEvent;
	
	
}
void GigaDAQ::updateDisplays(void){
	int i;
	for(i=0; i<NUM_TEXTBOXES; i++){
		if(textbox[i].w > 0 && textbox[i].h > 0 && textbox[i].dispText.equals(textbox[i].prevDispText) == false){
			drawTextbox(i);
			textbox[i].prevDispText = textbox[i].dispText;
		}
	}
}
int GigaDAQ::maximizeFont(String dt, int boxW, int boxH, uint16_t *boundBoxW, uint16_t *boundBoxH){
	int i, retval;
	int16_t xout, yout;
	uint16_t widout, hgtout;
	bool matchFound = false;
	
	
	graph.setTextWrap(false);
	
	i = 0;
	
	do{
		graph.setFont(sansFont[i]);
		graph.getTextBounds(dt, 0, 0, &xout, &yout, &widout, &hgtout);
		if(widout < boxW*95/100 && hgtout < boxH*95/100){
			retval = i;
			matchFound = true;
			*boundBoxW = widout;
			*boundBoxH = hgtout;
		}
		i++;
	} while( i <= 2 && matchFound == false);
	
	if(matchFound == false){
		retval = 3;
		graph.setFont(sansFont[retval]);
		graph.getTextBounds(dt, 0, 0, &xout, &yout, &widout, &hgtout);
		*boundBoxW = widout;
		*boundBoxH = hgtout;	
	}
	
	return retval;
}
