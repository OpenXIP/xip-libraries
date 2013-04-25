varying vec3 lightDir;
varying vec3 viewDir;
varying vec3 v;

void main()
{
	// transform vertex position into eye-space
	gl_Position = ftransform();
	v = gl_ModelViewMatrix * gl_Vertex;

	// output texture coordinates for diffuse map
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	// view direction in eye-space
	viewDir = normalize(gl_NormalMatrix * vec3(0, 0, 1));
    lightDir = normalize(gl_NormalMatrix * vec3(0, 0, 1));
}
