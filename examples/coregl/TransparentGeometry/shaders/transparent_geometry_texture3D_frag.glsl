uniform sampler3D depthtex;
uniform sampler3D colortex;

uniform vec4 viewsize;
uniform float z;  // (0.5 + layer) / texSizeZ

void main()
{
	vec4 coord = gl_FragCoord / viewsize;
	float visible = texture3D(depthtex, coord.xyz).r;
	
	//float depth = texture2D(depthtex, coord.xy);

	// Discard fragment if in or in-front of previous layer

	if (gl_FragCoord.z <= 0.0 /* visible */)
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
#if 0
		gl_FragColor = gl_Color;

		//vec4 addcol = gl_Color;
		
		// Assuming unassociated colors
		//addcol.rgb *= addcol.a;
		
		// No fancy per-pixel shading
		//gl_FragColor = color + (1.0 - color.a) * addcol;
#else
		gl_FragColor = vec4(1.0, 0.5, 0.2, 0.5); // gl_Color;
#endif
	}
}
