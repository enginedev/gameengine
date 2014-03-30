//============================================================================
// Name        : gameengine.cpp
// Author      : Armon Carigiet
// Version     :
// Copyright   : Armon Carigiet 2014
//============================================================================

#include <iostream>
#include "engine.h"


//using namespace std;

int main() {
	engine e;
	e.init();


	const float surface_points[]={
			-1.0f, 1.0f, 0.0f,
			-1.0f, 0.5f, 0.0f,
			-0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.5f, 0.0f,
			0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 0.5f, 0.0f
	};

	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), surface_points, GL_STATIC_DRAW);

	unsigned int vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main () {"
		"  gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main () {"
		"  frag_colour = vec4 (0.3, 0.7, 0.3, 1.0);"
		"}";

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	unsigned int shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);



	    glfwSwapBuffers(e.window);

	    glfwPollEvents();

		if (glfwGetKey(e.window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
			glfwSetWindowShouldClose (e.window, 1);
		}
	}while(!glfwWindowShouldClose(e.window));

	return 0;
}
