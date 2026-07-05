#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
private:
    static const int maxitem = 6;
    sf::Font font;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::Text title;
    sf::Text items[maxitem];
    const char* itemNames[maxitem];
    int selectedIndex;
    int screenX;
    int screenY;

public:
    Menu()
    {
        selectedIndex = 0;
        screenX = 1600;
        screenY = 900;
        itemNames[0] = "Campaign";
        itemNames[1] = "Survival";
        itemNames[2] = "Instructions";
        itemNames[3] = "Credits";
        itemNames[4] = "Scoreboard";
        itemNames[5] = "Exit";
    }
    void load(const char* fontPath, const char* bgPath)
    {
        font.loadFromFile(fontPath);
        bgTexture.loadFromFile(bgPath);
        bgSprite.setTexture(bgTexture);
        sf::Vector2u texSize = bgTexture.getSize();
        bgSprite.setScale(
            (float)screenX / texSize.x,
            (float)screenY / texSize.y
        );
        title.setFont(font);
        title.setString("METAL SLUG");
        title.setCharacterSize(120);
        title.setFillColor(sf::Color::Yellow);
        title.setOutlineColor(sf::Color::Black);
        title.setOutlineThickness(4);
        title.setStyle(sf::Text::Bold);
        sf::FloatRect tBounds = title.getLocalBounds();
        title.setPosition((screenX - tBounds.width) / 2.f, 80.f);
        for (int i = 0; i < maxitem; i++)
        {
            items[i].setFont(font);
            items[i].setString(itemNames[i]);
            items[i].setCharacterSize(50);
            items[i].setFillColor(sf::Color::White);
            items[i].setOutlineColor(sf::Color::Black);
            items[i].setOutlineThickness(2);
            sf::FloatRect b = items[i].getLocalBounds();
            items[i].setPosition(
                (screenX - b.width) / 2.f,
                300.f + i * 80.f
            );
        }
    }
    void moveUp()
    {
        selectedIndex--;
        if (selectedIndex < 0) selectedIndex = maxitem - 1;
    }
    void moveDown()
    {
        selectedIndex++;
        if (selectedIndex >= maxitem) selectedIndex = 0;
    }
    void handleInput(sf::Event ev)
    {
        if (ev.type == sf::Event::KeyPressed)
        {
            if (ev.key.code == sf::Keyboard::Up)   moveUp();
            if (ev.key.code == sf::Keyboard::Down) moveDown();
        }
    }
    int getChoice(sf::Event ev)
    {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
            return selectedIndex;
        return -1;
    }
    void draw(sf::RenderWindow& window)
    {
        window.draw(bgSprite);
        window.draw(title);

        for (int i = 0; i < maxitem; i++)
        {
            if (i == selectedIndex)
            {
                items[i].setFillColor(sf::Color::Red);
                char buf[100];
                sprintf_s(buf, "> %s <", itemNames[i]);
                items[i].setString(buf);
            }
            else
            {
                items[i].setFillColor(sf::Color::White);
                items[i].setString(itemNames[i]);
            }
            sf::FloatRect b = items[i].getLocalBounds();
            items[i].setPosition(
                (screenX - b.width) / 2.f,
                300.f + i * 80.f
            );
            window.draw(items[i]);
        }
    }
};