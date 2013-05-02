uniform sampler3D volume;
uniform sampler2D lut;

void main()
{
    float density = texture3D(volume, gl_TexCoord[0].xyz).x;
    float index=density*65536.0;
	vec2 index2;
	index2.x=mod(index,256.0);
	index2.y=floor(index/256.0);
    index2/=vec2(256.0,256.0);
    gl_FragColor = texture2D(lut, index2);
}