

uniform sampler3D DualCTVolume1;
uniform sampler3D DualCTVolume2;

varying vec4 data1;
varying vec4 data2;
varying vec3 vertPos;

void main()
{
    vertPos = gl_Vertex.xyz;

    data1 = texture3D(DualCTVolume1, vertPos);
    data2 = texture3D(DualCTVolume2, vertPos);

	gl_Position = vec4(2.0*data1.x - 1.0, 2.0*data2.x - 1.0, 0.0, 1.0);// vec4(0.0, 0.0, 0.0, 1.0);//
    //gl_Position = vec4(data1.x, data2.x, 0.0, 1.0);
}

// gl_ModelViewProjectionMatrix * gl_Vertex; //
// gl_ProjectionMatrix * vec4(data1.x, data2.x, 0.0, 1.0);//
// gl_ModelViewProjectionMatrix * vec4(data1.x, data2.x, 0.0, 1.0); //