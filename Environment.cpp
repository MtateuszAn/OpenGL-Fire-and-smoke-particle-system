#include "Environment.h"

Environment::Environment()
{
	Texture metalTextures[]
	{
		Texture("models/dirty-metal-low-res-dark.jpg", "diffuse", 0),
	};

	std::vector <Texture> metalTexture(metalTextures, metalTextures + sizeof(metalTextures) / sizeof(Texture));

	MeshList.push_back(loadOBJ("models/torchPost.obj", metalTexture));


	Texture wallTextures[]
	{
		Texture("models/grunge-wall-texture.jpg", "diffuse", 0),
	};

	std::vector <Texture> wallTexture(wallTextures, wallTextures + sizeof(wallTextures) / sizeof(Texture));

	MeshList.push_back(loadOBJ("models/roomWall.obj", wallTexture));

	Texture planksTextures[]
	{
		Texture("models/planks.png", "diffuse", 0),
		Texture("models/planksSpec.png", "specular", 1)
	};

	std::vector <Texture> planksTexture(planksTextures, planksTextures + sizeof(planksTextures) / sizeof(Texture));

	MeshList.push_back(loadOBJ("models/roomFllorobj.obj", planksTexture));
}

void Environment::Draw(Shader& shader, Camera& camera)
{
	for (Mesh& mesh : MeshList)
	{
		mesh.Draw(shader, camera, glm::mat4(1.0f), translation, rotation, scale);
	}
}
