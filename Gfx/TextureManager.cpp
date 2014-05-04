#include "TextureManager.h"
#include <stdlib.h>
#include <string>
#include <SFML/Graphics.hpp>

sf::Texture& TextureManager::loadTexture(std::string filename)
{
	for (std::map<std::string, sf::Texture>::iterator i = textures.begin(); i != textures.end(); ++i)
	if (i->first == filename)
		return i->second;
	sf::Texture tex;
	if (tex.loadFromFile(filename))
	{
		textures[filename] = tex;
		return textures[filename];
	}
	else
		return texture_blank;
}