uniform sampler3D volume;
varying vec4 texCoord0;
varying vec3 vertexNormal;

vec4 tf2(float dens)
{
    vec4 res = vec4(0.0);
    res.r = smoothstep(0.7, 1.0, dens);
    res.g = 0.0;
    res.b = smoothstep(0.4, 0.5, dens) - smoothstep(0.44, 0.54, dens);
    res.a = dens;
    return res;
}

void main()
{
    vec4 data = texture3D(volume, texCoord0.xyz);

    data = tf2(data.x);

    data.rgb *= data.a;

    gl_FragColor = data;
}
