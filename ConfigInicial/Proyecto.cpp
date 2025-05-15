//Proyecto 
//Fecha de entrega 05 de Mayo de 2025
//315118894
//317019450

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

//Hand
float handRot = 0.0f;
float handRotZ = 0.0f;
float handD1RotZ = 0.0f;
float handD2RotZ = 0.0f;
float handD3RotZ = 0.0f;
float handD4RotZ = 0.0f;
float handD5RotZ = 0.0f;

//Robot 
float cabezaRot = 0.0f;	
float brazoDRX = 0.0f;
float brazoDRY = 0.0f;
float brazoDRZ = 0.0f;
float brazoIRX = 0.0f;
float brazoIRY = 0.0f;
float brazoIRZ = 0.0f;
float piernaDRX = 0.0f;
float piernaDRY = 0.0f;
float piernaDRZ = 0.0f;
float piernaIRX = 0.0f;
float piernaIRY = 0.0f;
float piernaIRZ = 0.0f;

//Animación del armado del robot 

bool assemblingRobot = false;
float assembleSpeed = 0.01f;
float assembleProgress = 0.0f;

float deskProgress = 0.0f; // Progreso de la animación del escritorio

float deskProgress2 = 0.0f; // Progreso de la animación del escritorio 2

//Animacion de escritorios
// Duración en segundos de la animación
const float deskAnimDuration = 3.0f;
const float deskAnim2Duration = 3.0f;
float deskAnimTime = 0.0f;
float deskAnim2Time = 0.0f;
const float targetDeskScale = 1.0f;      // la escala final “x”
bool deskAnimDone = false;
bool deskAnim2Done = false;

// Coordenadas iniciales 
glm::vec3 initialBrazoDPos(-1.2f, -0.5f, 0.463f);
glm::vec3 initialBrazoIPos(1.2f, -0.5f, 12.499f);
glm::vec3 initialPiernaDPos(-2.19f, 0.0f, -5.49f);
glm::vec3 initialPiernaIPos(-2.19f, 0.0f, -8.5f);
glm::vec3 initialTorzoPos(-5.217f, -2.0f, 9.461f);
glm::vec3 initialCabezaPos(1.222f, -3.0f, 5.473f);

// Coordenadas finales 
glm::vec3 finalBrazoDPos(-1.2f, 0.2f, 5.463f);
glm::vec3 finalBrazoIPos(-1.2f, 0.2f, 5.49f);
glm::vec3 finalPiernaDPos(-1.19f, 0.0f, 5.49f);
glm::vec3 finalPiernaIPos(-1.19f, 0.0f, 5.5f);
glm::vec3 finalTorzoPos(-1.217f, 0.1f, 5.461f);
glm::vec3 finalCabezaPos(-1.222f, 0.2f, 5.473f);

// Variables para guardar las posiciones actuales durante el ensamblado
glm::vec3 currentBrazoDPos = initialBrazoDPos;
glm::vec3 currentBrazoIPos = initialBrazoIPos;
glm::vec3 currentPiernaDPos = initialPiernaDPos;
glm::vec3 currentPiernaIPos = initialPiernaIPos;
glm::vec3 currentTorzoPos = initialTorzoPos;
glm::vec3 currentCabezaPos = initialCabezaPos;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

//KeyFrames
//Perro
float dogPosX, dogPosY, dogPosZ;
//Dron
float dronPosX, dronPosY, dronPosZ;
//Hand
float handPosX, handPosY, handPosZ;
#define MAX_FRAMES 90
int i_max_steps = 150;
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
	float robot;
	float robotInc;

	

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

typedef struct _framehand {

	float handPosX;
	float handPosY;
	float handPosZ;

	float handIncX;
	float handIncY;
	float handIncZ;

	float handRot;
	float handRotZ;
	float handD1RotZ;
	float handD2RotZ;
	float handD3RotZ;
	float handD4RotZ;
	float handD5RotZ;

	float handRotInc;
	float handRotZInc;
	float handD1RotZInc;
	float handD2RotZInc;
	float handD3RotZInc;
	float handD4RotZInc;
	float handD5RotZInc;

}FRAMEHAND;
//robot
typedef struct _framerobot {
	float cabezaRot;
	float brazoDRX;
	float brazoDRY;
	float brazoDRZ;
	float brazoIRX;
	float brazoIRY;
	float brazoIRZ;
	float piernaDRX;
	float piernaDRY;
	float piernaDRZ;
	float piernaIRX;
	float piernaIRY;
	float piernaIRZ;

	float cabezaRotInc;
	float brazoDRXInc;
	float brazoDRYInc;
	float brazoDRZInc;
	float brazoIRXInc;
	float brazoIRYInc;
	float brazoIRZInc;
	float piernaDRXInc;
	float piernaDRYInc;
	float piernaDRZInc;
	float piernaIRXInc;
	float piernaIRYInc;
	float piernaIRZInc;
}FRAMEROBOT;



