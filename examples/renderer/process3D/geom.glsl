#version 120
#extension EXT_gpu_shader4: require
#extension EXT_geometry_shader4: require
#extension NV_geometry_shader4: require
#extension GL_EXT_geometry_shader4: enable

void main(void)
{
	int i;
	for (i = 0; i<gl_VerticesIn; i++)
	{
		gl_Position = gl_PositionIn[i];
		gl_TexCoord[0] = gl_TexCoordIn[i][0];
		gl_Layer = int(gl_TexCoordIn[i][0].w);
		EmitVertex();
	}
	EndPrimitive();
}