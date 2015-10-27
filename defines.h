//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   defines.h
//  Description :   defines declaration file.
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#pragma once

#ifndef __DEFINES_H__
#define __DEFINES_H__

// Library Includes
#include <d3dx9.h>
#define SystemFunction036 NTAPI SystemFunction036
#include <NTSecAPI.h>
#undef SystemFunction036
#ifdef _DEBUG
#include <cassert>
#endif // _DEBUG

// Local Includes

// Types
typedef char				int8;
typedef unsigned char		uint8;
typedef short				int16;
typedef unsigned short		uint16;
typedef int					int32;
typedef unsigned int		uint32;
typedef __int64				int64;
typedef unsigned __int64	uint64;
typedef float				float32;
typedef double				float64;

#define RENDERTYPE_OPAQUE		0x0	// Flag for non alpha blended objects
#define RENDERTYPE_ALPHABLEND		0x1	// Flag for alpha blended objects
#define RENDERTYPE_3DCOORDS		0x0	// Flag for objects in 3D coordinates
#define RENDERTYPE_SCREENALIGNED	0x2	// Flag for objects in screen coordinates

#define BAD_ID ((uint32)(-1))

const uint8 g_uiSideLength = 15;
const uint8 g_uiSideNodeTotal = g_uiSideLength* g_uiSideLength;
const uint8 g_uiTileSize = 3;	//a tile is 3 units big
const uint32 g_uiTileTotal = g_uiSideNodeTotal * 6;
const uint32 g_uiTilePlane = g_uiTileTotal*g_uiTileTotal;
const uint32 g_uiTileHeight = g_uiSideLength*3;
const uint32 g_uiTileWidth = g_uiSideLength*4;

// Prototypes
enum EAIState
{
	AI_STATE_IDLE,
	AI_STATE_GETFLAG,
	AI_STATE_CAPTUREFLAG,
	AI_STATE_DISABLED,
	AI_STATE_PROTECTFLAG,
	AI_STATE_PROTECTPLAYER,
	AI_STATE_RETRIEVEFLAG,
	AI_STATE_NULL
};

enum EWallSide
{
    WALL_SIDE_FRONT,
    WALL_SIDE_BACK,
    WALL_SIDE_LEFT,
    WALL_SIDE_RIGHT,
    WALL_SIDE_MAX
};

enum ETowerAIState
{
	TOWERAI_STATE_IDLE,
	TOWERAI_STATE_DISABLED,
	TOWERAI_STATE_ATTACK,
	TOWERAI_STATE_NONE
};

enum ELogMessageType
{
	LOG_MESSAGE_INIT,
    LOG_MESSAGE_PATHS,
	LOG_MESSAGE_SOUND,
	LOG_MESSAGE_OUTPUT,
	LOG_MESSAGE_TEST,
	LOG_MESSAGE_MAX
};

enum EFacePosition
{
	// Edited by Rigardt de Vries
	FACE_TOP = 0,
	FACE_BOTTOM,
	FACE_FRONT,
	FACE_BACK,
	FACE_LEFT,
	FACE_RIGHT,
	FACE_NONE
};

enum ETeam
{ //Edited by Michael McQuarrie
	TEAM_NEUTRAL = 0,
	TEAM_GREEN,
	TEAM_PURPLE
};

enum ETileType
{
	TILE_NORMAL,
	TILE_WALL,
	TILE_TOWER,
	TILE_BB,
	TILE_FLAME,
	TILE_AMMO,
	TILE_FLAG,
	TILE_MAG,
	TILE_NONE
};

enum EFlagState
{
	FLAG_AT_BASE,
	FLAG_ON_PLAYER,
    FLAG_ON_FLOOR
};

#ifdef _DEBUG
enum ECheatMode
{
	CHEAT_INVINCIBILITY,
	CHEAT_NEVER_ENDING_GAME,
	CHEAT_INVISIBILITY
};
#endif // _DEBUG