FRAME KeyFrame[MAX_FRAMES];
FRAMEDRON KeyFrameDron[MAX_FRAMES];
FRAMEHAND KeyFrameHand[MAX_FRAMES];
FRAMEROBOT KeyFrameRobot[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
int FrameIndexHand = 0;	//introducir datos
int FrameIndexDron = 0;	//introducir datos
int FrameIndexRobot = 0;	//introducir datos

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

void saveFrameHand(void)
{
	printf("frameindexhand %d\n", FrameIndexHand);
	KeyFrameHand[FrameIndexHand].handPosX = handPosX;
	KeyFrameHand[FrameIndexHand].handPosY = handPosY;
	KeyFrameHand[FrameIndexHand].handPosZ = handPosZ;
	KeyFrameHand[FrameIndexHand].handRot = handRot;
	KeyFrameHand[FrameIndexHand].handRotZ = handRotZ;
	KeyFrameHand[FrameIndexHand].handD1RotZ = handD1RotZ;
	KeyFrameHand[FrameIndexHand].handD2RotZ = handD2RotZ;
	KeyFrameHand[FrameIndexHand].handD3RotZ = handD3RotZ;
	KeyFrameHand[FrameIndexHand].handD4RotZ = handD4RotZ;
	KeyFrameHand[FrameIndexHand].handD5RotZ = handD5RotZ;

	FrameIndexHand++;
}

void saveFrameRobot(void)
{
	printf("frameindexrobot %d\n", FrameIndexRobot);
	KeyFrameRobot[FrameIndexRobot].cabezaRot = cabezaRot;
	KeyFrameRobot[FrameIndexRobot].brazoDRX = brazoDRX;
	KeyFrameRobot[FrameIndexRobot].brazoDRY = brazoDRY;
	KeyFrameRobot[FrameIndexRobot].brazoDRZ = brazoDRZ;
	KeyFrameRobot[FrameIndexRobot].brazoIRX = brazoIRX;
	KeyFrameRobot[FrameIndexRobot].brazoIRY = brazoIRY;
	KeyFrameRobot[FrameIndexRobot].brazoIRZ = brazoIRZ;
	KeyFrameRobot[FrameIndexRobot].piernaDRX = piernaDRX;
	KeyFrameRobot[FrameIndexRobot].piernaDRY = piernaDRY;
	KeyFrameRobot[FrameIndexRobot].piernaDRZ = piernaDRZ;
	KeyFrameRobot[FrameIndexRobot].piernaIRX = piernaIRX;
	KeyFrameRobot[FrameIndexRobot].piernaIRY = piernaIRY;
	KeyFrameRobot[FrameIndexRobot].piernaIRZ = piernaIRZ;

	FrameIndexRobot++;
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


void SaveKeyFramesHandToFile(const std::string& filename) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Error al abrir el archivo para guardar los keyframes: " << filename << std::endl;
		return;
	}
	outFile << FrameIndexHand << std::endl;
	for (int i = 0; i < FrameIndexHand; ++i) {
		outFile << KeyFrameHand[i].handPosX << " "
			<< KeyFrameHand[i].handPosY << " "
			<< KeyFrameHand[i].handPosZ << " "
			<< KeyFrameHand[i].handRot << " "
			<< KeyFrameHand[i].handRotZ << " "
			<< KeyFrameHand[i].handD1RotZ << " "
			<< KeyFrameHand[i].handD2RotZ << " "
			<< KeyFrameHand[i].handD3RotZ << " "
			<< KeyFrameHand[i].handD4RotZ << " "
			<< KeyFrameHand[i].handD5RotZ << std::endl;
	}
	outFile.close();
	std::cout << "Keyframes guardados correctamente en el archivo: " << filename << std::endl;
}
//Robot
void SaveKeyFramesRobotToFile(const std::string& filename) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Error al abrir el archivo para guardar los keyframes: " << filename << std::endl;
		return;
	}
	outFile << FrameIndexRobot << std::endl;
	for (int i = 0; i < FrameIndexRobot; ++i) {
		outFile << KeyFrameRobot[i].cabezaRot << " "
			<< KeyFrameRobot[i].brazoDRX << " "
			<< KeyFrameRobot[i].brazoDRY << " "
			<< KeyFrameRobot[i].brazoDRZ << " "
			<< KeyFrameRobot[i].brazoIRX << " "
			<< KeyFrameRobot[i].brazoIRY << " "
			<< KeyFrameRobot[i].brazoIRZ << " "
			<< KeyFrameRobot[i].piernaDRX << " "
			<< KeyFrameRobot[i].piernaDRY << " "
			<< KeyFrameRobot[i].piernaDRZ << " "
			<< KeyFrameRobot[i].piernaIRX << " "
			<< KeyFrameRobot[i].piernaIRY << " "
			<< KeyFrameRobot[i].piernaIRZ << std::endl;
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

	handPosX = KeyFrameHand[0].handPosX;
	handPosY = KeyFrameHand[0].handPosY;
	handPosZ = KeyFrameHand[0].handPosZ;
	handRot = KeyFrameHand[0].handRot;
	handRotZ = KeyFrameHand[0].handRotZ;
	handD1RotZ = KeyFrameHand[0].handD1RotZ;
	handD2RotZ = KeyFrameHand[0].handD2RotZ;
	handD3RotZ = KeyFrameHand[0].handD3RotZ;
	handD4RotZ = KeyFrameHand[0].handD4RotZ;
	handD5RotZ = KeyFrameHand[0].handD5RotZ;

	cabezaRot = KeyFrameRobot[0].cabezaRot;
	brazoDRX = KeyFrameRobot[0].brazoDRX;
	brazoDRY = KeyFrameRobot[0].brazoDRY;
	brazoDRZ = KeyFrameRobot[0].brazoDRZ;
	brazoIRX = KeyFrameRobot[0].brazoIRX;
	brazoIRY = KeyFrameRobot[0].brazoIRY;
	brazoIRZ = KeyFrameRobot[0].brazoIRZ;
	piernaDRX = KeyFrameRobot[0].piernaDRX;
	piernaDRY = KeyFrameRobot[0].piernaDRY;
	piernaDRZ = KeyFrameRobot[0].piernaDRZ;
	piernaIRX = KeyFrameRobot[0].piernaIRX;
	piernaIRY = KeyFrameRobot[0].piernaIRY;
	piernaIRZ = KeyFrameRobot[0].piernaIRZ;


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

	
	

	if (KeyFrameHand[playIndex + 1].handPosX != 0)
	{
		KeyFrameHand[playIndex].handIncX = (KeyFrameHand[playIndex + 1].handPosX - KeyFrameHand[playIndex].handPosX) / i_max_steps;
		KeyFrameHand[playIndex].handIncY = (KeyFrameHand[playIndex + 1].handPosY - KeyFrameHand[playIndex].handPosY) / i_max_steps;
		KeyFrameHand[playIndex].handIncZ = (KeyFrameHand[playIndex + 1].handPosZ - KeyFrameHand[playIndex].handPosZ) / i_max_steps;
		KeyFrameHand[playIndex].handRotInc = (KeyFrameHand[playIndex + 1].handRot - KeyFrameHand[playIndex].handRot) / i_max_steps;
		KeyFrameHand[playIndex].handRotZInc = (KeyFrameHand[playIndex + 1].handRotZ - KeyFrameHand[playIndex].handRotZ) / i_max_steps;
		KeyFrameHand[playIndex].handD1RotZInc = (KeyFrameHand[playIndex + 1].handD1RotZ - KeyFrameHand[playIndex].handD1RotZ) / i_max_steps;
		KeyFrameHand[playIndex].handD2RotZInc = (KeyFrameHand[playIndex + 1].handD2RotZ - KeyFrameHand[playIndex].handD2RotZ) / i_max_steps;
		KeyFrameHand[playIndex].handD3RotZInc = (KeyFrameHand[playIndex + 1].handD3RotZ - KeyFrameHand[playIndex].handD3RotZ) / i_max_steps;
		KeyFrameHand[playIndex].handD4RotZInc = (KeyFrameHand[playIndex + 1].handD4RotZ - KeyFrameHand[playIndex].handD4RotZ) / i_max_steps;
		KeyFrameHand[playIndex].handD5RotZInc = (KeyFrameHand[playIndex + 1].handD5RotZ - KeyFrameHand[playIndex].handD5RotZ) / i_max_steps;
	}
	

	KeyFrameRobot[playIndex].cabezaRotInc = (KeyFrameRobot[playIndex + 1].cabezaRot - KeyFrameRobot[playIndex].cabezaRot) / i_max_steps;
	KeyFrameRobot[playIndex].brazoDRXInc = (KeyFrameRobot[playIndex + 1].brazoDRX - KeyFrameRobot[playIndex].brazoDRX) / i_max_steps;
	KeyFrameRobot[playIndex].brazoDRYInc = (KeyFrameRobot[playIndex + 1].brazoDRY - KeyFrameRobot[playIndex].brazoDRY) / i_max_steps;
	KeyFrameRobot[playIndex].brazoDRZInc = (KeyFrameRobot[playIndex + 1].brazoDRZ - KeyFrameRobot[playIndex].brazoDRZ) / i_max_steps;
	KeyFrameRobot[playIndex].brazoIRXInc = (KeyFrameRobot[playIndex + 1].brazoIRX - KeyFrameRobot[playIndex].brazoIRX) / i_max_steps;
	KeyFrameRobot[playIndex].brazoIRYInc = (KeyFrameRobot[playIndex + 1].brazoIRY - KeyFrameRobot[playIndex].brazoIRY) / i_max_steps;
	KeyFrameRobot[playIndex].brazoIRZInc = (KeyFrameRobot[playIndex + 1].brazoIRZ - KeyFrameRobot[playIndex].brazoIRZ) / i_max_steps;
	KeyFrameRobot[playIndex].piernaDRXInc = (KeyFrameRobot[playIndex + 1].piernaDRX - KeyFrameRobot[playIndex].piernaDRX) / i_max_steps;
	KeyFrameRobot[playIndex].piernaDRYInc = (KeyFrameRobot[playIndex + 1].piernaDRY - KeyFrameRobot[playIndex].piernaDRY) / i_max_steps;
	KeyFrameRobot[playIndex].piernaDRZInc = (KeyFrameRobot[playIndex + 1].piernaDRZ - KeyFrameRobot[playIndex].piernaDRZ) / i_max_steps;
	KeyFrameRobot[playIndex].piernaIRXInc = (KeyFrameRobot[playIndex + 1].piernaIRX - KeyFrameRobot[playIndex].piernaIRX) / i_max_steps;
	KeyFrameRobot[playIndex].piernaIRYInc = (KeyFrameRobot[playIndex + 1].piernaIRY - KeyFrameRobot[playIndex].piernaIRY) / i_max_steps;
	KeyFrameRobot[playIndex].piernaIRZInc = (KeyFrameRobot[playIndex + 1].piernaIRZ - KeyFrameRobot[playIndex].piernaIRZ) / i_max_steps;


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

// Función para actualizar el ensamblado
void UpdateAssembling() {
	if (!assemblingRobot) return;

	assembleProgress += assembleSpeed;

	// Mover cada parte hacia su posición final
	currentBrazoDPos = glm::mix(initialBrazoDPos, finalBrazoDPos, assembleProgress);
	currentBrazoIPos = glm::mix(initialBrazoIPos, finalBrazoIPos, assembleProgress);
	currentPiernaDPos = glm::mix(initialPiernaDPos, finalPiernaDPos, assembleProgress);
	currentPiernaIPos = glm::mix(initialPiernaIPos, finalPiernaIPos, assembleProgress);
	currentTorzoPos = glm::mix(initialTorzoPos, finalTorzoPos, assembleProgress);
	currentCabezaPos = glm::mix(initialCabezaPos, finalCabezaPos, assembleProgress);

	// Cuando llegue al 100%, detener la animación
	if (assembleProgress >= 1.0f) {
		assemblingRobot = false;
		assembleProgress = 1.0f;
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

void LoadKeyFramesHandFromFile(const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cerr << "Error al abrir el archivo para cargar los keyframes: " << filename << std::endl;
		return;
	}
	inFile >> FrameIndexHand;
	for (int i = 0; i < FrameIndexHand; ++i) {
		inFile >> KeyFrameHand[i].handPosX
			>> KeyFrameHand[i].handPosY
			>> KeyFrameHand[i].handPosZ
			>> KeyFrameHand[i].handRot
			>> KeyFrameHand[i].handRotZ
			>> KeyFrameHand[i].handD1RotZ
			>> KeyFrameHand[i].handD2RotZ
			>> KeyFrameHand[i].handD3RotZ
			>> KeyFrameHand[i].handD4RotZ
			>> KeyFrameHand[i].handD5RotZ;
	}
	inFile.close();
	std::cout << "Keyframes cargados correctamente desde el archivo: " << filename << std::endl;
	// Inicializar elementos y preparar la primera interpolaci?n

	if (FrameIndexHand > 1) {
		resetElements();  // Restablece los elementos al primer keyframe
		interpolation();  // Prepara la interpolaci?n para la animaci?n
	}
}

void LoadKeyFramesRobotFromFile(const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cerr << "Error al abrir el archivo para cargar los keyframes: " << filename << std::endl;
		return;
	}
	inFile >> FrameIndexRobot;
	for (int i = 0; i < FrameIndexRobot; ++i) {
		inFile >> KeyFrameRobot[i].cabezaRot
			>> KeyFrameRobot[i].brazoDRX
			>> KeyFrameRobot[i].brazoDRY
			>> KeyFrameRobot[i].brazoDRZ
			>> KeyFrameRobot[i].brazoIRX
			>> KeyFrameRobot[i].brazoIRY
			>> KeyFrameRobot[i].brazoIRZ
			>> KeyFrameRobot[i].piernaDRX
			>> KeyFrameRobot[i].piernaDRY
			>> KeyFrameRobot[i].piernaDRZ
			>> KeyFrameRobot[i].piernaIRX
			>> KeyFrameRobot[i].piernaIRY
			>> KeyFrameRobot[i].piernaIRZ;
			
	}
	inFile.close();
	std::cout << "Keyframes cargados correctamente desde el archivo: " << filename << std::endl;
	// Inicializar elementos y preparar la primera interpolaci?n

	if (FrameIndexRobot > 1) {
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

		KeyFrameDron[i].dronRotInc = 0;

		KeyFrameHand[i].handPosX = 0;
		KeyFrameHand[i].handPosY = 0;
		KeyFrameHand[i].handPosZ = 0;
		KeyFrameHand[i].handIncX = 0;
		KeyFrameHand[i].handIncY = 0;
		KeyFrameHand[i].handIncZ = 0;
		KeyFrameHand[i].handRot = 0;
		KeyFrameHand[i].handRotZ = 0;
		KeyFrameHand[i].handD1RotZ = 0;
		KeyFrameHand[i].handD2RotZ = 0;
		KeyFrameHand[i].handD3RotZ = 0;
		KeyFrameHand[i].handD4RotZ = 0;
		KeyFrameHand[i].handD5RotZ = 0;

		KeyFrameHand[i].handRotInc = 0;
		KeyFrameHand[i].handRotZInc = 0;
		KeyFrameHand[i].handD1RotZInc = 0;
		KeyFrameHand[i].handD2RotZInc = 0;
		KeyFrameHand[i].handD3RotZInc = 0;
		KeyFrameHand[i].handD4RotZInc = 0;
		KeyFrameHand[i].handD5RotZInc = 0;

		KeyFrameRobot[i].cabezaRot = 0;
		KeyFrameRobot[i].brazoDRX = 0;
		KeyFrameRobot[i].brazoDRY = 0;
		KeyFrameRobot[i].brazoDRZ = 0;
		KeyFrameRobot[i].brazoIRX = 0;
		KeyFrameRobot[i].brazoIRY = 0;
		KeyFrameRobot[i].brazoIRZ = 0;
		KeyFrameRobot[i].piernaDRX = 0;
		KeyFrameRobot[i].piernaDRY = 0;
		KeyFrameRobot[i].piernaDRZ = 0;
		KeyFrameRobot[i].piernaIRX = 0;
		KeyFrameRobot[i].piernaIRY = 0;
		KeyFrameRobot[i].piernaIRZ = 0;

		KeyFrameRobot[i].cabezaRotInc = 0;
		KeyFrameRobot[i].brazoDRXInc = 0;
		KeyFrameRobot[i].brazoDRYInc = 0;
		KeyFrameRobot[i].brazoDRZInc = 0;
		KeyFrameRobot[i].brazoIRXInc = 0;
		KeyFrameRobot[i].brazoIRYInc = 0;
		KeyFrameRobot[i].brazoIRZInc = 0;
		KeyFrameRobot[i].piernaDRXInc = 0;
		KeyFrameRobot[i].piernaDRYInc = 0;
		KeyFrameRobot[i].piernaDRZInc = 0;
		KeyFrameRobot[i].piernaIRXInc = 0;
		KeyFrameRobot[i].piernaIRYInc = 0;
		KeyFrameRobot[i].piernaIRZInc = 0;

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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Monroy Salazar y Alfaro Fragoso", nullptr, nullptr);

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

	Model Salon((char*)"Models/salon.obj");
	Model Banca1((char*)"Models/Bancas1.obj");
	Model Banca2((char*)"Models/Bancas2.obj");
	Model BancaOld((char*)"Models/BancasOld.obj");

	Model dron((char*)"Models/DronT2.obj");
	//robot
	Model brazoD((char*)"Models/brazoD.obj");
	Model brazoI((char*)"Models/brazoI.obj");
	Model cabeza((char*)"Models/Cabeza.obj");
	Model piernaD((char*)"Models/piernaD.obj");
	Model piernaI((char*)"Models/piernaI.obj");
	Model torzo((char*)"Models/torzo.obj");

	//Hand
	Model Hand((char*)"Models/Hand/HandRob.obj");
	Model HandD1((char*)"Models/Hand/HandRobD1.obj");
	Model HandD2((char*)"Models/Hand/HandRobD2.obj");
	Model HandD3((char*)"Models/Hand/HandRobD3.obj");
	Model HandD4((char*)"Models/Hand/HandRobD4.obj");
	Model HandD5((char*)"Models/Hand/HandRobD5.obj");

	//KeyFrames
	ResetKeyFrames();

	LoadKeyFramesFromFile("keyframes.dat");
	LoadKeyFramesDronFromFile("keyframesdron.dat");
	LoadKeyFramesHandFromFile("keyframeshand.dat");
	LoadKeyFramesRobotFromFile("keyframesrobot.dat");


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
		/*model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);*/

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


		//Viejas

		// Ejemplo para Banca1M1, ajustar posiciones según tu escena
		glm::mat4 modelDesk = glm::mat4(1.0f);
		// traslada a posición
		modelDesk = glm::translate(modelDesk, glm::vec3(0.0f, -0.5f, 0.0f));
		// rota según progreso (360° completo)
		float totalRot = glm::two_pi<float>() + glm::half_pi<float>(); // 2π + π/2 = 450°
		float angle = deskProgress * totalRot;
		modelDesk = glm::rotate(modelDesk, angle, glm::vec3(0, 1, 0));
		// escala uniformemente de 0 a targetDeskScale
		float scale = glm::mix(1.0f, 0.0f, deskProgress);
		modelDesk = glm::scale(modelDesk, glm::vec3(scale));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelDesk));
		BancaOld.Draw(lightingShader);

		//Nuevas

		if (deskAnimDone)
		{
			//glm::mat4 modelB2M1(1);
			//modelB2M1 = glm::translate(modelB2M1, glm::vec3(-10.0f, -0.5f, -12.8f));
			//modelB2M1 = glm::rotate(modelB2M1, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			////glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB2M1));
			//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			//Banca2.Draw(lightingShader);
			////glDisable(GL_BLEND);  //Desactiva el canal alfa 
			//glBindVertexArray(0);

			float totalRot = glm::two_pi<float>() + glm::half_pi<float>(); // 2π + π/2 = 450°
			float angle = deskProgress2 * totalRot;
			// escala uniformemente de 0 a targetDeskScale
			float scale = glm::mix(0.0f, targetDeskScale, deskProgress2);
			

			// Ejemplo para Banca1M1, ajustar posiciones según tu escena
			glm::mat4 B2M1 = glm::mat4(1.0f);
			
			B2M1 = glm::translate(B2M1, glm::vec3(-10.0f, -0.5f, -12.8f));
			B2M1 = glm::rotate(B2M1, angle, glm::vec3(0, 1, 0));
			B2M1 = glm::scale(B2M1, glm::vec3(scale));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(B2M1));
			Banca2.Draw(lightingShader);


			glm::mat4 modelB2M2 = glm::mat4(1.0f);
			modelB2M2 = glm::translate(modelB2M2, glm::vec3(0.0f, -0.5f, -12.8f));
			//modelB2M2 = glm::rotate(modelB2M2, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			modelB2M2 = glm::rotate(modelB2M2, angle, glm::vec3(0, 1, 0));
			modelB2M2 = glm::scale(modelB2M2, glm::vec3(scale));
			//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB2M2));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			Banca2.Draw(lightingShader);
			//glDisable(GL_BLEND);  //Desactiva el canal alfa 
			glBindVertexArray(0);







			glm::mat4 modelB1M1 = glm::mat4(1.0f);
			modelB1M1 = glm::translate(modelB1M1, glm::vec3(-10.0f, -0.5f, -5.0f));
			modelB1M1 = glm::rotate(modelB1M1, angle, glm::vec3(0, 1, 0));
			modelB1M1 = glm::scale(modelB1M1, glm::vec3(scale));
			//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB1M1));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			Banca1.Draw(lightingShader);
			//glDisable(GL_BLEND);  //Desactiva el canal alfa 
			glBindVertexArray(0);





			glm::mat4 modelB1M2 = glm::mat4(1.0f);
			modelB1M2 = glm::translate(modelB1M2, glm::vec3(0.0f, -0.5f, -5.0f));
			modelB1M2 = glm::rotate(modelB1M2, angle, glm::vec3(0, 1, 0));
			modelB1M2 = glm::scale(modelB1M2, glm::vec3(scale));
			//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB1M2));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			Banca1.Draw(lightingShader);
			//glDisable(GL_BLEND);  //Desactiva el canal alfa 
			glBindVertexArray(0);



			glm::mat4 modelB1M3 = glm::mat4(1.0f);
			modelB1M3 = glm::translate(modelB1M3, glm::vec3(0.0f, -0.5f, 5.0f));
			modelB1M3 = glm::rotate(modelB1M3, angle, glm::vec3(0, 1, 0));
			modelB1M3 = glm::scale(modelB1M3, glm::vec3(scale));
			//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB1M3));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			Banca1.Draw(lightingShader);
			//glDisable(GL_BLEND);  //Desactiva el canal alfa 
			glBindVertexArray(0);

			glm::mat4 modelB1M4 = glm::mat4(1.0f);
			modelB1M4 = glm::translate(modelB1M4, glm::vec3(-10.0f, -0.5f, 5.0f));
			modelB1M4 = glm::rotate(modelB1M4, angle, glm::vec3(0, 1, 0));
			modelB1M4 = glm::scale(modelB1M4, glm::vec3(scale));
			//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB1M4));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			Banca1.Draw(lightingShader);
			//glDisable(GL_BLEND);  //Desactiva el canal alfa 
			glBindVertexArray(0);


			glm::mat4 modelB2M3 = glm::mat4(1.0f);
			modelB2M3 = glm::translate(modelB2M3, glm::vec3(-10.0f, -0.5f, 15.0f));
			modelB2M3 = glm::rotate(modelB2M3, angle, glm::vec3(0, 1, 0));
			modelB2M3 = glm::scale(modelB2M3, glm::vec3(scale));
			//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB2M3));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			Banca2.Draw(lightingShader);
			//glDisable(GL_BLEND);  //Desactiva el canal alfa 
			glBindVertexArray(0);

			glm::mat4 modelB2M4 = glm::mat4(1.0f);
			modelB2M4 = glm::translate(modelB2M4, glm::vec3(0.0f, -0.5f, 15.0f));
			modelB2M4 = glm::rotate(modelB2M4, angle, glm::vec3(0, 1, 0));
			modelB2M4 = glm::scale(modelB2M4, glm::vec3(scale));
			//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelB2M4));
			glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
			Banca2.Draw(lightingShader);
			//glDisable(GL_BLEND);  //Desactiva el canal alfa 
			glBindVertexArray(0);


			
		}

		if (deskAnim2Done)
		{
			//Hand
			glm::mat4 modelH(1);
			modelH = glm::mat4(1);
			modelH = glm::scale(modelH, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH = glm::translate(modelH, glm::vec3(handPosX, handPosY, handPosZ));
			modelH = glm::rotate(modelH, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH = glm::rotate(modelH, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH));
			Hand.Draw(lightingShader);
			glBindVertexArray(0);

			//D1
			modelH = glm::mat4(1);
			modelH = glm::scale(modelH, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH = glm::translate(modelH, glm::vec3(handPosX, handPosY, handPosZ));
			modelH = glm::rotate(modelH, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH = glm::rotate(modelH, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH = glm::rotate(modelH, glm::radians(handD1RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH));
			HandD1.Draw(lightingShader);
			glBindVertexArray(0);

			//D2
			modelH = glm::mat4(1);
			modelH = glm::scale(modelH, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH = glm::translate(modelH, glm::vec3(handPosX, handPosY, handPosZ));
			modelH = glm::rotate(modelH, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH = glm::rotate(modelH, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH = glm::rotate(modelH, glm::radians(handD2RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH));
			HandD2.Draw(lightingShader);
			glBindVertexArray(0);

			//D3
			modelH = glm::mat4(1);
			modelH = glm::scale(modelH, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH = glm::translate(modelH, glm::vec3(handPosX, handPosY, handPosZ));
			modelH = glm::rotate(modelH, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH = glm::rotate(modelH, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH = glm::rotate(modelH, glm::radians(handD3RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH));
			HandD3.Draw(lightingShader);
			glBindVertexArray(0);

			//D4
			modelH = glm::mat4(1);
			modelH = glm::scale(modelH, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH = glm::translate(modelH, glm::vec3(handPosX, handPosY, handPosZ));
			modelH = glm::rotate(modelH, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH = glm::rotate(modelH, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH = glm::rotate(modelH, glm::radians(handD4RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH));
			HandD4.Draw(lightingShader);
			glBindVertexArray(0);


			//D5
			modelH = glm::mat4(1);
			modelH = glm::scale(modelH, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH = glm::translate(modelH, glm::vec3(handPosX, handPosY, handPosZ));
			modelH = glm::rotate(modelH, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH = glm::rotate(modelH, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH = glm::rotate(modelH, glm::radians(handD5RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH));
			HandD5.Draw(lightingShader);
			glBindVertexArray(0);



			//Hand2
			glm::mat4 modelH2(1);

			modelH2 = glm::mat4(1);
			modelH2 = glm::scale(modelH2, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH2 = glm::translate(modelH2, glm::vec3(handPosX - 20, handPosY, handPosZ));
			modelH2 = glm::rotate(modelH2, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH2));
			Hand.Draw(lightingShader);
			glBindVertexArray(0);

			//D1
			modelH2 = glm::mat4(1);
			modelH2 = glm::scale(modelH2, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH2 = glm::translate(modelH2, glm::vec3(handPosX - 20, handPosY, handPosZ));
			modelH2 = glm::rotate(modelH2, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handD1RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH2));
			HandD1.Draw(lightingShader);
			glBindVertexArray(0);

			//D2
			modelH2 = glm::mat4(1);
			modelH2 = glm::scale(modelH2, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH2 = glm::translate(modelH2, glm::vec3(handPosX - 20, handPosY, handPosZ));
			modelH2 = glm::rotate(modelH2, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handD2RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH2));
			HandD2.Draw(lightingShader);
			glBindVertexArray(0);

			//D3
			modelH2 = glm::mat4(1);
			modelH2 = glm::scale(modelH2, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH2 = glm::translate(modelH2, glm::vec3(handPosX - 20, handPosY, handPosZ));
			modelH2 = glm::rotate(modelH2, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handD3RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH2));
			HandD3.Draw(lightingShader);
			glBindVertexArray(0);

			//D4
			modelH2 = glm::mat4(1);
			modelH2 = glm::scale(modelH2, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH2 = glm::translate(modelH2, glm::vec3(handPosX - 20, handPosY, handPosZ));
			modelH2 = glm::rotate(modelH2, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handD4RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH2));
			HandD4.Draw(lightingShader);
			glBindVertexArray(0);


			//D5
			modelH2 = glm::mat4(1);
			modelH2 = glm::scale(modelH2, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH2 = glm::translate(modelH2, glm::vec3(handPosX - 20, handPosY, handPosZ));
			modelH2 = glm::rotate(modelH2, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH2 = glm::rotate(modelH2, glm::radians(handD5RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH2));
			HandD5.Draw(lightingShader);
			glBindVertexArray(0);


			//Hand3
			glm::mat4 modelH3(1);

			modelH3 = glm::mat4(1);
			modelH3 = glm::scale(modelH3, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH3 = glm::translate(modelH3, glm::vec3(handPosX - 50, handPosY, handPosZ));
			modelH3 = glm::rotate(modelH3, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH3));
			Hand.Draw(lightingShader);
			glBindVertexArray(0);

			//D1
			modelH3 = glm::mat4(1);
			modelH3 = glm::scale(modelH3, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH3 = glm::translate(modelH3, glm::vec3(handPosX - 50, handPosY, handPosZ));
			modelH3 = glm::rotate(modelH3, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handD1RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH3));
			HandD1.Draw(lightingShader);
			glBindVertexArray(0);

			//D2
			modelH3 = glm::mat4(1);
			modelH3 = glm::scale(modelH3, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH3 = glm::translate(modelH3, glm::vec3(handPosX - 50, handPosY, handPosZ));
			modelH3 = glm::rotate(modelH3, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handD2RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH3));
			HandD2.Draw(lightingShader);
			glBindVertexArray(0);

			//D3
			modelH3 = glm::mat4(1);
			modelH3 = glm::scale(modelH3, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH3 = glm::translate(modelH3, glm::vec3(handPosX - 50, handPosY, handPosZ));
			modelH3 = glm::rotate(modelH3, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handD3RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH3));
			HandD3.Draw(lightingShader);
			glBindVertexArray(0);

			//D4
			modelH3 = glm::mat4(1);
			modelH3 = glm::scale(modelH3, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH3 = glm::translate(modelH3, glm::vec3(handPosX - 50, handPosY, handPosZ));
			modelH3 = glm::rotate(modelH3, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handD4RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH3));
			HandD4.Draw(lightingShader);
			glBindVertexArray(0);


			//D5
			modelH3 = glm::mat4(1);
			modelH3 = glm::scale(modelH3, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH3 = glm::translate(modelH3, glm::vec3(handPosX - 50, handPosY, handPosZ));
			modelH3 = glm::rotate(modelH3, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH3 = glm::rotate(modelH3, glm::radians(handD5RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH3));
			HandD5.Draw(lightingShader);
			glBindVertexArray(0);


			//Hand4
			glm::mat4 modelH4(1);

			modelH4 = glm::mat4(1);
			modelH4 = glm::scale(modelH4, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH4 = glm::translate(modelH4, glm::vec3(handPosX - 70, handPosY, handPosZ));
			modelH4 = glm::rotate(modelH4, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH4));
			Hand.Draw(lightingShader);
			glBindVertexArray(0);

			//D1
			modelH4 = glm::mat4(1);
			modelH4 = glm::scale(modelH4, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH4 = glm::translate(modelH4, glm::vec3(handPosX - 70, handPosY, handPosZ));
			modelH4 = glm::rotate(modelH4, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handD1RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH4));
			HandD1.Draw(lightingShader);
			glBindVertexArray(0);

			//D2
			modelH4 = glm::mat4(1);
			modelH4 = glm::scale(modelH4, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH4 = glm::translate(modelH4, glm::vec3(handPosX - 70, handPosY, handPosZ));
			modelH4 = glm::rotate(modelH4, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handD2RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH4));
			HandD2.Draw(lightingShader);
			glBindVertexArray(0);

			//D3
			modelH4 = glm::mat4(1);
			modelH4 = glm::scale(modelH4, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH4 = glm::translate(modelH4, glm::vec3(handPosX - 70, handPosY, handPosZ));
			modelH4 = glm::rotate(modelH4, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handD3RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH4));
			HandD3.Draw(lightingShader);
			glBindVertexArray(0);

			//D4
			modelH4 = glm::mat4(1);
			modelH4 = glm::scale(modelH4, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH4 = glm::translate(modelH4, glm::vec3(handPosX - 70, handPosY, handPosZ));
			modelH4 = glm::rotate(modelH4, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handD4RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH4));
			HandD4.Draw(lightingShader);
			glBindVertexArray(0);


			//D5
			modelH4 = glm::mat4(1);
			modelH4 = glm::scale(modelH4, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH4 = glm::translate(modelH4, glm::vec3(handPosX - 70, handPosY, handPosZ));
			modelH4 = glm::rotate(modelH4, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH4 = glm::rotate(modelH4, glm::radians(handD5RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH4));
			HandD5.Draw(lightingShader);
			glBindVertexArray(0);


			//Hand5
			glm::mat4 modelH5(1);

			modelH5 = glm::mat4(1);
			modelH5 = glm::scale(modelH5, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH5 = glm::translate(modelH5, glm::vec3(handPosX, handPosY, handPosZ + 50));
			modelH5 = glm::rotate(modelH5, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH5));
			Hand.Draw(lightingShader);
			glBindVertexArray(0);

			//D1
			modelH5 = glm::mat4(1);
			modelH5 = glm::scale(modelH5, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH5 = glm::translate(modelH5, glm::vec3(handPosX, handPosY, handPosZ + 50));
			modelH5 = glm::rotate(modelH5, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handD1RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH5));
			HandD1.Draw(lightingShader);
			glBindVertexArray(0);

			//D2
			modelH5 = glm::mat4(1);
			modelH5 = glm::scale(modelH5, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH5 = glm::translate(modelH5, glm::vec3(handPosX, handPosY, handPosZ + 50));
			modelH5 = glm::rotate(modelH5, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handD2RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH5));
			HandD2.Draw(lightingShader);
			glBindVertexArray(0);

			//D3
			modelH5 = glm::mat4(1);
			modelH5 = glm::scale(modelH5, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH5 = glm::translate(modelH5, glm::vec3(handPosX, handPosY, handPosZ + 50));
			modelH5 = glm::rotate(modelH5, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handD3RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH5));
			HandD3.Draw(lightingShader);
			glBindVertexArray(0);

			//D4
			modelH5 = glm::mat4(1);
			modelH5 = glm::scale(modelH5, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH5 = glm::translate(modelH5, glm::vec3(handPosX, handPosY, handPosZ + 50));
			modelH5 = glm::rotate(modelH5, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handD4RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH5));
			HandD4.Draw(lightingShader);
			glBindVertexArray(0);


			//D5
			modelH5 = glm::mat4(1);
			modelH5 = glm::scale(modelH5, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH5 = glm::translate(modelH5, glm::vec3(handPosX, handPosY, handPosZ + 50));
			modelH5 = glm::rotate(modelH5, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH5 = glm::rotate(modelH5, glm::radians(handD5RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH5));
			HandD5.Draw(lightingShader);
			glBindVertexArray(0);



			//Hand6
			glm::mat4 modelH6(1);

			modelH6 = glm::mat4(1);
			modelH6 = glm::scale(modelH6, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH6 = glm::translate(modelH6, glm::vec3(handPosX - 20, handPosY, handPosZ + 50));
			modelH6 = glm::rotate(modelH6, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH6));
			Hand.Draw(lightingShader);
			glBindVertexArray(0);

			//D1
			modelH6 = glm::mat4(1);
			modelH6 = glm::scale(modelH6, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH6 = glm::translate(modelH6, glm::vec3(handPosX - 20, handPosY, handPosZ + 50));
			modelH6 = glm::rotate(modelH6, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handD1RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH6));
			HandD1.Draw(lightingShader);
			glBindVertexArray(0);

			//D2
			modelH6 = glm::mat4(1);
			modelH6 = glm::scale(modelH6, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH6 = glm::translate(modelH6, glm::vec3(handPosX - 20, handPosY, handPosZ + 50));
			modelH6 = glm::rotate(modelH6, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handD2RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH6));
			HandD2.Draw(lightingShader);
			glBindVertexArray(0);

			//D3
			modelH6 = glm::mat4(1);
			modelH6 = glm::scale(modelH6, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH6 = glm::translate(modelH6, glm::vec3(handPosX - 20, handPosY, handPosZ + 50));
			modelH6 = glm::rotate(modelH6, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handD3RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH6));
			HandD3.Draw(lightingShader);
			glBindVertexArray(0);

			//D4
			modelH6 = glm::mat4(1);
			modelH6 = glm::scale(modelH6, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH6 = glm::translate(modelH6, glm::vec3(handPosX - 20, handPosY, handPosZ + 50));
			modelH6 = glm::rotate(modelH6, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handD4RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH6));
			HandD4.Draw(lightingShader);
			glBindVertexArray(0);


			//D5
			modelH6 = glm::mat4(1);
			modelH6 = glm::scale(modelH6, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH6 = glm::translate(modelH6, glm::vec3(handPosX - 20, handPosY, handPosZ + 50));
			modelH6 = glm::rotate(modelH6, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH6 = glm::rotate(modelH6, glm::radians(handD5RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH6));
			HandD5.Draw(lightingShader);
			glBindVertexArray(0);


			//Hand7
			glm::mat4 modelH7(1);

			modelH7 = glm::mat4(1);
			modelH7 = glm::scale(modelH7, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH7 = glm::translate(modelH7, glm::vec3(handPosX - 50, handPosY, handPosZ + 50));
			modelH7 = glm::rotate(modelH7, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH7));
			Hand.Draw(lightingShader);
			glBindVertexArray(0);

			//D1
			modelH7 = glm::mat4(1);
			modelH7 = glm::scale(modelH7, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH7 = glm::translate(modelH7, glm::vec3(handPosX - 50, handPosY, handPosZ + 50));
			modelH7 = glm::rotate(modelH7, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handD1RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH7));
			HandD1.Draw(lightingShader);
			glBindVertexArray(0);

			//D2
			modelH7 = glm::mat4(1);
			modelH7 = glm::scale(modelH7, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH7 = glm::translate(modelH7, glm::vec3(handPosX - 50, handPosY, handPosZ + 50));
			modelH7 = glm::rotate(modelH7, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handD2RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH7));
			HandD2.Draw(lightingShader);
			glBindVertexArray(0);

			//D3
			modelH7 = glm::mat4(1);
			modelH7 = glm::scale(modelH7, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH7 = glm::translate(modelH7, glm::vec3(handPosX - 50, handPosY, handPosZ + 50));
			modelH7 = glm::rotate(modelH7, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handD3RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH7));
			HandD3.Draw(lightingShader);
			glBindVertexArray(0);

			//D4
			modelH7 = glm::mat4(1);
			modelH7 = glm::scale(modelH7, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH7 = glm::translate(modelH7, glm::vec3(handPosX - 50, handPosY, handPosZ + 50));
			modelH7 = glm::rotate(modelH7, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handD4RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH7));
			HandD4.Draw(lightingShader);
			glBindVertexArray(0);


			//D5
			modelH7 = glm::mat4(1);
			modelH7 = glm::scale(modelH7, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH7 = glm::translate(modelH7, glm::vec3(handPosX - 50, handPosY, handPosZ + 50));
			modelH7 = glm::rotate(modelH7, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH7 = glm::rotate(modelH7, glm::radians(handD5RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH7));
			HandD5.Draw(lightingShader);
			glBindVertexArray(0);


			//Hand8
			glm::mat4 modelH8(1);

			modelH8 = glm::mat4(1);
			modelH8 = glm::scale(modelH8, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH8 = glm::translate(modelH8, glm::vec3(handPosX - 70, handPosY, handPosZ + 50));
			modelH8 = glm::rotate(modelH8, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH8));
			Hand.Draw(lightingShader);
			glBindVertexArray(0);

			//D1
			modelH8 = glm::mat4(1);
			modelH8 = glm::scale(modelH8, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH8 = glm::translate(modelH8, glm::vec3(handPosX - 70, handPosY, handPosZ + 50));
			modelH8 = glm::rotate(modelH8, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handD1RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH8));
			HandD1.Draw(lightingShader);
			glBindVertexArray(0);

			//D2
			modelH8 = glm::mat4(1);
			modelH8 = glm::scale(modelH8, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH8 = glm::translate(modelH8, glm::vec3(handPosX - 70, handPosY, handPosZ + 50));
			modelH8 = glm::rotate(modelH8, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handD2RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH8));
			HandD2.Draw(lightingShader);
			glBindVertexArray(0);

			//D3
			modelH8 = glm::mat4(1);
			modelH8 = glm::scale(modelH8, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH8 = glm::translate(modelH8, glm::vec3(handPosX - 70, handPosY, handPosZ + 50));
			modelH8 = glm::rotate(modelH8, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handD3RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH8));
			HandD3.Draw(lightingShader);
			glBindVertexArray(0);

			//D4
			modelH8 = glm::mat4(1);
			modelH8 = glm::scale(modelH8, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH8 = glm::translate(modelH8, glm::vec3(handPosX - 70, handPosY, handPosZ + 50));
			modelH8 = glm::rotate(modelH8, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handD4RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH8));
			HandD4.Draw(lightingShader);
			glBindVertexArray(0);


			//D5
			modelH8 = glm::mat4(1);
			modelH8 = glm::scale(modelH8, glm::vec3(0.2f, 0.2f, 0.2f));
			modelH8 = glm::translate(modelH8, glm::vec3(handPosX - 70, handPosY, handPosZ + 50));
			modelH8 = glm::rotate(modelH8, glm::radians(handRot), glm::vec3(0.0f, 1.0f, 0.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handRotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			modelH8 = glm::rotate(modelH8, glm::radians(handD5RotZ), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelH8));
			HandD5.Draw(lightingShader);
			glBindVertexArray(0);
		}

		

		//Robot 

	// Brazo derecho 
		glm::mat4 modelBD(1);
		modelBD = glm::translate(modelBD, currentBrazoDPos);
		modelBD = glm::rotate(modelBD, glm::radians(brazoDRX), glm::vec3(1.0f, 0.0f, 0.0f));
		modelBD = glm::rotate(modelBD, glm::radians(brazoDRY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelBD = glm::rotate(modelBD, glm::radians(brazoDRZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBD));
		brazoD.Draw(lightingShader);
		glBindVertexArray(0);

		// Brazo Izquierdo 
		glm::mat4 modelBI(1);
		modelBI = glm::translate(modelBI, currentBrazoIPos);
		modelBI = glm::rotate(modelBI, glm::radians(brazoIRX), glm::vec3(1.0f, 0.0f, 0.0f));
		modelBI = glm::rotate(modelBI, glm::radians(brazoIRY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelBI = glm::rotate(modelBI, glm::radians(brazoIRZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBI));
		brazoI.Draw(lightingShader);
		glBindVertexArray(0);

		// Cabeza
		glm::mat4 modelC(1);
		modelC = glm::translate(modelC, currentCabezaPos);
		modelC = glm::rotate(modelC, glm::radians(cabezaRot), glm::vec3(0.0f, 1.0f, 0.0f));
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelC));
		cabeza.Draw(lightingShader);
		glBindVertexArray(0);

		// PiernaD 
		glm::mat4 modelPD(1);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		modelPD = glm::translate(modelPD, currentPiernaDPos);
		modelPD = glm::rotate(modelPD, glm::radians(piernaDRX), glm::vec3(1.0f, 0.0f, 0.0f));
		modelPD = glm::rotate(modelPD, glm::radians(piernaDRY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelPD = glm::rotate(modelPD, glm::radians(piernaDRZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPD));
		piernaD.Draw(lightingShader);
		glBindVertexArray(0);

		// Pierna izquierda 
		glm::mat4 modelPI(1);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		modelPI = glm::translate(modelPI, currentPiernaIPos);
		modelPI = glm::rotate(modelPI, glm::radians(piernaIRX), glm::vec3(1.0f, 0.0f, 0.0f));
		modelPI = glm::rotate(modelPI, glm::radians(piernaIRY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelPI = glm::rotate(modelPI, glm::radians(piernaIRZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPI));
		piernaI.Draw(lightingShader);
		glBindVertexArray(0);

		// Torzo
		glm::mat4 modelT(1);
		modelT = glm::translate(modelT, currentTorzoPos);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelT));
		torzo.Draw(lightingShader);
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
	UpdateAssembling();
	//Dog Controls

	/*if (keys[GLFW_KEY_4])
	{

		head += 1.0f;

	}

	if (keys[GLFW_KEY_5])
	{

		head -= 1.0f;

	}*/

	//if (keys[GLFW_KEY_1])
	//{
	//	//rotDog += 1.0f;
	//	handD1RotZ += 1.0f;

	//}

	//if (keys[GLFW_KEY_2])
	//{

	//	
	//	//rotDog += 1.0f;

	//	handD1RotZ -= 1.0f;


	//}

	//if (keys[GLFW_KEY_3])
	//{
	//	//rotDog += 1.0f;
	//	handD2RotZ += 1.0f;
	//}

	//if (keys[GLFW_KEY_4])
	//{
	//	//rotDog += 1.0f;
	//	handD2RotZ -= 1.0f;
	//}

	//if (keys[GLFW_KEY_5])
	//{
	//	//rotDog += 1.0f;
	//	handD3RotZ += 1.0f;
	//}

	//if (keys[GLFW_KEY_6])
	//{
	//	//rotDog += 1.0f;
	//	handD3RotZ -= 1.0f;
	//}

	//if (keys[GLFW_KEY_7])
	//{
	//	//rotDog += 1.0f;
	//	handD4RotZ += 1.0f;
	//}

	//if (keys[GLFW_KEY_8])
	//{
	//	//rotDog += 1.0f;
	//	handD4RotZ -= 1.0f;
	//}

	//if (keys[GLFW_KEY_9])
	//{
	//	//rotDog += 1.0f;
	//	handD5RotZ += 1.0f;
	//}

	//if (keys[GLFW_KEY_0])
	//{
	//	//rotDog += 1.0f;
	////	handD5RotZ -= 1.0f;
	////}

	//if (keys[GLFW_KEY_V])
	//{

	//	//rotDog -= 1.0f;
	//	handRotZ += 1.0f;

	//}

	//if (keys[GLFW_KEY_B])
	//{

	//	//rotDog -= 1.0f;
	//	handRotZ -= 1.0f;

	//}

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

	//if (keys[GLFW_KEY_G])
	//{
	//	//dronPosX -= 0.03;
	//	handPosX -= 0.03f;
	//}

	//if (keys[GLFW_KEY_J])
	//{
	//	//dronPosX += 0.03;
	//	handPosX += 0.03f;
	//}

	//if (keys[GLFW_KEY_H])
	//{
	//	//dronPosZ += 0.03;
	//	handPosZ += 0.03f;
	//}

	//if (keys[GLFW_KEY_Y])
	//{
	//	
	//	//dronPosZ -= 0.03;
	//	handPosZ -= 0.03f;
	//}

	//if (keys[GLFW_KEY_UP])
	//{
	//	//dronPosY += 0.03;
	//	handPosY += 0.03f;
	//}

	//if (keys[GLFW_KEY_DOWN])
	//{
	//	//dronPosY -= 0.03;
	//	handPosY -= 0.03f;
	//}

	//if (keys[GLFW_KEY_LEFT])
	//{
	//	//dronRot += 1.0f;
	//	handRot += 1.0f;
	//}

	//if (keys[GLFW_KEY_RIGHT])
	//{
	//	//dronRot -= 1.0f;
	//	handRot -= 1.0f;
	//}
	//Robot 

	//if (keys[GLFW_KEY_0])
	//{
	//	//cabeza;
	//	cabezaRot += 0.3f;
	//}
	//if (keys[GLFW_KEY_1])
	//{
	//	//cabeza;
	//	cabezaRot -= 0.3f;
	//}
	//if (keys[GLFW_KEY_2])
	//{
	//	//brazos;
	//	 brazoDRX+= 0.3f;
	//}
	//if (keys[GLFW_KEY_3])
	//{
	//	//brazos;
	//	brazoDRX -= 0.3f;

	//}
	//if (keys[GLFW_KEY_4])
	//{
	//	//brazos;
	//	brazoDRY += 0.3f;
	//}
	//if (keys[GLFW_KEY_5])
	//{
	//	//brazos;
	//	brazoDRY -= 0.3f;

	//}
	//if (keys[GLFW_KEY_6])
	//{
	//	//brazo;
	//	brazoDRZ += 0.3f;
	//	
	//}
	//if (keys[GLFW_KEY_7])
	//{
	//	//Píerna;
	//	brazoDRZ -= 0.3f;
	//}
	//if (keys[GLFW_KEY_8])
	//{
	//	//brazos;
	//	brazoIRX += 0.3f;
	//}
	//if (keys[GLFW_KEY_9])
	//{
	//	//brazos;
	//	brazoIRX -= 0.3f;

	//}
	//if (keys[GLFW_KEY_E])
	//{
	//	//brazos;
	//	brazoIRY += 0.3f;
	//}
	//if (keys[GLFW_KEY_R])
	//{
	//	//brazos;
	//	brazoIRY -= 0.3f;

	//}
	//if (keys[GLFW_KEY_T])
	//{
	//	//brazo;
	//	brazoIRZ += 0.3f;

	//}
	//if (keys[GLFW_KEY_Y])
	//{
	//	//Píerna;
	//	brazoIRZ -= 0.3f;
	//}
	//if (keys[GLFW_KEY_U])
	//{
	//	//brazos;
	//	piernaIRX += 0.3f;
	//}
	//if (keys[GLFW_KEY_I])
	//{
	//	//brazos;
	//	piernaIRX -= 0.3f;

	//}
	//if (keys[GLFW_KEY_O])
	//{
	//	//brazos;
	//	piernaIRY += 0.3f;
	//}
	//if (keys[GLFW_KEY_F])
	//{
	//	//brazos;
	//	piernaIRY -= 0.3f;

	//}
	//if (keys[GLFW_KEY_G])
	//{
	//	//brazo;
	//	piernaIRZ += 0.3f;

	//}
	//if (keys[GLFW_KEY_H])
	//{
	////Píerna;
	//	piernaIRZ -= 0.3f;
	//}
	//if (keys[GLFW_KEY_J])
	//{
	//	//brazos;
	//	piernaDRX += 0.3f;
	//}
	//if (keys[GLFW_KEY_K])
	//{
	//	//brazos;
	//	piernaDRX -= 0.3f;

	//}
	//if (keys[GLFW_KEY_Z])
	//{
	//	//brazos;
	//	piernaDRY += 0.3f;
	//}
	//if (keys[GLFW_KEY_X])
	//{
	//	//brazos;
	//	piernaDRY -= 0.3f;

	//}
	//if (keys[GLFW_KEY_C])
	//{
	//	//brazo;
	//	piernaDRZ += 0.3f;

	//}
	//if (keys[GLFW_KEY_V])
	//{
	//	//Píerna;
	//	piernaDRZ -= 0.3f;
	//}

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
		if (play == false && (FrameIndex > 1) && (FrameIndexDron > 1) && (FrameIndexHand > 1) && (FrameIndexRobot > 1))
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
		//saveFrame();
		//SaveKeyFramesToFile("keyframes.dat");

		//Hand
		saveFrameHand();
		SaveKeyFramesHandToFile("keyframeshand.dat");
	}
	//Robot 
	if (keys[GLFW_KEY_P])
	{
		//Dog
		//saveFrame();
		//SaveKeyFramesToFile("keyframes.dat");

		//Hand
		saveFrameRobot();
		SaveKeyFramesRobotToFile("keyframesrobot.dat");
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

	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		if (!assemblingRobot) {
			assemblingRobot = true;
			assembleProgress = 0.0f;
			// Resetear posiciones a las iniciales
			currentBrazoDPos = initialBrazoDPos;
			currentBrazoIPos = initialBrazoIPos;
			currentPiernaDPos = initialPiernaDPos;
			currentPiernaIPos = initialPiernaIPos;
			currentTorzoPos = initialTorzoPos;
			currentCabezaPos = initialCabezaPos;
		}
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
			if (playIndex > FrameIndex - 2 && playIndex > FrameIndexDron - 2 && playIndex > FrameIndexHand - 2 && playIndex > FrameIndexRobot - 2)	//end of total animation?
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


			
			handPosX += KeyFrameHand[playIndex].handIncX;
			
			handPosY += KeyFrameHand[playIndex].handIncY;
			handPosZ += KeyFrameHand[playIndex].handIncZ;
			handRot += KeyFrameHand[playIndex].handRotInc;
			handRotZ += KeyFrameHand[playIndex].handRotZInc;
			handD1RotZ += KeyFrameHand[playIndex].handD1RotZInc;
			handD2RotZ += KeyFrameHand[playIndex].handD2RotZInc;
			handD3RotZ += KeyFrameHand[playIndex].handD3RotZInc;
			handD4RotZ += KeyFrameHand[playIndex].handD4RotZInc;
			handD5RotZ += KeyFrameHand[playIndex].handD5RotZInc;

			brazoDRX += KeyFrameRobot[playIndex].brazoDRXInc;
			brazoDRY += KeyFrameRobot[playIndex].brazoDRYInc;
			brazoDRZ += KeyFrameRobot[playIndex].brazoDRZInc;
			brazoIRX += KeyFrameRobot[playIndex].brazoIRXInc;
			brazoIRY += KeyFrameRobot[playIndex].brazoIRYInc;
			brazoIRZ += KeyFrameRobot[playIndex].brazoIRZInc;
			cabezaRot += KeyFrameRobot[playIndex].cabezaRotInc;
			piernaDRX += KeyFrameRobot[playIndex].piernaDRXInc;
			piernaDRY += KeyFrameRobot[playIndex].piernaDRYInc;
			piernaDRZ += KeyFrameRobot[playIndex].piernaDRZInc;
			piernaIRX += KeyFrameRobot[playIndex].piernaIRXInc;
			piernaIRY += KeyFrameRobot[playIndex].piernaIRYInc;
			piernaIRZ += KeyFrameRobot[playIndex].piernaIRZInc;


			i_curr_steps++;
		}

		// Avanza el tiempo de la animación de escritorio
		deskAnimTime = std::min(deskAnimTime + deltaTime, deskAnimDuration);
		deskProgress = deskAnimTime / deskAnimDuration;

		if (deskProgress >= 1.0f) {
			deskAnimDone = true;
			deskProgress = 1.0f;
		}

		if (deskAnimDone) {

			// Avanza el tiempo de la animación de escritorio
			deskAnim2Time = std::min(deskAnim2Time + deltaTime, deskAnim2Duration);
			deskProgress2 = deskAnim2Time / deskAnim2Duration;

			if (deskProgress2 >= 1.0f) {
				deskAnim2Done = true;
				deskProgress2 = 1.0f;
			}
			
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