/*
 * Tool.cpp
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
 */

#include <math.h>
#include "Tool.h"

/**
 * Applies this tools mask to the provided pixel buffer, updating pixels with the
 * provided color data.
 * @param x The x coordinate to be used in applying the mask
 * 		  y The y coordinate to be used in applying the mask
 * 		  buffer The pixelbuffer to apply this tool to, passed by reference
 * 		  color The colordata to utilize in applying this tool
 */
void Tool::applyTool( int x, int y, PixelBuffer &buffer, ColorData color ) {
	int originX = x - ( m_maskWidth / 2 );
	int originY = ( buffer.getHeight() - y ) - ( m_maskHeight / 2 );

	for( int row = 0; row < m_maskHeight; row++ ) {
		for( int col = 0; col < m_maskWidth; col++ ) {
			float opacity = getOpacity( col, row );
			buffer.setPixel( col + originX, row + originY, ( color * opacity ) + ( buffer.getPixel( col + originX, row + originY ) * ( 1.0f - opacity ) ) );
		}
	}
}

/**
 * Initializes a tool with an empty mask.
 */
Tool::Tool() {
	m_maskWidth = 0;
	m_maskHeight = 0;
	m_mask = new float[0]; //Seems unnecessary, but at least we know the mask is initialized
}

/**
 * Initializes a tool with a circular mask with the given radius, with linear
 * falloff to the provided mask value.
 * @param radius The radius of the mask, in pixels
 * 		  fallOff The mask value of the outermost mask pixels
 */
Tool::Tool( int radius, float fallOff ) {
	int diameter = 2 * radius;
	m_maskWidth = diameter;
	m_maskHeight = diameter;

	m_mask = new float[m_maskWidth * m_maskHeight];

	//Iterate over all pixels in the mask, in row major fashion
	for( int y = 0; y < m_maskHeight; y++ ) {
		for( int x = 0; x < m_maskWidth; x++ ) {
			float distance = sqrt( pow( radius - x, 2 ) + pow( radius - y, 2) );
			float opacity = distance > radius ? 0.0f : 1.0f - ( ( 1.0f - fallOff ) * distance ) / radius;
			m_mask[ y * m_maskWidth + x ] = opacity;
		}
	}
}

/**
 * Initializes a tool with a rectangular/square mask, with the given opacity.
 * @param width The x dimension of the mask
 * 		  height The y dimension of the mask
 * 		  opacity The uniform mask value
 */
Tool::Tool( int width, int height, float opacity ) {
	m_maskWidth = width;
	m_maskHeight = height;

	m_mask = new float[m_maskWidth * m_maskHeight];

	for( int y = 0; y < m_maskHeight; y++ ) {
		for( int x = 0; x < m_maskWidth; x++ ) {
			m_mask[ y * m_maskWidth + x ] = opacity;
		}
	}
}

/**
 * Releases any resources used by this tool.
 */
Tool::~Tool() {
	delete[] m_mask; //Free the mask array
}
