#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "../Util/Singleton.h"


class TextureManager : public Singleton<TextureManager>
{
private:
	std::map<std::string, sf::Texture> textures;
	sf::Texture texture_blank;

public:
	sf::Texture& loadTexture(std::string filename);
};
