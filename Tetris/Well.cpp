#include "Well.h"
#include "UserInterface.h"

Well::Well(int x, int y)
	:m_x(x), m_y(y)
{
}

void Well::display(Screen& screen, int x, int y)
{
	//draw the walls
	for (int i = y; i < y + m_y; i++)
	{
		screen.gotoXY(x, i);
		screen.printChar('@');
		screen.gotoXY(x+m_x+1, i);
		screen.printChar('@');
	}

	//draw the bottom
	for (int i = 0; i <= m_x+1; i++)
	{
		screen.gotoXY(i, m_y);
		screen.printChar('@');
	}
}
