
#include <vector>

#include "Object.h"
#include <stdio.h>


#ifndef OBJECT_MANAGER
	#define OBJECT_MANAGER


class ObjectManager{

	public:
		ObjectManager();
		~ObjectManager();
		void addObject(Object* object);
		void drawObjects();
		std::vector<Object*> getObjects();
	private:
		std::vector<Object*> objVec;
		int maxObjectID;
		

};

#endif
