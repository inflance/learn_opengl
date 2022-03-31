#include "UniformTest.h"

UniformTest::UniformTest()
{
	//��ʼ��GLFW
	glfwInit();
	//����GLFW, 3.3�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//���ÿ��ߣ�����
	GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpengl", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "�޷�����GLFW����" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	//�����ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD��

	//����glad����ϵͳ��ص�OpenGL����ָ���ַ�ĺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "�޷���ʼ��GLAD" << std::endl;
	}

	//�����ӿ�ViewPort��x, y, width, height��
	glViewport(0, 0, 800, 600);

	//���ûص������������û��ı䴰�ڴ�Сʱ�ӿ�Ҳ�ᱻ����
	glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);
	
	Shader myShader("res/shader/Shader.vs", "res/shader/uniformShader.fs");


	//���Ӷ�������
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	//ʹ��glGenBuffers������һ������ID����һ��VBO����
	unsigned int VBO, VAO;

	//�����������index buffer obj
	//unsigned int IBO;

	glGenVertexArrays(1, &VAO);
	//�������󶨶��㻺��
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glGenBuffers(1, &EBO);

	//���Ȱ�VAO��Ȼ������ö��㻺������������ö�������
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//GL_FALSE (void*)ƫ����
	//����
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO);

	//GL_LINE�߿�ģʽ GL_FILL ͼ��ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//���ѭ����Ⱦ
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.useProgram();

		double timeValue = glfwGetTime();		//��õ�ǰʱ��
		float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		int vertexColorLocation = glGetUniformLocation(myShader.id, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);		//����fs r�� g�� b g��ʱ��仯

		glDrawArrays(GL_TRIANGLES, 0, 3);

		//��Ⱦָ��
		//�������¼�
		glfwPollEvents();

		//������ɫ������
		//˫��������һǰһ�󣬵��󻺳�����Ⱦ��ϲ��滻ǰ������������ͼ�񲻻���˸
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//�ͷ���Դ
	glfwTerminate();
}


