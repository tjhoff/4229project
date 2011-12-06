varying vec2 texcoord;

void main()
{
	gl_Position = gl_Vertex;
	texcoord = vec2(gl_Position) * 0.5 + 0.5;
}

