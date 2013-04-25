

void main()
{
	gl_Position = ftransform();//gl_ModelviewProjectionMatrix() * gl_Vertex ;//* vec4(data1.x, data2.x, 0.0, 0.0);
}
