//  Cartoon vertex shader
//  Adapted from Lighthouse3D

varying vec3 N;
varying vec3 L;
varying float S;
varying float distance;
	
void main()
{
	//  P is the vertex coordinate on body
	vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
	//  L is the light vector
	L = vec3(gl_LightSource[0].position) - P;
	//  Normal
	N = gl_NormalMatrix * gl_Normal;
	S = 0.0;
	vec2 treecolor = vec2(.6,.4);
	vec4 glcolor = gl_Color;
	
	if(glcolor.b < 0.001)
	{
		glcolor.b = 0.001;
	}
	
	if (gl_Color.rg == treecolor) S = glcolor.b+2.0;
	else if (gl_Vertex.y <= -.4) S = (-2.0)*gl_Vertex.y;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
	
	distance = sqrt(pow(gl_Position.x, 2.0) + pow(gl_Position.z, 2.0));
} 
