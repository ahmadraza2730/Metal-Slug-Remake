#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

class Leaderboard
{
private:
    static const int maxEntries = 10;

    struct Entry
    {
        char  name[50];
        int   score;
    };

    Entry entries[maxEntries];
    int   entryCount;

    sf::Text  titleText;
    sf::Text  entryText[maxEntries];
    sf::Font  font;

    const char* saveFile;

public:
    Leaderboard()
    {
        entryCount = 0;
        saveFile = "leaderboard.txt";

        for (int i = 0; i < maxEntries; i++)
        {
            entries[i].score = 0;
            entries[i].name[0] = '\0';
        }
    }

    void loadFont(const char* path)
    {
        font.loadFromFile(path);

        titleText.setFont(font);
        titleText.setCharacterSize(50);
        titleText.setFillColor(sf::Color::Yellow);
        titleText.setOutlineColor(sf::Color::Black);
        titleText.setOutlineThickness(3);
        titleText.setString("HIGH SCORES");
        titleText.setPosition(600, 50);

        for (int i = 0; i < maxEntries; i++)
        {
            entryText[i].setFont(font);
            entryText[i].setCharacterSize(35);
            entryText[i].setFillColor(sf::Color::White);
            entryText[i].setOutlineColor(sf::Color::Black);
            entryText[i].setOutlineThickness(2);
            entryText[i].setPosition(400, 150.0f + i * 60.0f);
        }
    }

    // load scores from file
    void load()
    {
        std::ifstream file(saveFile);
        if (!file.is_open()) return;

        entryCount = 0;
        while (entryCount < maxEntries && !file.eof())
        {
            file >> entries[entryCount].name
                >> entries[entryCount].score;
            entryCount++;
        }
        file.close();
    }

    void save()
    {
        std::ofstream file(saveFile);
        if (!file.is_open()) return;

        for (int i = 0; i < entryCount; i++)
        {
            file << entries[i].name << " "
                << entries[i].score << "\n";
        }
        file.close();
    }
    void addScore(const char* name, int score)
    {
        int pos = entryCount;
        for (int i = 0; i < entryCount; i++)
        {
            if (score > entries[i].score)
            {
                pos = i;
                break;
            }
        }

        int limit = entryCount < maxEntries ? entryCount : maxEntries - 1;
        for (int i = limit; i > pos; i--)
        {
            entries[i] = entries[i - 1];
        }

        if (pos < maxEntries)
        {
            int j = 0;
            while (name[j] != '\0' && j < 49)
            {
                entries[pos].name[j] = name[j];
                j++;
            }
            entries[pos].name[j] = '\0';
            entries[pos].score = score;

            if (entryCount < maxEntries)
                entryCount++;
        }

        save();
    }

    bool isHighScore(int score)
    {
        if (entryCount < maxEntries) return true;
        return score > entries[entryCount - 1].score;
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(titleText);

        for (int i = 0; i < entryCount; i++)
        {
            char buf[100] = "";
            sprintf_s(buf, "%d.  %-20s  %d", i + 1, entries[i].name, entries[i].score);
            entryText[i].setString(buf);

            if (i == 0)
                entryText[i].setFillColor(sf::Color(255, 215, 0));  
            else if (i == 1)
                entryText[i].setFillColor(sf::Color(192, 192, 192)); 
            else if (i == 2)
                entryText[i].setFillColor(sf::Color(205, 127, 50));  
            else
                entryText[i].setFillColor(sf::Color::White);

            window.draw(entryText[i]);
        }
    }
};