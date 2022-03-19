#shader vertex
#version 330 core

in vec3 position;
out vec3 color;

void main()
{
    gl_Position = vec4(position, 1.0); // see how we directly give a vec3 to vec4's constructor
    color = vec3(position.x + 0.5, 0.0, position.y + 0.5); // set the output variable to a dark-red color
}

#shader fragment
#version 330 core

in vec3 color;
out vec4 out_color;

void main()
{
    out_color = vec4(color, 1.0);
} 