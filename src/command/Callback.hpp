/*
* Uses vector as underlying container to avoid memory overhead
* Fast beginning insertion provided by std::deque is not needed
*/
#pragma once
#include <ucurses/command/Command.hpp>

namespace ucurses { 

	struct Callback
	{
		Callback(int key, std::function<void()> func, const std::string& tip) : command(key,func), tip(tip) {}

		Command command;
		std::string tip;
	};

	class CallbackStack
	{
		public:

			CallbackStack(size_t size = 4);

			void Emplace(int key, std::function<void()> callback);
			void Execute();


			/* Only tests the last added callback (top()) */
			void Process(int key);						

			std::string getTip() const;
			void setTip(const std::string& inTip);


		protected:

			std::vector<Callback> stack_array;
	};
}