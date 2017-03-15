#pragma once
#include <windows.h>
#include <Vector>
#include <Types.h>
#include <Graphics.h>
#include <UI.h>


class Botton : public UIGrid
{
public:
	vec2 size,pos;
	int id;
	void drawBotton(int id);
	tFont * Font;
	void setFont(tFont * pick);
	
	Botton();
	~Botton();
};