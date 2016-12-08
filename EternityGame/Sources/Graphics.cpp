#include "Graphics.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>

/**************************
* Functions
*
**************************/

void StartDraw2D(int sizeX, int sizeY)
{
	glPushMatrix(); // сохраняем GL_MODELVIEW
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); // текущая - проекция
	glPushMatrix(); // сохраняем
	glLoadIdentity();
	// включаем 2D режим
	gluOrtho2D(0, sizeX, sizeY, 0);
	glMatrixMode(GL_MODELVIEW);
}

void EndDraw2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); // возвращаем GL_PROJECTION 
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix(); // возвращаем GL_MODELVIEW
}

GLuint LoadTex(const char * FilePath)
{
	Tga tex = Tga(FilePath);
	GLuint TexID = 0;
	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.GetWidth(), tex.GetWidth(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tex.GetPixels().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return TexID;
}

void DrawSprite(unsigned int tex, float size, float x, float y)
{
	size /= 2;

	glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f); 		glVertex2f(x-size, y-size);
	glTexCoord2f(1.0f, 1.0f);		glVertex2f(x+size, y-size);
	glTexCoord2f(1.0f, 0.0f); 		glVertex2f(x+size, y+size);
	glTexCoord2f(0.0f, 0.0f); 		glVertex2f(x-size, y+size);

	glEnd();
}

/**************************
* TGA Class
*
**************************/

typedef union PixelInfo
{
	std::uint32_t Colour;
	struct
	{
		std::uint8_t B, G, R, A;
	};
} *PPixelInfo;



Tga::Tga(const char* FilePath)
{
	std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
	if (!hFile.is_open()) { throw MessageBox(NULL, "File not found!.", "Texture TGA Load failed!", MB_OK | MB_ICONINFORMATION); }

	std::uint8_t Header[18] = { 0 };
	std::vector<std::uint8_t> ImageData;
	static std::uint8_t DeCompressed[12] = { 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	static std::uint8_t IsCompressed[12] = { 0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

	hFile.read(reinterpret_cast<char*>(&Header), sizeof(Header));

	if (!memcmp(DeCompressed, &Header, sizeof(DeCompressed)))
	{
		BitsPerPixel = Header[16];
		width = Header[13] * 0x100 + Header[12];
		height = Header[15] * 0x100 + Header[14];
		size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

		if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
		{
			hFile.close();
			throw MessageBox(NULL, "Invalid File Format. Required: 24 or 32 Bit Image.", "Texture TGA Load failed!", MB_OK | MB_ICONINFORMATION);

		}

		ImageData.resize(size);
		ImageCompressed = false;
		hFile.read(reinterpret_cast<char*>(ImageData.data()), size);
	}
	else if (!memcmp(IsCompressed, &Header, sizeof(IsCompressed)))
	{
		BitsPerPixel = Header[16];
		width = Header[13] * 0x100 + Header[12];
		height = Header[15] * 0x100 + Header[14];
		size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

		if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
		{
			hFile.close();
			throw MessageBox(NULL, "Invalid File Format. Required: 24 or 32 Bit Image.", "Texture TGA Load failed!", MB_OK | MB_ICONINFORMATION);
		}

		PixelInfo Pixel = { 0 };
		int CurrentByte = 0;
		std::size_t CurrentPixel = 0;
		ImageCompressed = true;
		std::uint8_t ChunkHeader = { 0 };
		int BytesPerPixel = (BitsPerPixel / 8);
		ImageData.resize(width * height * sizeof(PixelInfo));

		do
		{
			hFile.read(reinterpret_cast<char*>(&ChunkHeader), sizeof(ChunkHeader));

			if (ChunkHeader < 128)
			{
				++ChunkHeader;
				for (int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
				{
					hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

					ImageData[CurrentByte++] = Pixel.B;
					ImageData[CurrentByte++] = Pixel.G;
					ImageData[CurrentByte++] = Pixel.R;
					if (BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
				}
			}
			else
			{
				ChunkHeader -= 127;
				hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

				for (int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
				{
					ImageData[CurrentByte++] = Pixel.B;
					ImageData[CurrentByte++] = Pixel.G;
					ImageData[CurrentByte++] = Pixel.R;
					if (BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
				}
			}
		} while (CurrentPixel < (width * height));
	}
	else
	{
		hFile.close();
		MessageBox(NULL, "Invalid File Format. Required: 24 or 32 Bit Image.", "Texture TGA Load failed!", MB_OK | MB_ICONINFORMATION);
	}

	hFile.close();
	this->Pixels = ImageData;
}

tFont::tFont(const char * FilePath, int charsize, int count, int firstchar)
{
	tex = LoadTex(FilePath);
	offset.insert(offset.begin(), count, charsize/2);
	fchar = firstchar;
	csize = charsize;
}

void tFont::loadOffset(const char * FilePath, int count)
{
	std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
	if (!hFile.is_open()) { throw MessageBox(NULL, "File not found!.", "Font load failed!", MB_OK | MB_ICONINFORMATION); }

	for (int i(0); i < offset.size(); i++)
		hFile.read(reinterpret_cast<char*>(&offset[i]), 1);
	hFile.close();
}

void tFont::outText(int x, int y, const char * text) // Output string at screen
{
	glBindTexture(GL_TEXTURE_2D, tex);

	float size = csize / 2;
	float mx = 0;
	float bs = 1.0f / 16.0f; // Block size;

	for (int i(0); i < strlen(text); i++)
	{
		float u = ((uint8_t)text[i] - fchar) % 16;
		float v = ((uint8_t)text[i] - fchar) / 16;
		/* Texture coordinates */
		u = u / 16; 
		v = (16 - v - 1) / 16;
		/* Draw */
		glBegin(GL_QUADS);

		glTexCoord2f(u, bs + v); 		glVertex2f(mx + x - size, y - size);
		glTexCoord2f(bs + u, bs + v);	glVertex2f(mx + x + size, y - size);
		glTexCoord2f(bs + u, v); 		glVertex2f(mx + x + size, y + size);
		glTexCoord2f(u, v); 			glVertex2f(mx + x - size, y + size);

		glEnd();
		/* Add offset to position x*/
		mx += offset[(uint8_t)text[i] - fchar];
	}
}
