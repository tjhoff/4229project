//  Cartoon fragment shader
//  Adapted from Lighthouse3D

varying vec3 N;
varying vec3 L;
varying float S;
uniform sampler2D tex;
uniform bool fog_enabled;

void main()
{
	float intensity = dot(normalize(N),normalize(L));
	vec4 color = (texture2D(tex, gl_TexCoord[0].st));

	if(intensity < 0.1)
		intensity = 0.1;

	color = normalize(color);
	if (S >= 2.0){
		color.rgb = vec3(0.3,.2+S-2.0,.1);
	}
	else if (S < 2.0 && S > 0.0 ) {
		color.b = S*.4;
		color -= S*.05;
	}
	
	if(fog_enabled)
	{
		float z = (gl_FragCoord.z / gl_FragCoord.w) / 8.0;
		color += vec4(z, z, z, 1.0);
	}

	color *=intensity;
	color.a = 1.0;
	gl_FragColor = color;
}


