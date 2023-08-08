#pragma once
class Swipe_Palette
{
private:
	Swipe_Palette();
	~Swipe_Palette();

public:

	static Swipe_Palette* GetInst()
	{
		static Swipe_Palette singleton;
		return &singleton;
	}

public:
	const pair<HPEN, HBRUSH>& GetBallColorPair() const { return ballColorPair; }

	const pair<HPEN, HBRUSH>& GetSampleBallColorPair() const { return ballSampleColors; }

	const HPEN GetFloorCeilPen() const { return floorCeilPen; }

	const HPEN GetPlayerDirPen() const { return playerDirPen; }
	
	const pair<HPEN, HBRUSH>& GetBgColorPair() const { return bgColorPair; }

	const pair<HPEN, HBRUSH>& GetBrickColorPair() const { return brickColorPair; }

	const pair<HPEN, HBRUSH>& GetWhiteColorPair() const { return whiteColorPair; }

	const pair<HPEN, HBRUSH>& GetItemColorPair() const { return itemColorPair; }

	const pair<HPEN, HBRUSH>& GetParticleColorGreen() const { return particleColorGreen; }

	const pair<HPEN, HBRUSH>& GetParticleColorRed() const { return particleColorRed; }

	const pair<HPEN, HBRUSH>& GetParticlColorBlack() const { return particleColorBlack; }

	const vector<pair<HPEN, HBRUSH>>& GetBrickColorVec() const { return brickColorVec; }

	const HFONT& GetFont() const { return hFont; }

	

private:
	
	HPEN floorCeilPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

	//HPEN playerDirPen = CreatePen(PS_DOT, 1, RGB(92, 172, 242));
	HPEN playerDirPen = nullptr;


	pair<HPEN, HBRUSH> bgColorPair = { CreatePen(PS_SOLID, 1, RGB(230, 230, 230)), CreateSolidBrush(RGB(230, 230, 230)) };

	pair<HPEN, HBRUSH> ballColorPair = { CreatePen(PS_SOLID, 1, RGB(92, 172, 242)), CreateSolidBrush(RGB(92, 172, 242)) };
	pair<HPEN, HBRUSH> ballSampleColors = { CreatePen(PS_SOLID, 3, RGB(255, 0, 0)), CreateSolidBrush(RGB(230, 230, 230)) };

	pair<HPEN, HBRUSH> brickColorPair = { CreatePen(PS_SOLID, 1, RGB(254, 74, 86)), CreateSolidBrush(RGB(254, 74, 86)) };
	vector<pair<HPEN, HBRUSH>> brickColorVec = {};

	pair<HPEN, HBRUSH> whiteColorPair = { CreatePen(PS_SOLID, 1, RGB(255, 255, 255)), CreateSolidBrush(RGB(255, 255, 255)) };

	pair<HPEN, HBRUSH> itemColorPair = { CreatePen(PS_SOLID, 1, RGB(86, 235, 128)), CreateSolidBrush(RGB(86, 235, 128)) };
		
	pair<HPEN, HBRUSH> particleColorGreen = { CreatePen(PS_SOLID, 1, RGB(86, 235, 128)), CreateSolidBrush(RGB(86, 235, 128)) };
	pair<HPEN, HBRUSH> particleColorRed = { CreatePen(PS_SOLID, 1, RGB(242, 159, 119)), CreateSolidBrush(RGB(242, 159, 119)) };
	pair<HPEN, HBRUSH> particleColorBlack = { CreatePen(PS_SOLID, 1, RGB(0, 0, 0)), CreateSolidBrush(RGB(0, 0, 0)) };

	HFONT hFont;

};
