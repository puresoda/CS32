#ifndef WELL_INCLUDED
#define WELL_INCLUDED

class Screen;

class Well
{
  public:
	Well(int x, int y);
    void display(Screen& screen, int x, int y);
private:
	int m_x;
	int m_y;
};

#endif // WELL_INCLUDED
