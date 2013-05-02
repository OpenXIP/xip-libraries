uniform sampler3D volume;
uniform sampler2D lut;

void main()
{
    float density = texture3D(volume, gl_TexCoord[0].xyz).x;
    gl_FragColor = texture2D(lut, vec2(density));
}