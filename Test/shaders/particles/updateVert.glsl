#version 410

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Velocity;
layout(location = 2) in float size;
layout(location = 3) in float lifeTime;

out vec3 pPosition;
out vec3 pVelocity;
out float pSize;
out float pLifeTime;

uniform float time;
uniform float deltaTime;
uniform float lifeSpan;
uniform float speed;
uniform vec3 emitterPosition;

const float INVERSE_MAX_UINT = 1.0f / 4294967295.0f;

float rand(uint seed, float range) {
	uint i = (seed ^ 12345391u) * 2654435769u;
	i ^= (i << 6u) ^ (i << 26u);
	i *= 2654435769u;
	i += (i << 5u) ^ (i >> 12u);
	return float(range * i) * INVERSE_MAX_UINT;
}

void main() {
	pPosition = Position + Velocity * deltaTime;
	pVelocity = Velocity;
	pLifeTime = lifeTime * deltaTime;
	pSize = size;
	
	if (lifeTime > lifeSpan) {
		uint seed = uint(time * 1000.0) + uint(gl_VertexID);
		pVelocity.x = rand(seed++, 2) - 1;
		pVelocity.y = rand(seed++, 2) - 1;
		pVelocity.z = rand(seed++, 2) - 1;
		pVelocity = normalize(pVelocity) * speed;
		pPosition = emitterPosition;
		pLifeTime = 0;
		pSize = 0;//probably moot;
	}
}