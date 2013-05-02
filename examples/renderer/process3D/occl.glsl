// -*- Mode: c; c-indentation-style: stroustrup; c-basic-offset: 4 -*-

varying vec4 fragCoord;

/*
  Basic Vertex Program
*/

void main(void)
{
    //gl_TexCoord[0] = gl_MultiTexCoord0;
    //gl_TexCoord[0] = gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	fragCoord = gl_Vertex;
    gl_Position = ftransform();
}
