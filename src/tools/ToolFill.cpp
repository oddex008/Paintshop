/*
 * ToolFill.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: Tom Odde
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

/*
 * TODO: Need to not make the fillColor a condition.
 */


void ToolFill::applyMask( int x, int y, PixelBuffer &buffer, ColorData color ) {
	cerr << "Call applyMask: " << x << " " << y << endl;
	y = m_maskHeight - y;
	ColorData originColor = buffer.getPixel(x, y);
	int yMax = m_maskHeight;
	int xMax = m_maskWidth;
	applyFill(x, y, originColor, color, buffer, xMax, yMax);


	bool workDone = 1;

	while(workDone)
	{
		workDone = 0;
		for(int j = 1; j < buffer.getWidth() - 1 ; j++ )
		{
			for(int k = 1; k < buffer.getHeight() - 1; k++)
			{
				if(checkRecurse(j, k, color, buffer) & colorCompare(originColor, buffer.getPixel(j, k)))
				{
					applyFill(j, k, originColor, color, buffer, xMax, yMax);
					workDone = 1;
				}
			}
		}
	}


	for(int i = 0; i < m_maskHeight * m_maskWidth ; i++ )
	{
		m_loc[i] = 0;
	}
}

void ToolFill::applyFill( int x, int y, ColorData originColor, ColorData fillColor, PixelBuffer &buffer, int xMax, int yMax) {
	cerr << "Iterative Call applyFill: " << x << " " << y << endl;
	buffer.setPixel(x, y, fillColor);

	int ur_y = canvasTraverseY(x, y + 1, 1, 1, xMax, yMax, originColor, fillColor, buffer);
	int ur_x = canvasTraverseX(x, y + 1, 1, 1, xMax, yMax, originColor, fillColor, buffer);

	int lr_y = canvasTraverseY(x + 1, y, 1, -1, xMax, -1, originColor, fillColor, buffer);
	int lr_x = canvasTraverseX(x + 1, y, 1, -1, xMax, -1, originColor, fillColor, buffer);

	int ll_y = canvasTraverseY(x, y - 1, -1, -1, -1, -1, originColor, fillColor, buffer);
	int ll_x = canvasTraverseX(x, y - 1, -1, -1, -1, -1, originColor, fillColor, buffer);

	int ul_y = canvasTraverseY(x - 1, y, -1, 1, -1, yMax, originColor, fillColor, buffer);
	int ul_x = canvasTraverseX(x - 1, y, -1, 1, -1, yMax, originColor, fillColor, buffer);


	/*
	 * Upper Right Quadrant
	 * k(y)++, j(x)++
	 */


	//int k = y + 1;
	//int j = x;
	/*
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

	int ur_y = k;

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

	int ur_x = j;
*/


	/*
	 * Lower Right Quadrant
	 * k(y)--, j(x)++
	 */

	/*
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

	int lr_y = k;

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

	int lr_x = j;

*/
	/*
	 * Lower Left Quadrant
	 * k(y)--, j(x)--
	 */
/*
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

	int ll_y = k;

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

	int ll_x = j;

*/

	/*
	 * Upper Left Quadrant
	 * k(y)++, j(x)--
	 */
/*
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

	int ul_y = k;


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

	int ul_x = j;
*/


	/*
	 * Recursive calls if pockets were missed by the loops above.
	 *
	 * To get a call
	 * Same color as origin was:
	 * In bounds.
	 *
	 */

	/*
	if(checkRecurse(ur_x, ur_y, fillColor, buffer) & colorCompare(originColor, buffer.getPixel(ur_x, ur_y)))
	{
		cerr << "Recursive Call applyFill ur: " << ur_x << " " << ur_y << endl;
		applyFill(ur_x, ur_y, originColor, fillColor, buffer, xMax, yMax);
	}
	if(checkRecurse(lr_x, lr_y, fillColor, buffer) & colorCompare(originColor, buffer.getPixel(lr_x, lr_y)))
	{
		cerr << "Recursive Call applyFill lr: " << lr_x << " " << lr_y << endl;
		applyFill(lr_x, lr_y, originColor, fillColor, buffer, xMax, yMax);
	}
	if(checkRecurse(ll_x, ll_y, fillColor, buffer) & colorCompare(originColor, buffer.getPixel(ll_x, ll_y)))
	{
		cerr << "Recursive Call applyFill ll: " << ll_x << " " << ll_y << endl;
		applyFill(ll_x, ll_y, originColor, fillColor, buffer, xMax, yMax);
	}
	if(checkRecurse(ul_x, ul_y, fillColor, buffer) & colorCompare(originColor, buffer.getPixel(ul_x, ul_y)))
	{
		cerr << "Recursive Call applyFill ul: " << ul_x << " " << ul_y << endl;
		applyFill(ul_x, ul_y, originColor, fillColor, buffer, xMax, yMax);
	}

*/
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
		if(colorCompare(fillColor, left) & m_loc[y * m_maskWidth + (x - 1)])
		{
			return 1;
		}
		else if(colorCompare(fillColor, down) & m_loc[(y - 1) * m_maskWidth + x])
		{
			return 1;
		}
		else if(colorCompare(fillColor, up) & m_loc[(y + 1) * m_maskWidth + x])
		{
			return 1;
		}
		else if(colorCompare(fillColor, right) & m_loc[y * m_maskWidth + (x + 1)])
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

int ToolFill::canvasTraverseY(int x, int y, int xmove, int ymove, int xlim, int ylim, ColorData originColor, ColorData fillColor, PixelBuffer &buffer)
{

	int k = y;
	int j = x;
	while(k != ylim)
	{
		while(j != xlim)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k)))  & ~m_loc[k * m_maskWidth + j])
			{
				m_loc[k * m_maskWidth + j] = 1;
				buffer.setPixel(j, k, fillColor);
				j += xmove;
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		j = x;
		k += ymove;

		if(k != ylim)
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
	return k;
}

int ToolFill::canvasTraverseX(int x, int y, int xmove, int ymove, int xlim, int ylim, ColorData originColor, ColorData fillColor, PixelBuffer &buffer)
{

	int k = y;
	int j = x;
	while(j != xlim)
	{
		while(k != ylim)
		{
			if((colorCompare(originColor, buffer.getPixel(j, k)) || colorCompare(fillColor, buffer.getPixel(j, k))))
			{
				if(m_loc[k * m_maskWidth + j])
				{
					k += ymove;
				}
				else
				{
					m_loc[k * m_maskWidth + j] = 1;
					buffer.setPixel(j, k, fillColor);
					k += ymove;
				}
			}
			else
			{
				m_loc[k * m_maskWidth + j] = 1;
				break;
			}
		}
		k = y;
		j += xmove;

		if(j != xlim)
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
	return j;
}

ToolFill::ToolFill() : Tool(800, 800, 0.0f){
	int len = m_maskWidth * m_maskHeight;
	m_loc = new int[len];
	for(int i = 0; i < len ; i++ )
	{
		m_loc[i] = 0;
	}
}

