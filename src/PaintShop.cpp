//
//  ColorData.cpp
//
//  Created by CSCI3081W Guru on 1/15/15.
//  Copyright (c) 2015 CSCI3081W Guru. All rights reserved.
//


#include "PaintShop.h"
#include "ColorData.h"
#include "PixelBuffer.h"

#include "tools/ToolCalligraphyPen.h"
#include "tools/ToolEraser.h"
#include "tools/ToolFill.h"
#include "tools/ToolHighlighter.h"
#include "tools/ToolPen.h"
#include "tools/ToolSprayCan.h"

#include <cmath>

using std::cout;
using std::endl;

PaintShop::PaintShop(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
	// Set the name of the window
	setCaption("PaintShop");
	
	
	// Initialize Interface
	initializeBuffers(backgroundColor, width, height);
	
	// Initialize the tools array
	//TODO: Make initializer list with Tool types?
	m_tools = new Tool*[6];
	m_tools[0] = new ToolPen();
	m_tools[1] = new ToolEraser();
	m_tools[2] = new ToolSprayCan();
	m_tools[3] = new ToolCalligraphyPen();
	m_tools[4] = new ToolHighlighter();
	m_tools[5] = new ToolFill();

	
	initGlui();
	initGraphics();
}

void PaintShop::display()
{
	// TODO: Update the contents of the display buffer
	drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}



PaintShop::~PaintShop()
{
	if (m_displayBuffer)
	{
		delete m_displayBuffer;
	}

	delete m_color;
	delete[] m_tools;
}


void PaintShop::mouseDragged(int x, int y)
{
	
}

void PaintShop::mouseMoved(int x, int y)
{
	
}


void PaintShop::leftMouseDown(int x, int y)
{
	m_tools[m_curTool]->applyMask( x, y, *m_displayBuffer, *m_color );
	std::cout << "mousePressed " << x << " " << y << std::endl;
}

void PaintShop::leftMouseUp(int x, int y)
{
	std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void PaintShop::initializeBuffers(ColorData backgroundColor, int width, int height) {
	m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
}


void PaintShop::initGlui()
{
	// Select first tool (this activates the first radio button in glui)
	m_curTool = 0;
	
	GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
	GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
	
	// Create interface buttons for different tools:
	new GLUI_RadioButton(radio, "Pen");
	new GLUI_RadioButton(radio, "Eraser");
	new GLUI_RadioButton(radio, "Spray Can");
	new GLUI_RadioButton(radio, "Calligraphy Pen");
	new GLUI_RadioButton(radio, "Highlighter");
	new GLUI_RadioButton(radio, "Fill");
	
	GLUI_Panel *colPanel = new GLUI_Panel(m_glui, "Tool Color");
	
	//Initialize the current color data, and pass references to components to the selection ui
	m_color = new ColorData( 0.0f, 0.0f, 0.0f );
	spinner1  = new GLUI_Spinner(colPanel, "Red:", &m_color->m_red, UI_COLOR_R, s_gluicallback);
	spinner1->set_float_limits(0, 1.0);
	
	spinner2  = new GLUI_Spinner(colPanel, "Green:", &m_color->m_green, UI_COLOR_G, s_gluicallback);
	spinner2->set_float_limits(0, 1.0);
	
	spinner3  = new GLUI_Spinner(colPanel, "Blue:", &m_color->m_blue, UI_COLOR_B, s_gluicallback);
	spinner3->set_float_limits(0, 1.0);
	new GLUI_Button(colPanel, "Red", UI_PRESET_RED, s_gluicallback);
	new GLUI_Button(colPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
	new GLUI_Button(colPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
	new GLUI_Button(colPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
	new GLUI_Button(colPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
	new GLUI_Button(colPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
	new GLUI_Button(colPanel, "White", UI_PRESET_WHITE, s_gluicallback);
	new GLUI_Button(colPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
	
	
	new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
}

void PaintShop::gluiControl(int controlID)
{
	switch (controlID)
	{
		case UI_PRESET_RED:
			m_color->setColor( 1.0f, 0.0f, 0.0f );
			break;
		case UI_PRESET_ORANGE:
			m_color->setColor( 1.0f, 0.5f, 0.0f );
			break;
		case UI_PRESET_YELLOW:
			m_color->setColor( 1.0f, 1.0f, 0.0f );
			break;
		case UI_PRESET_GREEN:
			m_color->setColor( 0.0f, 1.0f, 0.0f );
			break;
		case UI_PRESET_BLUE:
			m_color->setColor( 0.0f, 0.0f, 1.0f );
			break;
		case UI_PRESET_PURPLE:
			m_color->setColor( 0.5f, 0.0f, 1.0f );
			break;
		case UI_PRESET_WHITE:
			m_color->setColor( 1.0f, 1.0f, 1.0f );
			break;
		case UI_PRESET_BLACK:
			m_color->setColor( 0.0f, 0.0f, 0.0f );
			break;
		default:
			break;
	}
	
	spinner3->set_float_val( m_color->getBlue() );
	spinner2->set_float_val( m_color->getGreen() );
	spinner1->set_float_val( m_color->getRed() );
}
