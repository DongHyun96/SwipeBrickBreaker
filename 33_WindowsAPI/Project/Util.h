#pragma once

template <typename T>
static T GetRandom(const T& start, const T& end)
{
    if (start >= end)
        return (T)0;

    int range = (int)(end - start + 1);

    return (T)(start + rand() % range);
}

template <typename T>
static void Clamp(T& target, const T& floor, const T& ceil)
{
    if (target < floor) target = floor;
    else if (target > ceil) target = ceil;
}

template <typename T>
static T MappingtoNewRange(T num, T srcMin, T srcMax, T dstMin, T dstMax)
{
    if (srcMin > srcMax)
        return T();

    if (dstMin > dstMax)
        return T();

    if (srcMin == srcMax)
        return (T)(((num - srcMin) * (dstMax - dstMin)) + dstMin);

    return (T)(((num - srcMin) * (dstMax - dstMin)) / (srcMax - srcMin) + dstMin);
}

static float Lerp(float src, float dst, float alpha)
{
    if (alpha >= 1)
        return dst;

    if (alpha <= 0)
        return src;

    return (1 - alpha) * src + alpha * dst;
}

static TCHAR lpOut[1024];
