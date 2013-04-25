varying vec4 texCoord0;
varying vec3 vertexNormal;
varying vec3 lightDir;
varying vec3 viewDir;

uniform mat4  rad_boundingModelMatrix;
void main()
{
	// transform vertex position into homogenous clip-space
	//gl_Position = ftransform();

	// output texture coordinates for diffuse map
	texCoord0 = gl_TextureMatrix[0] *  gl_MultiTexCoord0;
	gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;

//	viewDir = normalize(vec3(0, 0, -1) * gl_NormalMatrix);
//	lightDir = normalize(lightRotation * vec3(0, 0, -1) * gl_NormalMatrix);
//	eye = vec3(gl_ModelViewMatrixInverse * vec4(0, 0, 0, 1));
	

	// for now have to multiply texture matrix of the volume stage into gl_Position 
	// to account for transformation to world space to be compatible with rad examiner
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix  * gl_MultiTexCoord0;
	//gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_TextureMatrix[0] * gl_MultiTexCoord0;
}
