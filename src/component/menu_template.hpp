/*
 * Mix-in class to avoid code duplication
 *
 */

#pragma once
#include <string>
#include <vector>

namespace ucurses { 

 	/* T must be constructable from a std::string */
	template <typename T>
	class menu_template
	{
		public:

			menu_template();

			/* Retrieval methods */
			
			const T& getSelectedItem() const;           
			T& getSelectedItem();           
			const T& getItem(short id) const;  				/* Performs bounds checking */ 
			T& getItem(short id);  				            /* Performs bounds checking */ 
			const T& back();
			short getSelectedIndex();

			void removeAll();
			void removeSelectedItem();

			T& addItem(const std::string& label);

			const std::vector<T>& getItems() const;
			std::vector<T>& getItems();

			void selectNext();
			void selectPrevious();

            bool noneSelected() const;

		protected:

			std::vector<T> items;
			void removeItem(short id);
			
			short selection;
			bool last()									{ return (selection + 1) == items.size(); }
	};
}
#include <ucurses/component/menu_imp.hpp>
