#include "display.h"
#include "GL/glew.h"
#include <iostream>



Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);     //genereaza 2^8 nuante de rosu
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);	//32 biti/pixel(cel putin)
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);     //depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//anti aliasing:
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);	
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cout << "Glew nu a reusit sa fie initializat" << std::endl;
	}

	m_isClosed = false;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);		//rezolva hidden face overwrite issue(partial)
	glEnable(GL_DEPTH_TEST);	//best
	glEnable(GL_MULTISAMPLE);



	
	//keyboard:
	key_left = false;
	key_right = false;
	key_up = false;
	key_down = false;
	mouse_x = 0;
	mouse_y = 0;
	x = 320;
	y = 240;
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

}

void Display::Update(Transform& transform)
{

	SDL_GL_SwapWindow(m_window);   //swapping buffers
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			m_isClosed = true;

		if (e.type = SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				key_left = true;
				transform.GetPos()->x += 0.1f;
				break;
			case SDLK_d:
				key_right = true;
				transform.GetPos()->x -= 0.1f;;
				break;
			case SDLK_w:
				key_up = true;
				transform.GetPos()->y += 0.1f;;
				break;
			case SDLK_s:
				key_down = true;
				transform.GetPos()->y -= 0.1f;;
				break;

			case SDLK_LEFT:
				transform.GetRot()->y += 0.05f;
					break;

			case SDLK_RIGHT:
				transform.GetRot()->y -= 0.05f;
				break;

			case SDLK_UP:
				transform.GetRot()->z += 0.05f;
				break;

			case SDLK_DOWN:
				transform.GetRot()->z -= 0.05f;
				break;

			case SDLK_z:
				transform.SetScale(glm::vec3(transform.GetScale()->x + 0.05f,
											transform.GetScale()->y + 0.05f,
											transform.GetScale()->z + 0.05f));
				break;

			case SDLK_x:
				if (transform.GetScale()->x > 0.05 &&
					transform.GetScale()->y > 0.05 &&
					transform.GetScale()->z > 0.05    )
					transform.SetScale(glm::vec3(transform.GetScale()->x-0.05f,
											transform.GetScale()->y - 0.05f,
											transform.GetScale()->z - 0.05f));
				
				break;

			}
		}

		if (e.type = SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				key_left = false;
				break;


			case SDLK_RIGHT:
				key_right = false;

				break;
			case SDLK_UP:
				key_up = false;

				break;
			case SDLK_DOWN:
				key_down = false;

				break;
			}
		}

		
	}
	

}

bool Display::IsClosed()
{
	return m_isClosed;
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g ,b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}