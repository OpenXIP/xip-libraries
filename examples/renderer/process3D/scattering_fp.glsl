// Local Ambient Occlusion Volume

// textures
uniform sampler3D volume;
uniform sampler3D lightvol;
//uniform sampler1D clut;
uniform sampler2D lut;

uniform vec3 volsize;
uniform vec3 lightpos;
uniform vec3 lightpos2;
uniform int  raycount;

void scattering()
{
}

void sample_out( in vec3 pos, in vec3 offset, out float opac)
{
	vec3 newpos = pos + offset;
	
	opac = texture3D(volume, newpos).r;
	//opac = smoothstep(0.2, 0.6, opac);
}

	
void sample(in vec3 pos, out vec4 sum)
{
	volsize = vec3( 160.0, 430.0, 183.0);
	
	vec3 dir[6];
	dir[0] = vec3( 1, 0, 0);
	dir[1] = vec3(-1, 0, 0);
	dir[2] = vec3( 0, 1, 0);
	dir[3] = vec3( 0,-1, 0);
	dir[4] = vec3( 0, 0, 1);
	dir[5] = vec3( 0, 0,-1);
	
	int numsteps = 5;
	float radius = .05;
	float distance = 0.0;
	float mindelta = radius / float(numsteps);
	vec3 offset;
	
	//int raycount = 2;
		
	float newOpac[6];
		
	float opac; 
	float finalopac;
	finalopac = 0.0;
	
	//sample_out(pos, vec3(0,0,0), finalopac);
	
	float ambience = 0.0;
	
	vec4 shadow = vec4(0.0);
	
	float opacX = texture3D(volume,  pos);
	float colX = texture2D(lut, vec2(opacX));
	
	for (int x = 0; x < 6; x++) {
		//newOpac[x] = 1.0;
		newOpac[x] = 0.0;
		dir[x] = normalize(dir[x]);
		float dI = 1.0; // / float(numsteps);
		for (int i = 0; i < numsteps; i++)
		{
			distance += mindelta;
			offset = distance * dir[x];
			
			shadow = texture3D(lightvol,  pos + offset);			
			
			sample_out(pos, offset, opac);
			//opac = (1.0-pow(1.0-opac,mindelta*0.5)); 		// vielleicht nicht
			vec4 col = texture2D(lut, vec2(opac));
			
			ambience += max(col,0.0) * max(shadow, 0.0) * max(1.0 - newOpac[x], 0.0);
			newOpac[x] += col * max(1.0 - newOpac[x], 0.0);
		}	
		distance = 0.0;
		finalopac += newOpac[x];	
	}
	//finalopac /=6;
	//sum = vec4(finalopac);
	//sum = vec4(ambience/30);
	sum = texture3D(lightvol,  pos) + vec4(ambience/3);
	//sum = texture3D(lightvol,  pos);
	//sum = vec4(ambience/6);
	//sum = vec4(opac);
	//opac = texture3D(volume,  pos);
	//sum = texture2D(lut, vec2(opac));
}


void main()
{
	volsize = vec3( 160.0, 430.0, 183.0);
	 vec3 pos = vec3(gl_FragCoord.xy / volsize.xy, gl_TexCoord[0].z);
	//vec3 pos = vec3(gl_TexCoord[0].xyz);
	
	vec4 col = vec4(0.0);
	
	sample(pos, col);

	//gl_FragColor = vec4(1.0)-col;
	gl_FragColor = col;
}
