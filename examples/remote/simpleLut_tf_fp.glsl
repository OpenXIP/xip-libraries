uniform sampler3D volume;
uniform sampler2D transferFunc; 

varying vec4 texCoord0;
varying vec3 vertexNormal;

void main()
{

	
	vec4 data = texture3D(volume, abs(vec3(0.0,0.0,1.0)-texCoord0.zxy));
	vec4 color=texture2D(transferFunc,data.xy);
    gl_FragColor = vec4(color.xyz,0.01);
	//gl_FragColor = vec4(data.xyz,0.01);
}
