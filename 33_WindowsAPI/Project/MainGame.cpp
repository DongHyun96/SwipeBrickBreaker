#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	srand(time(NULL));

	HDC hdc = GetDC(hWnd); // 이 hWnd와 연결되어 있는 hdc(메인 hdc)를 꺼내옴

	hBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT); // 현 hdc와 호환 가능한 비트맵 생성 
	backDC = CreateCompatibleDC(hdc);

	SelectObject(backDC, hBitmap);

	ReleaseDC(hWnd, hdc);

	//scene = new PaintScene;
	//scene = new CollisionScene;
	//scene = new AvoidScene;
	//scene = new FortressScene;
	//scene = new ArkanoidScene;
	scene = new SwipeScene;
}

MainGame::~MainGame()
{
	delete scene;

	DeleteDC(backDC);
	DeleteObject(hBitmap);

	Time::Delete();
}

void MainGame::Update()
{
	scene->Update();

	Time::GetInstance()->Update();
}

void MainGame::Render(HDC hdc)
{
	// backDC invalidateRect
	PatBlt // 특정 패턴으로 화면을 초기화해주는 함수 , 화면을 하얗게 초기화 (이게 InvalidateRect함수와 비슷한 함수)
	(
		backDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS
	);

	scene->Render(backDC); // backDC에 그림

	Time::GetInstance()->Render();

	// 메인 hdc에 backDC를 복사
	BitBlt // bit블릿 함수 / 고속 복사 (화면을 복사해주는 함수), Src(Source, 원본) -> Dest(Destination, 목적지, 대상)
	(
		hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, backDC, 0, 0, SRCCOPY
	);

}
