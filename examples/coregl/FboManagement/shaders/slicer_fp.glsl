uniform sampler3D volume;
varying vec4 texCoord0;
varying vec3 vertexNormal;

#ifdef MASK
uniform sampler2D mask;
uniform sampler2D mask2;
#endif

vec4 tf1(float dens)
{
    vec4 res = vec4(0.0);
    res.r = smoothstep(0.4, 1.0, dens);
    res.g = res.r;
    res.b = res.r;
    res.a = dens;
    return res;
}

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

	vec4 data0 = tf1(data.x);
    vec4 data1 = tf2(data.x);

    data0.rgb *= data0.a;
    data1.rgb *= data1.a;
 
#ifdef MASK
    vec4 m = texture2D(mask, gl_FragCoord.xy/vec2(512,512));
    vec4 m2 = texture2D(mask2, gl_FragCoord.xy/vec2(512,512));
#else
    vec4 m = vec4(1.0);
    vec4 m2 = vec4(1.0);
#endif

#ifdef MR2
    gl_FragData[0] = data0 + m2;
    gl_FragData[1] = vec4(data1.rgb * clamp(m.rgb, vec3(0.5), vec3(1.0)), data1.a);
#elif defined MR4
    gl_FragData[0] = data0;
    gl_FragData[1] = data1;
    gl_FragData[2] = clamp(data0 + data1, vec4(0.0), vec4(1.0));
    gl_FragData[3] = clamp(data0 - data1, vec4(0.0), vec4(1.0));
#else
    gl_FragColor = data0;
#endif
}
