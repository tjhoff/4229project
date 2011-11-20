// object.h
#include "CSCIx229.h"
class Object{

	public:
		Object(char* filename);
		void load(char* filename);
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
