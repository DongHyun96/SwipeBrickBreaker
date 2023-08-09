#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	srand(time(NULL));

	HDC hdc = GetDC(hWnd); // �� hWnd�� ����Ǿ� �ִ� hdc(���� hdc)�� ������

	hBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT); // �� hdc�� ȣȯ ������ ��Ʈ�� ���� 
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
	PatBlt // Ư�� �������� ȭ���� �ʱ�ȭ���ִ� �Լ� , ȭ���� �Ͼ�� �ʱ�ȭ (�̰� InvalidateRect�Լ��� ����� �Լ�)
	(
		backDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS
	);

	scene->Render(backDC); // backDC�� �׸�

	Time::GetInstance()->Render();

	// ���� hdc�� backDC�� ����
	BitBlt // bit�� �Լ� / ��� ���� (ȭ���� �������ִ� �Լ�), Src(Source, ����) -> Dest(Destination, ������, ���)
	(
		hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, backDC, 0, 0, SRCCOPY
	);

}
