uniform sampler2D texture;

varying vec3 N;
varying vec3 v;

void main(void)
{
	vec3 L = normalize(gl_LightSource[0].position.xyz - v);   
	vec4 diffuse = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);  
	diffuse = clamp(diffuse, 0.0, 1.0); 
	
	float avg = (diffuse.x + diffuse.y + diffuse.z + diffuse.w)/4;
	if(avg < 0.25)
	{
		diffuse = vec4(0.25);
	}
	
	vec4 color = (texture2D(texture, gl_TexCoord[0].st)) * diffuse;
	color.a = 1.0;

	gl_FragColor = color;
}
    
