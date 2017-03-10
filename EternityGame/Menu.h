#pragma once
#include <windows.h>
#include <Vector>
#include <Types.h>



class Botton
{
public:
	vec2 size,pos;
	int id;
	void drawBotton(int id);
	Botton();
	~Botton();
};