#pragma once

enum GameState
{
	INIT,
	PLAYING,
	GAMEOVER
};

enum AnimState
{
	IDLE,
	SPAWNING,
	POSITIONING
};

class Swipe_BrickManager;
class Swipe_ItemManager;

struct Swipe_GameData
{
	Swipe_GameData() {}

	Swipe_GameData(
		GameState gameState,
		UINT level,
		UINT bestLevelReached,
		UINT itemEarned,
		Point ballStartPos,
		Swipe_BrickManager* brickMgr, Swipe_ItemManager* itemMgr)
		:
		gameState(gameState),
		level(level),
		bestLevelReached(bestLevelReached),
		itemEarned(itemEarned),
		ballStartPos(ballStartPos),
		brickManager(brickMgr), itemManager(itemMgr)
	{
	}

	~Swipe_GameData()
	{
	}


	// GameManager data
	GameState gameState;
	UINT level;
	UINT bestLevelReached;
	UINT itemEarned;
	Point ballStartPos;

	// Brick data
	Swipe_BrickManager* brickManager = nullptr;

	// Item data
	Swipe_ItemManager* itemManager = nullptr;

	template <class Archive>
	void serialize(Archive& ar, const UINT version)
	{
		// GameManager Data
		ar& gameState;
		ar& level;
		ar& bestLevelReached;
		ar& itemEarned;
		ar& ballStartPos;

		ar& brickManager; // Brick Data
		ar& itemManager; // Item Data
	}
};

class Swipe_GameManager
{
private:

	Swipe_GameManager();
	~Swipe_GameManager();

public:
	
	static Swipe_GameManager* GetInst()
	{
		static Swipe_GameManager singleton;
		return &singleton;
	}

public:

	void Update();

	const GameState& GetGameState() const { return gameState; }
	void SetGameState(const GameState& gameState) { this->gameState = gameState; }

	UINT GetLevel() const { return level; }
	void AddLevel() { level++; }

	const UINT GetItemEarned() const { return itemEarned; }
	void AddItemEarned() { itemEarned++; }
	void SetItemEarned(const UINT& itemEarned) { this->itemEarned = itemEarned; }

	void SetBallStartPos(const Point& point) { ballStartPos = point; }
	const Point& GetBallStartPos() const { return ballStartPos; }

	set<Point>& GetBallPosSet() { return ballPosSet; }

	UINT GetBestLevelReached() const { return bestLevelReached; }
	void SetBestLevelReached(const UINT& level) { this->bestLevelReached = level; }

public:

	/// <summary> R 누를 때 재시작 시 사용  </summary>
	void InitGame();

public:

	const bool& PrevDataExist() const { return prevDataExist; }
	const Swipe_GameData& GetGameData() const { return gameData; }

	template <class Archive>
	void serialize(Archive& ar, const UINT version);

private:

	bool prevDataExist = false;
	Swipe_GameData gameData{};

private:

	GameState gameState = INIT;

	UINT level = 0;
	UINT bestLevelReached = 0;

	UINT itemEarned = 0;

	Point ballStartPos = { WIN_WIDTH * 0.5, SWIPE_FLOOR - 11 };

	set<Point> ballPosSet = {}; // 모든 fieldBall들의 position을 담을 것임
};

template<class Archive>
inline void Swipe_GameManager::serialize(Archive& ar, const UINT version)
{
	ar& gameState;
	ar& level;
	ar& bestLevelReached;
	ar& itemEarned;
	ar& ballStartPos;
}
