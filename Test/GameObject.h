#pragma once
#include "Assets.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"

struct GameObject
{
	glm::mat4 trasform;

	nsfw::Asset<nsfw::ASSET::VAO> mesh;
	nsfw::Asset<nsfw::ASSET::VERTEX_COUNT> tris;

	nsfw::Asset<nsfw::ASSET::TEXTURE> diffuse;
	bool useNormMap = false;
	nsfw::Asset<nsfw::ASSET::TEXTURE> normMap;

};