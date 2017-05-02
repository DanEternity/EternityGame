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
#include <Globals.h>

/**************************
* Functions
*
**************************/

void StartDraw2D(int sizeX, int sizeY)
{
	glPushMatrix(); // сохран€ем GL_MODELVIEW
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); // текуща€ - проекци€
	glPushMatrix(); // сохран€ем
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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

void DrawSprite2v(unsigned int tex, float sizeW, float sizeH, float x, float y)
{
	float sizex = sizeW / 2;
	float sizey = sizeH / 2;
	glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f); 		glVertex2f(x - sizex, y - sizey);
	glTexCoord2f(1.0f, 1.0f);		glVertex2f(x + sizex, y - sizey);
	glTexCoord2f(1.0f, 0.0f); 		glVertex2f(x + sizex, y + sizey);
	glTexCoord2f(0.0f, 0.0f); 		glVertex2f(x - sizex, y + sizey);

	glEnd();
}
void DrawImage(unsigned int tex, int texSizeX, int texSizeY, int PartSizeX, int PartSizeY, int PosX, int PosY, int Sx, int Sy)
{
	/*
		tex - texture id
		texSize - file resolution (image resolution -> 512 512)
		PartSize - fragment resoluton // показывает размер картинки в файле, если картинка меньше чем размер текстуры
		Pos - left up point of image // показывает левый верхний угол выводимого изображени€
		Sx, Sy - ћасштабирование по X и Y. ѕоказывает фактическую ширину изображени€	
	*/

	float SizeX = PartSizeX/texSizeX;
	float SizeY = PartSizeY/ (PartSizeY-texSizeY);
	glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);
	/*
	glTexCoord2f(0.0f, 1.0f); 		glVertex2f(PosX - sizex, PosY - sizey);
	glTexCoord2f(1.0f, 1.0f);		glVertex2f(PosX + sizex, PosY - sizey);
	glTexCoord2f(1.0f, 0.0f); 		glVertex2f(PosX + sizex, PosY + sizey);
	glTexCoord2f(0.0f, 0.0f); 		glVertex2f(PosX - sizex, PosY + sizey);
	*/
	glTexCoord2f(0.0f, 1.0f); 		glVertex2f(PosX, PosY);
	glTexCoord2f(SizeX, 1.0f);		glVertex2f(PosX + Sx, PosY);
	glTexCoord2f(SizeX, SizeY); 	glVertex2f(PosX + Sx, PosY + Sy);
	glTexCoord2f(0.0f, SizeY); 		glVertex2f(PosX, PosY + Sy);

	glEnd();
}

void VectorRotate(vec2 & vec, double angle)
{
	vec = 
	{ 
		float(vec.x * cos(angle) - vec.y * sin(angle)),
		float(vec.x * sin(angle) + vec.y * cos(angle)) 
	};
}

void DrawSprite3v(unsigned int tex, int sizeW, int sizeH, float x, float y)
{
	glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 1.0f); 		glVertex2f(x, y);
	glTexCoord2f(1.0f, 1.0f);		glVertex2f(x + sizeW, y);
	glTexCoord2f(1.0f, 0.0f); 		glVertex2f(x + sizeW, y + sizeH);
	glTexCoord2f(0.0f, 0.0f); 		glVertex2f(x, y + sizeH);

	glEnd();
}

void DrawSprite4v(int size, int texId, float x, float y)
{
	texId += 32;
	float tx = texId%targetTextureMapSizeX, ty = targetTextureMapSizeY - texId/targetTextureMapSizeX;
	float texSize = 1.0f / targetTextureMapSizeX;
	glBegin(GL_QUADS);

	glTexCoord2f(tx / targetTextureMapSizeX, ty / targetTextureMapSizeY + texSize); 				glVertex2f(x, y);
	glTexCoord2f(tx / targetTextureMapSizeX + texSize, ty / targetTextureMapSizeY + texSize);		glVertex2f(x + size, y);
	glTexCoord2f(tx / targetTextureMapSizeX + texSize, ty / targetTextureMapSizeY); 				glVertex2f(x + size, y + size);
	glTexCoord2f(tx / targetTextureMapSizeX, ty / targetTextureMapSizeY); 							glVertex2f(x, y + size);

	glEnd();
}

