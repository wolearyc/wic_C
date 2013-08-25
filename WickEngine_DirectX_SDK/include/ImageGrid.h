// ------------------------------------------------------------------------------------------------
// File:			ImageGrid.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-ImageGrid
//-------------------------------------------------------------------------------------------------

#ifndef IMAGEGRID_H
#define IMAGEGRID_H
#include "Image.h"
namespace wick
{
	class ImageGrid : public Image
	{
	public:

		// Constructors.
		ImageGrid(Texture* texture, Pair location, Box bounds, Pair cellDimensions);
		ImageGrid(Texture* texture, Pair location, Box bounds, Pair scale, Pair cellDimensions);
		ImageGrid(Texture* texture, Pair location, Box bounds, double rotation, Pair cellDimensions);
		ImageGrid(Texture* texture, Pair location, Box bounds, Pair scale, double rotation,
				  Pair cellDimensions);
		ImageGrid(Texture* texture, Pair location, Box bounds, double rotation, Pair center,
				  Pair cellDimensions);
		ImageGrid(const ImageGrid& other);
		ImageGrid();

		// Methods modifying bounds and cell dimensions.
		Box getBounds();
		Pair getCellDimensions();
		void setBoundsAndCellDimensions(Box bounds, Pair cellDimensions);

		// Methods modifying the selected cell.
		Pair getCellIndex();
		void setCellIndex(Pair index);

	protected:

		Box imageBounds_;
		Pair cellDimensions_;
		Pair index_;

	};
}
#endif
