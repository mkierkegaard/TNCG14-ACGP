uniform sampler2D testTexture;
uniform float time;

varying vec4 v_color;
varying vec2 v_texCoord;

void main( void )
{
  vec2 temp_texcoord = vec2(v_texCoord.x + 0.1*sin(4.0*v_texCoord.x+time),
                            v_texCoord.y + 0.1*sin(4.0*v_texCoord.y+time));
	gl_FragColor = v_color - texture2D( testTexture, temp_texcoord );

}

