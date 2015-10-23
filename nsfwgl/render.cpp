#include "render.h"
#include "Assets.h"

#include "gl_core_4_4.h"
#include "nsfw.h"

// Each Case should set up a uniform using the pass parameters
bool nsfw::RenderPass::setUniform(const char *name, nsfw::UNIFORM::TYPE type, const void *value, unsigned count, bool normalize) 
{
	unsigned loc = glGetUniformLocation(*shader, name);

	float* castFloat;
	castFloat = (float*)value;
	unsigned* castInt;
	castInt = (unsigned*)value;

	switch (type)
	{
	case nsfw::UNIFORM::FLO1: 
		glUniform1fv(loc, count, castFloat);
		return true;
		/*TODO_D("Setup float uniform!");*/
		break;
	case nsfw::UNIFORM::FLO3:
		glUniform3fv(loc, count, castFloat);
		return true;
		//TODO_D("Setup vec3 uniform!");
		break;
	case nsfw::UNIFORM::FLO4:
		glUniform4fv(loc, count, castFloat);
		return true;
		//TODO_D("Setup vec4 uniform!");      
		break;
	case nsfw::UNIFORM::MAT4:
		glUniformMatrix4fv(loc, count, normalize, castFloat);
		return true;
		//TODO_D("Setup mat4 uniform!");	  
		break;
	case nsfw::UNIFORM::INT1: 
		glUniform1i(loc, *castInt);
		return true;
		//TODO_D("Setup integer uniform!");	  
		break;
	case nsfw::UNIFORM::TEX2:
		glActiveTexture(GL_TEXTURE0 + count);
		glBindTexture(GL_TEXTURE_2D, *castInt);
		glUniform1i(loc, count);
		return true;
		//TODO_D("Setup texture2D uniform!"); 
		break;
	default:
		#ifdef _DEBUG
		std::cerr << "an invalid uniform type has been passed for item: " << name << std::endl;
		#endif
		return false;
		//TODO_D("INVALID Uniform type.");	  
		break;
	}

	return false;
}

// set GL state settings and globally accessible uniforms! Should be called before rendering occurs!
void nsfw::RenderPass::prep() { TODO_D("OVERRIDE: Setup the state of the card for this pass."); }

// reset the GL state- undo what we did just in case.
void nsfw::RenderPass::post() { TODO_D("OVERRIDE: Clean up the state of the card."); }