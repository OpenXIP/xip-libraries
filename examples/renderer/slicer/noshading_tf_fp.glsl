uniform sampler3D volume;

uniform sampler2D transferFunc;
uniform int width;
uniform int height;
uniform int depth;



vec3 computegradient()
{
	//samples for forward differences
    vec3 sample1;
    vec3 sample2;
	vec3 offset = vec3(1.0/width,1.0/height,1.0/depth);
    sample1.x = texture3D(volume, gl_TexCoord[0].xyz-vec3(offset.x,0.0,0.0)).x;
    sample2.x = texture3D(volume, gl_TexCoord[0].xyz+vec3(offset.x,0.0,0.0)).x;
    sample1.y = texture3D(volume, gl_TexCoord[0].xyz-vec3(0.0,offset.y,0.0)).y;
    sample2.y = texture3D(volume, gl_TexCoord[0].xyz+vec3(0.0,offset.y,0.0)).y;
    sample1.z = texture3D(volume, gl_TexCoord[0].xyz-vec3(0.0,0.0,offset.z)).z;
    sample2.z = texture3D(volume, gl_TexCoord[0].xyz+vec3(0.0,0.0,offset.z)).z;

    //forward differences gradient
    //vec3 gradient = data.xxx - sample1;
    //central differences gradient
    return sample2 - sample1;	
}


vec4 shade( vec4 data,
            vec4 shadingParam)
{
	vec3 lightdir = vec3(-gl_NormalMatrix[0][2],-gl_NormalMatrix[1][2],-gl_NormalMatrix[2][2]);
	vec3 halfway = lightdir;
	//vec4 color = vec4(data.xyz,0.01);
	float index=data.x*256.0*256.0;
	vec2 index2;
	index2.x=mod(index,256.0);
	index2.y=floor(index/256.0);
  index2/=vec2(256.0,256.0);
	vec4 color =texture2D(transferFunc, index2);
	
    return color;
}
void main()
{
   vec4 data = texture3D(volume, abs(vec3(0.0,0.0,1.0)-gl_TexCoord[0].zxy));
	

	gl_FragColor =shade(data, vec4(.3,0.6,0.6,64));
	
}