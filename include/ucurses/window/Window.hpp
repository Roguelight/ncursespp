// Copyright Sat Feb 18 14:42:55 2017
// Liam Rogers, All rights reserved.

/*
 * Window provides an interface for manipulating NCurses WINDOW 
 * structure and mapping commands to keys
 * 
 * Constructor is exposed through the ucurses::GUI object. Window* handle = gui.createWindow();
 * This ensures safe initialization and storage.
 */

#pragma once
#include <string>
#include <map>
#include <algorithm>

#include <ctk/log/GlobalLogger.hpp>

#include <ucurses/window/types.hpp>
#include <ucurses/app/Color.hpp>

#include <ucurses/command/Command.hpp>
#include <ucurses/command/Callback.hpp>
#include <ucurses/component/ComponentArray.hpp>

#include <ncurses.h>

namespace ucurses { 

	class UCurses;
    class State;
    class Interface;
	class Window
	{
		friend class WindowContainer;
		friend class Component;
		friend class UCurses;
		static ColorContainer* colors;

		public:
		   
            static UCurses* ucurses;								/* Static reference for creating new windows */

			/* Construction */

			Window(); 											/* Full size, input delayed, not deletable */
			Window(coord2d size, coord2d position); 			/* Size position specific constructor. */
			~Window(); 											/* Safely releases NCurses WINDOW data */

			void 	setTitle(const std::string& s);
			void	setDelay(bool b);							/* Windows can delay until input is received */
			void	setDelete(bool b);							/* Enables deletion of the window */
			bool	isDelay() const;
			Window* subWindow(coord2d size, coord2d pos);
			Window* subWindow(ctk::Vec2f size, ctk::Vec2f pos);

			void ClearScreen();									/* Erases contents of screen */

			/* Window Manipulation */

			void setPosition(coord x, coord y);					/* Set window position to new position */

			/* Cursor Manipulation */

			void  setCursor(coord x, coord y); 					/* Sets cursor to absolute position 			*/
			void  moveCursor(coord x, coord y);        			/* Moves cursor to relative to current position */
			void  print(const std::string& inString);        	/* Prints from current cursor position 			*/
			void  print(int c);
			void  print(char* c);
            void  print(Cell& cell);

			/* Attributes */

			void setAttributes(int attributes);				/* Attributes can be OR | for combined effects */
			void attributeOn(int attributes);				/* eg attributeOn(A_BLINK | COLOR_PAIR(n)) */
			void attributeOff(int attributes);
	        void setDefaultColor(short color);
			void setColor(short color);						/* Sets a temporary color for drawing. Usually calls unset after */
			void resetColor();						        /* Unsets color for window, must already be created with init_pair */
			short getColor();

			/*  Highlighting */

			void highlightWord(coord2d wordpos, int size, short color = 0, attr_t attributes = A_STANDOUT);                  
			void highlightRow(coord row, short color = 0, attr_t attributes = A_STANDOUT);                  
			void highlightColumn(coord column, short color = 0, attr_t attributes = A_STANDOUT);                  
			void highlightChar(coord2d pos, short color = 0, attr_t attributes = A_STANDOUT);                  

			/* Retrieval Methods */

			coord2d   getSize()         const;
			coord2d   getCursor()       const;
			coord2d	  getPosition()		const;
			coord2d   getMiddle()       const; 
			WINDOW*   getHandle()  		const		{ return H_Window; }
			string    getTitle()   		const		{ return title; } 

		public:

			/* Commands */

			CommandArray Commands;
			CallbackStack callback_stack;				/* Escape command. Changed independantly of commands stored CommandArray */
			void setCallbackTip(const string& in);
			void addTip(const std::string& tip);
			void addTip(std::string&& tip);
			void Escape();


		protected:

			std::vector<std::string> tips;				/* Command tips displayed in bottom left corner of window */

            void Process(int input);
			void printCommands(); 

		protected:

			void Update(); // Update components
			void printBorder();

		public:

            ComponentArray Components;
			void Clear(); 										/* Destroys all components and commands */
            void ClearTips();

			// A window can only have one given state at a time
			// However a state is an interface that clears the window on binding
            void Bind(State* new_state);
            void Bind(Interface* new_interface);

			std::vector<Interface*> interfaces;
			void UnbindAll();

		private:

			WINDOW* H_Window;      						/* Direct handle to NCurses WINDOW data */
            State*  state;                              /* State pattern for handling UI Transitions */
			string title;
			bool deletable;
			bool delay;
			short color;
			void EnableColor(ColorContainer* s_ptr);

			friend bool operator==(const Window& lhs, const string& rhs) 
			{ 
				if (lhs.getTitle() == rhs)
					return true;
				else
					return false;
			}
	};
}
