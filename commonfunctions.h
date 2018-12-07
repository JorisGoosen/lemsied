#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <stdlib.h>
#include <time.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <algorithm>

inline float randfloat(float min, float max) { return min+((((float)(rand()%RAND_MAX))/((float)RAND_MAX))* (max-min)); }

inline glm::vec3 randcolor()                            { return glm::vec3(randfloat(0.0f, 1.0f), randfloat(0.0f, 1.0f), randfloat(0.0f, 1.0f));	}
inline glm::vec4 randvec4(glm::vec4 min, glm::vec4 max) { return glm::vec4(randfloat(min.x, max.x), randfloat(min.y, max.y), randfloat(min.z, max.z), randfloat(min.w, max.w)); }
inline glm::vec4 randvec4(float min, float max)         { return glm::vec4(randfloat(min, max), randfloat(min, max), randfloat(min, max), randfloat(min, max)); }
inline glm::vec3 randvec3(float min, float max)         { return glm::vec3(randfloat(min, max), randfloat(min, max), randfloat(min, max)); }

inline void InitRandSeed() { srand(time_t(NULL)); }

inline float unisin(float ang) { return 0.5f + ( 0.5f * sinf(ang) ); }
inline float unicos(float ang) { return 0.5f + ( 0.5f * cosf(ang) ); }

inline glm::vec3 mixCol(glm::vec3 a, glm::vec3 b, float r) { r = std::min(1.0f, std::max(0.0f, r)); return ( a * (1.0f - r) ) + ( b * r ); }

const float pi = 3.14159265359f;

#endif // COMMONFUNCTIONS_H
