varying vec3 N;
varying vec3 v;
varying float S;

void main(void)
{
	v = vec3(gl_ModelViewMatrix * gl_Vertex);       
	N = normalize(gl_NormalMatrix * gl_Normal);
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	if (gl_Vertex.y < -.4)
	{ 
		S = 1.0;
	}
	else 
	{
		S = 0.0;
	}
}
