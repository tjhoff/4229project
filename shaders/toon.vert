//  Cartoon vertex shader
//  Adapted from Lighthouse3D

varying vec3 N;
varying vec3 L;
	
void main()
{
   //  P is the vertex coordinate on body
   vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
   //  L is the light vector
   L = vec3(gl_LightSource[0].position) - P;
   //  Normal
   N = gl_NormalMatrix * gl_Normal;
   gl_TexCoord[0] = gl_MultiTexCoord0;
   gl_Position = ftransform();
} 
