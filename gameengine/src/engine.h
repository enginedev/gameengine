/*
 * engine.h
 *
 *  Created on: 29.03.2014
 *      Author: armoncarigiet
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>



class engine{
public:
	int error;
	void init();
	void close();

private:
	GLFWwindow* window;
};

#endif /* ENGINE_H_ */
