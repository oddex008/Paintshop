/*
 * ToolFill.cpp
 *
 *  Created on: Feb 18, 2015
 *      Author: christopher
 */

#include "ToolFill.h"


using std::cerr;
using std::endl;
/**
 * Reverts any pixels touched by non-zero mask values to the background color in
 * the provided pixelbuffer.
 * @param x The x coordinate to be used in applying the mask
 * 		  y The y coordinate to be used in applying the mask
 * 		  buffer The pixelbuffer to erase from
 * 		  color The currently selected color
 */



void ToolFill::applyMask( int x, int y, PixelBuffer &buffer, ColorData color ) {
	cerr << "Call applyMask: " << x << " " << y << endl;
	y = m_maskHeight - y;
	ColorData originColor = buffer.getPixel(x, y);
	buffer.setPixel(x, y, color);
	int yMax = m_maskHeight;
	int xMax = m_maskWidth;
	applyFill(x, y, originColor, color, buffer, xMax, yMax);
	for(int i = 0; i < m_maskHeight * m_maskWidth ; i++ )
	{
		m_loc[i] = 0;
	}
}

void ToolFill::applyFill( int x, int y, ColorData originColor, ColorData fillColor, PixelBuffer &buffer, int xMax, int yMax) {
	cerr << "Iterative Call applyFill: " << x << " " << y << endl;


	/*
	 * Upper Right Quadrant
	 * k(y)++, j(x)++
	 */
	int k = y + 1;
	int j = x;
	while(k < yMax)
	{

		while(j < xMax)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k)))  & ~m_loc[k * m_maskWidth + j])
			{
				m_loc[k * m_maskWidth + j] = 1;
				buffer.setPixel(j, k, fillColor);
				j++;
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		j = x;
		k++;

		if(k < yMax)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)) | colorCompare(fillColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}

	k = y + 1;
	j = x;
	while(j < xMax)
	{
		while(k < yMax)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k))))
			{
				if(m_loc[k * m_maskWidth + j])
				{
					k++;
				}
				else
				{
					m_loc[k * m_maskWidth + j] = 1;
					buffer.setPixel(j, k, fillColor);
					k++;
				}
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		k = y + 1;
		j++;

		if(j < xMax)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)) | colorCompare(fillColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}


	/*
	 * Lower Right Quadrant
	 * k(y)--, j(x)++
	 */

	k = y;
	j = x + 1;
	while(k >= 0)
	{

		while(j < xMax)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k)))  & ~m_loc[k * m_maskWidth + j])
			{
				m_loc[k * m_maskWidth + j] = 1;
				buffer.setPixel(j, k, fillColor);
				j++;
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		j = x;
		k--;

		if(k >= 0)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)) | colorCompare(fillColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}


	k = y;
	j = x + 1;
	while(j < xMax)
	{
		while(k >= 0)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k))))
			{
				if(m_loc[k * m_maskWidth + j])
				{
					k--;
				}
				else
				{
					m_loc[k * m_maskWidth + j] = 1;
					buffer.setPixel(j, k, fillColor);
					k--;
				}
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		k = y;
		j++;

		if(j < xMax)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)) | colorCompare(fillColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}




	/*
	 * Lower Left Quadrant
	 * k(y)--, j(x)--
	 */

	k = y - 1;
	j = x;
	while(k >= 0)
	{
		while(j >= 0)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k)))  & ~m_loc[k * m_maskWidth + j])
			{
				m_loc[k * m_maskWidth + j] = 1;
				buffer.setPixel(j, k, fillColor);
				j--;
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		j = x;
		k--;

		if(k >= 0)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)) | colorCompare(fillColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}


	k = y - 1;
	j = x;
	while(j >= 0)
	{
		while(k >= 0)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k))))
			{
				if(m_loc[k * m_maskWidth + j])
				{
					k--;
				}
				else
				{
					m_loc[k * m_maskWidth + j] = 1;
					buffer.setPixel(j, k, fillColor);
					k--;
				}
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		k = y - 1;
		j--;

		if(j >= 0)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)) | colorCompare(fillColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}





	/*
	 * Upper Left Quadrant
	 * k(y)++, j(x)--
	 */

	k = y;
	j = x - 1;
	while(k < yMax)
	{
		while(j >= 0)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k)))  & ~m_loc[k * m_maskWidth + j])
			{
				m_loc[k * m_maskWidth + j] = 1;
				buffer.setPixel(j, k, fillColor);
				j--;
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		j = x - 1;
		k++;

		if(k < yMax)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)) | colorCompare(fillColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}


	k = y;
	j = x - 1;
	while(j >= 0)
	{
		while(k < yMax)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k))))
			{
				if(m_loc[k * m_maskWidth + j])
				{
					k++;
				}
				else
				{
					m_loc[k * m_maskWidth + j] = 1;
					buffer.setPixel(j, k, fillColor);
					k++;
				}
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		k = y;
		j--;

		if(j >= 0)
		{
			if(colorCompare(originColor, buffer.getPixel(j, k)) | colorCompare(fillColor, buffer.getPixel(j, k)))
			{
			}
			else
			{
				break;
			}
		}
	}


