//Practica#4 (Modelado) Monroy Salazar
//Fecha de entrega 2 de Marzo de 2025
//315118894

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico Monroy Salazar", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 0.94f, 0.54f,0.796f,//Front
		0.5f, -0.5f, 0.5f,  0.94f, 0.54f,0.796f,
		0.5f,  0.5f, 0.5f,  0.94f, 0.54f,0.796f,
		0.5f,  0.5f, 0.5f,  0.94f, 0.54f,0.796f,
		-0.5f,  0.5f, 0.5f, 0.94f, 0.54f,0.796f,
		-0.5f, -0.5f, 0.5f, 0.94f, 0.54f,0.796f,
		
	    -0.5f, -0.5f,-0.5f, 0.94f, 0.54f,0.796f,//Back
		 0.5f, -0.5f,-0.5f, 0.94f, 0.54f,0.796f,
		 0.5f,  0.5f,-0.5f, 0.94f, 0.54f,0.796f,
		 0.5f,  0.5f,-0.5f, 0.94f, 0.54f,0.796f,
	    -0.5f,  0.5f,-0.5f, 0.94f, 0.54f,0.796f,
	    -0.5f, -0.5f,-0.5f, 0.94f, 0.54f,0.796f,
		
		 0.5f, -0.5f,  0.5f, 0.94f, 0.54f,0.796f,
		 0.5f, -0.5f, -0.5f, 0.94f, 0.54f,0.796f,
		 0.5f,  0.5f, -0.5f,  0.94f, 0.54f,0.796f,
		 0.5f,  0.5f, -0.5f,  0.94f, 0.54f,0.796f,
		 0.5f,  0.5f,  0.5f,  0.94f, 0.54f,0.796f,
		 0.5f,  -0.5f, 0.5f, 0.94f, 0.54f,0.796f,
      
		-0.5f,  0.5f,  0.5f,  0.94f, 0.54f,0.796f,
		-0.5f,  0.5f, -0.5f,  0.94f, 0.54f,0.796f,
		-0.5f, -0.5f, -0.5f,  0.94f, 0.54f,0.796f,
		-0.5f, -0.5f, -0.5f,  0.94f, 0.54f,0.796f,
		-0.5f, -0.5f,  0.5f,  0.94f, 0.54f,0.796f,
		-0.5f,  0.5f,  0.5f,  0.94f, 0.54f,0.796f,
		
		-0.5f, -0.5f, -0.5f, 0.94f, 0.54f,0.796f,
		0.5f, -0.5f, -0.5f,  0.94f, 0.54f,0.796f,
		0.5f, -0.5f,  0.5f,  0.94f, 0.54f,0.796f,
		0.5f, -0.5f,  0.5f,  0.94f, 0.54f,0.796f,
		-0.5f, -0.5f,  0.5f, 0.94f, 0.54f,0.796f,
		-0.5f, -0.5f, -0.5f, 0.94f, 0.54f,0.796f,
		
		-0.5f,  0.5f, -0.5f, 0.94f, 0.54f,0.796f,
		0.5f,  0.5f, -0.5f,  0.94f, 0.54f,0.796f,
		0.5f,  0.5f,  0.5f,  0.94f, 0.54f,0.796f,
		0.5f,  0.5f,  0.5f,  0.94f, 0.54f,0.796f,
		-0.5f,  0.5f,  0.5f, 0.94f, 0.54f,0.796f,
		-0.5f,  0.5f, -0.5f, 0.94f, 0.54f,0.796f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	// Datos de vértices para el "ojo" (mismo cubo, pero con color negro)
	float eyeVertices[] = {
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		// Right face
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 // Left face
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 // Top face
		 -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
	};




	GLuint VBO_eye, VAO_eye;
	glGenVertexArrays(1, &VAO_eye);
	glGenBuffers(1, &VBO_eye);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO_eye);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO_eye);
	glBufferData(GL_ARRAY_BUFFER, sizeof(eyeVertices), eyeVertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	


	// Datos de vértices para el "ojo" (mismo cubo, pero con color negro)
	float bocaVertices[] = {
		// Front face
		-0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		// Back face
		- 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		// Right face
		 0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		// Left face
		- 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		// Top face
		- 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f,  0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f,  0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		// Bottom face
		- 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		 0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f, -0.5f,  0.5f,  0.79f, 0.34f, 0.60f,
		- 0.5f, -0.5f, -0.5f,  0.79f, 0.34f, 0.60f,
	};




	GLuint VBO_boca, VAO_boca;
	glGenVertexArrays(1, &VAO_boca);
	glGenBuffers(1, &VBO_boca);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO_boca);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO_boca);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bocaVertices), bocaVertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	glm::mat4 projection=glm::mat4(1);


	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
	

		//Cuerpo
	    model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.8f, 0.8f, 2.1f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		
		
		//Cabeza1
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.8f, 1.0f, 0.8f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, (1.45)/(0.8f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Ojo1

		glBindVertexArray(VAO_eye);
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.8f) / (0.2f), 0.0f, (1.95f) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Ojo2

		glBindVertexArray(VAO_eye);
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((0.8f) / (0.2f), 0.0f, (1.95f) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Boca

		glBindVertexArray(VAO_boca);
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, (1.95f) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//C2

		glBindVertexArray(VAO);
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.8f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, (0.3f) / (0.4), (1.95f) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//C3


		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.8f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, (-0.3f) / (0.4), (1.95f) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//C4

		
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.45f) / (0.5), 0.0f, (1.95f) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//C4


		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((0.45f) / (0.5), 0.0f, (1.95f) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Cola1

		glBindVertexArray(VAO_boca);


		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 2.7f));
		model = glm::translate(model, glm::vec3(0.0f, (0.5f) / (0.2f), (-0.5) / (2.7f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola2

		


		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.8f));
		model = glm::translate(model, glm::vec3(0.0f, (0.3f) / (0.2f), (-1.85) / (0.8f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola3




		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.8f));
		model = glm::translate(model, glm::vec3(0.0f, (0.1f) / (0.2f), (-2.25) / (0.8f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola4
			
		glBindVertexArray(VAO);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.4f));
		model = glm::translate(model, glm::vec3(0.0f, (0.3f) / (0.2f), (-1.25) / (0.4f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola5

		

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.8f));
		model = glm::translate(model, glm::vec3(0.0f, (0.1f) / (0.2f), (-1.45) / (0.8f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola6



		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 1.6f));
		model = glm::translate(model, glm::vec3(0.0f, (-0.1f) / (0.2f), (-1.85) / (1.6f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola7

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 1.6f));
		model = glm::translate(model, glm::vec3(0.0f, (-0.2f) / (0.2f), (-1.85) / (1.6f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola8

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(0.0f, (-0.15f) / (0.6f), (-2.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Crespa 1

		

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.1f));
		model = glm::translate(model, glm::vec3((-1.0f) / (0.2f), (-0.2f) / (0.4f), (1.1) / (0.1f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Crespa 2



		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.1f));
		model = glm::translate(model, glm::vec3((-1.1f) / (0.2f), (-0.1f) / (0.4f), (1.1) / (0.1f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Crespa 3



		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.1f));
		model = glm::translate(model, glm::vec3((-1.0f) / (0.2f), (0.4f) / (0.4f), (1.1) / (0.1f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Crespa 4



		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.1f));
		model = glm::translate(model, glm::vec3((-1.1f) / (0.2f), (0.5f) / (0.4f), (1.1) / (0.1f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);




		//Crespa 5



		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.1f));
		model = glm::translate(model, glm::vec3((1.0f) / (0.2f), (-0.2f) / (0.4f), (1.1) / (0.1f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Crespa 6



		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.1f));
		model = glm::translate(model, glm::vec3((1.1f) / (0.2f), (-0.1f) / (0.4f), (1.1) / (0.1f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Crespa 7



		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.1f));
		model = glm::translate(model, glm::vec3((1.0f) / (0.2f), (0.4f) / (0.4f), (1.1) / (0.1f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Crespa 8



		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.1f));
		model = glm::translate(model, glm::vec3((1.1f) / (0.2f), (0.5f) / (0.4f), (1.1) / (0.1f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Pierna1

		glBindVertexArray(VAO);
		

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3((0.85f) / (0.1f), (-0.7f) / (0.6f), (0.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo1

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((0.85f) / (0.1f), (-0.9f) / (0.2f), (0.95) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo2

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((0.85f) / (0.1f), (-0.9f) / (0.2f), (0.55) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo3

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((0.85f) / (0.1f), (-1.0f) / (0.2f), (0.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Pierna2

		glBindVertexArray(VAO);
		

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.85f) / (0.1f), (-0.7f) / (0.6f), (0.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo4

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.85f) / (0.1f), (-0.9f) / (0.2f), (0.95) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo5

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.85f) / (0.1f), (-0.9f) / (0.2f), (0.55) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo6

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.85f) / (0.1f), (-1.0f) / (0.2f), (0.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);



		//Pierna3

		glBindVertexArray(VAO);
		

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3((0.85f) / (0.1f), (-0.7f) / (0.6f), (-0.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo7

		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((0.85f) / (0.1f), (-0.9f) / (0.2f), (-0.95) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo8

		
		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((0.85f) / (0.1f), (-0.9f) / (0.2f), (-0.55) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo9

		
		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((0.85f) / (0.1f), (-1.0f) / (0.2f), (-0.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Pierna4

		glBindVertexArray(VAO);
		

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.85f) / (0.1f), (-0.7f) / (0.6f), (-0.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo10

		
		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.85f) / (0.1f), (-0.9f) / (0.2f), (-0.95) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo11

		
		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.85f) / (0.1f), (-0.9f) / (0.2f), (-0.55) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Dedo12

		
		glBindVertexArray(VAO_boca);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3((-0.85f) / (0.1f), (-1.0f) / (0.2f), (-0.75) / (0.2f)));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);



		/*
		//Pata 2
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 1.5f, 0.1f));
		model = glm::translate(model, glm::vec3(-14.5f, -0.467f, 9.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pata 3
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 1.5f, 0.1f));
		model = glm::translate(model, glm::vec3(-14.5f, -0.467f, -9.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pata 4
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.1f, 1.5f, 0.1f));
		model = glm::translate(model, glm::vec3(14.5f, -0.467f, -9.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		*/

		

				
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO_eye);
	glDeleteBuffers(1, &VBO_eye);
	glDeleteVertexArrays(1, &VAO_boca);
	glDeleteBuffers(1, &VBO_boca);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 movY -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ += 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ -= 0.02f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot -= 0.1f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot += 0.1f;
 }


