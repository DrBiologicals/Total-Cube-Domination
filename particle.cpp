#include "entity structures/particle/particle.h"

bool 
TParticle::operator<(const TParticle& _kr)
{
	return (fDepth > _kr.fDepth);
}