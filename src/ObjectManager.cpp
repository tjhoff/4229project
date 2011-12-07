#include "ObjectManager.h"

ObjectManager::ObjectManager(){

}

ObjectManager::~ObjectManager(){

	std::vector<Object*>::iterator it;
	for (it = objVec.begin(); it!=objVec.end(); it++){
		Object* obj = *it;
		delete obj;
	}

}

void ObjectManager::drawObjects(){
	std::vector<Object*>::iterator it;
	if (objVec.size() == 0) return;
	for (it = objVec.begin(); it!=objVec.end(); it++){
		Object* obj = *it;
		printf("Object drawn\n");
		obj->draw();
		
	}

}

void ObjectManager::addObject(Object* newObject){

	objVec.push_back(newObject);

}



std::vector<Object*> ObjectManager::getObjects(){

	return objVec;

}
