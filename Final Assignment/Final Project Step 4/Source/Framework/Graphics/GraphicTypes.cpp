#include "GraphicTypes.h"
#include "Texture.h"

namespace GameDev2D
{
    FontData::FontData() :
        lineHeight(0),
        baseline(0),
        size(0)
    {
    }

    FontData::~FontData()
    {
        delete texture;
    }
}