/*
 * ToolFill.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: Tom Odde
 */

#include "ToolFill.h"


/**
 * Changes the selected pixels and all neighboring pixels that are the
 * same color to the selected color.
 * @param x The x coordinate to be used in applying the mask
 * 		  y The y coordinate to be used in applying the mask
 * 		  buffer The pixelbuffer
 * 		  color The currently selected color
 */



void ToolFill::applyTool( int x, int y, PixelBuffer &buffer, ColorData color ) {
	y = buffer.getHeight() - y;
	ColorData originColor = buffer.getPixel(x, y);
	int yMax = buffer.getHeight();
	int xMax = buffer.getWidth();
	applyFill(x, y, originColor, color, buffer, xMax, yMax);


	bool workDone = 1;
	while(workDone)
	{
		workDone = 0;
		for(int j = 1; j < xMax - 1 ; j++ )
		{
			for(int k = 1; k < yMax - 1; k++)
			{
				if(checkRecurse(j, k, color, buffer) & colorCompare(originColor, buffer.getPixel(j, k)))
				{
					applyFill(j, k, originColor, color, buffer, xMax, yMax);
					workDone = 1;
				}
			}
		}
	}

	for(int i = 0; i < yMax * xMax ; i++ )
	{
		m_loc[i] = 0;
	}
}

void ToolFill::applyFill( int x, int y, ColorData originColor, ColorData fillColor, PixelBuffer &buffer, int xMax, int yMax) {
	buffer.setPixel(x, y, fillColor);

	canvasTraverseY(x, y + 1, 1, 1, xMax, yMax, originColor, fillColor, buffer);
	canvasTraverseX(x, y + 1, 1, 1, xMax, yMax, originColor, fillColor, buffer);

	canvasTraverseY(x + 1, y, 1, -1, xMax, -1, originColor, fillColor, buffer);
	canvasTraverseX(x + 1, y, 1, -1, xMax, -1, originColor, fillColor, buffer);

	canvasTraverseY(x, y - 1, -1, -1, -1, -1, originColor, fillColor, buffer);
	canvasTraverseX(x, y - 1, -1, -1, -1, -1, originColor, fillColor, buffer);

	canvasTraverseY(x - 1, y, -1, 1, -1, yMax, originColor, fillColor, buffer);
	canvasTraverseX(x - 1, y, -1, 1, -1, yMax, originColor, fillColor, buffer);

}

bool ToolFill::colorCompare(ColorData a, ColorData b)
{
	return ((a.getRed() == b.getRed()) & (a.getBlue() == b.getBlue()) & (a.getGreen() == b.getGreen()) & (a.getAlpha() == b.getAlpha()));
}

bool ToolFill::checkRecurse(int x, int y, ColorData fillColor, PixelBuffer &buffer)
{
	int xMax = buffer.getWidth() - 1;
	int yMax = buffer.getHeight() - 1;

	if(colorCompare(fillColor, buffer.getPixel(x, y)))
	{
		return 0;
	}

	if(x >= 1 && x < xMax && y >= 1 && y < yMax)
	{
		ColorData up = buffer.getPixel(x, y + 1);
		ColorData left = buffer.getPixel(x - 1, y);
		ColorData down = buffer.getPixel(x, y - 1);
		ColorData right = buffer.getPixel(x + 1, y);
		if(colorCompare(fillColor, left) & m_loc[y * buffer.getWidth() + (x - 1)])
		{
			return 1;
		}
		else if(colorCompare(fillColor, down) & m_loc[(y - 1) * buffer.getWidth() + x])
		{
			return 1;
		}
		else if(colorCompare(fillColor, up) & m_loc[(y + 1) * buffer.getWidth() + x])
		{
			return 1;
		}
		else if(colorCompare(fillColor, right) & m_loc[y * buffer.getWidth() + (x + 1)])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void ToolFill::canvasTraverseY(int x, int y, int xmove, int ymove, int xlim, int ylim, ColorData originColor, ColorData fillColor, PixelBuffer &buffer)
{

	int k = y;
	int j = x;
	int width = buffer.getWidth();
	while(k != ylim)
	{
		while(j != xlim)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k))  & ~m_loc[k * width + j])
			{
				m_loc[k * width + j] = 1;
				buffer.setPixel(j, k, fillColor);
				j += xmove;
			}
			else
			{
				m_loc[k * width + j] = 1;
				break;
			}
		}
		j = x;
		k += ymove;

		if(k != ylim)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}
}

void ToolFill::canvasTraverseX(int x, int y, int xmove, int ymove, int xlim, int ylim, ColorData originColor, ColorData fillColor, PixelBuffer &buffer)
{

	int k = y;
	int j = x;
	int width = buffer.getWidth();
	while(j != xlim)
	{
		while(k != ylim)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)))
			{
				if(m_loc[k * width + j])
				{
					k += ymove;
				}
				else
				{
					m_loc[k * width + j] = 1;
					buffer.setPixel(j, k, fillColor);
					k += ymove;
				}
			}
			else
			{
				m_loc[k * width + j] = 1;
				break;
			}
		}
		k = y;
		j += xmove;

		if(j != xlim)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}
}

ToolFill::ToolFill() : Tool(){
	int dim = 800;
	int len = dim * dim;
	m_loc = new int[len];
	for(int i = 0; i < len ; i++ )
	{
		m_loc[i] = 0;
	}
}

