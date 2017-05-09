// Copyright Fri Mar 10 18:04:52 2017
// Liam Rogers, All rights reserved.

/*
 * File description
 */

#pragma once
#include <ucurses/gui/Component.hpp>

namespace ucurses { namespace gui {

    class Window;

    class ComponentArray
    {
        friend class Window;

        public:

            ComponentArray();
            ~ComponentArray();

            void Add(Component* component);
            void Update();
            void RemoveAll();

        protected:

            vector<Component*> M_Components;
            /* 
             * Prefix M_ indicates owner of this data is responsible
             * for memory management of every instance of this data
             */
            

    };

}}
