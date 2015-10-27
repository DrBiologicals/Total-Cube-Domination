// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   humanplayer.cpp
//  Description :   humanplayer.cppfor implementation of humanplayer.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//
// Library Includes

// Local Includes
#include "tank.h"
#include "playermanager.h"
#include "ai/pathfinder.h"
#include "../../engine/input/inputhandler.h"
#include "../../engine/input/input.h"
#include "../HUD/hud.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/viewport/camera.h"
#include "../../engine/viewport/viewport.h"
#include "../../engine/totalcubedomination.h"


// This Includes
#include "humanplayer.h"

// Static Variables

// Static Function Prototypes

// Implementation

CHumanPlayer::CHumanPlayer()
: m_uiController(0)
, m_pCamera(0)
, m_pHUD(0)
, m_bIsDisabled(false)
, m_fScoutAnimation(0.0f)
, m_fScoutTimer(5.0f)
, m_fAutoAimMax(0.95f)
{
}

CHumanPlayer::~CHumanPlayer()
{
	delete m_pHUD;
	m_pHUD = 0;
}

/*
* 
* @author Michael McQuarrie
* @param _uiControllerID  Id for controller
* @param _iPlayerID The ID of the player
* @param _eTeam the team the player will be on 
* @param _tPlayerSpawnLocation Where the player spawns
* @return bool
*/
bool
CHumanPlayer::Initialise(CTank* _pTank, uint32 _uiControllerID, int32 _iPlayerID, ETeam _eTeam )
{
	//Set Controller ID
	m_uiController = _uiControllerID;

	//Create new player
	m_pHUD = new CHUD();
	uint32 uiHudTextureID = CTextureManager::GetInstance().CreateTexture("textures/hud/hud_textures.png");
	m_pHUD->Initialise(_iPlayerID, uiHudTextureID);

	m_bIsHuman = true;

	CPlayer::Initialise(_pTank, _iPlayerID, _eTeam);

	return (true);
}

