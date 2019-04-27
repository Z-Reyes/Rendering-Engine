#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
struct ShadowBucket {
	unsigned int shadow_buffer, shadow_texId;
	glm::mat4 lightV_matrix, lightP_matrix, shadowMVP, shadowMVP2, b;
};

extern ShadowBucket shadowData;