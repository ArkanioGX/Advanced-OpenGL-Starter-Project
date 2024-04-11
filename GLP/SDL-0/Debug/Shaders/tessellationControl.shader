#version 450 core

layout (vertices = 3) out;

uniform float inTessLevel;
uniform float outTessLevel;

void main(void)
{
    if(gl_InvocationID == 0) {
		gl_TessLevelInner[0] = inTessLevel;
		gl_TessLevelOuter[0] = outTessLevel;
		gl_TessLevelOuter[1] = outTessLevel;
		gl_TessLevelOuter[2] = outTessLevel;
	}
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
