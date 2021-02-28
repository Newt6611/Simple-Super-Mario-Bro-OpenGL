#include "Texture.h"

std::unordered_map<std::string, Texture> Texture::Textures;

void Texture::LoadTexture(const char* name, const char* file, bool isAlpha)
{
	Texture texture;
	
	if (isAlpha) 
	{
		texture.image_format = GL_RGBA;
		texture.internal_format = GL_RGBA;
	}
	
	int w, h, c;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(file, &w, &h, &c, 0);
	if (data)
	{
		texture.Gernerate(w, h, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		Texture::Textures[name] = texture;
		stbi_image_free(data);
	}
	else 
	{
		std::cout << "Load Texture Error ! " << std::endl;
	}
}

Texture& Texture::GetTexture(const char* name)
{
	return Texture::Textures[name];
}

void Texture::Gernerate(unsigned int width, unsigned int height, unsigned char* data)
{
	glGenTextures(1, &m_Id);
	this->wrap_s = GL_REPEAT;
	this->wrap_t = GL_REPEAT;
	this->filter_min = GL_LINEAR;
	this->filter_max = GL_LINEAR;

	this->width = width;
	this->height = height;
	
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}
