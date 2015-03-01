/*
 * ToolEraser.h
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
 */

#ifndef TOOLERASER_H_
#define TOOLERASER_H_

#include "Tool.h"

class ToolEraser: public Tool {
public:
	void applyTool( int x, int y, PixelBuffer &buffer, ColorData color );

	ToolEraser();
};

#endif /* TOOLERASER_H_ */
