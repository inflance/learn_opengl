#pragma once
#include <glad/glad.h>
//GLAD����������OpenGL�ĺ���ָ��
#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Practice2
{
public:
	Practice2();


private:
	const char* fragmentShaderSourceOrange = "#version 330 core\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"} ";

	//������ɫ������
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSourceYellow = "#version 330 core\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
		"} ";


};