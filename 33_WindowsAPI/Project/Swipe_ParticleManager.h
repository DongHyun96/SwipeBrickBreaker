#pragma once
class Swipe_ParticleManager : public Swipe_Pool<Swipe_Particle>
{
private:
	Swipe_ParticleManager();
	~Swipe_ParticleManager();

public:
	static Swipe_ParticleManager* GetInst()
	{
		static Swipe_ParticleManager singleton;
		return &singleton;
	}
	
	// Swipe_Pool을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render(const HDC& hdc) override;

	void Spawn(Point spawnPos, ParticleType type);

private:
	virtual void Spawn(Point spawnPos) override;

};
