/*
 * ToolFill.h
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
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
	ToolFill();
};

#endif /* TOOLFILL_H_ */
