//skybox.h

#include <QtOpenGL>

class Skybox{

	public:
		Skybox();
		GLuint right;
		GLuint left;
		GLuint front;
		GLuint back;
		GLuint top;
		void draw();


};
