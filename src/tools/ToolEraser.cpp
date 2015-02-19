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

}

/**
 * Initializes an eraser with a radius of 16px.
 */
ToolEraser::ToolEraser() : Tool( 16, 1.0f ) { }

