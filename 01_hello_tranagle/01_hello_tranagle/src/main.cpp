#include <glad/glad.h>
//GLAD是用来管理OpenGL的函数指针
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	//检查有没有按下esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main()
{
	//初始化GLFW
	glfwInit();
	//配置GLFW, 3.3版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//设置宽，高，标题
	GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpengl", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "无法创建GLFW窗口" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//所以在调用任何OpenGL的函数之前我们需要初始化GLAD。

	//传入glad加载系统相关的OpenGL函数指针地址的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "无法初始化GLAD" << std::endl;
		return -1;
	}

	//设置视口ViewPort（x, y, width, height）
	glViewport(0, 0, 800, 600);

	//设置回调函数，这样用户改变窗口大小时视口也会被调整
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//顶点着色器代码
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	//创建顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//编译着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//查看编译是否成功
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//创建片段着色器
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"} ";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//合并，链接着色器程序
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	//检查
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//激活程序对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//链接顶点属性
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	//float vertices[] = {
	//0.0f, 0.5f, 0.0f,    //右上角
	//0.0f, -0.5f, 0.0f,   //右下角
	//-1.0f, -0.5f, 0.0f,  //左下角
	//1.0f, -0.5f, 0.0f    //左上角
	//};

	//unsigned int indices[] = {  //注意索引从0开始! 
	//	0, 1, 2,  //第一个三角形
	//	0, 1, 3   //第二个三角形
	//};

	//使用glGenBuffers函数和一个缓冲ID生成一个VBO对象：
	unsigned int VBO, VAO;

	//索引缓冲对象（index buffer obj
	//unsigned int IBO;

	glGenVertexArrays(1, &VAO);
	//缓冲区绑定顶点缓冲
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glGenBuffers(1, &EBO);

	//首先绑定VAO，然后绑定设置顶点缓冲区，最后配置顶点属性
	glBindVertexArray(VAO);

	//设置EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//GL_FALSE (void*)偏移量
	//启用
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//GL_LINE线框模式 GL_FILL 图形模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//添加循环渲染
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//指定类型，起始索引，顶点数
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//渲染指令
		//检查调用事件
		glfwPollEvents();

		//交换颜色缓冲区
		//双缓冲区，一前一后，当后缓冲区渲染完毕才替换前缓冲区，这样图像不会闪烁
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//释放资源
	glfwTerminate();

	return 0;
}