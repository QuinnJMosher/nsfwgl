#pragma warning(disable : 4996)
#include "gl_core_4_4.h"
#include "nsfw.h"
#include "stb\stb_image.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "fbx\FBXFile.h"
#include <fstream>;

using namespace nsfw::ASSET;

const char *nsfw::TYPE_NAMES[eSIZE + 1] = { "NONE","vao","ibo","vbo","tri-size","fbo","rbo","texture","shader","SIZE" };

#ifdef _DEBUG
#define ASSET_LOG(type) do { std::cerr << "Trying to create key: <" << TYPE_NAMES[type] << ">" << name << std::endl; } while(0)
#else 
#define ASSET_LOG(type) do {} while (0)
#endif


nsfw::GL_HANDLE nsfw::Assets::getVERIFIED(const AssetKey &key) const
{
#ifdef _DEBUG
			if (!handles.count(key))
			{
				std::cerr << "Asset Key not found: <" << TYPE_NAMES[key.first] << ">" << key.second << std::endl;
				return 0;
			}
#endif
			return handles.at(key);
}

bool nsfw::Assets::setINTERNAL(ASSET::GL_HANDLE_TYPE t, const char *name, GL_HANDLE handle)
{
	AssetKey key(t, name);
#ifdef _DEBUG
	if (handles.count(key))
	{
		std::cerr << "Asset Key already exists: <" << TYPE_NAMES[key.first] << ">" << key.second << " ignoring." << std::endl;
		return false;
	}
	else std::cerr << "Asset Key successfully created: <" << TYPE_NAMES[key.first] << ">" << key.second << std::endl;
#endif
	handles[key] = handle;
	return true;
}


bool nsfw::Assets::makeVAO(const char * name, const struct Vertex *verts, unsigned vsize,  const unsigned * tris, unsigned tsize)
{
	ASSET_LOG(GL_HANDLE_TYPE::VBO);
	ASSET_LOG(GL_HANDLE_TYPE::IBO);
	ASSET_LOG(GL_HANDLE_TYPE::VAO);
	ASSET_LOG(GL_HANDLE_TYPE::SIZE);

	GL_HANDLE newVAO;
	GL_HANDLE newIBO;
	GL_HANDLE newVBO;
	GL_HANDLE newSize = 0;

	glGenVertexArrays(1, &newVAO);
	glGenBuffers(1, &newVBO);
	glGenBuffers(1, &newIBO);

	glBindVertexArray(newVAO);
	glBindBuffer(GL_ARRAY_BUFFER, newVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newIBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec2) + (sizeof(glm::vec4) * 2)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if (setINTERNAL(ASSET::VAO, name, newVAO)) {
		if (setINTERNAL(ASSET::VBO, name, newVBO)) {
			if (setINTERNAL(ASSET::IBO, name, newIBO)) {
				return setINTERNAL(ASSET::SIZE, name, newSize);
			}
		}
	}
	
	//TODO_D("Should generate VBO, IBO, VAO, and SIZE using the parameters, storing them in the 'handles' map.\nThis is where vertex attributes are set!");
	return false;
}

bool nsfw::Assets::makeFBO(const char * name, unsigned w, unsigned h, unsigned nTextures, const char * names[], const unsigned depths[])
{
	ASSET_LOG(GL_HANDLE_TYPE::FBO);

	GL_HANDLE newFBO;
	GL_HANDLE newRenderBuff;
	GL_HANDLE* newTexts = new GL_HANDLE[nTextures];

	for (int i = 0; i < nTextures; i++) {
		if (makeTexture(names[i], w, h, depths[i])) {
			newTexts[i] = instance().get<ASSET::TEXTURE>(name);
		}
		else 
		{
			return false;
		}
	}

	glGenFramebuffers(1, &newFBO);
	glGenRenderbuffers(1, &newRenderBuff);
	
	glBindFramebuffer(GL_FRAMEBUFFER, newFBO);
	glBindRenderbuffer(GL_RENDERBUFFER, newRenderBuff);

	for (int i = 0; i < nTextures; i++) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, newTexts[i], 0);
	}

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, newRenderBuff);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//TODO_D("Create an FBO! Array parameters are for the render targets, which this function should also generate!\nuse makeTexture.\nNOTE THAT THERE IS NO FUNCTION SETUP FOR MAKING RENDER BUFFER OBJECTS.");
	return false;
}

