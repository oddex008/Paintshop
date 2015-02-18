/*
 * BaseTool.cpp
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
 */

#include <math.h>
#include "BaseTool.h"

/**
 * Applies this tools mask to the provided pixel buffer, updating pixels with the
 * provided color data.
 * @param x The x coordinate to be used in applying the mask
 * 		  y The y coordinate to be used in applying the mask
 * 		  buffer The pixelbuffer to apply this tool to, passed by reference
 * 		  color The colordata to utilize in applying this tool
 */
void BaseTool::applyMask( int x, int y, PixelBuffer &buffer, ColorData color ) {

}

/**
 * Initializes a tool with a circular mask with the given radius, with linear
 * falloff to the provided mask value.
 * @param radius The radius of the mask, in pixels
 * 		  fallOff The mask value of the outermost mask pixels
 */
BaseTool::BaseTool( int radius, float fallOff ) {
	// TODO Auto-generated constructor stub

}

/**
 * Initializes a tool with a rectangular/square mask, with the given opacity.
 * @param width The x dimension of the mask
 * 		  height The y dimension of the mask
 * 		  opacity The uniform mask value
 */
BaseTool::BaseTool( int width, int height, float opacity ) {
	// TODO Auto-generated constructor stub

}

/**
 * Releases any resources used by this tool.
 */
BaseTool::~BaseTool() {
	delete[] m_mask; //Free the mask array
}
