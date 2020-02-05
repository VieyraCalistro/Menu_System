
#pragma once
#include "SLList.h"
#include "Menu.h"


using namespace std;


class MenuManager
{
public:

	MenuManager();
	~MenuManager();


	SLList<Menu> activeItems;

	SLLIter<Menu> iter = activeItems;

	void Push(Menu menu);

	void PopMenuOff();

	void Render();

	void CreateMenusFromFiles(string filePath);

	bool inMenu = true;

	void Update();

	short menuPages = 0;

	void StartTheMenu();

	void RealTimeUpdate();

	
};

