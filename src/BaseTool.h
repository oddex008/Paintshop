/*
 * BaseTool.h
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
 */

#ifndef BASETOOL_H_
#define BASETOOL_H_

#include "PixelBuffer.h"
#include "ColorData.h"

class BaseTool {
public:
	int m_maskWidth;
	int m_maskHeight;
	float *m_mask;

	virtual void applyMask( int x, int y, PixelBuffer &buffer, ColorData color );

	BaseTool( int radius, float fallOff = 1.0f );
	BaseTool( int width, int height, float opacity = 1.0f );
	virtual ~BaseTool();
};

#endif /* BASETOOL_H_ */
