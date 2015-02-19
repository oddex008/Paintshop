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
	void applyMask( int x, int y, PixelBuffer &buffer, ColorData color );

	ToolFill();
};

#endif /* TOOLFILL_H_ */
