void main()
{
	// transform vertex position into homogenous clip-space
	gl_Position = ftransform();

	// output texture coordinates for diffuse map
	gl_TexCoord[0] = gl_TextureMatrix[0] *  gl_MultiTexCoord0;	
}
