uniform sampler2D image;
uniform sampler3D volume;

void main()
{
	vec4 data = texture2D(image, gl_TexCoord[0].st);
	vec4 vdata = texture3D(volume, vec3(gl_TexCoord[0].xyz));
	
	#if defined(USEVOL)
	gl_FragColor = vec4(vdata.xyz,1)* 1.5 * vec4(1,.6,.29,1);
	#else 
	gl_FragColor = vec4(vdata.xyz,1)* vec4(1,0,0,1) + vec4(.5,0.3,0.1,0);
	#endif
}