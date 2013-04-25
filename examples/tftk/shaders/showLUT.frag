
uniform sampler2D transferFunc1D;
uniform vec2 windowSize;



void main()
{
    // get the density value from the 3D texture
    int shift = 10.0;
    float xCoord = (gl_FragCoord.x/windowSize.x/0.9 - 0.04);
    vec4 data = texture2D(transferFunc1D, vec2(xCoord, 0.5));
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
    gl_FragColor = data; 
    
    if (gl_FragCoord.x/windowSize.x/0.9 <= 0.04)
        gl_FragColor = vec4(0.15, 0.05, 0.05, 1.0);
    else if(xCoord >= 1.0 )
        gl_FragColor = vec4(0.15, 0.05, 0.05, 1.0);
}
