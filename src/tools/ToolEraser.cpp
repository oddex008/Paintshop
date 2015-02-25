/*
 * ToolEraser.cpp
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
 */

#include "ToolEraser.h"

/**
 * Reverts any pixels touched by non-zero mask values to the background color in
 * the provided pixelbuffer.
 * @param x The x coordinate to be used in applying the mask
 * 		  y The y coordinate to be used in applying the mask
 * 		  buffer The pixelbuffer to erase from
 * 		  color The currently selected color
 */
void ToolEraser::applyMask( int x, int y, PixelBuffer &buffer, ColorData color ) {
	ColorData bgColor = buffer.getBackgroundColor();
	int originX = x - ( m_maskWidth / 2 );
	int originY = ( buffer.getHeight() - y ) - ( m_maskHeight / 2 );

	for( int row = 0; row < m_maskHeight; row++ ) {
		for( int col = 0; col < m_maskWidth; col++ ) {
			float opacity = m_mask[row * m_maskWidth + col];
			buffer.setPixel( col + originX, row + originY, ( bgColor * opacity ) + ( buffer.getPixel( col + originX, row + originY ) * ( 1.0f - opacity ) ) );
		}
	}

}

/**
 * Initializes an eraser with a radius of 16px.
 */
ToolEraser::ToolEraser() : Tool( 16, 1.0f ) { }

