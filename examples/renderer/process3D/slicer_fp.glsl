uniform sampler3D volume;

void main()
{
	vec4 data = texture3D(volume, abs(vec3(0.0,0.0,1.0)-gl_TexCoord[0].zxy));
	gl_FragColor = vec4(data.xyz * data.x , data.x);
}