bool nsfw::Assets::makeTexture(const char * name, unsigned w, unsigned h, unsigned depth, const char *pixels)
{
	ASSET_LOG(GL_HANDLE_TYPE::TEXTURE);
	char * name2 = "";
	strcpy_s(name2, sizeof(name), name);
	GL_HANDLE newTex;

	glGenTextures(1, &newTex);

	glBindTexture(GL_TEXTURE_2D, newTex);

	glTexImage2D(GL_TEXTURE_2D, 0, depth, w, h, 0, depth, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return setINTERNAL(ASSET::TEXTURE, name2, newTex);

	//TODO_D("Allocate a texture using the given space/dimensions. Should work if 'pixels' is null, so that you can use this same function with makeFBO\n note that Dept will use a GL value.");
	return false;
}

bool nsfw::Assets::loadTexture(const char * name, const char * path)
{
	GL_HANDLE texture;
	int width, height, format;
	unsigned char* data = stbi_load(path, &width, &height, &format, STBI_default);

	unsigned glFormat = 0;
	switch (format)
	{
	case 1:
		//gl  red
		glFormat = GL_RED;
		break;
	case 2:
		//gl rg
		glFormat = GL_RG;
		break;
	case 3:
		//gl rgb
		glFormat = GL_RGB;
		break;
	case 4:
		//gl rgba
		glFormat = GL_RGBA;
		break;
	default: //including case 0;
		#ifdef _DEBUG
		std::cerr << "texture: " << name << " path: " << path << " failed to load!\n";
		if (format == 0) {
			std::cerr << "stbi returned format code 0 (failure)\n";
		}
		else 
		{
			std::cerr << "stbi returned format code " << format << " (invalid/unknown)\n";
		}
		#endif

		return false;
		break;
	}

	bool sucess = makeTexture(name, width, height, glFormat, (const char*)data);

	stbi_image_free(data);

	//TODO_D("This should load a texture from a file, using makeTexture to perform the allocation.\nUse STBI, and make sure you switch the format STBI provides to match what openGL needs!");
	return sucess;
}

nsfw::GL_HANDLE nsfw::Assets::internLoadShader(unsigned type, const char* filename) {
	std::fstream in(filename);
	std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	char* src = new char[contents.length() + 1];
	strncpy(src, contents.c_str(), contents.length() + 1);

	GL_HANDLE shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, 0);

	glCompileShader(shader);
	delete[] src;

	return shader;
}

bool nsfw::Assets::loadShader(const char * name, const char * vpath, const char * fpath)
{
	ASSET_LOG(GL_HANDLE_TYPE::SHADER);

	GL_HANDLE program = glCreateProgram();
	GL_HANDLE vShader = internLoadShader(GL_VERTEX_SHADER, vpath);
	GL_HANDLE fShader = internLoadShader(GL_FRAGMENT_SHADER, fpath);

	int success;

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return setINTERNAL(ASSET::SHADER, name, program);
	//TODO_D("Load shader from a file.");
}

bool nsfw::Assets::loadFBX(const char * name, const char * path)
{
	//name/meshName
	//name/textureName

	std::string namePrefix = name;
	namePrefix += "_";

	FBXFile fbxFile;
	fbxFile.load(path);

	for (int i = 0; i < fbxFile.getMeshCount(); i++) {
		FBXMeshNode* modelData = fbxFile.getMeshByIndex(i);
		Vertex* vertices = new Vertex[modelData->m_vertices.size()];

		for (int j = 0; j < modelData->m_vertices.size(); j++) {
			Vertex newVert;
			newVert.position = modelData->m_vertices[i].position;
			newVert.normal = modelData->m_vertices[i].normal;
			newVert.tangent = modelData->m_vertices[i].tangent;
			newVert.texCoord = modelData->m_vertices[i].texCoord1;

			vertices[i] = newVert;
		}

		std::string newName = namePrefix + modelData->m_name;
		makeVAO(newName.c_str(), vertices, modelData->m_vertices.size(), modelData->m_indices.data(), modelData->m_indices.size());
	}

	fbxFile.initialiseOpenGLTextures();
	for (int i = 0; i < fbxFile.getTextureCount(); i++) {
		FBXTexture* tex = fbxFile.getTextureByIndex(i);

		std::string newName = namePrefix + tex->name;

		setINTERNAL(ASSET::TEXTURE, newName.c_str(), tex->handle);
	}

	fbxFile.unload();

	return true;
	//TODO_D("FBX file-loading support needed.\nThis function should call loadTexture and makeVAO internally.\nFBX meshes each have their own name, you may use this to name the meshes as they come in.\nMAKE SURE YOU SUPPORT THE DIFFERENCE BETWEEN FBXVERTEX AND YOUR VERTEX STRUCT!\n");
}

