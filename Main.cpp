#include"particleSystemFire.h"
#include <chrono>
#include "Environment.h"



const unsigned int width = 800;
const unsigned int height = 800;
//Global DeltaTime
float deltaTime = 0.0f;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL-Fire and Smoke", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	
	
	// texture
	Texture textures[]
	{
		Texture("models/planks.png", "diffuse", 0),
		Texture("models/planksSpec.png", "specular", 1)
	};

	Texture fireTextures[]
	{
		Texture("models/fire.png", "diffuse", 0),
	};
	Texture smokeTextures[]
	{
		Texture("models/smoke.png", "diffuse", 0),
	};
	

	std::vector <Texture> tex(fireTextures, fireTextures + sizeof(fireTextures) / sizeof(Texture));
	std::vector <Texture> smoketex(smokeTextures, smokeTextures + sizeof(smokeTextures) / sizeof(Texture));
	Mesh fireModel = loadOBJ("models/untitled.obj", tex);

	Mesh smokeModel = loadOBJ("models/untitled.obj", smoketex);

	//Fire PartycleSystem
	Shader noLightShaderProgram("noLight.vert", "noLight.frag");

	glm::vec3 emiterPos = glm::vec3(0.0f, 0.0f, 0.0f);
	float emiterCircleSize = 0.05f;
	float fireParEmitSpeed = 0.05f;
	glm::vec3 particleTransf = glm::vec3(0.0f, -0.75f, 0.0f);
	glm::vec3 particleScale = glm::vec3(0.2f);
	int fireMaxPar = 50;
	float fireParlifeTime = 1.2f;
	ParticleSystemFire firePS(fireModel, emiterPos, emiterCircleSize, fireParEmitSpeed, fireMaxPar, particleTransf, particleScale, fireParlifeTime);

	//Smoke ParticleSystem
	ParticleSystemFire smokePS(smokeModel, glm::vec3(0.0f, -0.65f, 0.0f), 0.15f, 0.45f, 50, glm::vec3(0.0f, -0.4f, 0.0f), glm::vec3(0.15f), 2.4f);


	// Generates defoult Shader program
	Shader shaderProgram("default.vert", "default.frag");


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.2f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	//activate Shader programs
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	noLightShaderProgram.Activate();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	//
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Environment envi;

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Delta Time variables
	auto lastTime = std::chrono::high_resolution_clock::now();
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Delta Time
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> deltaTimeDuration = currentTime - lastTime;
		lastTime = currentTime;
		deltaTime = deltaTimeDuration.count();
		
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Update Particle systems 
		firePS.Update();
		smokePS.Update();

		// Draws meshes
		firePS.Draw(noLightShaderProgram, camera);
		envi.Draw(shaderProgram, camera);
		// Draws transparent meshes
		glEnable(GL_BLEND);
		smokePS.Draw(shaderProgram, camera);
		glDisable(GL_BLEND);
		


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}