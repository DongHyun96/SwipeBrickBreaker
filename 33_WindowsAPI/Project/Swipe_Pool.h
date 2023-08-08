#pragma once

template <typename T>
class Swipe_Pool
{
public:
	Swipe_Pool();
	Swipe_Pool(UINT poolCnt);
	virtual ~Swipe_Pool();

	virtual void Update() = 0;
	virtual void Render(const HDC& hdc) = 0;

	virtual void Spawn(Point spawnPos) = 0;

protected:
	vector<T*> pool = {};

};

template<typename T>
inline Swipe_Pool<T>::Swipe_Pool()
{
}

template<typename T>
Swipe_Pool<T>::Swipe_Pool(UINT poolCnt)
{
	for (UINT i = 0; i < poolCnt; i++)
		pool.push_back(new T);
}

template<typename T>
Swipe_Pool<T>::~Swipe_Pool()
{
	for (T* obj : pool)
		delete obj;

	pool.clear();
}
