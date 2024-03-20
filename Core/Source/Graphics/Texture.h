#pragma once
#include <string>


class Texture
{
public:
	unsigned int TextureID;
	std::string Source;
	unsigned int Filter;
	unsigned int Wrap;
	bool isValid;

	Texture(std::string Path);
	void CreateTexture(std::string Path, unsigned Filter, unsigned Wrap);
	Texture(std::string Path, unsigned int Filter, unsigned int Wrap);
	void Bind() const;

};

