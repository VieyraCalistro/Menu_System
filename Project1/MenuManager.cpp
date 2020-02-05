#include "pch.h"
#include "MenuManager.h"
#include <fstream>
#include <Windows.h>
#include <conio.h>



MenuManager::MenuManager()
{
}


MenuManager::~MenuManager()
{
	// Delete menu items in single link list.
	activeItems.clear();
}

void MenuManager::PopMenuOff()
{
	// Remove current Node.
	activeItems.remove(iter);

}

void MenuManager::Render()
{
	// Clear the screen.
	system("cls");


	// Set and create a HANDLE for cursor.
	CONSOLE_CURSOR_INFO cursorInfo;
	HANDLE out;
	out = GetStdHandle(STD_OUTPUT_HANDLE);


	// Hide the cursor.
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);


	// Give the X and Y position for the cursor.
	COORD cursorPosition = { iter.current().cursorAsteriskX, iter.current().cursorAsteriskY };
	SetConsoleCursorPosition(out, cursorPosition);


	// Make asterisk symbol to navigate with.
	cout << "*";


	// Set the cursor X and Y position where the menu screen should be.
	cursorPosition.X = iter.current().xMenuPos;
	cursorPosition.Y = iter.current().yMenuPos;
	SetConsoleCursorPosition(out, cursorPosition);

	
	// Print the title.
	cout << iter.current().title << endl;

	// Loop through and print out all the names.
	for (unsigned int index = 0; index < iter.current().choices.size(); index++)
	{

		// While looping increase the Y position on the screen so we do not print on the same line.
		cursorPosition.Y++;
		SetConsoleCursorPosition(out, cursorPosition);
		cout << iter.current().choices[index].name << endl;


	}

	cursorPosition.Y++;
	SetConsoleCursorPosition(out, cursorPosition);

	// Print out exit on screen.
	cout << "Exit" << endl;


	// Get the max Y position for the asterisk.
	iter.current().CursorAsteriskMaxYBounds = cursorPosition.Y;


}

void MenuManager::Push(Menu menu)
{
	// Add a new menu created into single link list.
	activeItems.addHead(menu);
	
	// Move current pointer back to the beginning of the list.
	iter.begin();
}

void MenuManager::CreateMenusFromFiles(string filePath)
{

	// Refernce an ifstream.
	ifstream inFile;


	// Open file.
	inFile.open(filePath);


	// Check to see if opening the file failed.
	if (inFile.fail())
	{

		cout << "Problem opening file. File could be already opened elsewhere." << endl;

	}
	else
	{
		

		// Create a buffer to help us store characters.
		char buffer0[128];


		// Read in the first line, just so we move the file pointer correctly.
		inFile.getline(buffer0, 128, '\n');


		// Create an integer to tell us the number on the second line.
		unsigned int numberOfLinesToPrintOut;


		// Read in the number on the second line.
		inFile >> numberOfLinesToPrintOut;



		// Move file input pointer back to the beginning.
		inFile.seekg(0, ios::beg);

		Menu CreateAMenu;
		MenuItem CreateMenuItem;
		// Create buffer's to store unique inputs response.
		char title[128];
		char type[128];
		char name[128];
		char path[128];
		string MENUorOPTION;


		// Read in the title.
		inFile.getline(title, 128, '\n');
		

		// Set the title to the Menu.
		CreateAMenu.title = title;


		// Create an integer to store the number of items on the screen.
		unsigned int numItems;


		// Read in the next line which is an integer.
		inFile >> numItems;


		// Now you know how many times to loop and print.
		for (unsigned int index = 0; index < numberOfLinesToPrintOut; index++)
		{

			// Read in the type, MENU or OPTIONS.
			// Stop at white space and this will be our MENU or OPTIONS.
			inFile >> type;


			// Now ignore the leading white space.
			inFile.ignore(INT_MAX, '\"');


			// Read in the name of the type.
			inFile.get(name, 128, '\"');

			
			// Store the name for the struct.
			CreateMenuItem.name = name;


			MENUorOPTION = type;

			// Determine if we need have a MENU or OPTION.
			if (MENUorOPTION == "MENU")
			{
				// Set true if this contains a sub menu.
				CreateMenuItem.is_subMenu = true;


				// Get the next character which is " .
				inFile.get();


				// Ignore up to the double quote " .
				inFile.ignore(INT_MAX, '\"');


				// Read in the path only if it is in fact a MENU and not an OPTION.
				inFile.get(path, 128, '\"');


				// Save the path file if it does contain a sub menu.
				CreateMenuItem.subMenuPath = path;


				// Go ahead and ignore until new line now.
				inFile.ignore(INT_MAX, '\n');
			}
			else
			{
				// Set the sub menu to false.
				CreateMenuItem.is_subMenu = false;
				CreateMenuItem.subMenuPath = "";

				// Go ahead and ignore until new line now.
				inFile.ignore(INT_MAX, '\n');
				cout << endl;
			}

			// Append the menuItems to the menu referenced.
			CreateAMenu.choices.append(CreateMenuItem);

			
		}

		//Add SavingMenu to your single link list.
		Push(CreateAMenu);


		// Close file when done.
		inFile.close();

	}

}



