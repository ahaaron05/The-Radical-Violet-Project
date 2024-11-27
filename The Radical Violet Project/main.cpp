#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Settings
const unsigned int SCREEN_WIDTH = 900;
const unsigned int SCREEN_HEIGHT = 700;
const float FOV_Y = 60.0f;

int main()
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Radical Violet Project", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	// query GPU info
	const char* GPUVendor = (const char*)glGetString(GL_VENDOR);
	const char* GPURenderer = (const char*)glGetString(GL_RENDERER);
	std::cout << "GPU Vendor::" << GPUVendor << std::endl << "GPU Renderer::" << GPURenderer << std::endl;
	// query max GPU vertex attributes
	int nAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttributes);
	std::cout << "GPU Vertex Attributes supported::" << nAttributes << std::endl;
	
	// Shader program
	Shader shaderProgram("shader.vert", "shader.frag");

	// Vertex data
	float vertices[] =
	{   // positions				colors
		-0.5f, -0.5f, -0.5f,	  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	  0.0f, 1.0f, 0.0f,
								  
		-0.5f, -0.5f,  0.5f,	  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	  0.0f, 1.0f, 0.0f,
								  
		-0.5f,  0.5f,  0.5f,	  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	  0.0f, 1.0f, 0.0f,
								  
		 0.5f,  0.5f,  0.5f,	  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	  0.0f, 1.0f, 0.0f,
								  
		-0.5f, -0.5f, -0.5f,	  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	  0.0f, 1.0f, 0.0f,
								  
		-0.5f,  0.5f, -0.5f,	  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	  0.0f, 1.0f, 0.0f,
	};
	unsigned int indices[] =
	{
		0, 1, 3,	// tri 1
		1, 2, 3,	// tri 2
	};

	unsigned int VBO, VAO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO); //! BIND VAO FIRST
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // unbind for safety

	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f)); // NOTE: right-handed system
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 0.1f, 100.0f);

	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render commands
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0, 1, 0));
		
		shaderProgram.setMat4("model", model);
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);

		// Drawing
		glBindVertexArray(VAO);
		shaderProgram.use();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// check for events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// deallocate
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

// Allows for window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Handles all input within GLFW window
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}