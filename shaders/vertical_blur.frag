uniform sampler2D texture; 
varying vec2 texcoord;
 
const float blurSize = 1.0/512.0;
 
void main(void)
{
	vec4 sum = vec4(0.0);

	sum += texture2D(texture, vec2(texcoord.x, texcoord.y - 4.0*blurSize)) * 0.05;
	sum += texture2D(texture, vec2(texcoord.x, texcoord.y - 3.0*blurSize)) * 0.09;
	sum += texture2D(texture, vec2(texcoord.x, texcoord.y - 2.0*blurSize)) * 0.12;
	sum += texture2D(texture, vec2(texcoord.x, texcoord.y - blurSize)) * 0.15;
	sum += texture2D(texture, vec2(texcoord.x, texcoord.y)) * 0.16;
	sum += texture2D(texture, vec2(texcoord.x, texcoord.y + blurSize)) * 0.15;
	sum += texture2D(texture, vec2(texcoord.x, texcoord.y + 2.0*blurSize)) * 0.12;
	sum += texture2D(texture, vec2(texcoord.x, texcoord.y + 3.0*blurSize)) * 0.09;
	sum += texture2D(texture, vec2(texcoord.x, texcoord.y + 4.0*blurSize)) * 0.05;

	float brightness = (sum.x + sum.y + sum.z) / 3.0;
	sum *= 1.3;
	gl_FragColor = mix(texture2D(texture, texcoord), sum, pow(brightness, 2.0));
}
