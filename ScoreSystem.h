#pragma once
#include <SFML/Graphics.hpp>

class ScoreSystem
{
private:
    int   totalScore;
    int   killStreak;      
    int   multiKillCount;  

    static const int SCORE_REBEL = 50;
    static const int SCORE_SHIELDED = 75;
    static const int SCORE_BAZOOKA = 100;
    static const int SCORE_GRENADE = 100;
    static const int SCORE_PARA = 25;   
    static const int SCORE_MUMMY = 150;
    static const int SCORE_ZOMBIE = 100;
    static const int SCORE_MARTIAN = 200;

    static const int SCORE_BOSS_NORMAL = 500;
    static const int SCORE_BOSS_ULTIMATE = 1500;


    static const int bonusMelee = 50;
    static const int BONUS_AERIAL = 100;
    static const int BONUS_MULTIKILL = 200;
    static const int BONUS_MASSACRE = 300;

    static const int SCORE_SURVIVAL_CLEAR = 1000;
    static const int SCORE_CAMPAIGN_CLEAR = 3000;
    static const int SCORE_FLAWLESS = 5000;

    sf::Text  popupText;
    sf::Font  font;
    float     popupTimer;
    char      popupBuf[100];

public:
    ScoreSystem()
    {
        totalScore = 0;
        killStreak = 0;
        multiKillCount = 0;
        popupTimer = 0;
    }

    void loadFont(const char* path)
    {
        font.loadFromFile(path);
        popupText.setFont(font);
        popupText.setCharacterSize(35);
        popupText.setFillColor(sf::Color::Yellow);
        popupText.setOutlineColor(sf::Color::Black);
        popupText.setOutlineThickness(2);
        popupText.setPosition(700, 400);
    }

    void showPopup(const char* msg, int bonus)
    {
        sprintf_s(popupBuf, "%s  +%d", msg, bonus);
        popupText.setString(popupBuf);
        popupTimer = 120;  
    }

 
    void addKillScore(int enemyType, bool isAerial, bool isMelee)
    {
        int base = 0;

        if (enemyType == 0)       base = SCORE_REBEL;
        else if (enemyType == 1)  base = SCORE_SHIELDED;
        else if (enemyType == 2)  base = SCORE_BAZOOKA;
        else if (enemyType == 3)  base = SCORE_GRENADE;
        else if (enemyType == 4)  base = SCORE_REBEL + SCORE_PARA;
        else if (enemyType == 5)  base = SCORE_MUMMY;
        else if (enemyType == 6)  base = SCORE_ZOMBIE;
        else if (enemyType == 7)  base = SCORE_MARTIAN;

        totalScore += base;
        showPopup("KILL", base);

        if (isAerial)
        {
            totalScore += BONUS_AERIAL;
            showPopup("AERIAL KILL!", BONUS_AERIAL);
        }

        if (isMelee)
        {
            totalScore += bonusMelee;
            showPopup("MELEE KILL!", bonusMelee);
        }

        killStreak++;
    }
    void addMultiKill(int enemiesKilled)
    {
        if (enemiesKilled == 2)
        {
            totalScore += BONUS_MULTIKILL;
            showPopup("MULTI KILL!", BONUS_MULTIKILL);
        }
        else if (enemiesKilled >= 3)
        {
            int bonus = BONUS_MASSACRE + (enemiesKilled - 3) * 50;
            totalScore += bonus;
            showPopup("MASSACRE!!!", bonus);
        }
    }

    
    void addBossKill(bool isUltimate)
    {
        if (isUltimate)
        {
            totalScore += SCORE_BOSS_ULTIMATE;
            showPopup("ULTIMATE BOSS!", SCORE_BOSS_ULTIMATE);
        }
        else
        {
            totalScore += SCORE_BOSS_NORMAL;
            showPopup("BOSS KILL!", SCORE_BOSS_NORMAL);
        }
    }

    void addLevelClear(bool isCampaign, bool isFlawless)
    {
        if (isFlawless)
        {
            totalScore += SCORE_FLAWLESS;
            showPopup("FLAWLESS VICTORY!", SCORE_FLAWLESS);
        }
        else if (isCampaign)
        {
            totalScore += SCORE_CAMPAIGN_CLEAR;
            showPopup("CAMPAIGN CLEAR!", SCORE_CAMPAIGN_CLEAR);
        }
        else
        {
            totalScore += SCORE_SURVIVAL_CLEAR;
            showPopup("LEVEL CLEAR!", SCORE_SURVIVAL_CLEAR);
        }
    }

    void update()
    {
        if (popupTimer > 0)
            popupTimer--;
    }

    void drawPopup(sf::RenderWindow& window)
    {
        if (popupTimer > 0)
        {
            sf::Uint8 alpha = static_cast<sf::Uint8>((popupTimer / 120.0f) * 255);
            sf::Color c = popupText.getFillColor();
            c.a = alpha;
            popupText.setFillColor(c);
            window.draw(popupText);
        }
    }

    void  resetStreak() 
    { 
        killStreak = 0; 
    }
    void  reset() 
    { 
        totalScore = 0; 
        killStreak = 0; 
    }
    int   getScore()     const 
    { 
        return totalScore; 
    }
    int   getStreak()    const 
    {
        return killStreak; 
    }
};