uniform sampler3D volume;
uniform sampler3D lightvol;
uniform sampler2D lut;

const float Ibias = 0.1;

void main()
{
	vec3 pos = abs(vec3(0.0,0.0,1.0)-gl_TexCoord[0].xyz);
	float scalar = texture3D(volume, pos).r;
	vec4 amb = texture3D(lightvol,  pos);
	//scalar *= 2;
	//amb *= 6;
	float brightness = 2.0;
	vec4 col = texture2D(lut, vec2(scalar));				//right				
	col.rgb *= mix(amb, 1.0, Ibias) * brightness;			//right
	//col.rgb *= amb * brightness;			
	gl_FragColor = col;										//right
	gl_FragColor = vec4(col.rgb/1, col.a/1);
	//gl_FragColor = vec4 (col.rgb * amb.r , col.r);
	//gl_FragColor = vec4 (col.rgb * amb *4, 0.0);
	//gl_FragColor = vec4 (2,2,2, 0.0);
	//gl_FragColor = vec4 (vec3(amb) * brightness, 0.0);
	//gl_FragColor = vec4 (vec3(amb*amb) * brightness, amb);
	//gl_FragColor = vec4 (vec3(scalar*scalar), scalar);
	//gl_FragColor = vec4 (vec3(col*col), col);
}