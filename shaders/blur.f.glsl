#version 120

uniform sampler2D texture;
varying vec2 texcoord;

float blur_size = 1.0/512.0;
int kernel_size = 4;

void main()
{
	vec4 sum = vec4(0.0);
	
	for(int i = -kernel_size; i < kernel_size; i++)
	{
		for(int j = -kernel_size; j < kernel_size; j++)
 		{
 			vec2 loc = vec2(texcoord.x + (i * blur_size), texcoord.y + (j * blur_size));
 			float multiplier = 1.0/(74.0);
 			sum += texture2D(texture, loc) * multiplier;
 		}
 	}
 	
   	gl_FragColor = sum;
}	
