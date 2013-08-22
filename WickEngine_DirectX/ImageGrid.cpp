// ------------------------------------------------------------------------------------------------
// File:			ImageGrid.cpp
//-------------------------------------------------------------------------------------------------

#include "ImageGrid.h"
namespace wick
{
	// Constructors.
	ImageGrid::ImageGrid(Texture* texture, Pair location, Box bounds, Pair cellDimensions)
			 : Image(texture, location, bounds)
	{
		index_ = Pair();
		setBoundsAndCellDimensions(bounds, cellDimensions);
	}
	ImageGrid::ImageGrid(Texture* texture, Pair location, Box bounds, Pair scale, Pair cellDimensions)
			 : Image(texture, location, bounds, scale)
	{
		index_ = Pair();
		setBoundsAndCellDimensions(bounds, cellDimensions);
	}
	ImageGrid::ImageGrid(Texture* texture, Pair location, Box bounds, double rotation,
						 Pair cellDimensions) : Image(texture, location, bounds, rotation)
	{
		index_ = Pair();
		setBoundsAndCellDimensions(bounds, cellDimensions);
	}
	ImageGrid::ImageGrid(Texture* texture, Pair location, Box bounds, Pair scale, double rotation,
						 Pair cellDimensions) : Image(texture, location, bounds, scale, rotation)
	{
		index_ = Pair();
		setBoundsAndCellDimensions(bounds, cellDimensions);
	}
	ImageGrid::ImageGrid(Texture* texture, Pair location, Box bounds, double rotation, Pair center,
						 Pair cellDimensions) : Image(texture, location, bounds, rotation, center)
	{
		index_ = Pair();
		setBoundsAndCellDimensions(bounds, cellDimensions);
	}
	ImageGrid::ImageGrid(const ImageGrid& other) : Image(other)
	{
		imageBounds_ = other.imageBounds_;
		cellDimensions_ = other.cellDimensions_;
		index_ = other.index_;
	}
	ImageGrid::ImageGrid() : Image()
	{
		imageBounds_ = Box();
		cellDimensions_ = Pair();
		index_ = Pair();
	}

	// Methods modifying bounds and cell dimensions.
	Box ImageGrid::getBounds()
	{
		return(imageBounds_);
	}
	Pair ImageGrid::getCellDimensions()
	{
		return(cellDimensions_);
	}
	void ImageGrid::setBoundsAndCellDimensions(Box bounds, Pair cellDimensions)
	{
		if((bounds.getLowerRight()-bounds.getUpperLeft()) % (cellDimensions) != Pair())
		{
			wickThrowError("Invalid cell dimensions or image dimensions.");
		}
		imageBounds_ = bounds;
		cellDimensions_ = cellDimensions;
		setCellIndex(index_);
	}

	// Methods modifying the selected cell.
	Pair ImageGrid::getCellIndex()
	{
		return(index_);
	}
	void ImageGrid::setCellIndex(Pair index)
	{
		Pair imageDimensions = imageBounds_.getLowerRight() - imageBounds_.getUpperLeft();
		if(imageDimensions.x_ / cellDimensions_.x_ < index.x_ + 1 || index.x_ < 0 ||
		   imageDimensions.y_ / cellDimensions_.y_ < index.y_ + 1 || index.y_ < 0)
		{
			wickThrowError("Invalid cell index.");
		}
		index_ = index;
		Pair upperLeft = index_ * cellDimensions_ + imageBounds_.getUpperLeft();
		Pair lowerRight = upperLeft + cellDimensions_;
		setBounds(Box(upperLeft, lowerRight));
	}
}

