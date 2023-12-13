#version 330 core

layout (location = 0) in vec3 position_attr;
layout (location = 1) in vec3 color_attr;

uniform mat4 u_perspective_matrix;
uniform mat4 u_view_matrix;

out vec3 color;

void main()
{
	color = color_attr;
	vec4 position = vec4(position_attr.x, position_attr.y, position_attr.z, 1.0);
	gl_Position = u_perspective_matrix * u_view_matrix * position;
}