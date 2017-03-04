precision mediump float;

varying vec4 f_Color;
varying vec2 v_texCoord;

uniform sampler2D s_texture;
void main()
{

    gl_FragColor = texture2D(s_texture, v_texCoord);
    //gl_FragColor = f_Color;
}