#version 330

in vec2 frag_uv;
in vec4 frag_color;
uniform sampler2D u_color_map;

void main()
{
	gl_FragColor= texture(u_color_map, frag_uv) * frag_color;
}