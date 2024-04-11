#version 450 core

void main(void)
{
	const vec4 vertices[4] = vec4[]
	(
        vec4(1, -1, 0.5, 1.0),
        vec4(-1, -1, 0.5, 1.0),
        vec4(1, 1, 0.5, 1.0),
        vec4(-1, 1, 0.5, 1.0)
    );

	gl_Position = vertices[gl_VertexID];
}
