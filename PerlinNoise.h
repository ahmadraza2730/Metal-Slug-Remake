#pragma once
#pragma once
#include <cmath>

class PerlinNoise
{
public:

    static float noise(int x, int seed)
    {
        x = x + seed * 1000;
        x = (x << 13) ^ x;
        return (1.0f - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    }

    static float interpolate(float a, float b, float t)
    {
        float fade = t * t * (3 - 2 * t);
        return a + fade * (b - a);
    }
    static float smoothNoise(float x, int seed)
    {
        int ix = (int)floor(x);
        float fx = x - ix;
        return interpolate(noise(ix, seed), noise(ix + 1, seed), fx);
    }
    static float generate(float x, int seed, int octaves = 4)
    {
        float result = 0;
        float amplitude = 1.0f;
        float frequency = 1.0f;
        float maxVal = 0;
        for (int i = 0; i < octaves; i++)
        {
            result += smoothNoise(x * frequency, seed + i * 100) * amplitude;
            maxVal += amplitude;
            amplitude *= 0.5f;
            frequency *= 2.0f;
        }
        return result / maxVal; 
    }
};