uniform sampler2D texture; 
 
void main(void)
{
	vec4 color = texture2D(texture, gl_TexCoord[0].st);
	
	float avg = (color.r + color.g + color.b) / 3.0;
	
	if(avg < 0.5)
		discard;
		
	gl_FragColor = color;
}
