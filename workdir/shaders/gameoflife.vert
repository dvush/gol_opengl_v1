attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_Texture;

varying vec4 f_Color;
varying vec2 v_texCoord;

void main()
{

    gl_Position = a_Position;
    f_Color = a_Color;
    v_texCoord = a_Texture;
}