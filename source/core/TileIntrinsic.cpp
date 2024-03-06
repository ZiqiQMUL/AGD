//¨C Flyweight (10%)
#include "../core/TileIntrinsic.h"
#include <exception>
#include <sstream>

TileIntrinsic::TileIntrinsic(const std::string& textureFile, TileType tt) : type(tt) 
{
	if (!texture.loadFromFile(textureFile)) 
	{
		std::stringstream sss;
		sss << "Texture file not found: " << textureFile;
		throw std::exception(sss.str().c_str());
	}
}
