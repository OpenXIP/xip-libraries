
void main() {

    gl_FragData[0] = vec4(1.0);

    vec2 fcoord = gl_FragCoord.xy/vec2(512, 512);
    float d = pow(1.0 - length(fcoord - vec2(0.5, 0.5)), 16.0);

    gl_FragData[1] = vec4(d, d, d, 1.0);
}
