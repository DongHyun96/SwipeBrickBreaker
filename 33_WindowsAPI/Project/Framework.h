// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <dwmapi.h>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

#define PI 3.141592f

#define WIN_WIDTH			650.f
#define WIN_HEIGHT			800.f

#define WIN_CENTER			Point(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define COLOR_BLACK			RGB(0, 0, 0)
#define COLOR_WHITE			RGB(255, 255, 255)

#define COLOR_RED			RGB(255, 0, 0)
#define COLOR_GREEN			RGB(0, 255, 0)
#define COLOR_BLUE			RGB(0, 0, 255)

#define COLOR_CYAN			RGB(0, 255, 255)
#define COLOR_MAGENTA		RGB(255, 0, 255)
#define COLOR_YELLOW		RGB(255, 255, 0)

#define COLOR_GRAY			RGB(128, 128, 128)
#define COLOR_ORANGE		RGB(255, 165, 0)
#define COLOR_PINK			RGB(255, 192, 203)

// Swipe defines
#define SWIPE_CEIL			WIN_HEIGHT * 0.1f
#define SWIPE_FLOOR			WIN_HEIGHT * 0.9f
#define SWIPE_HEIGHT		SWIPE_FLOOR - SWIPE_CEIL

#define FIRE_Y_LIMIT		SWIPE_FLOOR * 0.93

#define SWIPE_ROW_CNT		9
#define SWIPE_COL_CNT		6

#define SWIPE_MARGIN		5.f

#define BRICK_SIZE_X		( WIN_WIDTH - ( SWIPE_MARGIN * (SWIPE_COL_CNT + 1) ) ) / SWIPE_COL_CNT
#define BRICK_SIZE_Y		( SWIPE_HEIGHT - ( SWIPE_MARGIN * (SWIPE_ROW_CNT + 1) ) ) / SWIPE_ROW_CNT
#define BRICK_SIZE			Point(BRICK_SIZE_X, BRICK_SIZE_Y)

#define SWIPE_GAME_OVER_Y	SWIPE_FLOOR - SWIPE_MARGIN - BRICK_SIZE_Y - 1.f

// Object
#include "Point.h"
#include "Vector2.h"

#include "Circle.h"
#include "Rect.h"
#include "Line.h"

// Utility
#include "Util.h"
#include "Collision.h"
#include "Time.h"

// GameObject
#include "Poo.h"

#include "CannonBall.h"
#include "CannonBallManager.h"
#include "Tank.h"

#include "ArkaPlayer.h"
#include "ArkaBrick.h"
#include "ArkaBrickManager.h"
#include "ArkaBall.h"

// Swipe GameObjects
#include "Swipe_Palette.h"

#include "Swipe_UIManager.h"
#include "Swipe_GameManager.h"
#include "Swipe_Pool.h"

#include "Swipe_Particle.h"
#include "Swipe_ParticleManager.h"

#include "Swipe_Ball.h"

#include "Swipe_BallManager.h"

#include "Swipe_Brick.h"
#include "Swipe_BrickManager.h"

#include "Swipe_Item.h"
#include "Swipe_ItemManager.h"


// Scene
#include "Scene.h"
#include "PaintScene.h"
#include "CollisionScene.h"
#include "AvoidScene.h"
#include "FortressScene.h"
#include "ArkanoidScene.h"
#include "SwipeScene.h"

#include "MainGame.h"

#include "Swipe_GameData.h"

// extern - 전역변수를 뿌려주는 키워드
extern HWND		hWnd; // 어딘가 이게 있으니 여기에 전방선언 한다
extern Point	mousePos;
extern HDC		backDC;
extern HDC		hdc;	// Main DC