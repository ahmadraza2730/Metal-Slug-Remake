#pragma once
#include <SFML/Graphics.hpp>
#include "DamageState.h"

class HUD
{
private:
    sf::Font font;
    bool fontLoaded;

    sf::RectangleShape healthBarBg;
    sf::RectangleShape healthBarFill;

    sf::Text livesText;
    sf::Text healthText;
    sf::Text stateText;
    sf::Text gameOverText;

public:
    HUD()
    {
        fontLoaded = false;

       
        healthBarBg.setSize(sf::Vector2f(200.0f, 20.0f));
        healthBarBg.setFillColor(sf::Color(80, 80, 80));
        healthBarBg.setPosition(20.0f, 20.0f);

        healthBarFill.setSize(sf::Vector2f(200.0f, 20.0f));
        healthBarFill.setFillColor(sf::Color::Green);
        healthBarFill.setPosition(20.0f, 20.0f);
    }

    bool loadFont(const char* path)
    {
        if (font.loadFromFile(path))
        {
            fontLoaded = true;

            livesText.setFont(font);
            livesText.setCharacterSize(22);
            livesText.setFillColor(sf::Color::White);
            livesText.setOutlineColor(sf::Color::Black);
            livesText.setOutlineThickness(2);
            livesText.setPosition(20.0f, 50.0f);

            healthText.setFont(font);
            healthText.setCharacterSize(18);
            healthText.setFillColor(sf::Color::White);
            healthText.setOutlineColor(sf::Color::Black);
            healthText.setOutlineThickness(2);
            healthText.setPosition(20.0f, 45.0f);

            stateText.setFont(font);
            stateText.setCharacterSize(20);
            stateText.setOutlineColor(sf::Color::Black);
            stateText.setOutlineThickness(2);
            stateText.setPosition(20.0f, 75.0f);

            gameOverText.setFont(font);
            gameOverText.setCharacterSize(60);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setOutlineColor(sf::Color::Black);
            gameOverText.setOutlineThickness(3);
            gameOverText.setString("GAME OVER");
            gameOverText.setPosition(550.0f, 380.0f);

            return true;
        }
        return false;
    }

    void draw(sf::RenderWindow& window, int currentHealth, int maxHealth, int lives, int damageState, bool isDead)
    {
        if (!fontLoaded) return;

        healthBarBg.setPosition(20.0f, 20.0f);
        window.draw(healthBarBg);
        float ratio = 0.0f;
        if (maxHealth > 0)
            ratio = static_cast<float>(currentHealth) / static_cast<float>(maxHealth);

        healthBarFill.setSize(sf::Vector2f(200.0f * ratio, 20.0f));

        if (damageState == STATE_NORMAL)
            healthBarFill.setFillColor(sf::Color::Green);
        else if (damageState == STATE_INJURED)
            healthBarFill.setFillColor(sf::Color::Yellow);
        else if (damageState == STATE_CRITICAL)
            healthBarFill.setFillColor(sf::Color::Red);
        else
            healthBarFill.setFillColor(sf::Color(60, 60, 60));

        window.draw(healthBarFill);

        char hpStr[50] = "HP: ";
        char hpNum[20];
        int h = currentHealth;
        int m = maxHealth;
        int idx = 0;
        if (h == 0)
        {
            hpNum[idx++] = '0';
        }
        else
        {
            char tmp[10];
            int t = 0;
            while (h > 0) { tmp[t++] = '0' + (h % 10); h /= 10; }
            for (int r = t - 1; r >= 0; r--) hpNum[idx++] = tmp[r];
        }
        hpNum[idx] = '\0';
        strcat_s(hpStr, hpNum);
        strcat_s(hpStr, " / ");
        char maxStr[10];
        idx = 0;
        if (m == 0)
        {
            maxStr[idx++] = '0';
        }
        else
        {
            char tmp[10];
            int t = 0;
            while (m > 0) { tmp[t++] = '0' + (m % 10); m /= 10; }
            for (int r = t - 1; r >= 0; r--) maxStr[idx++] = tmp[r];
        }
        maxStr[idx] = '\0';
        strcat_s(hpStr, maxStr);
        healthText.setString(hpStr);
        healthText.setPosition(230.0f, 20.0f);
        window.draw(healthText);

        
        char livesStr[30] = "Lives: ";
        char livesNum[10];
        idx = 0;
        int lv = lives;
        if (lv == 0)
        {
            livesNum[idx++] = '0';
        }
        else
        {
            char tmp[10];
            int t = 0;
            while (lv > 0) { tmp[t++] = '0' + (lv % 10); lv /= 10; }
            for (int r = t - 1; r >= 0; r--) livesNum[idx++] = tmp[r];
        }
        livesNum[idx] = '\0';
        strcat_s(livesStr, livesNum);
        livesText.setString(livesStr);
        livesText.setPosition(20.0f, 50.0f);
        window.draw(livesText);

        if (damageState == STATE_NORMAL)
        {
            stateText.setString("");
        }
        else if (damageState == STATE_INJURED)
        {
            stateText.setFillColor(sf::Color::Yellow);
            stateText.setString("INJURED");
        }
        else if (damageState == STATE_CRITICAL)
        {
            stateText.setFillColor(sf::Color::Red);
            stateText.setString("CRITICAL!");
        }
        else if (damageState == STATE_DEAD)
        {
            stateText.setFillColor(sf::Color::Red);
            stateText.setString("DEAD");
        }
        stateText.setPosition(20.0f, 78.0f);
        window.draw(stateText);

        if (isDead && lives <= 0)
        {
            window.draw(gameOverText);
        }
    }

    void drawEnemyHealthBar(sf::RenderWindow& window, float ex, float ey, float ew, int hp, int maxHp, float camX)
    {
        if (maxHp <= 0) return;

        float barW = ew;
        float barH = 6.0f;
        float screenX = ex - camX;
        float screenY = ey - 12.0f;

        sf::RectangleShape bg(sf::Vector2f(barW, barH));
        bg.setFillColor(sf::Color(80, 80, 80));
        bg.setPosition(screenX, screenY);
        window.draw(bg);

        float ratio = static_cast<float>(hp) / static_cast<float>(maxHp);
        sf::RectangleShape fill(sf::Vector2f(barW * ratio, barH));
        fill.setFillColor(sf::Color::Red);
        fill.setPosition(screenX, screenY);
        window.draw(fill);
    }

    ~HUD() 
    { }
};