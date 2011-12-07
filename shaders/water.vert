varying vec2 texcoord;

void main()
{
    gl_Position = gl_Vertex;
    texcoord = vec2(gl_Vertex) * vec2(0.5) + vec2(0.5);
}
