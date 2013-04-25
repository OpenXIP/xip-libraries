sampler2D depthtex;  // Must be setup as a normal texture, i.e. DEPTH_COMP_FUNC to NONE
sampler2D colortex;

uniform vec3 viewsize;

void main()
{
    vec2 coord = gl_FragCoord.xy * viewsize.xy;

    gl_FragDepth = texture2D(depthtex, coord);
    gl_FragColor = texture2D(colortex, coord);
    //gl_FragColor = vec4(coord, texture2D(depthtex, coord).r, 0.5 + 0.5*texture2D(colortex, coord).a);
}

