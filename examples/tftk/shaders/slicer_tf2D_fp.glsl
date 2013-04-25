

uniform sampler3D volume;
uniform sampler3D DualCTVolume1;
uniform sampler3D DualCTVolume2;
uniform sampler2D transferFunc2D;
uniform sampler2D transferFunc2DGrad;
varying vec4 texCoord0;
//abs(vec3(0.0,0.0,1.0)-texCoord0.zxy)
#ifdef  TFGRAD
vec3 computegradient()
{
	//samples for forward differences
    vec3 sample1;
    vec3 sample2;
	vec3 offset = vec3(1./128.,0.,0.);
    sample1.x = texture3D(volume, texCoord0.xyz-offset.xyz).x;
    sample2.x = texture3D(volume, texCoord0.xyz+offset.xyz).x;
    sample1.y = texture3D(volume, texCoord0.xyz-offset.yxz).y;
    sample2.y = texture3D(volume, texCoord0.xyz+offset.yxz).y;
    sample1.z = texture3D(volume, texCoord0.xyz-offset.yzx).z;
    sample2.z = texture3D(volume, texCoord0.xyz+offset.yzx).z;

    //forward differences gradient
    //vec3 gradient = data.xxx - sample1;
    //central differences gradient
    vec3 grad = vec3(0.0);
    int limit = 0.81;
    if (sample1.x > limit)
    {
        if (sample1.y > limit)
        {
            if (sample1.z > limit)
            {
                if (sample2.x > limit)
                {
                    if (sample2.y > limit)
                    {
                        if (sample2.z > limit)
                        {
                            grad = sample2 - sample1;
                        }
                    }
                }
            }
        }
    }


    return grad;	
}

#elif defined  TFGRAD_CT
vec3 computegradient()
{
	//samples for forward differences
    vec3 sample1;
    vec3 sample2;
	vec3 offset = vec3(1./128,0.,0.);
    sample1.x = texture3D(DualCTVolume1, texCoord0.xyz-offset.xyz).x;
    sample2.x = texture3D(DualCTVolume1, texCoord0.xyz+offset.xyz).x;
    sample1.y = texture3D(DualCTVolume1, texCoord0.xyz-offset.yxz).y;
    sample2.y = texture3D(DualCTVolume1, texCoord0.xyz+offset.yxz).y;
    sample1.z = texture3D(DualCTVolume1, texCoord0.xyz-offset.yzx).z;
    sample2.z = texture3D(DualCTVolume1, texCoord0.xyz+offset.yzx).z;

    //forward differences gradient
    //vec3 gradient = data.xxx - sample1;
    //central differences gradient
    return sample2 - sample1;	
}

#elif defined  TF_DUAL_GRAD
vec3 computegradient()
{
	//samples for forward differences
    vec3 sample1;
    vec3 sample2;
	vec3 offset = vec3(1./128,0.,0.);
    sample1.x = texture3D(DualCTVolume1, texCoord0.xyz-offset.xyz).x;
    sample2.x = texture3D(DualCTVolume1, texCoord0.xyz+offset.xyz).x;
    sample1.y = texture3D(DualCTVolume1, texCoord0.xyz-offset.yxz).y;
    sample2.y = texture3D(DualCTVolume1, texCoord0.xyz+offset.yxz).y;
    sample1.z = texture3D(DualCTVolume1, texCoord0.xyz-offset.yzx).z;
    sample2.z = texture3D(DualCTVolume1, texCoord0.xyz+offset.yzx).z;

    //forward differences gradient
    //vec3 gradient = data.xxx - sample1;
    //central differences gradient
    return sample2 - sample1;	
}

#elif defined  TF_GRAD_DIFF
vec3 computegradient()
{
	//samples for forward differences
    vec3 sample1;
    vec3 sample2;
	vec3 offset = vec3(1./128,0.,0.);
    sample1.x = texture3D(DualCTVolume1, texCoord0.xyz-offset.xyz).x;
    sample2.x = texture3D(DualCTVolume1, texCoord0.xyz+offset.xyz).x;
    sample1.y = texture3D(DualCTVolume1, texCoord0.xyz-offset.yxz).y;
    sample2.y = texture3D(DualCTVolume1, texCoord0.xyz+offset.yxz).y;
    sample1.z = texture3D(DualCTVolume1, texCoord0.xyz-offset.yzx).z;
    sample2.z = texture3D(DualCTVolume1, texCoord0.xyz+offset.yzx).z;

    //forward differences gradient
    //vec3 gradient = data.xxx - sample1;
    //central differences gradient
    return sample2 - sample1;	
}

vec3 computegradient2()
{
	//samples for forward differences
    vec3 sample1;
    vec3 sample2;
	vec3 offset = vec3(1./128,0.,0.);
    sample1.x = texture3D(DualCTVolume2, texCoord0.xyz-offset.xyz).x;
    sample2.x = texture3D(DualCTVolume2, texCoord0.xyz+offset.xyz).x;
    sample1.y = texture3D(DualCTVolume2, texCoord0.xyz-offset.yxz).y;
    sample2.y = texture3D(DualCTVolume2, texCoord0.xyz+offset.yxz).y;
    sample1.z = texture3D(DualCTVolume2, texCoord0.xyz-offset.yzx).z;
    sample2.z = texture3D(DualCTVolume2, texCoord0.xyz+offset.yzx).z;

    //forward differences gradient
    //vec3 gradient = data.xxx - sample1;
    //central differences gradient
    return sample2 - sample1;	
}

