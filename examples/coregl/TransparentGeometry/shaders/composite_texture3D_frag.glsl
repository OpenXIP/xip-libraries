uniform sampler3D depthtex;  // Must be setup as a normal texture, i.e. DEPTH_COMP_FUNC to NONE
uniform sampler3D colortex;

uniform vec3 viewsize;
uniform float z;
uniform int numLayers;

void main()
{
    vec2 coord = gl_FragCoord.xy * viewsize.xy;
    float dz = 1.0 / float(numLayers);
    vec3 coord3D = vec3( coord, 0.5 * dz );

    vec4 color = texture3D(colortex, coord3D);
    float depth = texture3D(depthtex, coord3D).z;

    for(int i=1; i<numLayers; i++)
    {
	coord3D.z += dz;

	vec4 layerColor = texture3D(colortex, coord3D);

	// Assuming unassociated colors
	layerColor.rgb *= layerColor.a;
	
	color += layerColor * (1.0 - color.a);
    }

    gl_FragColor = color;
    gl_FragDepth = depth;
}
//gl_FragColor = vec4( coord3D, 0.5 );
//vec4( z, 0.5, 0.5, 0.5 ); /* texture3D(depthtex, coord3D).r */
//gl_FragDepth = texture3D(depthtex, coord3D);
//gl_FragColor = vec4( texture2D(colortex, coord).r, 0.5, 0.5, 0.5 );
