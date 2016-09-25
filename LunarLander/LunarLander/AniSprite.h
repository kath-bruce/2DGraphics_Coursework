/** AniSprite (Animated Sprite) class.
 *
 * Copyright (c) 2010, Alistair McMonnies
 * alistair.mcmonnies@uws.ac.uk

   This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

  alistair.mcmonnies@uws.ac.uk

 *
 */

#ifndef ANISPRITE_H
#define ANISPRITE_H
#include "Bitmap.h"

/// Enumeration to indicate how a sprite goes from cell to cell.
enum UpdateMode{
	UPDATEONASK,	// Respond to nextCell() call
	UPDATEONMOVE	// Select next cell on a move() or move(x,y) call
};

/// Enumeration to indicate whether a sprite is flipped (left-to-right) or not.
enum DrawMode{
	NOFLIP,			// Never reverse image
	FLIPCELL,		// Mirror image (L-R)
	AUTOFLIP		// Orientation according to x-velocity
};

class AniSprite
{
public:
	// Constructor for a given image filename...
	AniSprite(float initial_x, float initial_y,				// Starting position
			  const char *file, 						// Bitmap file
			  int incols, int inrows);					// Cells x Rows of sprite sheet.
	// Constructor for an already created bitmap image...
	AniSprite(float initial_x, float initial_y,				// Starting position
			  Bitmap *ipic, 							// Image handle
			  int incols, int inrows);					// Cells x Rows of sprite sheet.
	// As first constructor, but with velocity supplied...
	AniSprite(float initial_x, float initial_y,				// Starting position
			  float initial_dx, float initial_dy,			// Starting velocity
			  const char *file,							// Bitmap file
			  int incols, int inrows);					// Cells x Rows of sprite sheet
	// As second constructor but with velocity...
	AniSprite(float initial_x, float initial_y,				// Starting position
			  float initial_dx, float initial_dy,			// Starting velocity
			  Bitmap *ipic, 							// Image handle
			  int incols, int inrows);					// Cells x Rows of sprite sheet
	// Member functions...
	void draw();						/// Render the cell (include in the display() delegate function)
	void setUpdatemode(UpdateMode um);	/// Specify whether cell changes happen on motion or by call
	void setDrawmode(DrawMode dm);		/// Specify orientation
	void nextCell();					/// Move to next cell in the sequence
	void prevCell();					/// Move to previous cell in the sequence
	void move();						/// Move by dx, dy
	void move(float by_x, float by_y);		/// Move by given amounts
	void moveTo(int newX, int newY) {x=newX-ref_x; y=newY-ref_y;}	/// Move to specified position
	int getX() { return x+ref_x;}
	int getY() { return y+ref_y;}
	void setReferencePixel(int x, int y) {ref_x=x; ref_y = y;}	/// Where the sprite is positioned (relative to top-left)
	void setVelocity(float idx, float idy){dx=idx; dy=idy;}			/// Change dx, dy
	int getVelX(){return dx;}
	int getVelY(){return dy;}
	int getWidth(){ return cellWidth;}
	int getHeight(){return cellHeight;}
	bool intersects(int x, int y, int width, int height);	/// Simple as it gets collision detection
	void setSpriteSheetDimensions(int w, int h);			/// To allow a sprite-sheet that is not full-size
	Bitmap* getPic(){return pic;}
	~AniSprite();
private:
	Bitmap* pic;
	int currentCell;
	float x, y, dx, dy;
	int width, height;
	int sheet_width, sheet_height;		/// To allow for padding in a sprite sheet
	int ncols, nrows;
	int ref_x, ref_y;
	int cellWidth, cellHeight;
	UpdateMode updatemode;
	DrawMode drawmode;
	void init(float ix, float iy, int icols, int irows, float idx, float idy);
	void calculate_cells();
};

#endif