bool nsfw::Assets::loadOBJ(const char * name, const char * path)
{
	std::vector<Vertex> verticies;
	std::vector<unsigned> indicies;

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> mats;

	std::string err = tinyobj::LoadObj(shapes, mats, path);
	printf(err.c_str());

	for (int meshIndex = 0; meshIndex < shapes.size(); meshIndex++) {
		tinyobj::mesh_t* curMesh = &shapes[meshIndex].mesh;

		bool minusOne = false;
		for (int j = 0; j < curMesh->positions.size() / 3; j++) {
			Vertex newVert;

			newVert.position.x = curMesh->positions[3 * j + 0];
			newVert.position.y = curMesh->positions[3 * j + 1];
			newVert.position.z = curMesh->positions[3 * j + 2];
			newVert.position.w = 1;

			newVert.normal.x = curMesh->normals[3 * j + 0];
			newVert.normal.y = curMesh->normals[3 * j + 1];
			newVert.normal.z = curMesh->normals[3 * j + 2];
			newVert.normal.w = 1;

			newVert.tangent = vec4(0);

			if (minusOne) {
				newVert.texCoord.x = curMesh->texcoords[3 * j - 1];
				newVert.texCoord.y = curMesh->texcoords[3 * j + 0];
			}
			else 
			{
				newVert.texCoord.x = curMesh->texcoords[3 * j + 0];
				newVert.texCoord.y = curMesh->texcoords[3 * j + 1];
			}

			minusOne = !minusOne;

			verticies.emplace_back(newVert);
		}

		indicies.emplace_back(curMesh->indices);
	}

	return makeVAO(name, verticies.data(), verticies.size(), indicies.data(), indicies.size());

	//TODO_D("OBJ file-loading support needed.\nThis function should call makeVAO and loadTexture (if necessary), MAKE SURE TO TAKE THE OBJ DATA AND PROPERLY LINE IT UP WITH YOUR VERTEX ATTRIBUTES (or interleave the data into your vertex struct).\n");
}

void nsfw::Assets::init()
{
	TODO_D("Load up some default assets here if you want.");
	
	setINTERNAL(FBO,"Screen",0);
	
	makeVAO("Cube",CubeVerts,24,CubeTris,36);
	makeVAO("Quad",QuadVerts, 4, QuadTris,6);
	/*
	char w[] = { 255,255,255,255 };
	makeTexture("White", 1, 1, GL_RGB8, w);
	*/

}

void nsfw::Assets::term()
{
	TODO();
	for each(std::pair<AssetKey,unsigned> k in handles)
	{
		switch (k.first.first)
		{
		case VBO:		glDeleteBuffers(1, &k.second);		 /*TODO_D("VBO deletion");*/break;
		case IBO:		glDeleteBuffers(1, &k.second);		 /*TODO_D("IBO deletion");*/break;
		case VAO:		glDeleteVertexArrays(1, &k.second);  /*TODO_D("VAO deletion");*/break;
		case SHADER:	glDeleteProgram(k.second);		  /*TODO_D("Shader deletion");*/break;
		case TEXTURE:	glDeleteTextures(1, &k.second);  /*TODO_D("Texture deletion");*/break;
		case RBO:		glDeleteRenderbuffers(1, &k.second); /*TODO_D("RBO deletion");*/break;
		case FBO:		glDeleteFramebuffers(1, &k.second);  /*TODO_D("FBO deletion");*/break;
		}
	}
}


