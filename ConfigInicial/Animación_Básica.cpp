//Practica#10 (AnimBasica) Monroy Salazar
//Fecha de entrega 08 de Abril de 2025
//315118894

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "CameraVR.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 1280, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
CameraVR cameraVR(glm::vec3(0.0f, 0.0f, 3.0f));



// Camera options
bool activeCamera = true;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);


//Anim

//Perro
float rotBall = 0.0f;
float rotDog = 0.0f;
int dogAnim = 0;
float FLegs = 0.0f;
float RLegs = 0.0f;
float head = 0.0f;
float tail = 0.0f;

//Dron
float dronRot = 0.0f;




// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

//KeyFrames
//Perro
float dogPosX, dogPosY, dogPosZ;
//Dron
float dronPosX=10.0f, dronPosY=10.0f, dronPosZ=10.0f;

#define MAX_FRAMES 90
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame {

	float rotDog;
	float rotDogInc;
	float dogPosX;
	float dogPosY;
	float dogPosZ;
	float dogIncX;
	float dogIncY;
	float dogIncZ;
	float head;
	float headInc;

	

}FRAME;

typedef struct _framedron {

	float dronPosX;
	float dronPosY;
	float dronPosZ;

	float dronRot;
	float dronRotInc;

	float dronIncX;
	float dronIncY;
	float dronIncZ;


}FRAMEDRON;



FRAME KeyFrame[MAX_FRAMES];
FRAMEDRON KeyFrameDron[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos

int FrameIndexDron = 0;	//introducir datos

bool play = false;
int playIndex = 0;



void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].dogPosX = dogPosX;
	KeyFrame[FrameIndex].dogPosY = dogPosY;
	KeyFrame[FrameIndex].dogPosZ = dogPosZ;

	KeyFrame[FrameIndex].rotDog = rotDog;
	KeyFrame[FrameIndex].head = head;

	



	FrameIndex++;
}


void saveFrameDron(void)
{

	printf("frameindexdron %d\n", FrameIndexDron);



	KeyFrameDron[FrameIndexDron].dronPosX = dronPosX;
	KeyFrameDron[FrameIndexDron].dronPosY = dronPosY;
	KeyFrameDron[FrameIndexDron].dronPosZ = dronPosZ;
	KeyFrameDron[FrameIndexDron].dronRot = dronRot;



	FrameIndexDron++;
}

void SaveKeyFramesToFile(const std::string & filename) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Error al abrir el archivo para guardar los keyframes: " << filename << std::endl;
		return;
	}

	outFile << FrameIndex << std::endl;
	for (int i = 0; i < FrameIndex; ++i) {
		outFile << KeyFrame[i].dogPosX << " "
			<< KeyFrame[i].dogPosY << " "
			<< KeyFrame[i].dogPosZ << " "
			<< KeyFrame[i].rotDog << " "
			<< KeyFrame[i].head << std::endl;
	}

	outFile.close();
	std::cout << "Keyframes guardados correctamente en el archivo: " << filename << std::endl;
}


void SaveKeyFramesDronToFile(const std::string & filename) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Error al abrir el archivo para guardar los keyframes: " << filename << std::endl;
		return;
	}

	outFile << FrameIndexDron << std::endl;
	for (int i = 0; i < FrameIndexDron; ++i) {
		outFile << KeyFrameDron[i].dronPosX << " "
			<< KeyFrameDron[i].dronPosY << " "
			<< KeyFrameDron[i].dronPosZ << " "
			<< KeyFrameDron[i].dronRot << std::endl;
	}

	outFile.close();
	std::cout << "Keyframes guardados correctamente en el archivo: " << filename << std::endl;
}





