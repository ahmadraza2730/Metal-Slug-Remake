#pragma once

#include <SFML/Graphics.hpp>
#include "PerlinNoise.h"

class InfiniteMap
{
private:

    static const int FOREST = 0;
    static const int CAVE = 1;

    int cellSize;
    int screenWidth;
    int screenHeight;

    int terrainSeed;
    int biomeSeed;

    sf::Texture grassTexture;
    sf::Texture dirtTexture;
    sf::Texture stoneTexture;
    sf::Texture deepSlateTexture;

    sf::Sprite grassSprite;
    sf::Sprite dirtSprite;
    sf::Sprite stoneSprite;
    sf::Sprite deepSlateSprite;

    sf::RectangleShape sky;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

private:

    int getGroundRow(int column)
    {
        float noise = PerlinNoise::generate(column * 0.02f, terrainSeed);

        int groundRow = 10 + static_cast<int>(noise * 2);

        if (groundRow < 9)
            groundRow = 9;

        if (groundRow > 11)
            groundRow = 11;

        return groundRow;
    }

    int getBiome(int column)
    {
        float noise = PerlinNoise::generate(column * 0.008f, biomeSeed);

        if (noise > 0)
            return CAVE;

        return FOREST;
    }

public:

    InfiniteMap(int cell, int width, int height)
    {
        cellSize = cell;
        screenWidth = width;
        screenHeight = height;

        terrainSeed = 42;
        biomeSeed = 137;
    }

    bool loadTextures(
        const char* grassPath,
        const char* dirtPath,
        const char* stonePath,
        const char* deepSlatePath)
    {
        bool loaded = true;

        loaded &= grassTexture.loadFromFile(grassPath);
        loaded &= dirtTexture.loadFromFile(dirtPath);
        loaded &= stoneTexture.loadFromFile(stonePath);
        loaded &= deepSlateTexture.loadFromFile(deepSlatePath);
        backgroundTexture.loadFromFile("Assets/build-up-background.png");

        backgroundSprite.setTexture(backgroundTexture);
        grassSprite.setTexture(grassTexture);
        dirtSprite.setTexture(dirtTexture);
        stoneSprite.setTexture(stoneTexture);
        deepSlateSprite.setTexture(deepSlateTexture);

        return loaded;
    }

    float getGroundY(float x)
    {
        int column = static_cast<int>(x / cellSize);

        return static_cast<float>(getGroundRow(column) * cellSize);
    }

    void draw(sf::RenderWindow& window, float cameraX)
    {
        int startColumn = static_cast<int>(cameraX / cellSize) - 1;
        int endColumn = startColumn + (screenWidth / cellSize) + 2;

        backgroundSprite.setPosition(0.f, 0.f);

        backgroundSprite.setScale(
            (float)screenWidth / backgroundTexture.getSize().x,
            (float)screenHeight / backgroundTexture.getSize().y
        );

        window.draw(backgroundSprite);

        for (int column = startColumn; column <= endColumn; column++)
        {
            float x = static_cast<float>(column * cellSize) - cameraX;

            int groundRow = getGroundRow(column);

            int currentBiome = getBiome(column);

            if (currentBiome == FOREST)
            {
                grassSprite.setPosition(
                    x,
                    static_cast<float>(groundRow * cellSize)
                );

                window.draw(grassSprite);
            }
            else
            {
                stoneSprite.setPosition(
                    x,
                    static_cast<float>(groundRow * cellSize)
                );

                window.draw(stoneSprite);
            }

            for (int row = groundRow + 1; row < 14; row++)
            {
                if (currentBiome == FOREST)
                {
                    dirtSprite.setPosition(
                        x,
                        static_cast<float>(row * cellSize)
                    );

                    window.draw(dirtSprite);
                }
                else
                {
                    deepSlateSprite.setPosition(
                        x,
                        static_cast<float>(row * cellSize)
                    );

                    window.draw(deepSlateSprite);
                }
            }
        }
    }
};