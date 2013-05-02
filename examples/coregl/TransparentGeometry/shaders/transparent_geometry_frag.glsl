uniform sampler2DShadow depthtex;
uniform sampler2D colortex;
uniform int layer;
uniform vec4 viewsize;

void main()
{
	vec4 coord = gl_FragCoord / viewsize;

	float visible = shadow2D(depthtex, coord.xyz).z;
	
	//float depth = texture2D(depthtex, coord.xy);
		//gl_FragColor = vec4(1.0, 0.5, 0.2, 0.5); // gl_Color;
	//return;
	// Discard fragment if in or in-front of previous layer
	if (visible < 0.5) /* gl_FragCoord.z < depth */
	{
#if 0
		gl_FragColor = texture2D(colortex, coord);
		// gl_FragDepth = 1.0;
#else
		discard;
#endif
	}
	else
	{
#if 1
		vec4 color = texture2D(colortex, coord.xy);
		vec4 addcol = gl_Color;
		
		// Assuming unassociated colors
		addcol.rgb *= addcol.a;
		
		// No fancy per-pixel shading
		gl_FragColor = color + (1.0 - color.a) * addcol;
#else
		gl_FragColor = vec4(1.0, 0.5, 0.2, 0.5); // gl_Color;
#endif
	}
}
