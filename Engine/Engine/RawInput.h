#pragma once
#include <Windows.h>

#define LEFT_BUTTON 0
#define MIDDLE_BUTTON 1
#define RIGHT_BUTTON 2
#define ADD 3
#define SUBTRACT 4


namespace Engine
{
	class RawInput
	{
	private:
		int xPos;
		int yPos;
		RawInput();
	public:
		
		static RawInput* instance();

		~RawInput();

		void setX(LPARAM lparam);
		void setY(LPARAM lparam);

		int getX();
		int getY();

		int getButton(WPARAM wParam);

	};
};