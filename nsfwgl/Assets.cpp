#include "gl_core_4_4.h"
#include "nsfw.h"

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

bool nsfw::Assets::setINTERNAL(ASSET::GL_HANDLE_TYPE t, char *name, GL_HANDLE handle)
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
	char * name2 = "";
	strcpy_s(name2, sizeof(name), name);

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

	if (setINTERNAL(ASSET::VAO, name2, newVAO)) {
		if (setINTERNAL(ASSET::VBO, name2, newVBO)) {
			if (setINTERNAL(ASSET::IBO, name2, newIBO)) {
				return setINTERNAL(ASSET::SIZE, name2, newSize);
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
	TODO_D("This should load a texture from a file, using makeTexture to perform the allocation.\nUse STBI, and make sure you switch the format STBI provides to match what openGL needs!");
	return false;
}

bool nsfw::Assets::loadShader(const char * name, const char * vpath, const char * fpath)
{
	ASSET_LOG(GL_HANDLE_TYPE::SHADER);
	TODO_D("Load shader from a file.");
	return false;
}

bool nsfw::Assets::loadFBX(const char * name, const char * path)
{
	//name/meshName
	//name/textureName
	TODO_D("FBX file-loading support needed.\nThis function should call loadTexture and makeVAO internally.\nFBX meshes each have their own name, you may use this to name the meshes as they come in.\nMAKE SURE YOU SUPPORT THE DIFFERENCE BETWEEN FBXVERTEX AND YOUR VERTEX STRUCT!\n");
	return false;
}

bool nsfw::Assets::loadOBJ(const char * name, const char * path)
{
	TODO_D("OBJ file-loading support needed.\nThis function should call makeVAO and loadTexture (if necessary), MAKE SURE TO TAKE THE OBJ DATA AND PROPERLY LINE IT UP WITH YOUR VERTEX ATTRIBUTES (or interleave the data into your vertex struct).\n");
	return false;
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
		case VBO:		TODO_D("VBO deletion");		break;
		case IBO:		TODO_D("IBO deletion");		break;
		case VAO:		TODO_D("VAO deletion");		break;
		case SHADER:	TODO_D("Shader deletion");	break;
		case TEXTURE:	TODO_D("Texture deletion"); break;
		case RBO:		TODO_D("RBO deletion");		break;
		case FBO:		TODO_D("FBO deletion");		break;
		}
	}
}


