#pragma once
#include <SFML/Graphics.hpp>
#include "DamageState.h"

class GameHUD
{
private:
    sf::Font     font;
    sf::Text     livesText;
    sf::Text     scoreText;
    sf::Text     stateText;

    sf::RectangleShape healthBarBg;
    sf::RectangleShape healthBarFill;

public:
    GameHUD()
    {
        healthBarBg.setSize(sf::Vector2f(200, 20));
        healthBarBg.setFillColor(sf::Color(80, 0, 0));
        healthBarBg.setPosition(20, 50);

        healthBarFill.setSize(sf::Vector2f(200, 20));
        healthBarFill.setFillColor(sf::Color::Red);
        healthBarFill.setPosition(20, 50);
    }

    void loadFont(const char* path)
    {
        font.loadFromFile(path);

        livesText.setFont(font);
        livesText.setCharacterSize(28);
        livesText.setFillColor(sf::Color::White);
        livesText.setOutlineColor(sf::Color::Black);
        livesText.setOutlineThickness(2);
        livesText.setPosition(20, 10);

        scoreText.setFont(font);
        scoreText.setCharacterSize(28);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setOutlineThickness(2);
        scoreText.setPosition(20, 80);

        stateText.setFont(font);
        stateText.setCharacterSize(24);
        stateText.setOutlineColor(sf::Color::Black);
        stateText.setOutlineThickness(2);
        stateText.setPosition(20, 110);
    }

    void drawEnemyHealthBar(sf::RenderWindow& window,
        float ex, float ey, float ew,
        int hp, int maxHp, float camX)
    {
        float ratio = static_cast<float>(hp) / static_cast<float>(maxHp);
        float barW = ew;

        sf::RectangleShape bg;
        bg.setSize(sf::Vector2f(barW, 6));
        bg.setFillColor(sf::Color(80, 0, 0));
        bg.setPosition(ex - camX, ey - 10);
        window.draw(bg);

        sf::RectangleShape fill;
        fill.setSize(sf::Vector2f(barW * ratio, 6));
        fill.setFillColor(sf::Color::Red);
        fill.setPosition(ex - camX, ey - 10);
        window.draw(fill);
    }

    void draw(sf::RenderWindow& window, int damageState, int lives, int score)
    {
        char livesBuf[50] = "";
        sprintf_s(livesBuf, "Lives: %d", lives);
        livesText.setString(livesBuf);
        window.draw(livesText);

        char scoreBuf[50] = "";
        sprintf_s(scoreBuf, "Score: %d", score);
        scoreText.setString(scoreBuf);
        window.draw(scoreText);
        if (damageState == STATE_INJURED)
        {
            stateText.setFillColor(sf::Color::Yellow);
            stateText.setString("INJURED!");
            window.draw(stateText);
        }
        else if (damageState == STATE_CRITICAL)
        {
            stateText.setFillColor(sf::Color::Red);
            stateText.setString("CRITICAL!");
            window.draw(stateText);
        }
    }
};