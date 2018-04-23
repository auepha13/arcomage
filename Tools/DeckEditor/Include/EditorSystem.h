#ifndef _EditorSystem_h_
#define _EditorSystem_h_

#include <string>
#include <sstream>
#include <Singleton.h>
class EditorSystem : public Arcomage::Singleton<EditorSystem>{
	friend class Arcomage::Singleton<EditorSystem>;

private:
	std::string RenderViewInstance;
	int InstanceCount;
	bool running;

	EditorSystem() 
		: RenderViewInstance("CardViewWidget"), 
		InstanceCount(0),
		running(false) {

	}
public:
	std::string getRenderView();
	void increaseInstanceCount() {
		InstanceCount++;
	}

	void setRunning(bool run) {
		running = run;
	}

	bool getRunning() {
		return running;
	}

};


#endif