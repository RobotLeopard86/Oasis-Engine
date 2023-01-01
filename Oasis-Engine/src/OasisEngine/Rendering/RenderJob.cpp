#include "OasisPCH.h"
#include "RenderJob.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Oasis {
	RendererAPI* RenderJob::backendAPI = new OpenGLRendererAPI;
}