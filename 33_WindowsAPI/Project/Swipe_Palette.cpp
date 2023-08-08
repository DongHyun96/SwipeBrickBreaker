#include "Framework.h"
#include "Swipe_Palette.h"

Swipe_Palette::Swipe_Palette()
{
	int r = 254;
	int g = 74;
	int b = 86;

	int r2 = 242;
	int g2 = 159;
	int b2 = 119;

	for (int i = r - r2 - 1; i >= 0; i--)
	{
		int currentG = g + ((g2 - g) / (r - r2)) * i;
		int currentB = b + ((b2 - b) / (r - r2)) * i;

		HPEN pen = CreatePen(PS_SOLID, 1, RGB(r - i, currentG, currentB));
		HBRUSH brush = CreateSolidBrush(RGB(r - i, currentG, currentB));

		brickColorVec.push_back({ pen, brush });
	}

	hFont = CreateFont(
		30,				  // Desired font size
		0,                // Font width
		0,                // Font escapement
		0,                // Orientation
		FW_NORMAL,        // Font weight
		FALSE,            // Italic
		FALSE,            // Underline
		FALSE,            // Strikeout
		DEFAULT_CHARSET,  // Character set
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Impact")     // Font name
	);

	LOGBRUSH logBrush;

	logBrush.lbColor = RGB(92, 172, 242);

	logBrush.lbStyle = PS_SOLID;

	playerDirPen = ExtCreatePen(PS_GEOMETRIC| PS_ENDCAP_FLAT | PS_JOIN_ROUND | PS_DASH, 3, &logBrush, 0, NULL);

}

Swipe_Palette::~Swipe_Palette()
{
	DeleteObject(floorCeilPen);

	DeleteObject(playerDirPen);

	DeleteObject(bgColorPair.first);
	DeleteObject(bgColorPair.second);


	DeleteObject(ballColorPair.first);
	DeleteObject(ballColorPair.second);

	DeleteObject(ballSampleColors.first);
	DeleteObject(ballSampleColors.second);

	DeleteObject(brickColorPair.first);
	DeleteObject(brickColorPair.second);

	for (pair<HPEN, HBRUSH> p : brickColorVec)
	{
		DeleteObject(p.first);
		DeleteObject(p.second);
	}

	brickColorVec.clear();


	DeleteObject(whiteColorPair.first);
	DeleteObject(whiteColorPair.second);

	DeleteObject(itemColorPair.first);
	DeleteObject(itemColorPair.second);

	DeleteObject(particleColorGreen.first);
	DeleteObject(particleColorGreen.second);

	DeleteObject(particleColorRed.first);
	DeleteObject(particleColorRed.second);

	DeleteObject(particleColorBlack.first);
	DeleteObject(particleColorBlack.second);

	

	DeleteObject(hFont);

}