struct TPoint
{
	//Edited by Michael McQuarrie
	D3DXVECTOR3 vec3Point;
	EFacePosition eFacePosition;
};

struct TUpAndRightVecs
{
	D3DXVECTOR3 vec3Direction;
	D3DXVECTOR3 vec3Right;
	D3DXVECTOR3 vec3Up;
};

const TUpAndRightVecs g_atUpRightDirectionVecs[6] =
{
	{D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f) },
	{D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f) },
	{D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f) },
	{D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f) },
	{D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f) },
	{D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f) }
};

const D3DXQUATERNION g_aquatFaceQuaternions[6] = 
{
	D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f),
	D3DXQUATERNION(0.0f, 0.0f, 1.0f, 0.0f),
	D3DXQUATERNION(-0.707107f, 0.0f, 0.0f, 0.707107f),
	D3DXQUATERNION(0.0f, 0.707107f, 0.707107f, 0.0f),
	D3DXQUATERNION(0.5f, -0.5f, -0.5f, -0.5f),
	D3DXQUATERNION(0.5f, 0.5f, 0.5f, -0.5f),
};

enum EFaceTransition
{
    TRANSITION_FRONT_TOP = 0,
    TRANSITION_FRONT_LEFT,
    TRANSITION_FRONT_RIGHT,
    TRANSITION_BACK_LEFT,
    TRANSITION_BACK_RIGHT,
    TRANSITION_BACK_BOTTOM,
    TRANSITION_MAX
};

enum EFileTileType
{
	FTILE_EMPTY = 0,
	FTILE_WALL,
	FTILE_BARRIER,
	FTILE_FLAME_GRATE,
	FTILE_AMMO,
	FTILE_MAG_PLATE,
	FTILE_PLAYER_SPAWN,
	FTILE_POWER_SPAWN,
	FTILE_TOWER,
	FTILE_FLAG_PLATE,
};

enum EFileOwner
{
	FOWNER_NONE = 0,
	FOWNER_TEAM_GREEN,
	FOWNER_TEAM_PURPLE,
	FOWNER_NEUTRAL
};

enum EFileDirection
{
	DIR_LEFT = 0,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
};

enum EEdgeBlock
{
    BLOCK_LEFT_TOP = 0,
    BLOCK_BACK_TOP,
    BLOCK_RIGHT_TOP,
    BLOCK_LEFT_BOTTOM,
    BLOCK_FRONT_BOTTOM,
    BLOCK_RIGHT_BOTTOM,
    BLOCK_MAX
};

enum EPIC
{
    PIC_NO,
    PIC_BULLET_SPEED,
    PIC_MOVE_SPEED,
    PIC_BULLET_DAMAGE,
    PIC_EXPLODE_RADIUS,
    PIC_SHIELD
};

enum EDirection
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_NONE
};

enum EParticleType
{
	PARTICLE_NO,
	PARTICLE_FLAME,
	PARTICLE_EXPLODE,
	PARTICLE_FLAG,
    PARTICLE_SPIRAL,
	PARTICLE_BULLET_TRAIL,
	PARTICLE_BULLET_WALL,
	PARTICLE_PIC
};

struct TSPT
{
	float32 aCost[6][g_uiSideNodeTotal];
};

struct TIPoint
{
	int32 x;
	int32 y;
};

struct TNode
{
	int32 iX;
	int32 iY;
	EFacePosition eFace;
};

/**
* Returns a float between 0.0f and 1.0f
*
* @author	Cameron MacIntosh
**/
inline float32 RandomFloat()
{
	BYTE pbData[4];
	uint32 ui;
	if (!RtlGenRandom(pbData, 4)) {
		/* Handle error */
		return (0.0f);
	} else {
		memcpy(&ui, pbData, 4);
		return(static_cast<float32>(ui/(INT_MAX+0.0f))*0.5f);
	}
}

#endif // __DEFINES_H__