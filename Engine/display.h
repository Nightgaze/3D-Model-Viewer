#pragma once

#include "SDL2\SDL.h"
#include <string>
#include "transform.h"
class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	virtual ~Display();
	void Update(Transform& transform);
	bool IsClosed();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;

	//keyboard:
	bool key_left;
	bool key_right;
	bool key_up;
	bool key_down;
	int mouse_x;
	int mouse_y;
	int x;
	int y;



};