void resetElements(void)
{
	dogPosX = KeyFrame[0].dogPosX;
	dogPosY = KeyFrame[0].dogPosY;
	dogPosZ = KeyFrame[0].dogPosZ;
	head = KeyFrame[0].head;

	rotDog = KeyFrame[0].rotDog;

	dronPosX = KeyFrameDron[0].dronPosX;
	dronPosY = KeyFrameDron[0].dronPosY;
	dronPosZ = KeyFrameDron[0].dronPosZ;
	dronRot = KeyFrameDron[0].dronRot;

}
void interpolation(void)
{

	KeyFrame[playIndex].dogIncX = (KeyFrame[playIndex + 1].dogPosX - KeyFrame[playIndex].dogPosX) / i_max_steps;
	KeyFrame[playIndex].dogIncY = (KeyFrame[playIndex + 1].dogPosY - KeyFrame[playIndex].dogPosY) / i_max_steps;
	KeyFrame[playIndex].dogIncZ = (KeyFrame[playIndex + 1].dogPosZ - KeyFrame[playIndex].dogPosZ) / i_max_steps;
	KeyFrame[playIndex].headInc = (KeyFrame[playIndex + 1].head - KeyFrame[playIndex].head) / i_max_steps;

	KeyFrame[playIndex].rotDogInc = (KeyFrame[playIndex + 1].rotDog - KeyFrame[playIndex].rotDog) / i_max_steps;

	KeyFrameDron[playIndex].dronIncX = (KeyFrameDron[playIndex + 1].dronPosX - KeyFrameDron[playIndex].dronPosX) / i_max_steps;
	KeyFrameDron[playIndex].dronIncY = (KeyFrameDron[playIndex + 1].dronPosY - KeyFrameDron[playIndex].dronPosY) / i_max_steps;
	KeyFrameDron[playIndex].dronIncZ = (KeyFrameDron[playIndex + 1].dronPosZ - KeyFrameDron[playIndex].dronPosZ) / i_max_steps;
	KeyFrameDron[playIndex].dronRotInc = (KeyFrameDron[playIndex + 1].dronRot - KeyFrameDron[playIndex].dronRot) / i_max_steps;


}

void LoadKeyFramesFromFile(const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cerr << "Error al abrir el archivo para cargar los keyframes: " << filename << std::endl;
		return;
	}

	inFile >> FrameIndex;
	for (int i = 0; i < FrameIndex; ++i) {
		inFile >> KeyFrame[i].dogPosX
			>> KeyFrame[i].dogPosY
			>> KeyFrame[i].dogPosZ
			>> KeyFrame[i].rotDog
			>> KeyFrame[i].head;

	}

	inFile.close();
	std::cout << "Keyframes cargados correctamente desde el archivo: " << filename << std::endl;

	// Inicializar elementos y preparar la primera interpolaci?n
	if (FrameIndex > 1) {
		resetElements();  // Restablece los elementos al primer keyframe
		interpolation();  // Prepara la interpolaci?n para la animaci?n
	}
}

void LoadKeyFramesDronFromFile(const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cerr << "Error al abrir el archivo para cargar los keyframes: " << filename << std::endl;
		return;
	}

	inFile >> FrameIndexDron;
	for (int i = 0; i < FrameIndexDron; ++i) {
		inFile >> KeyFrameDron[i].dronPosX
			>> KeyFrameDron[i].dronPosY
			>> KeyFrameDron[i].dronPosZ
			>> KeyFrameDron[i].dronRot;

	}

	inFile.close();
	std::cout << "Keyframes cargados correctamente desde el archivo: " << filename << std::endl;

	// Inicializar elementos y preparar la primera interpolaci?n
	if (FrameIndexDron > 1) {
		resetElements();  // Restablece los elementos al primer keyframe
		interpolation();  // Prepara la interpolaci?n para la animaci?n
	}
}

void ResetKeyFrames(void)
{
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].dogPosX = 0;
		KeyFrame[i].dogPosY = 0;
		KeyFrame[i].dogPosZ = 0;
		KeyFrame[i].dogIncX = 0;
		KeyFrame[i].dogIncY = 0;
		KeyFrame[i].dogIncZ = 0;
		KeyFrame[i].rotDog = 0;
		KeyFrame[i].rotDogInc = 0;
		KeyFrame[i].head = 0;
		KeyFrame[i].headInc = 0;


		KeyFrameDron[i].dronPosX = 0;
		KeyFrameDron[i].dronPosY = 0;
		KeyFrameDron[i].dronPosZ = 0;
		KeyFrameDron[i].dronIncX = 0;
		KeyFrameDron[i].dronIncY = 0;
		KeyFrameDron[i].dronIncZ = 0;

		KeyFrameDron[i].dronRot = 0;
	}
}


