#pragma once
#include<vector>
#include<string>
#include<Types.h>

void StartDraw2D(int sizeX, int sizeY);
void EndDraw2D();
unsigned int LoadTex(const char* FilePath);
void DrawSprite(unsigned int tex, float size, float x, float y);
void DrawSprite2v(unsigned int tex, float sizeW, float sizeH, float x, float y);
void DrawImage(unsigned int tex, int texSizeX, int texSizeY, int PartSizeX, int PartSizeY, int PosX, int PosY, int Sx, int Sy);
void VectorRotate(vec2 &vec, double angle);
/* 
DrawImage()
tex - texture id
texSize - file resolution (image resolution -> 512 512)
PartSize - fragment resoluton // показывает размер картинки в файле, если картинка меньше чем размер текстуры
Pos - left up point of image // показывает левый верхний угол выводимого изображени€
Sx, Sy - ћасштабирование по X и Y. ѕоказывает фактическую ширину изображени€
*/

void DrawSprite3v(unsigned int tex, int sizeW, int sizeH, float x, float y);
void DrawSprite4v(int size, int texId, float x, float y); // using for texture map
void DrawSprite5v(ModelInfo model, float size, double angle, float x, float y); // rotatable; new format
void DrawTile1v(ModelInfo model, float size, double angle, float multiplier, vec2 diff, float x, float y); // rotatable; new format
void AssignTextureMap(int id, int sizeX, int sizeY);
void GetScale(int sizeW, int sizeH, int texSizeX, int texSizeY, float &scaleX, float &scaleY);

class Tga
{
private:
	std::vector<std::uint8_t> Pixels;
	bool ImageCompressed;
	std::uint32_t width, height, size, BitsPerPixel;

public:
	Tga(const char* FilePath);
	std::vector<std::uint8_t> GetPixels() { return this->Pixels; }
	std::uint32_t GetWidth() const { return this->width; }
	std::uint32_t GetHeight() const { return this->height; }
	bool HasAlphaChannel() { return BitsPerPixel == 32; }
};

class tFont
{
public:
	tFont(const char* FilePath, int charsize, int count, int firstchar);
	void loadOffset(const char* FilePath, int count);
	void outText(int x, int y, const char * text);
	void outString(int x, int y, const std::string * text);
	void outInt(int x, int y, const int text);
private:
	unsigned int tex;
	std::vector<int> offset;
	int fchar;
	int csize;
};