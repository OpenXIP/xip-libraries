



uniform sampler3D DualCTVolume1;
uniform sampler3D DualCTVolume2;

varying vec4 data1;
varying vec4 data2;
varying vec3 vertPos;

void main()
{
    

//    vec4 data = texture2D(transferFunc, gl_FragCoord.xy/500.0);
/*
    if (gl_FragCoord.x <= shift)
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else if((gl_FragCoord.x-10.0)/450.0 >= 1.0 )
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else if (gl_FragCoord.y > 0 && gl_FragCoord.y < 25 )
        gl_FragColor = vec4(data.r, 0.0, 0.0, 1.0);
    else if (gl_FragCoord.y > 25 && gl_FragCoord.y < 50 )
        gl_FragColor = vec4(0.0, data.g, 0.0, 1.0);
    else if (gl_FragCoord.y > 50 && gl_FragCoord.y < 75 )
        gl_FragColor = vec4(0.0, 0.0, data.b, 1.0);
    else if (gl_FragCoord.y > 75 && gl_FragCoord.y < 100 )
        gl_FragColor = vec4(1.0, 1.0, 1.0, data.a);
    else if (gl_FragCoord.y > 100 )
        gl_FragColor = data;       
        */
//    gl_FragColor = data;
    vec4 dat1 = texture3D(DualCTVolume1, vertPos);
    vec4 dat2 = texture3D(DualCTVolume2, vertPos);
    
    if (dat1.x - dat2.x < 0.001)
        gl_FragColor = vec4(1.0, 1.0, 1.0, 0.5);
    else if( vertPos.x < 0.3)
        gl_FragColor = vec4(0.0, 1.0, 1.0, 0.5);
    else if( vertPos.y > 0.9)
        gl_FragColor = vec4(0.0, 0.0, 1.0, 0.5);
    else if( dat1.x < 0.01)
        gl_FragColor = vec4(0.0, 1.0, 0.0, 0.5); 
    else
        gl_FragColor = vec4(1.0, 0.0, 0.0, 0.5); 

}
