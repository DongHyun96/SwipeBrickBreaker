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

public:
	void InitGame();

private:
	GameState gameState = INIT;
	UINT level = 0;
	
	UINT itemEarned = 0;
	//UINT itemEarned = 5; // testing

	Point ballStartPos = { WIN_WIDTH * 0.5, SWIPE_FLOOR - 11 };

	set<Point> ballPosSet = {}; // 모든 fieldBall들의 position을 담을 것임
};
