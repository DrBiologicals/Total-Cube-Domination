// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logutil.cpp
//  Description :   
//  Author      :   
//  Mail        :   
//

// Library Includes

// Local Includes
#include "engine/TotalCubeDomination.h"
#include "engine/input/inputhandler.h"
#include "engine/graphics and sound/modelmanager.h"
#include "engine/graphics and sound/spritemanager.h"
#include "engine/graphics and sound/texturemanager.h"
#include "engine/graphics and sound/lightmanager.h"
#include "engine/graphics and sound/soundmanager.h"
#include "entity structures/player objects/playermanager.h"
#include "entity structures/entitymanager.h"
#include "entity structures/particle/emittermanager.h"
#include "engine/game/collisionmanager.h"
#include "entity structures/player objects/ai/pathfinder.h"
#include "engine/graphics and sound/fontmanager.h"
#include "engine/graphics and sound/billboardmanager.h"
#include "entity structures/player objects/Power up/powerupmanager.h"

// This Include
#include "singletons.h"

// Static Variables

// Static Function Prototypes

// Implementation
void 
DestroySingletons()
{
	CPowerUpManager::DestroyInstance();
	CPathfinder::DestroyInstance();
    CLightManager::DestroyInstance();
    CPlayerManager::DestroyInstance();
    CEmitterManager::DestroyInstance();
	CTotalCubeDomination::DestroyInstance();
	CInputHandler::DestroyInstance();
	CModelManager::DestroyInstance();
    CTextureManager::DestroyInstance();
	CFontManager::DestroyInstance();
    CEntityManager::DestroyInstance();
    CCollisionManager::DestroyInstance();
	CBillboardManager::DestroyInstance();
	CSpriteManager::DestroyInstance();
	CSoundManager::DestroyInstance();
}