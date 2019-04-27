#pragma once
struct ambient_positional_light {
	float ambientAura[4];
	float ambientLight[4];
	float diffuseLight[4];
	float specularLight[4];
	float position[3];
};

extern ambient_positional_light globalLight;