void DrawSprite5v(ModelInfo model, float size, double angle, float x, float y)
{
	glBindTexture(GL_TEXTURE_2D, model.tex);

	vec2 center = { (model.p2.x - model.p1.x) * size/2, (model.p2.y - model.p1.y) * size/2};
	
	vec2 t1 = { - center.x, - center.y };
	vec2 t2 = { size - center.x, - center.y };
	vec2 t3 = { size - center.x, size - center.y };
	vec2 t4 = { - center.x, size - center.y };

	VectorRotate(t1, angle);
	VectorRotate(t2, angle);
	VectorRotate(t3, angle);
	VectorRotate(t4, angle);

	glBegin(GL_QUADS);

	glTexCoord2f(model.p1.x, model.p2.y); 		glVertex2f(t1.x + x, t1.y + y);
	glTexCoord2f(model.p2.x, model.p2.y);		glVertex2f(t2.x + x, t2.y + y);
	glTexCoord2f(model.p2.x, model.p1.y); 		glVertex2f(t3.x + x, t3.y + y);
	glTexCoord2f(model.p1.x, model.p1.y); 		glVertex2f(t4.x + x, t4.y + y);

	glEnd();
}

void DrawTile1v(ModelInfo model, float size, double angle, float multiplier, vec2 diff, float x, float y)
{
	glBindTexture(GL_TEXTURE_2D, model.tex);

	vec2 center = { (model.p2.x - model.p1.x) * size / 2, (model.p2.y - model.p1.y) * size / 2 };

	vec2 t1 = { -center.x, -center.y };
	vec2 t2 = { size - center.x, -center.y };
	vec2 t3 = { size - center.x, size - center.y };
	vec2 t4 = { -center.x, size - center.y };

	VectorRotate(t1, angle);
	VectorRotate(t2, angle);
	VectorRotate(t3, angle);
	VectorRotate(t4, angle);

	glBegin(GL_QUADS);

	glTexCoord2f(model.p1.x + diff.x, model.p2.y*multiplier + diff.y); 					glVertex2f(t1.x + x, t1.y + y);
	glTexCoord2f(model.p2.x*multiplier + diff.x, model.p2.y*multiplier + diff.y);		glVertex2f(t2.x + x, t2.y + y);
	glTexCoord2f(model.p2.x*multiplier + diff.x, model.p1.y + diff.y); 					glVertex2f(t3.x + x, t3.y + y);
	glTexCoord2f(model.p1.x + diff.x, model.p1.y + diff.y); 							glVertex2f(t4.x + x, t4.y + y);

	glEnd();
}

void AssignTextureMap(int id, int sizeX, int sizeY)
{
	targetTextureMap = id;
	targetTextureMapSizeX = sizeX;
	targetTextureMapSizeY = sizeY;
	glBindTexture(GL_TEXTURE_2D, id);
}

void GetScale(int sizeW, int sizeH, int texSizeX, int texSizeY, float &scaleX, float &scaleY)
{
	scaleX = (float)texSizeX / (float)sizeW;
	scaleY = (float)texSizeY / (float)sizeH;
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

void tFont::outString(int x, int y, const std::string * text)
{
	char * temp = new char[text->size()+4];
	for (int i(0); i < text->size(); i++)
		temp[i] = text->at(i);
	temp[text->size()] = 0;
	outText(x, y, temp);
	delete temp;
}

void tFont::outInt(int x, int y, const int text)
{
	char st[32];
	_itoa_s(text, st, 10);
	outText(x, y, st);
}
