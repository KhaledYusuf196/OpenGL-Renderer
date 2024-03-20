#include "Texture.h"

#include "GL/glew.h"
#include  "STB/stb_image.h"

Texture::Texture(std::string Path) : TextureID(-1), Source(Path), Filter(GL_LINEAR), Wrap(GL_CLAMP), isValid(false)
{
	CreateTexture(Path, Filter, Wrap);
}

void Texture::CreateTexture(std::string Path, unsigned Filter, unsigned Wrap)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* img = stbi_load(Path.c_str(), &width, &height, &channels, 4);
	if(img == nullptr)
	{
		img = new unsigned char[] {1,1,1,1};
		width = 1;
		height = 1;
	}


	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap);
	isValid = true;
}

Texture::Texture(std::string Path, unsigned int Filter, unsigned int Wrap) : TextureID(-1), Source(Path), Filter(Filter), Wrap(Wrap), isValid(false)
{
	CreateTexture(Path, Filter, Wrap);
}

void Texture::Bind(unsigned int slot) const
{
	glBindTextureUnit(slot, TextureID);
}
