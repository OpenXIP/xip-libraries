

uniform sampler3D volume;
uniform sampler3D DualCTVolume1;
uniform sampler3D DualCTVolume2;
uniform sampler2D transferFunc1D;
varying vec4 texCoord0;


void main()
{

#ifdef VOL1
    vec4 data = texture3D(DualCTVolume1, texCoord0.zxy);
    vec4 color = texture2D(transferFunc1D, data.x);  
    color.rgb *= color.a;
    gl_FragColor = color;	

#elif defined VOL2
    vec4 data = texture3D(DualCTVolume2, texCoord0.zxy);
    vec4 color = texture2D(transferFunc1D, data.x);    
    color.rgb *= color.a;
    gl_FragColor = color;	

#else
    vec4 data = texture3D(volume, texCoord0.zxy);
    vec4 color = texture2D(transferFunc1D, data.x);  
    color.rgb *= color.a;
    gl_FragColor = color;	

#endif

#ifdef SHOW_TF
    color = texture2D(transferFunc1D, vec2(gl_FragCoord.x/500.0, 0.5));      
    gl_FragColor = color;
#endif

}