void MenuManager::Update()
{

	// Add a sleep timer to slow down and accept user input.
	Sleep(85);

	// 1 - get user input
	if (_kbhit())
	{
		char ch = _getch();

		// Arrow down pressed.
		if (ch == 80)
		{

			// Set boundries.
			if (iter.current().cursorAsteriskY > iter.current().CursorAsteriskMaxYBounds - 1)
			{
				// Re-set the asterisk symbol to the top of menu if the limit has been passed.
				iter.current().cursorAsteriskY = 3;
				Sleep(100);
			}
			else
			{
				// Increment the asterisk position.
				iter.current().cursorAsteriskY++;
				Sleep(100);

			}
		}

		// Arrow up key pressed.
		if (ch == 72)
		{

			// Set boundries for asterisk.
			if (iter.current().cursorAsteriskY < 4)
			{
				// Set the asterisk position to the bottom of the menu list when up arrow key pressed and you are at the first choice.
				iter.current().cursorAsteriskY = iter.current().CursorAsteriskMaxYBounds;
				Sleep(100);
			}
			else
			{
				// Decrement the asterisk position.
				iter.current().cursorAsteriskY--;
				Sleep(100);

			}

		}

		// Enter, selection made.
		if (ch == 13)
		{
			
			// Check to see if the selection is a sub menu or not.
			if (iter.current().choices[iter.current().cursorAsteriskY - 3].is_subMenu == true)
			{

				CreateMenusFromFiles(iter.current().choices[iter.current().cursorAsteriskY - 3].subMenuPath);

				// Increase menu pages to keep track how far in the user is.
				menuPages++;
				
			}
			else
			{

				// Check to see if the user selected the last option in the menu, which would be the exit.
				if (iter.current().cursorAsteriskY == iter.current().CursorAsteriskMaxYBounds)
				{

					// Point the current pointer to the beginning.
					iter.begin();

					// Remove the current menu to go back to the previous.
					PopMenuOff();

					// Back track on the menu pages count.
					menuPages--;
					
					// Check to see if we are trying to back out of the only menu page.
					if (menuPages == 0)
					{
						// Set Realtime update while loop to false and exit.
						inMenu = false;

						cout << endl;
						cout << "GoodBye!" << endl;
					}
					
					// Slow the program down.
					Sleep(100);
				}

			}

		}

	}
}


void MenuManager::StartTheMenu()
{
	
	// Enter the main menu.
	CreateMenusFromFiles("main.mnu");

	// Increase the number of pages.
	menuPages++;
}

void MenuManager::RealTimeUpdate()
{

	// Enter while loop to keep updating and rendering the menu system.
	while (inMenu == true)
	{
		Render();
		Update();
	}

}