#else
vec3 computegradient()
{
    return vec3(1.0);
}
#endif

vec4 shade( vec4 data,
            vec4 shadingParam)
{
	vec4 color;
	vec3 lightdir = normalize(vec3(-0.5, -0.5, -0.5));
	vec3 halfway = lightdir;

    //central differences gradient
    vec3 gradient = computegradient();
    float l = length(gradient)/sqrt(3.0);

    // make a lookup in the transfer function texture
    vec2 lookup = vec2(data.x, l);
    color = texture2D(transferFunc2DGrad, lookup);
    vec4 temp = color;

    if (l > .01 && l < 0.5)
    {
        //normalize gradient
		gradient = normalize(gradient);

        float diffuse =  abs(dot(lightdir, gradient));
        color.a *= pow((1.0 - diffuse), 2.0);

        // assuming headlight, i.e. camerapos == lightpos
        float specular = pow(abs(dot(halfway, gradient)), shadingParam.w);
		float gradMag = pow(diffuse, 0.5);
        color.rgb = ((shadingParam.x + shadingParam.y * diffuse) * color.rgb +
                    shadingParam.z * specular * color.a)*gradMag + color.rgb*(1.0 - gradMag);
        color += 0.6*temp;
    }
    else
    {
        color += temp;
	    //color.a = 0.0;
    }

    //color += temp;
    
    //color.rgb *= color.a;
    

    return color;
}




void main()
{

#ifdef VOL1
    vec4 data = texture3D(DualCTVolume1, texCoord0.xyz);
    vec4 color = texture2D(transferFunc2D, vec2(data.x, data.x));    
	
#elif defined  VOL2
    vec4 data = texture3D(DualCTVolume2, texCoord0.xyz);
    vec4 color = texture2D(transferFunc2D, vec2(data.x, data.x )); 


#elif defined  TFGRAD
    vec4 data = texture3D(volume, texCoord0.xyz);
    //vec4 color = texture2D(transferFunc2D, vec2(data.x, clamp( length(computegradient()), 0.0, 1.0)));
    vec4 color = shade(data, vec4(0.7, 0.7, 0.5, 0.5));
    color.rgb *= color.a;

#elif defined  TFGRAD_CT
    vec4 data = texture3D(DualCTVolume1, texCoord0.xyz);
    //vec4 color = texture2D(transferFunc2D, vec2(data.x, clamp( length(computegradient()), 0.0, 1.0)));
    vec4 color = shade(data, vec4(0.7, 0.7, 0.5, 0.5));
    color.rgb *= color.a;

#elif defined  TF_DUAL_GRAD
    vec4 data  = texture3D(DualCTVolume1, texCoord0.xyz);
    vec4 data2 = texture3D(DualCTVolume2, texCoord0.xyz);
    vec4 dualcolor = texture2D(transferFunc2D, vec2(data.x, data2.x)); 
    vec4 gradcolor = shade(data, vec4(0.7, 0.7, 0.5, 0.5));
    gradcolor.rgb *=gradcolor.a;
    vec4 color = dualcolor;

    color.rgb = (gradcolor.rgb + 1.0*dualcolor.rgb)/5.0;

    if (dualcolor.a < 0.025)
        color.a += gradcolor.a;  
	//color = gradcolor;

#elif defined  TF_DIFF    
    vec4 data  = texture3D(DualCTVolume1, texCoord0.xyz);
    vec4 data2 = texture3D(DualCTVolume2, texCoord0.xyz);
    vec4 color = texture2D(transferFunc2D, vec2(data.x, 0.5 + (data2.x - data.x)) ); 
    
    if (data.x <= 0.001 || data2.x <= 0.001)
        color = vec4(0.0);
   
    color.rgb *= color.a;

#elif defined  TF_DIFF2    
    vec4 data  = texture3D(DualCTVolume1, texCoord0.xyz);
    vec4 data2 = texture3D(DualCTVolume2, texCoord0.xyz);
    vec4 color = texture2D(transferFunc2D, vec2(data2.x, 0.5 + (data.x - data2.x)) ); 
    
    if (data.x <= 0.001 || data2.x <= 0.001)
        color = vec4(0.0);
   
    color.rgb *= color.a;

#elif defined  TF_GRAD_DIFF 
    vec3 gradVol1 = computegradient();
    vec3 gradVol2 = computegradient2();

    vec4 data  = texture3D(DualCTVolume1, texCoord0.xyz);
    vec4 data2 = texture3D(DualCTVolume2, texCoord0.xyz);

    vec4 color = texture2D(transferFunc2D, vec2(data.x, 0.5 + (length(gradVol2) - length(gradVol1))) );
    //vec4 color = texture2D(transferFunc2D, vec2(length(gradVol1), length(gradVol1)) ); 
    
    if (data.x <= 0.001 || data2.x <= 0.001)
        color = vec4(0.0);
   
    color.rgb *= color.a;


#else 
    vec4 data  = texture3D(DualCTVolume1, texCoord0.xyz);
    vec4 data2 = texture3D(DualCTVolume2, texCoord0.xyz);
    vec4 color = texture2D(transferFunc2D, vec2(data.x, data2.x)); 
    color.rgb *= color.a;

#endif

    //color.rgb *= color.a;
    gl_FragColor = color;

}