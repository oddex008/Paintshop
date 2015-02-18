/*
 * Tool.h
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
 */

#ifndef TOOL_H_
#define TOOL_H_

#include "PixelBuffer.h"
#include "ColorData.h"

class Tool {
public:
	int m_maskWidth;
	int m_maskHeight;
	float *m_mask;

	virtual void applyMask( int x, int y, PixelBuffer &buffer, ColorData color );

	Tool();
	Tool( int radius, float fallOff = 1.0f );
	Tool( int width, int height, float opacity = 1.0f );
	virtual ~Tool();
};

#endif /* TOOL_H_ */
