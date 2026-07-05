#pragma once
#include <SFML/Graphics.hpp>

class PlayerSelect
{
private:
    static const int ncharacter = 4;

    sf::Font font;
    sf::Texture bgTexture;
    sf::Sprite  bgSprite;
    sf::Texture charTextures[ncharacter];
    sf::Sprite  charSprites[ncharacter];
    const char* charNames[ncharacter];

    sf::Text title;
    sf::Text nameText;
    sf::Text hint;

    sf::RectangleShape highlightBox;

    int selectedIndex;
    int screenX;
    int screenY;

public:
    PlayerSelect()
    {
        selectedIndex = 0;
        screenX = 1600;
        screenY = 900;
        charNames[0] = "MARCO";
        charNames[1] = "TARMA";
        charNames[2] = "ERI";
        charNames[3] = "FIO";
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

        const char* paths[ncharacter];
        paths[0] = "Assets/marco.png";
        paths[1] = "Assets/tarma.png";
        paths[2] = "Assets/eri.png";
        paths[3] = "Assets/fio.png";

        float spacing = (float)screenX / (ncharacter + 1);
        float yPos = 350.0f;
        float targetSize = 200.0f;
        for (int i = 0; i < ncharacter; i = i + 1)
        {
            charTextures[i].loadFromFile(paths[i]);
            charSprites[i].setTexture(charTextures[i]);

            sf::Vector2u s = charTextures[i].getSize();
            float scale = targetSize / (float)s.x;
            charSprites[i].setScale(scale, scale);

            float xCenter = spacing * (i + 1);
            charSprites[i].setPosition(
                xCenter - (s.x * scale) / 2.0f,
                yPos
            );
        }

        title.setFont(font);
        title.setString("SELECT YOUR CHARACTER");
        title.setCharacterSize(55);
        title.setFillColor(sf::Color::Blue);
        title.setOutlineColor(sf::Color::Red);
        title.setOutlineThickness(4);
        title.setStyle(sf::Text::Bold);

        sf::FloatRect tBounds = title.getLocalBounds();
        title.setPosition((screenX - tBounds.width) / 2.0f, 80.0f);

        nameText.setFont(font);
        nameText.setCharacterSize(40);
        nameText.setFillColor(sf::Color::White);
        nameText.setOutlineColor(sf::Color::Black);
        nameText.setOutlineThickness(3);

        hint.setFont(font);
        hint.setString("LEFT Or RIGHT to choose       ENTER to confirm       ESC to go back");
        hint.setCharacterSize(28);
        hint.setFillColor(sf::Color::Magenta);

        sf::FloatRect hBounds = hint.getLocalBounds();
        hint.setPosition((screenX - hBounds.width) / 2.0f, 800.0f);

        highlightBox.setSize(sf::Vector2f(targetSize + 20.0f, targetSize + 20.0f));
        highlightBox.setFillColor(sf::Color::Transparent);
        highlightBox.setOutlineColor(sf::Color::Red);
        highlightBox.setOutlineThickness(5);
    }

    void moveLeft()
    {
        selectedIndex = selectedIndex - 1;
        if (selectedIndex < 0)
            selectedIndex = ncharacter - 1;
    }
    void moveRight()
    {
        selectedIndex = selectedIndex + 1;
        if (selectedIndex >= ncharacter)
            selectedIndex = 0;
    }

    void handleInput(sf::Event ev)
    {
        if (ev.type == sf::Event::KeyPressed)
        {
            if (ev.key.code == sf::Keyboard::Left)  moveLeft();
            if (ev.key.code == sf::Keyboard::Right) moveRight();
        }
    }

    int getChoice(sf::Event ev)
    {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
            return selectedIndex;
        return -1;
    }

    bool wantsBack(sf::Event ev)
    {
        if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
            return true;
        return false;
    }
    int getSelectedIndex()
    {
        return selectedIndex;
    }
    const char* getSelectedName()
    {
        return charNames[selectedIndex];
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(bgSprite);
        window.draw(title);
        sf::FloatRect b = charSprites[selectedIndex].getGlobalBounds();
        highlightBox.setPosition(b.left - 10.0f, b.top - 10.0f);
        highlightBox.setSize(sf::Vector2f(b.width + 20.0f, b.height + 20.0f));
        window.draw(highlightBox);
        for (int i = 0; i < ncharacter; i = i + 1)
        {
            if (i == selectedIndex)
                charSprites[i].setColor(sf::Color::White);
            else
                charSprites[i].setColor(sf::Color(150, 150, 150));

            window.draw(charSprites[i]);
        }
        nameText.setString(charNames[selectedIndex]);
        sf::FloatRect nBounds = nameText.getLocalBounds();
        nameText.setPosition((screenX - nBounds.width) / 2.0f, 620.0f);
        window.draw(nameText);
        window.draw(hint);
    }
};