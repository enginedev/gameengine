//============================================================================
// Name        : gameeng.cpp
// Author      : Armon Carigiet
// Version     :
// Copyright   : copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "engine.h"

#define GLM_FORCE_RADIANS 1
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

int main() {
	std::cout<<"lol"<<std::endl;
	engine e;
	e.init();


	float points[] = {
			0.0f,  0.5f,  0.0f,
			0.5f, -0.5f,  0.0f,
			-0.5f, -0.5f,  0.0f
		};

		float colours[] = {
			1.0f, 1.0f,  0.0f,
			0.0f, 1.0f,  1.0f,
			1.0f, 0.0f,  1.0f
		};



		glm::vec3 axis_z(0, 0, 1);
		float angle=M_PI/30;
		glm::mat4 identity(1.0f);
		glm::mat4 mat = glm::rotate(identity, angle, axis_z)
					  * glm::translate(identity, glm::vec3(0.25f, 0.0f, 0.0f));


	//	float matrix[] = {
	//		1.0f, 0.0f, 0.0f, 0.0f,
	//		0.0f, 1.0f, 0.0f, 0.0f,
	//		0.0f, 0.0f, 1.0f, 0.0f,
	//		0.0f, 0.0f, 0.0f, 1.0f
	//	};

		unsigned int points_vbo = 0;
		glGenBuffers (1, &points_vbo);
		glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
		glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);

		unsigned int colours_vbo = 0;
		glGenBuffers (1, &colours_vbo);
		glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
		glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), colours, GL_STATIC_DRAW);

		unsigned int vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer (GL_ARRAY_BUFFER, colours_vbo);
		glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


		const char* vertex_shader =
		"#version 400\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec3 vertex_colour;"
		"uniform mat4 matrix;"
		"out vec3 colour;"
		"void main () {"
		"	colour = vertex_colour;"
		"	gl_Position = matrix * vec4 (vertex_position, 1.0);"
		"}";


		const char* fragment_shader =
		"#version 400\n"
		"in vec3 colour;"
		"out vec4 frag_colour;"
		"void main () {"
		"	frag_colour = vec4 (colour, 1.0);"
		"}";

		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader, NULL);
		glCompileShader(vs);
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader, NULL);
		glCompileShader (fs);

		unsigned int shader_programme = glCreateProgram();
		glAttachShader(shader_programme, fs);
		glAttachShader(shader_programme, vs);
		glLinkProgram(shader_programme);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable (GL_CULL_FACE);
		glCullFace (GL_BACK);
		glFrontFace (GL_CW);

	    do{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			int matrix_location = glGetUniformLocation (shader_programme, "matrix");
			glUseProgram (shader_programme);
			glUniformMatrix4fv (matrix_location, 1, GL_FALSE, &mat[0][0]);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);


	        glfwSwapBuffers(e.window);

	        glfwPollEvents();

			if (glfwGetKey(e.window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
				glfwSetWindowShouldClose (e.window, 1);
			}
	    }while (!glfwWindowShouldClose(e.window));

	return 0;
}

