#pragma once

#define BALL_CNT_COLOR  RGB(92, 172, 242)
#define LEVEL_POS		Point(WIN_CENTER.x, SWIPE_CEIL - 30)

class Swipe_Brick;

class Swipe_UIManager
{
private:
	Swipe_UIManager();
	~Swipe_UIManager();

public:
	static Swipe_UIManager* GetInst()
	{
		static Swipe_UIManager singleton;
		return &singleton;
	}

	void Update();
	void Render(HDC hdc);
	
	void RenderPlayerDir(HDC hdc);

public:
	void AddBallCnt(const int& amount) { ballCnt += amount; }

	void SetBallCnt(const UINT& cnt) { ballCnt = cnt; }
	void SetBallCnt(const UINT& cnt, const float& xPos);
	void SetBallCntPosX(const float& xPos) { ballCntPos.x = xPos; }

	void SetLevel(const UINT& level) { this->level = level; }

	void SetPlayerDirStart(const Point& start) { dirLine->SetStart(start); }
	void SetIsDirPenActive(const bool& active) { isDirPenActive = active; }

	void SetBricks(const vector<Swipe_Brick*>& bricks) { this->bricks = bricks; }

	void SetGameOverAnimFinished(const bool& finished) { this->isGameOverAnimFin = finished; }

private:
	/// <summary>
	/// 가장 먼저 충돌하면 충돌처리 끝
	/// </summary>
	bool HandleSampleBallCollision();
	bool HandleCollisionBricks();
	bool HandleCollisionWall();

private:
	int ballCnt = 1;
	Point ballCntPos = {WIN_CENTER.x, SWIPE_FLOOR + 10};

	UINT level = 1;

private:

	HPEN dirPen = Swipe_Palette::GetInst()->GetPlayerDirPen();
	pair<HPEN, HBRUSH> sampleBallColors = Swipe_Palette::GetInst()->GetSampleBallColorPair();

	Line* dirLine = nullptr;
	Circle* sampleBall = nullptr;
	bool isDirPenActive = false;

	vector<Swipe_Brick*> bricks = {}; // 플레이어 사격방향 정보에 쓰일 것임

private:
	bool isGameOverAnimFin = false;
};
