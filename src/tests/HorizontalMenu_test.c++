#include <ucurses/ucurses.hpp>

using namespace ucurses;

int main()
{
	UCurses gui;
	Window* mainwindow = gui.createWindow();

    HorizontalMenu* menu = new HorizontalMenu(mainwindow, 5, 5);
    for (int i = 0; i < 5; ++i)
    {
        menu->addItem("Item " + std::to_string(i));
    }
	
    gui.Run();	
}
