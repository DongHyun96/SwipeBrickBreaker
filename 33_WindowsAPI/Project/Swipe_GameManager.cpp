#include "Framework.h"
#include "Swipe_GameManager.h"


Swipe_GameManager::Swipe_GameManager()
{
}

Swipe_GameManager::~Swipe_GameManager()
{
}

void Swipe_GameManager::Update()
{
	ballPosSet.clear();
}

void Swipe_GameManager::InitGame()
{
	gameState = INIT;
	level = 0;
	itemEarned = 0;
	ballStartPos = { WIN_WIDTH * 0.5, SWIPE_FLOOR - 11 };
}

