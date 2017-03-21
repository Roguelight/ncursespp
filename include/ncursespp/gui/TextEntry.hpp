// Copyright Wed Mar  8 22:49:41 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ncursespp/gui/Component.hpp>

namespace ncursespp { namespace gui {

	class TextEntry : public Component
	{
		public:

			TextEntry(coord x, coord y, Window* host); 

            void bindDefault();

        protected:

            void Update();

            void setSubject(string inString);

            string subject;
            string input;
            coord2d pos;

            // Commands
            
            void getInput(); // *->E
            void printCommands();

	};

}}
