#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include "commonfunctions.h"

#define PERLIN_NUM_GRADIENTS 1024

class Perlin
{
public:
                Perlin();
				~Perlin();
	void		Init();
		
    glm::mediump_vec3   GetGradient(glm::ivec3 loc);
    float 		GetIniqoQuilesNoise(glm::vec3 x);

	static Perlin * thePerlin();
	static Perlin * _Perlin;
	
private:
	void		InitGradients();
	void		InitPermutationTable();
    int			FoldingFunction(glm::ivec3 ijk) { return (*PermutationTable)[(*PermutationTable)[(*PermutationTable)[ijk[0]] + ijk[1]] + ijk[2]]; }

    std::vector<glm::mediump_vec3> *RandomGradients = NULL;
    std::vector<int>				*PermutationTable = NULL;
    
};


