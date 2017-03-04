precision mediump float;

varying vec4 f_Color;
varying vec2 v_texCoord;

uniform sampler2D s_texture;
uniform int paused;
uniform float screen_size;

void main()
{
    float delta = 1.0/screen_size;

    if(paused != 0){
        gl_FragColor = texture2D(s_texture, v_texCoord);
        return;
    }

    float y_up = fract(v_texCoord.y + delta) ;
    float y_down = fract(v_texCoord.y - delta);
    float x_right = fract(v_texCoord.x + delta);
    float x_left = fract(v_texCoord.x - delta);

    vec2 up = vec2(v_texCoord.x, y_up);
    vec2 down = vec2(v_texCoord.x, y_down);
    vec2 left = vec2(x_left, v_texCoord.y);
    vec2 right = vec2(x_right, v_texCoord.y);
    vec2 up_right = vec2(x_right, y_up);
    vec2 up_left = vec2(x_left, y_up);
    vec2 down_left = vec2(x_left, y_down);
    vec2 down_right = vec2(x_right, y_down);





    vec4 neighbours = texture2D(s_texture, up) +  texture2D(s_texture, down) + texture2D(s_texture, left) +
    texture2D(s_texture, right) +
    texture2D(s_texture, up_right) + texture2D(s_texture, up_left) +
     texture2D(s_texture, down_right) + texture2D(s_texture, down_left);
    int n = int(ceil(neighbours.x));
    int k = int(ceil(texture2D(s_texture, v_texCoord).x));

    if(n == 3){
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        return;
    }
    if(n + k == 3){
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        return;
    }
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    return;
}