int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion basica Monroy Salazar", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	
	//models
	//Model Ball((char*)"Models/ball.obj");
	//Model Piso((char*)"Models/piso.obj");
	/*Model Dog((char*)"Models/RedDog.obj");
	Model chair((char*)"Models/Chair/kursi.obj");
	Model tablec((char*)"Models/Table/Chair_and_Table_School.obj");
	Model room((char*)"Models/Room/Room.obj");
	Model board((char*)"Models/Piza/pizar.obj");
	Model dron((char*)"Models/Test/DronT2.obj");
	Model room2((char*)"Models/Test/test12.obj");
	Model hand((char*)"Models/Test/handRob.obj");
	Model handF1((char*)"Models/Test/handRobF1.obj");
	Model handF2((char*)"Models/Test/handRobF2.obj");
	Model handF3((char*)"Models/Test/handRobF3.obj");
	Model handF4((char*)"Models/Test/handRobF4.obj");
	Model handF5((char*)"Models/Test/handRobF5.obj");*/

	//models
	Model DogBody((char*)"Models/DogBody.obj");
	Model HeadDog((char*)"Models/HeadDog.obj");
	Model DogTail((char*)"Models/TailDog.obj");
	Model F_RightLeg((char*)"Models/F_RightLegDog.obj");
	Model F_LeftLeg((char*)"Models/F_LeftLegDog.obj");
	Model B_RightLeg((char*)"Models/B_RightLegDog.obj");
	Model B_LeftLeg((char*)"Models/B_LeftLegDog.obj");
	Model Piso((char*)"Models/piso.obj");
	Model Ball((char*)"Models/ball.obj");

	Model Salon((char*)"Models/salon.obj");
	Model Banca1((char*)"Models/Bancas1.obj");
	Model Banca2((char*)"Models/Bancas2.obj");

	Model dron((char*)"Models/Test/DronT2.obj");


	//KeyFrames
	ResetKeyFrames();

	LoadKeyFramesFromFile("keyframes.dat");
	LoadKeyFramesDronFromFile("keyframesdron.dat");



	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window)){

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);


		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp



		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));


		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);



		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);

		//Salon
		glm::mat4 modelR(1);
		//modelR = glm::translate(modelR, glm::vec3(0.0f, -0.45f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelR));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Salon.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		//Dron

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(dronPosX, dronPosY, dronPosZ));
		model = glm::rotate(model, glm::radians(dronRot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		dron.Draw(lightingShader);
		glBindVertexArray(0);


		//Bancas


		glm::mat4 modelB2M1(1);
		modelB2M1 = glm::translate(modelB2M1, glm::vec3(-10.0f, -0.9f, -10.0f));
		modelB2M1 = glm::rotate(modelB2M1, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB2M1));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Banca2.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		glm::mat4 modelB2M2(1);
		modelB2M2 = glm::translate(modelB2M2, glm::vec3(0.0f, -0.9f, -10.0f));
		modelB2M2 = glm::rotate(modelB2M2, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB2M2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Banca2.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		glm::mat4 modelB1M1(1);
		modelB1M1 = glm::translate(modelB1M1, glm::vec3(-10.0f, -0.9f, 0.0f));
		modelB1M1 = glm::rotate(modelB1M1, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB1M1));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Banca1.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		glm::mat4 modelB1M2(1);
		modelB1M2 = glm::translate(modelB1M2, glm::vec3(0.0f, -0.9f, 0.0f));
		modelB1M2 = glm::rotate(modelB1M2, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB1M2));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Banca1.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		glm::mat4 modelB1M3(1);
		modelB1M3 = glm::translate(modelB1M3, glm::vec3(0.0f, -0.9f, -10.0f));
		modelB1M3 = glm::rotate(modelB1M3, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB1M3));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Banca1.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		glm::mat4 modelB1M4(1);
		modelB1M4 = glm::translate(modelB1M4, glm::vec3(-10.0f, -0.9f, -10.0f));
		modelB1M4 = glm::rotate(modelB1M4, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB1M4));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Banca1.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);


		glm::mat4 modelB2M3(1);
		modelB2M3 = glm::translate(modelB2M3, glm::vec3(-10.0f, -0.9f, -15.0f));
		modelB2M3 = glm::rotate(modelB2M3, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB2M3));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Banca2.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		glm::mat4 modelB2M4(1);
		modelB2M4 = glm::translate(modelB2M4, glm::vec3(0.0f, -0.9f, -15.0f));
		modelB2M4 = glm::rotate(modelB2M4, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB2M4));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Banca2.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);

		


		


		


		//model = glm::mat4(1);
		////Body
		//modelTemp = model = glm::translate(model, glm::vec3(dogPosX, dogPosY, dogPosZ));
		//modelTemp = model = glm::rotate(model, glm::radians(rotDog), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//DogBody.Draw(lightingShader);
		////Head
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
		//model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//HeadDog.Draw(lightingShader);
		////Tail 
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
		//model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//DogTail.Draw(lightingShader);
		////Front Left Leg
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
		//model = glm::rotate(model, glm::radians(FLegs), glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//F_LeftLeg.Draw(lightingShader);
		////Front Right Leg
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
		//model = glm::rotate(model, glm::radians(FLegs), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//F_RightLeg.Draw(lightingShader);
		////Back Left Leg
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218));
		//model = glm::rotate(model, glm::radians(RLegs), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//B_LeftLeg.Draw(lightingShader);
		////Back Right Leg
		//model = modelTemp;
		//model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		//model = glm::rotate(model, glm::radians(RLegs), glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//B_RightLeg.Draw(lightingShader);


		//model = glm::mat4(1);
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		//model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Ball.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 
		//glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)

		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);
	

		
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}




