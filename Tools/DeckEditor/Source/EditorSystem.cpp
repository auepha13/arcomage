#include "EditorSystem.h"


// -----------------------------------------------------------------------------
std::string EditorSystem::getRenderView()	{
	std::stringstream ss;
	ss << RenderViewInstance;
	ss << InstanceCount;
	return ss.str();
}