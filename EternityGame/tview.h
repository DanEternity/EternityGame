#pragma once
#include <vector>;
#include <UI.h>
class Tview
{
public:
	std::string name;
	UISmartGrid * tUISmartGrid;
	Tview();
	~Tview();
};

class Batton : public Tview
{
public:
	void init(int id);
	void drawBatton();
	Batton();
	~Batton();
};
class RichText : public Tview
{
public:
	std::vector<std::string>text;
	void add(std::string newstring);
	void read();
	void write();
	RichText();
	~RichText();
};