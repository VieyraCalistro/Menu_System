
#pragma once
#include "DynArray.h"
#include <string>

using namespace std;


struct MenuItem
{

	string name;

	bool is_subMenu;

	string subMenuPath;


};

class Menu
{
public:

	Menu();
	~Menu();

	string title;

	DynArray<MenuItem> choices;

	short xMenuPos = 4;
	short yMenuPos = 2;

	short cursorAsteriskX = 2;
	short cursorAsteriskY = 3;

	short CursorAsteriskMinYBounds = 3;
	short CursorAsteriskMaxYBounds;



};

