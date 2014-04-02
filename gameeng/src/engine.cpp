/*
 * engine.cpp
 *
 *  Created on: 29.03.2014
 *      Author: armoncarigiet
 */
#include <iostream>
#include "engine.h"


void engine::init(){
	if(!glfwInit()) {
		error=-1;
	}
#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videomode = glfwGetVideoMode(monitor);
	this->window = glfwCreateWindow(videomode->width/3*2, videomode->height/3*2, "Hello World", NULL, NULL);

	if(!window){
	        glfwTerminate();
	        error=-1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	// optional
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


}

void engine::close(){
	glfwTerminate();
	exit(1);	// just for debug
}

