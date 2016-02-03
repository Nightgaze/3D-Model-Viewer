#include <iostream>
#include "GL\glew.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"


int WIDTH = 500;
int HEIGHT = 400;
int main(int argc, char** argv)
{
	Display display(800, 600, "Test");
	Shader shader("./shaders/basicshader");
	Shader shader2("./shaders/basicshader");
	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
						Vertex(glm::vec3(0, 0.5, 0) , glm::vec2(0.5, 1.0)),
						Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };
	unsigned int indices[] = { 0, 1, 2 };

	Texture texture("images/test.png");
	Transform transform;
	Transform origin;
	origin.SetPos(glm::vec3(0, 5, 0));

	float counter = 0.0f;
	Camera camera(glm::vec3(0, 0, -30), 70.0f, (float)WIDTH/HEIGHT , 0.01f, 1000.0f);



	//Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Mesh mesh2("./images/mountainsuv.obj");
	//Mesh mesh3("./images/monkey3.obj");

	//Console stuff:
	std::cout << "   Controls:" << '\n' <<'\n'<< "   W A S D = sus stanga jos dreapta"
			  << '\n' << "  z = zoom in"
			  << '\n' << "  x = zoom out"
			  << '\n' << "  UP ARROW  = rotatie verticala sus"
			  << '\n' << "  DOWN ARROW  = rotatie verticala jos"
			  << '\n' << "  LEFT ARROW  = rotatie orizontala stanga"
			  << '\n' << "  RIGHT ARROW  = rotatie verticala dreapta";

	
	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.5f, 0.3f, 0.0f);

		shader.Bind();
		texture.Bind();

		
		mesh2.Draw();



		//mesh.Draw()
		shader.Update(transform, origin, camera);
		display.Update(transform);
		counter += 0.001f;

	}

	return 0;
}