/*
	cerr << "Recursive Call applyFill: " << x << " " << y << endl;
	if(x > 1 && x < xMax && y > 1 && y < yMax)
	{
		ColorData up = buffer.getPixel(x, y + 1);
		ColorData left = buffer.getPixel(x - 1, y);
		ColorData down = buffer.getPixel(x, y - 1);
		ColorData right = buffer.getPixel(x + 1, y);

		if(colorCompare(originColor, up) & ~m_loc[(y + 1) * m_maskWidth + x]){
			m_loc[(y + 1) * m_maskWidth + x] = 1;
			// m_mask[(y + 1) * m_maskWidth + x] = 1.0f;
			buffer.setPixel(x, y + 1, fillColor);
			applyFill(x, y + 1, originColor, fillColor, buffer, xMax, yMax);
		}
		if(colorCompare(originColor, left) & ~m_loc[y * m_maskWidth + (x - 1)]){
			m_loc[y * m_maskWidth + (x - 1)] = 1;
			// m_mask[y * m_maskWidth + (x - 1)] = 1.0f;
			buffer.setPixel(x - 1, y, fillColor);
			applyFill(x - 1, y, originColor, fillColor, buffer, xMax, yMax);
		}

		if(colorCompare(originColor, down) & ~m_loc[(y - 1) * m_maskWidth + x]){
			m_loc[(y - 1) * m_maskWidth + x] = 1;
			// m_mask[(y - 1) * m_maskWidth + x] = 1.0f;
			buffer.setPixel(x, y - 1, fillColor);
			applyFill(x, y - 1, originColor, fillColor, buffer, xMax, yMax);
		}
		if(colorCompare(originColor, right) & ~m_loc[y * m_maskWidth + (x + 1)]){
			m_loc[y * m_maskWidth + (x + 1)] = 1;
			// m_mask[y * m_maskWidth + (x + 1)] = 1.0f;
			buffer.setPixel(x + 1, y, fillColor);
			applyFill(x + 1, y, originColor, fillColor, buffer, xMax, yMax);
		}

	}
	*/
}

bool ToolFill::colorCompare(ColorData a, ColorData b)
{
	return ((a.getRed() == b.getRed()) & (a.getBlue() == b.getBlue()) & (a.getGreen() == b.getGreen()) & (a.getAlpha() == b.getAlpha()));
}



ToolFill::ToolFill() : Tool(800, 800, 0.0f){
	int len = m_maskWidth * m_maskHeight;
	m_loc = new int[len];
	for(int i = 0; i < len ; i++ )
	{
		m_loc[i] = 0;
	}
}

