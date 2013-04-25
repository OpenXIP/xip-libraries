
uniform sampler2D texture;

void main() {

    vec4 sample = texture2D(texture, gl_TexCoord[0].xy);

#ifdef TEXCOORDS
    gl_FragColor = vec4( gl_TexCoord[0].x, gl_TexCoord[0].y, 0.0, 1.0);
    return;
#endif

#ifdef FRAGDATA
    gl_FragData[0] = vec4( 1.0, 0.0, 0.0, 1.0);
    return;
#endif

    gl_FragColor = vec4( sample.rgb, 1.0);
}
