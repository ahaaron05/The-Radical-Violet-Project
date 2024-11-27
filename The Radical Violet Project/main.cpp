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
	float triVertices[] =
	{   // positions		colors
		.5, -.5, 0,			1, 0, 0,				// bottom right		
		-.5, -.5, 0,		0, 1, 0,			    // bottom left
		0, .5, 0,			0, 0, 1,				// top
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); //! BIND VAO FIRST
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // unbind for safety

	Shader shaderProgram2("shader.vert", "shader.frag");
	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render commands
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		// Transformations
		glm::mat4 transformMat(1.0f);
		transformMat = glm::translate(transformMat, glm::vec3(0.3f, 0.0f, 0.0f));
		transformMat = glm::rotate(transformMat, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		transformMat = glm::scale(transformMat, glm::vec3(0.5f, 0.5f, 0.5f));
		shaderProgram.setMat4("transform", transformMat);

		// Drawing
		glBindVertexArray(VAO);
		shaderProgram.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// 2nd tri
		transformMat = glm::mat4(1.0f);
		transformMat = glm::translate(transformMat, glm::vec3(-0.5f, 0.75f, 0.0f));
		transformMat = glm::scale(transformMat, glm::vec3(1/tan(glfwGetTime())));
		shaderProgram2.setMat4("transform", transformMat);
		shaderProgram2.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);

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