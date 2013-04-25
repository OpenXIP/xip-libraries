uniform sampler3D volume;
varying vec4 texCoord0;
varying vec3 vertexNormal;

vec4 tf1(float dens)
{
    vec4 res = vec4(0.0);
    res.r = 0.0;//smoothstep(0.4, 1.4, dens);
    res.g = smoothstep(0.4, 0.6, dens) - smoothstep(0.5, 0.7, dens);
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
