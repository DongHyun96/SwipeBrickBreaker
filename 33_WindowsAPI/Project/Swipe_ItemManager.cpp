#include "Framework.h"
#include "Swipe_ItemManager.h"


Swipe_ItemManager::Swipe_ItemManager(UINT poolCnt)
{
	for (UINT i = 0; i < poolCnt; i++)
		pool.push_back(new Swipe_Item);
}

Swipe_ItemManager::~Swipe_ItemManager()
{
}

void Swipe_ItemManager::Update()
{
	for (Swipe_Item* item : pool)
		item->Update();

	switch (animState)
	{
	case IDLE:
		break;
	case SPAWNING:

		for (Swipe_Item* item : pool)
		{
			if (item->IsActive() && item->GetAnimState() != IDLE) // ���� �����ϴ� ��
				return;
		}

		// ������ ��, positioning ����
		animState = POSITIONING;

		break;
	case POSITIONING: // Check for anim state update
	{

		static bool repoStarted = false;

		if (!repoStarted)
		{
			for (Swipe_Item* item : pool)
			{
				if (!item->IsActive())
					continue;

				item->SetAnimState(POSITIONING);
			}

			repoStarted = true;
		}

		for (Swipe_Item* item : pool)
		{
			if (item->IsActive() && item->GetAnimState() != IDLE) // ���� positioning �ϴ� ��
				return;
		}

		// positioning ��
		repoStarted = false;
		animState = IDLE;
	}
	break;
	default:
		break;
	}
}

void Swipe_ItemManager::Render(const HDC& hdc)
{
	for (Swipe_Item* item : pool)
		item->Render(hdc);
}

void Swipe_ItemManager::Spawn(Point spawnPos)
{
	animState = SPAWNING;

	for (Swipe_Item* item : pool)
	{
		if (item->IsActive())
			continue;

		item->Spawn(spawnPos);
		return;
	}
}

void Swipe_ItemManager::DestroyAllItems()
{
	for (Swipe_Item* item : pool)
	{
		if (!item->IsActive())
			continue;

		item->SetActive(false);
		Swipe_ParticleManager::GetInst()->Spawn(item->GetBody()->Pos(), PARTICLE_GREEN);
	}
}
