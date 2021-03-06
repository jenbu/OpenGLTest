#shader vertex
#version 330 core
layout (location = 0) in vec4 position; //
layout (location = 1) in vec2 texCoord;
out vec2 v_TexCoords;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoords = texCoord;
}  

#shader fragment
#version 330 core
in vec2 v_TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 u_Color;

void main()
{    
    float red = texture(text, v_TexCoords).r;
    float green = texture(text, v_TexCoords).g;
    float blue  = texture(text, v_TexCoords).b;
    vec4 sampled = vec4(1.0, 1.0, 1.0, red);
    color = u_Color * sampled;
}  