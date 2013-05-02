// Local Ambient Occlusion Volume

// textures
uniform sampler3D volume;
//uniform sampler1D clut;
uniform sampler2D lut;

uniform vec3 volsize;
uniform vec3 lightpos;
uniform vec3 lightpos2;
uniform int  raycount;
uniform float radius;

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
	vec3 _lightpos[2];
	_lightpos[0] = lightpos;
	_lightpos[1] = lightpos2;
	
	vec3 dir;
	
	int numsteps = 20;
	// radius = .1;
	float startoffs = 0.5;
	float mindelta = radius / numsteps;
	float distance = mindelta * startoffs;
	vec3 offset;
	
	//int raycount = 2;
		
	float newOpac[2];
	//newOpac[0] = 0.0;
	//newOpac[1] = 0.0;
		
	float opac;
	float finalamb = 0.0;
	float intensity = 1.0 / float(numsteps);
	
	for (int x = 0; x < raycount; x++) {
		newOpac[x] = 1.0;
		dir = (vec3(_lightpos[x]) - vec3(pos));
		dir = normalize(dir);
		vec4 col = vec4(intensity);
		vec4 amb = vec4(0.0);
		
		for (int i = 0; i < numsteps; i++)
		{
			distance += mindelta;
			offset = distance * dir;
			sample_out(pos, offset, opac);
			col.a = texture2D(lut, vec2(opac)).a;
			//col.a = 1.0 - pow(1.0 - col.a, 0.2); 		// vielleicht nicht
			//amb += (1.0 - amb.a) * col;
			 newOpac[x] *= 1.0 - col.a;
			 //newOpac[x] *= 1.0 - opac;
			//newOpac[x] += (1.0 - newOpac[x])*col;
		}	
		distance = mindelta * startoffs;
		//finalamb += amb.r; // newOpac[x];
		finalamb += newOpac[x];
	}

	sum = vec4(finalamb);
}


void main()
{
	volsize = vec3( 160.0, 430.0, 183.0);
	 vec3 pos = vec3(gl_FragCoord.xy / volsize.xy, gl_TexCoord[0].z);
	//vec3 pos = vec3(gl_TexCoord[0].xyz);
	
	vec4 col = vec4(0.0);
	
	sample(pos, col);

	// gl_FragColor = vec4(1.0)-col;
	 gl_FragColor = col;
}
