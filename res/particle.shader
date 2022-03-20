#shader vertex
#version 330 core

layout(location = 0) in vec3 in_position;
out vec3 fragPos;

uniform mat4 u_TransformationMatrix;

void main()
{
    gl_Position = u_TransformationMatrix * vec4(in_position, 1.0);
    fragPos = vec3(in_position.x + 0.5, 0.0, in_position.y + 0.5);
}

#shader fragment
#version 330 core

in vec3 fragPos;
layout(location = 0) out vec4 out_color;

uniform vec3 u_Color;
uniform vec2 u_Resolution;

void main()
{
    // vec2 uv = fragPos.xy / u_Resolution;
    // float aspectRatio = u_Resolution.x / u_Resolution.y;
    // uv.x *= aspectRatio;

    float pct = 0.0;
    pct = distance(fragPos.xyz, vec3(0.5));
// 
    vec3 color = vec3(pct);
    if (pct > 0.7)
        discard;

    out_color = vec4(u_Color, 1.0);
}