#shader vertex
#version 330 core
layout (location = 0) in vec4 position; //
layout (location = 1) in vec2 texCoord;
out vec2 v_TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * position;
    v_TexCoords = texCoord;
}  

#shader fragment
#version 330 core
in vec2 v_TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    float red = texture(text, v_TexCoords).r;
    float green = texture(text, v_TexCoords).g;
    float blue  = texture(text, v_TexCoords).b;
    vec4 sampled = vec4(1.0, 1.0, 1.0, red);
    color = vec4(textColor, 1.0) * sampled;
}  