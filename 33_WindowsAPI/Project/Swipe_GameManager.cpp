#include "Framework.h"
#include "Swipe_GameManager.h"

Swipe_GameManager::Swipe_GameManager()
{
	ifstream file("data.txt");

	// Check for saved data
	if (!file.is_open())
		return;

	// Data loaded successfully
	boost::archive::text_iarchive ia(file);
	ia >> gameData;

	file.close();

	prevDataExist = true;

	// Initing GameManager self - TODO (주석 풀기)
	gameState			= gameData.gameState;
	level				= gameData.level;
	bestLevelReached	= gameData.bestLevelReached;
	itemEarned			= gameData.itemEarned;
	ballStartPos		= gameData.ballStartPos;
}

Swipe_GameManager::~Swipe_GameManager()
{
	if (gameData.brickManager)
	{
		delete gameData.brickManager;
		gameData.brickManager = nullptr;
	}

	if (gameData.itemManager)
	{
		delete gameData.itemManager;
		gameData.itemManager = nullptr;
	}
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

