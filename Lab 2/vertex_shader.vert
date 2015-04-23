uniform float time;
// uniform sampler2D testTexture;
uniform vec4 center;

varying vec4 v_color;
varying vec2 v_texCoord;

void main( void )
{
#if 0
    vec4 pos = vec4(gl_Vertex.xyz +
                    gl_Normal * 0.1 * sin(10.0*(gl_Vertex.z + time)),
                    gl_Vertex.w);
#else
    vec4 pos = gl_Vertex;
    vec3 dir = pos.xyz - center.xyz;
    pos.xyz += 2.0 * normalize(dir) * exp(-center.w * length(dir));
#endif
    
	gl_Position = gl_ModelViewProjectionMatrix * pos;
	
	v_texCoord = gl_MultiTexCoord0.xy;

	v_color = vec4(vec3(0.5) + 0.5 * gl_Vertex.xyz, 1.0);

}