// Moves/alters the camera positions based on user input
void DoMovement()
{
	//Dog Controls

	/*if (keys[GLFW_KEY_4])
	{

		head += 1.0f;

	}

	if (keys[GLFW_KEY_5])
	{

		head -= 1.0f;

	}*/

	if (keys[GLFW_KEY_2])
	{

		rotDog += 1.0f;

	}

	if (keys[GLFW_KEY_3])
	{

		rotDog -= 1.0f;

	}

	/*if (keys[GLFW_KEY_H])
	{
		dogPosZ += 0.01;
	}

	if (keys[GLFW_KEY_Y])
	{
		dogPosZ -= 0.01;
	}

	if (keys[GLFW_KEY_G])
	{
		dogPosX -= 0.01;
	}

	if (keys[GLFW_KEY_J])
	{
		dogPosX += 0.01;
	}*/

	if (keys[GLFW_KEY_T])
	{
		dronPosX -= 0.01;
	}

	if (keys[GLFW_KEY_G])
	{
		dronPosX += 0.01;
	}

	if (keys[GLFW_KEY_F])
	{
		dronPosZ += 0.01;
	}

	if (keys[GLFW_KEY_H])
	{
		dronPosZ -= 0.01;
	}

	if (keys[GLFW_KEY_UP])
	{
		dronPosY += 0.01;
	}

	if (keys[GLFW_KEY_DOWN])
	{
		dronPosY -= 0.01;
	}

	if (keys[GLFW_KEY_LEFT])
	{
		dronRot += 1.0f;
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		dronRot -= 1.0f;
	}



	// Camera controls
	if (keys[GLFW_KEY_W])
	{
		if (activeCamera) {
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}
		else {
			cameraVR.ProcessKeyboard(FORWARDVR, deltaTime);
		}

	}

	if (keys[GLFW_KEY_S])
	{
		if (activeCamera) {
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}
		else {
			cameraVR.ProcessKeyboard(BACKWARDVR, deltaTime);
		}


	}

	if (keys[GLFW_KEY_A])
	{
		if (activeCamera) {
			camera.ProcessKeyboard(LEFT, deltaTime);
		}
		else {
			cameraVR.ProcessKeyboard(LEFTVR, deltaTime);
		}

		
	}

	if (keys[GLFW_KEY_D])
	{
		if (activeCamera) {
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}
		else {
			cameraVR.ProcessKeyboard(RIGHTVR, deltaTime);
		}


	}

	/*if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}*/
	
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1) && (FrameIndexDron)>1)
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (keys[GLFW_KEY_K])
	{
		
		if (FrameIndexDron < MAX_FRAMES)
		{
			
			//Dron
			saveFrameDron();
			SaveKeyFramesDronToFile("keyframesdron.dat");
		}

	}

	if (keys[GLFW_KEY_M])
	{
		//Dog
		saveFrame();
		SaveKeyFramesToFile("keyframes.dat");
	}

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 0.0f);
			
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
	/*if (keys[GLFW_KEY_N])
	{
		AnimBall = !AnimBall;

		
	}*/

	if (keys[GLFW_KEY_C])
	{
		// Alternar entre las cámaras
		activeCamera = !activeCamera;
	}
}
//void Animation() {
//	if (AnimBall)
//	{
//		rotBall += 0.2f;
//		//printf("%f", rotBall);
//	}
//	else
//	{
//		//rotBall = 0.0f;
//	}
//}

void Animation() {

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2 && playIndex > FrameIndexDron-2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			dogPosX += KeyFrame[playIndex].dogIncX;
			dogPosY += KeyFrame[playIndex].dogIncY;
			dogPosZ += KeyFrame[playIndex].dogIncZ;
			head += KeyFrame[playIndex].headInc;

			rotDog += KeyFrame[playIndex].rotDogInc;

			dronPosX += KeyFrameDron[playIndex].dronIncX;
			dronPosY += KeyFrameDron[playIndex].dronIncY;
			dronPosZ += KeyFrameDron[playIndex].dronIncZ;
			dronRot += KeyFrameDron[playIndex].dronRotInc;

			i_curr_steps++;
		}

	}

}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;
	if (activeCamera) {
		camera.ProcessMouseMovement(xOffset, yOffset);
	}
	else {
		cameraVR.ProcessMouseMovement(xOffset, yOffset);
	}
	
}