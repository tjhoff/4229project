// object.h
#include "CSCIx229.h"

#ifndef OBJECT
#define OBJECT
class Object{

	public:
		Object(int disp, float nx, float ny, float nz);
		void setLocation(double x, double y, double z);
		void setScale(double scale);
		void draw();
		
	private:
		int displayname;
		double x;
		double y;
		double z;
		double xRot;
		double yRot;
		double zRot;
		double scale;

};

#endif
