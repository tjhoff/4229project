//  Cartoon vertex shader
//  Adapted from Lighthouse3D

varying vec3 N;
varying vec3 L;
varying float S;
	
void main()
{
	//  P is the vertex coordinate on body
	vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
	//  L is the light vector
	L = vec3(gl_LightSource[0].position) - P;
	//  Normal
	N = gl_NormalMatrix * gl_Normal;
	
	if (gl_Vertex.y < -.4)
	{ 
		S = 1.0;
	}
	else 
	{
		S = 0.0;
	}
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
} 
