//  Cartoon fragment shader
//  Adapted from Lighthouse3D

varying vec3 N;
varying vec3 L;
varying float S;
uniform sampler2D tex;

void main()
{
   float intensity = dot(normalize(N),normalize(L));
   vec4 color = (texture2D(tex, gl_TexCoord[0].st));
      float f;


   if (intensity > 0.95)
      f= 1.0;
   else if (intensity > 0.5)
      f = 0.6;
   else if (intensity > 0.25)
      f = 0.3;
   else
      f = 0.1;
	
   color = normalize(color);
   if (S < 2.0 && S > 0.0 ) {
   		color.b = S*.4;
   		color -= S*.05;
	}
	else if (S!=0){
		color.rgb = vec3(0.3,.2+S-2.0,.1);
		
		color *= f;
		
	}
	else {
		color *=f;
	}
	color.a = 1.0;
   gl_FragColor = color;
}


