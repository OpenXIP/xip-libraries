uniform sampler3D volume;
varying vec4 texCoord0;
varying vec3 vertexNormal;

vec4 tf1(float dens)
{
    vec4 res = vec4(0.0);
    res.r = smoothstep(0.4, 1.0, dens);
    res.g = res.r;
    res.b = res.r;
    res.a = dens;
    return res;
}

void main()
{
    vec4 data = texture3D(volume, texCoord0.xyz);
 
    data = tf1(data.x);

    data.rgb *= data.a;

    gl_FragColor = data;
}
