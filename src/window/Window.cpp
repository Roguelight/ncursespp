// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

#include <ucurses/window/Window.hpp>
#include <ucurses/app/GUI.hpp>

namespace ucurses {

	Window::Window(coord2d size, coord2d position) 
	{
        H_Window = newwin(size.y, size.x, position.y, position.x);
        keypad(H_Window, TRUE);
	}
    
    Window::Window() : title("Main")
    {
        H_Window = stdscr;
        keypad(H_Window, TRUE);
        CommandMap.Add("Tab:", " Switch Active ");
        CommandMap.Add("F1:", " Close Application ");
    }

    Window::~Window()
	{
        delwin(H_Window);
	}

    void Window::printCommands()
    {
        setPosition(2, getSize().y - 2);
        for (auto& it : CommandMap.tips)
        {
            attributeOn(A_REVERSE);
            print(it.first);
            attributeOff(A_REVERSE);
            print(it.second);
        }
    }

    void Window::Clear()
    {
        Commands.Clear();
        CommandMap.Clear();
        Components.RemoveAll();
    }

    void Window::addComponent(Component* component)
    {
        Components.Add(component);
    }
    
    void Window::addCommand(int key, delegate func)
    {
        Commands.Add(key,func);
    }

    void Window::addTip(string& keyID, string& funcID)
    {
        CommandMap.Add(keyID, funcID);
    }

    void Window::addTip(string&& keyID, string&& funcID)
    {
        CommandMap.Add(keyID, funcID);
    }

    /* Update */

    void Window::Update()
    {
        werase(H_Window);
        printBorder();
        setPosition(2,0);
        print(title);
        printCommands();
        Components.Update();
    }
	
    void Window::printBorder()
    {
        box(H_Window, '|', '-');
    }

    /* Construction */
    /*
    void Window::resize(coord2d size, coord2d position)
    {
        GlobalLogger::instance().log(TRACE) << "Resizing window -> " << title << Sentinel::END;
        delwin(H_Window);
        GlobalLogger::instance().log(WARNING) << "Tried to resize ncurses stdscr!" << Sentinel::END;
    }
    */
    void Window::EnableColor(ColorContainer* s_ptr) 
    {
        S_Colors = s_ptr;
    }

    void Window::setTitle(string s)
    {
        title = s;        
    }

    /* Manipulation */

    void Window::move(coord x, coord y)
    { 
        coord2d curpos = getPosition();
        wmove(H_Window, curpos.y + y, curpos.x + x);
    }

    void Window::print(string inString)
    {
        waddstr(H_Window, inString.c_str());
    }
            
    void Window::setPosition(coord x, coord y)
    {
        wmove(H_Window, y, x);
    }
            
    // Attributes        
    void Window::setAttributes(int attributes)      
    {
        wattrset(H_Window, attributes); 
    }

    void Window::attributeOn(int attributes)
    { 
        wattron(H_Window, attributes);  
    } 

    void Window::attributeOff(int attributes)
    { 
        wattroff(H_Window, attributes); 
    }

    // Highlighting

    void Window::highlightRow(coord row)
    {
        mvwchgat(H_Window, row, 0, -1, A_REVERSE, COLOR_PAIR(0), NULL);
    }

    void Window::highlightColumn(coord column)
    {
        mvwchgat(H_Window, 0, column, -1, A_REVERSE, COLOR_PAIR(0), NULL);
    }    

    void Window::highlightWord(coord2d wordpos, int size)
    {
        mvwchgat(H_Window, wordpos.y + 1, wordpos.x, size, A_REVERSE, COLOR_PAIR(0), NULL);
    }

    /* Retrieval methods */
    
    coord2d Window::getSize() const
    {
        coord2d size;
        getmaxyx(H_Window, size.y, size.x);
        return size;
    }

    coord2d Window::getMiddle() const
    {
        coord2d size = getSize(); 
        coord2d middle(size.x / 2, size.y / 2);
        return middle;
    }
    
    WINDOW* Window::getHandle() const
    { 
        return H_Window;  
    }

    string Window::getTitle() const
    {
        return title;     
    }

    coord2d Window::getPosition() const
    {
        coord2d pos;
        getyx(H_Window, pos.y, pos.x);
        return pos;
    }

}