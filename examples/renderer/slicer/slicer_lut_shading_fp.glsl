varying vec3 lightDir;
varying vec3 viewDir;
uniform sampler3D volume;
uniform sampler2D lut;
uniform int width;
uniform int height;
uniform int depth;

vec3 computeGradient()
{
	//samples for forward differences
    vec3 sample1;
    vec3 sample2;
	vec4 offset = vec4(1.0/width, 1.0/height, 1.0/depth, 0.0);
    sample1.x = texture3D(volume, gl_TexCoord[0].xyz-offset.xww).x;
    sample2.x = texture3D(volume, gl_TexCoord[0].xyz+offset.xww).x;
    sample1.y = texture3D(volume, gl_TexCoord[0].xyz-offset.wyw).y;
    sample2.y = texture3D(volume, gl_TexCoord[0].xyz+offset.wyw).y;
    sample1.z = texture3D(volume, gl_TexCoord[0].xyz-offset.wwz).z;
    sample2.z = texture3D(volume, gl_TexCoord[0].xyz+offset.wwz).z;

    //central differences gradient
    return normalize(gl_NormalMatrix*(sample2 - sample1));	
}

vec4 shading(vec3 N, vec3 V, vec3 L, vec4 color)
{
	// ambient
	vec3 Ka = vec3(0.4, 0.4, 0.4);
	// diffuse
	vec3 Kd = vec3(0.6, 0.6, 0.6);
	// specular
	vec3 Ks = vec3(0.2, 0.2, 0.2);
	float n = 64.0;
		
	vec3 H = normalize(L+V);

	vec3 ambient = Ka * color.rgb;

	float diffuseLight = max(dot(L, N), 0.0);
	vec3 diffuse = Kd * color.rgb * diffuseLight;

	float specularLight = pow(max(-dot(H, N), 0.0), n);
	vec3 specular = Ks * color.a * specularLight;

	vec4 result;
	result.rgb = ambient + diffuse + specular;
	result.a = color.a;

	return result;
}

void main()
{
	float density = texture3D(volume, gl_TexCoord[0].xyz).x;	
	vec4 color = texture2D(lut, vec2(density, 0.5));
	vec3 gradient = computeGradient();
	gl_FragColor = shading(gradient, viewDir, lightDir, color);
}
