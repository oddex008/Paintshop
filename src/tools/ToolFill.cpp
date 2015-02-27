/*
 * ToolFill.cpp
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
 */

#include "ToolFill.h"

/**
 * Reverts any pixels touched by non-zero mask values to the background color in
 * the provided pixelbuffer.
 * @param x The x coordinate to be used in applying the mask
 * 		  y The y coordinate to be used in applying the mask
 * 		  buffer The pixelbuffer to erase from
 * 		  color The currently selected color
 */

void ToolFill::implementMask( int x, int y, PixelBuffer &buffer, ColorData color ) {
	int ylim = buffer.getWidth();
	int xlim = buffer.getHeight();
	int originX = 0;
	int originY = 0;

	for( int row = 0; row < ylim; row++ ) {
		for( int col = 0; col < xlim; col++ ) {
			float opacity = m_mask[row * m_maskWidth + col];
			buffer.setPixel( col + originX, ylim - (row + originY), ( color * opacity ) + ( buffer.getPixel( col + originX, row + originY ) * ( 1.0f - opacity ) ) );
		}
	}
}

void ToolFill::applyMask( int x, int y, PixelBuffer &buffer, ColorData color ) {
	ColorData originColor = buffer.getPixel(x, y);
	buffer.setPixel(x, y, color);
	m_mask[y * m_maskWidth + x] = 1.0f;
	m_loc[y * m_maskWidth + x] = 1;
	int yMax = buffer.getHeight() - 1;
	int xMax = buffer.getWidth() - 1;
	applyFill(x, y, originColor, color, buffer, xMax, yMax);
	implementMask(x, y, buffer, color);
}

void ToolFill::applyFill( int x, int y, ColorData originColor, ColorData fillColor, PixelBuffer &buffer, int xMax, int yMax) {

	if(x > 1 && x < xMax && y > 1 && y < yMax)
	{
		ColorData up = buffer.getPixel(x, y + 1);
		ColorData left = buffer.getPixel(x - 1, y);
		ColorData down = buffer.getPixel(x, y - 1);
		ColorData right = buffer.getPixel(x + 1, y);

		if(colorCompare(originColor, up) & ~colorCompare(fillColor, up) & ~m_loc[(y + 1) * m_maskWidth + x]){
			m_loc[(y + 1) * m_maskWidth + x] = 1;
			m_mask[(y + 1) * m_maskWidth + x] = 1.0f;
			applyFill(x, y + 1, originColor, fillColor, buffer, xMax, yMax);
		}
		if(colorCompare(originColor, left) & ~colorCompare(fillColor, left) & ~m_loc[y * m_maskWidth + (x - 1)]){
			m_loc[y * m_maskWidth + (x - 1)] = 1;
			m_mask[y * m_maskWidth + (x - 1)] = 1.0f;
			applyFill(x - 1, y, originColor, fillColor, buffer, xMax, yMax);
		}
		if(colorCompare(originColor, down) & ~colorCompare(fillColor, down) & ~m_loc[(y - 1) * m_maskWidth + x]){
			m_loc[(y - 1) * m_maskWidth + x] = 1;
			m_mask[(y - 1) * m_maskWidth + x] = 1.0f;
			applyFill(x, y - 1, originColor, fillColor, buffer, xMax, yMax);
		}
/*
		if(colorCompare(originColor, right) & ~colorCompare(fillColor, right) & ~m_loc[y * m_maskWidth + (x + 1)]){
			m_loc[y * m_maskWidth + (x + 1)] = 1;
			m_mask[y * m_maskWidth + (x + 1)] = 1.0f;
			applyFill(x + 1, y, originColor, fillColor, buffer, xMax, yMax);
		}
*/

	}
}

bool ToolFill::colorCompare(ColorData a, ColorData b)
{
	return ((a.getRed() == b.getRed()) & (a.getBlue() == b.getBlue()) & (a.getGreen() == b.getGreen()) & (a.getAlpha() == b.getAlpha()));
}



ToolFill::ToolFill() : Tool(600, 800, 0.0f){
	int len = m_maskWidth * m_maskHeight;
	m_loc = new int[len];
	for(int i = 0; i < len ; i++ )
	{
		m_loc[i] = 0;
	}

}

