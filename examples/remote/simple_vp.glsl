//varying vec4 texCoord0;
//varying vec3 vertexNormal;
varying vec3 lightDir;
varying vec3 viewDir;

void main()
{
	// transform vertex position into eye-space
	gl_Position = ftransform();

	// output texture coordinates for diffuse map
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	// view direction in eye-space
	viewDir = normalize(gl_NormalMatrix * vec3(0, 0, 1));

    lightDir = normalize(gl_NormalMatrix * vec3(0, 0, 1));
    	
	//	lightDir = normalize(lightRotation * vec3(0, 0, -1) * gl_NormalMatrix);
//	eye = vec3(gl_ModelViewMatrixInverse * vec4(0, 0, 0, 1));
	
	// for now have to multiply texture matrix of the volume stage into gl_Position 
	// to account for transformation to world space to be compatible with rad examiner
	//gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix  * gl_MultiTexCoord0;
	//gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