/*
* 
* @author Michael McQuarrie / Rigardt de Vries / Auto-aim code by Cameron MacIntosh
* @param _fDeltaTick
* @return void
*/
void
CHumanPlayer::Process(float32 _fDeltaTick)
{
	CPlayer::Process(_fDeltaTick);

	//Checking if it is possible to scout
	bool bIsScouting = false;
	//These are to hold values for the scouting
	float32 fHorizontalScout = 0.0f;
	float32 fVerticalScout = 0.0f;
	
	if((false == m_bIsDisabled)&&(_fDeltaTick>0.0f))
	{
		//Checking if its moving and button held down to scout
		if (CInputHandler::GetInstance().GetControlMagnitude(CONTROL_SCOUT, m_uiController) > 0)
		{
			if(!m_pTank->IsTransitioning())
			{
				//Set Scouting to true
				bIsScouting = true;
				//These are to move the camera during scout mode
				if(CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETRIGHT, m_uiController) > 0)
				{
					//Left
					//Grabing each value and making it bigger to move the camera and make it smooth
					fHorizontalScout = CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETRIGHT, m_uiController) * 20.0f;
				}
				else if(CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETRIGHT, m_uiController) < 0)
				{
					//Right
					fHorizontalScout = CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETRIGHT, m_uiController)* 20.0f;
				}
				if(CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETLEFT, m_uiController) < 0)
				{
					//Down
					fVerticalScout = CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETLEFT, m_uiController)* 20.0f;
				}
				else if(CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETLEFT, m_uiController) > 0)
				{
					//Up
					fVerticalScout = CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETLEFT, m_uiController)* 20.0f;
				}
			}
		}
		//Using an else if statement to make sure if the scouting ability is used you cant move
		else if (CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVEUP, m_uiController) > 0.9)
		{
			m_pTank->Move(_fDeltaTick, DIRECTION_UP);
		}
		else if (CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVEDOWN, m_uiController) < -0.9)
		{
			m_pTank->Move(_fDeltaTick, DIRECTION_DOWN);
		}
		else if (CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVELEFT, m_uiController) < -0.9)
		{
			m_pTank->Move(_fDeltaTick, DIRECTION_LEFT);
		}
		else if (CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVERIGHT, m_uiController) > 0.9)
		{
			m_pTank->Move(_fDeltaTick, DIRECTION_RIGHT);
		}
		
		D3DXVECTOR2 vec2Aim;
		vec2Aim.x = CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETRIGHT, m_uiController);
		vec2Aim.y =-CInputHandler::GetInstance().GetControlMagnitude(CONTROL_TURRETLEFT, m_uiController);
		if (vec2Aim.x != 0.0f || vec2Aim.y != 0.0f)
		{
			
			if (m_pTank->HasShot() == true)
			{
				if (m_pTank->HasAimed() == false)
				{
					m_pTank->SetAimed(true);
				}
			}

			//required for auto-aiming
			D3DXVec2Normalize(&vec2Aim,&vec2Aim);
			CPlayerManager& rPlayerManager = CPlayerManager::GetPlayerManagerInstance();
			CPathfinder& rPathfinder = CPathfinder::GetInstance();
			D3DXVECTOR2 cecrick(10.0f,10.0f);
			D3DXVECTOR2 vec2ThisPos;
			vec2ThisPos = m_pTank->GetPosition2D();
			EFacePosition eThisFace = m_pTank->GetFacePosition();

			float32 fBest = -2.0f; //less than dot product would return
			CTank* pBestTank = 0;
			D3DXVECTOR2 vec2BestAim(0.0f,0.0f);
			float32 fCurrent = 0.0f;
			D3DXVECTOR2 vec2CurrentAim(0.0f,0.0f);
			CTank* pTank;
			int32 i=0;
			//auto aim
			for(i=0; i<8; ++i)
			{
				pTank = rPlayerManager.GetPlayer(i)->GetTank();
				if((eThisFace==pTank->GetFacePosition())&&(m_pTank!=pTank)&&(m_eTeam!=pTank->GetTeam()))
				{
					vec2CurrentAim = pTank->GetPosition2D() - vec2ThisPos;
					D3DXVec2Normalize(&vec2CurrentAim,&vec2CurrentAim);
					fCurrent = D3DXVec2Dot(&vec2Aim, &vec2CurrentAim);
					//if the dot product result is more than the current highest value,
					// and therefore closer
					if(fCurrent>fBest)
					{
						//set the closest enemy tank/ best target
						fBest = fCurrent;
						pBestTank = pTank;
						vec2BestAim = vec2CurrentAim;
					}
				}
			}
			//if auto-aim is possible
			if(fBest>m_fAutoAimMax)
			{
				m_pTank->RotateTurret(vec2BestAim.x, -vec2BestAim.y, _fDeltaTick);
			}
			//else if auto-aim is not possible
			else
			{
				m_pTank->RotateTurret(vec2Aim.x, -vec2Aim.y, _fDeltaTick);
			}
		}
		else
		{
            vec2Aim.x = D3DXVec3Dot(&m_pTank->GetDirection() , &g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Right);
            vec2Aim.y = D3DXVec3Dot(&m_pTank->GetDirection() , &g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Direction);

            m_pTank->RotateTurret(vec2Aim.x, vec2Aim.y, _fDeltaTick);
		}

		if(!bIsScouting)
		{
			if (CInputHandler::GetInstance().GetControlMagnitude(CONTROL_SHOOT, m_uiController) > 0)
			{
				m_pTank->ShootPlasma();
			}
			if (CInputHandler::GetInstance().IsControlTriggered(CONTROL_EMP, m_uiController) == true)
			{
				m_pTank->ShootEMP();
			}
			if (CInputHandler::GetInstance().IsControlTriggered(CONTROL_MINE, m_uiController) == true)
			{
				m_pTank->DropMine();
			}
		}
	}

	D3DXVECTOR3 vec3Up;
	D3DXVECTOR3 vec3Right;
	D3DXVECTOR3 vec3Direction;
	D3DXVECTOR3 vec3Position;
	
    const D3DXMATRIX& krTankMatrix = m_pTank->GetWorldMatrix();

    if (m_pTank->IsTransitioning() )
    {
        vec3Up = m_pTank->GetTransitioningDirection(); 
        vec3Right = m_pTank->GetTransitioningRight();
        vec3Direction = -m_pTank->GetTransitioningUp();
    }
    else
    {
       vec3Right = g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Right;
       vec3Up = g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Direction;
       vec3Direction = -g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Up;
    }

	vec3Position.x = krTankMatrix._41;
	vec3Position.y = krTankMatrix._42;
	vec3Position.z = krTankMatrix._43;

	//This is for a scouting ability
	if(bIsScouting && m_pTank->GetAlive())
	{
		//This is an animation for the scouting ability
		if(m_fScoutAnimation != 20.0f)
		{
			m_fScoutAnimation = m_fScoutAnimation + m_fScoutTimer;
		}
		//Changing the vector to make it view the side
		//Just used the same code as the one in the flag plate and altered it to use the tank instead
		vec3Position = g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Up * (22.5f + m_fScoutAnimation);

		vec3Position += g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Right * (((7.0f * 3.0f) - 21.0f) + fHorizontalScout);

		vec3Position += g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Direction * (((7.0f * 3.0f) - 21.0f) + fVerticalScout);
	}
	else
	{
		//This is the reverse animation
		if(m_fScoutAnimation != 0.0f)
		{
			m_fScoutAnimation = m_fScoutAnimation - m_fScoutTimer;
			//Changing the vector to make it view the side
			vec3Position += g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Up * m_fScoutAnimation;
		}
	}

	if(VIEWPORTSIZE_SMALL == m_pCamera->GetViewport()->GetSizeType())
	{
		vec3Position -= vec3Direction * 20;
	}
	else if(VIEWPORTSIZE_WIDE == m_pCamera->GetViewport()->GetSizeType())
	{
		vec3Position -= vec3Direction * 26;
	}
	else if(VIEWPORTSIZE_LARGE == m_pCamera->GetViewport()->GetSizeType())
	{
		vec3Position -= vec3Direction * 33;
	}
	else
	{
		vec3Position -= vec3Direction * 45;
	}

	if (!m_pTank->GetAlive())
	{
		vec3Position += g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Up * 25.0f;
	}

	//vec3Position += vec3Up * 1.5;

	m_pCamera->SetView3D(vec3Right, vec3Up, vec3Direction, vec3Position);
}

/*
* 
* @author Michael McQuarrie
* @return void
*/
void
CHumanPlayer::Draw()
{

}

/*
* 
* @author Michael McQuarrie
* @return uint32 the controller ID
*/
uint32
CHumanPlayer::GetControllerID()
{
	return(m_uiController);
}

/*
* SetCamera
* @author Rigardt de Vries
* @param _uiID			the ID of the camera
* @return void
*/
void 
CHumanPlayer::SetCamera(uint32 _uiID, uint32 _uiViewportNumber)
{
	m_pCamera = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(_uiViewportNumber)->GetCamera(_uiID);
}

/**
* 
* Returns if the player is disabled or not.
* 
* @author Rebeccah Cox
* @return bool m_bIsDisabled 
*/
bool
CHumanPlayer::GetIfDisabled()
{
	return (m_bIsDisabled);
}

/**
* 
* Set if the player is disabled or not.
* 
* @author Rebeccah Cox
* @param bool _bIsDisabled
* @return void
*/
void
CHumanPlayer::SetIfDisabled(bool _bIsDisabled)
{
	m_bIsDisabled = _bIsDisabled;
}
