/*
 * ToolFill.h
 *
 *  Created on: Feb 28, 2015
 *      Author: Tom Odde
 */

#ifndef TOOLFILL_H_
#define TOOLFILL_H_

#include "Tool.h"

class ToolFill: public Tool {
public:
	int *m_loc;
	void applyMask( int x, int y, PixelBuffer &buffer, ColorData color );
	void applyFill( int x, int y, ColorData originColor, ColorData fillColor, PixelBuffer &buffer, int xMax, int yMax);
	bool colorCompare(ColorData a, ColorData b);
	bool checkRecurse(int x, int y, ColorData fillColor, PixelBuffer &buffer);
	int canvasTraverseY(int x, int y, int xmove, int ymove, int xlim, int ylim, ColorData originColor, ColorData fillColor, PixelBuffer &buffer);
	int canvasTraverseX(int x, int y, int xmove, int ymove, int xlim, int ylim, ColorData originColor, ColorData fillColor, PixelBuffer &buffer);
	ToolFill();
};

#endif /* TOOLFILL_H_ */
