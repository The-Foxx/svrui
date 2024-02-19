////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui_ogl_test.c
//  Version:     v1.00
//  Created:     18/02/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "../lib/glfw/GLFW/glfw3.h"
#include "stdio.h"
#include "GL/gl.h"
#include "stdlib.h"

static GLFWwindow* Window;

void key_callback(GLFWwindow* CurWindow, int Key, int Scancode, int Action, int Mods) {
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS) {
		glfwSetWindowShouldClose(CurWindow, GL_TRUE);

	}

}

static void main_loop() {
	float Ratio;
	int width, height;
	glfwGetFramebufferSize(Window, &width, &height);
	Ratio = width / (float) height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-Ratio, Ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
	glfwSwapBuffers(Window);
	glfwPollEvents();

}

int main(int argc, char* argv[]){
	printf("Starting vrui opengl test\n");
	int GlfwErrorCode = glfwInit();
	int GlfwMin, GlfwMaj, GlfwPatch;
	glfwGetVersion(&GlfwMaj, &GlfwMin, &GlfwPatch);
	printf("Glfw error code: %i version %i.%i.%i\n", GlfwErrorCode, GlfwMaj, GlfwMin, GlfwPatch);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window = glfwCreateWindow(1280, 960, "VRUI Test", NULL, NULL);
	glfwMakeContextCurrent(Window);

	//printf("Current shading lang version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glfwSetKeyCallback(Window, key_callback);

	while (!glfwWindowShouldClose(Window)) {
		main_loop();

	}

	glfwDestroyWindow(Window);
	glfwTerminate();
	
	return EXIT_SUCCESS;

}
