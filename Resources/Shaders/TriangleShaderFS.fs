precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_sampler2D;

void main()
{
	gl_FragColor = texture2D(u_sampler2D, v_uv);
}