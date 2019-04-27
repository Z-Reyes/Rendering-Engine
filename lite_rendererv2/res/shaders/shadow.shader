#shader vertex
#version 430
layout(location = 0) in vec3 vertPos;
uniform mat4 shadowMVP;

void main(void)
{
	gl_Position = shadowMVP * vec4(vertPos, 1.0);
}

#shader fragment
#version 430

// Ouput data
layout(location = 0) out float fragmentdepth;

void main() {
	// Not really needed, OpenGL does it anyway
	fragmentdepth = gl_FragCoord.z;
}