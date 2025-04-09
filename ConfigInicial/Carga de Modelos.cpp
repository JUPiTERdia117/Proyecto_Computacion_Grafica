
//Practica#6 (Carga de modelos) Monroy Salazar
//Fecha de entrega 16 de Marzo de 2025
//315118894



// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Practica 6 Monroy Salazar", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models
    Model dog((char*)"Models/RedDog.obj");
    Model chair((char*)"Models/Chair/kursi.obj");
    Model tablec((char*)"Models/Table/Chair_and_Table_School.obj");
    Model room((char*)"Models/Room/Room.obj");
    Model board((char*)"Models/Piza/pizar.obj");
    /*Model classroom((char*)"Models/Classroom/Classroom.obj");*/

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );


    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));




        //Cuarto
        glm::mat4 modelR(1);
        modelR = glm::translate(modelR, glm::vec3(0.0f, -0.45f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelR));
        room.Draw(shader);


        //Silla
        glm::mat4 modelChair(1);
        modelChair = glm::translate(modelChair, glm::vec3(0.0f, -0.5f, 0.0f));
        modelChair = glm::scale(modelChair, glm::vec3(0.4f, 0.4f, 0.4f));
        modelChair = glm::rotate(modelChair, -55.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelChair));
        chair.Draw(shader);

        //Silla2
        glm::mat4 modelChair2(1);
        modelChair2 = glm::translate(modelChair2, glm::vec3(-1.0f, -0.5f, 0.0f));
        modelChair2 = glm::scale(modelChair2, glm::vec3(0.4f, 0.4f, 0.4f));
        modelChair2 = glm::rotate(modelChair2, -55.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelChair2));
        chair.Draw(shader);

        //Silla3
        glm::mat4 modelChair3(1);
        modelChair3 = glm::translate(modelChair3, glm::vec3(1.0f, -0.5f, 0.0f));
        modelChair3 = glm::scale(modelChair3, glm::vec3(0.4f, 0.4f, 0.4f));
        modelChair3 = glm::rotate(modelChair3, -55.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelChair3));
        chair.Draw(shader);

        //Silla4
        glm::mat4 modelChair4(1);
        modelChair4 = glm::translate(modelChair4, glm::vec3(0.0f, -0.5f, 1.0f));
        modelChair4 = glm::scale(modelChair4, glm::vec3(0.4f, 0.4f, 0.4f));
        modelChair4 = glm::rotate(modelChair4, -55.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelChair4));
        chair.Draw(shader);

        //Silla5
        glm::mat4 modelChair5(1);
        modelChair5 = glm::translate(modelChair5, glm::vec3(-1.0f, -0.5f, 1.0f));
        modelChair5 = glm::scale(modelChair5, glm::vec3(0.4f, 0.4f, 0.4f));
        modelChair5 = glm::rotate(modelChair5, -55.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelChair5));
        chair.Draw(shader);

        //Silla3
        glm::mat4 modelChair6(1);
        modelChair6 = glm::translate(modelChair6, glm::vec3(1.0f, -0.5f, 1.0f));
        modelChair6 = glm::scale(modelChair6, glm::vec3(0.4f, 0.4f, 0.4f));
        modelChair6 = glm::rotate(modelChair6, -55.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelChair6));
        chair.Draw(shader);


        //Pizarron
        glm::mat4 modelBoard(1);
        modelBoard = glm::translate(modelBoard, glm::vec3(0.0f, 0.0f, -3.0f));
        modelBoard = glm::scale(modelBoard, glm::vec3(0.01f, 0.01f, 0.01f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelBoard));
        board.Draw(shader);



        //Mesa
        glm::mat4 modelTable(1);
        modelTable = glm::translate(modelTable, glm::vec3(-2.3f, -0.5f, -2.0f));
        modelTable = glm::rotate(modelTable, 135.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        modelTable = glm::scale(modelTable, glm::vec3(0.7f, 0.7f, 0.7f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelTable));
        tablec.Draw(shader);


        // Draw the loaded model dogo
        glm::mat4 mDog(1);
        mDog = glm::translate(mDog, glm::vec3(-2.2f, 0.58f, -1.5f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(mDog));
        dog.Draw(shader);


        







        
        

       
        

        /*glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        classroom.Draw(shader);*/



       /* model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));

        model = glm::rotate(model, 135.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);*/



        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

