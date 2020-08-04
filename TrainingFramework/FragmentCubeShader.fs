precision mediump float;
uniform samplerCube u_samplerCube;
varying vec4 v_pos;

void main()
{
	gl_FragColor = textureCube(u_samplerCube, v_pos.xyz);
}