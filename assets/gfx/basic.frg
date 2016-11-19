#version 130
uniform sampler2D texture0;
uniform vec4 Color = vec4(1.0,1.0,1.0,1.0);
in vec2 texCoord;
out vec4 outColor;
void main(void) {
	vec2 coord = texCoord;
	outColor = texture(texture0, coord);
	}

