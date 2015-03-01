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
	void applyMask( int x, int y, PixelBuffer &buffer, ColorData color );
	ToolFill();
private:
	void applyFill( int x, int y, ColorData originColor, ColorData fillColor, PixelBuffer &buffer, int xMax, int yMax);
	bool colorCompare(ColorData a, ColorData b);
	bool checkRecurse(int x, int y, ColorData fillColor, PixelBuffer &buffer);
	void canvasTraverseY(int x, int y, int xmove, int ymove, int xlim, int ylim, ColorData originColor, ColorData fillColor, PixelBuffer &buffer);
	void canvasTraverseX(int x, int y, int xmove, int ymove, int xlim, int ylim, ColorData originColor, ColorData fillColor, PixelBuffer &buffer);
	int *m_loc;
};

#endif /* TOOLFILL_H_ */
