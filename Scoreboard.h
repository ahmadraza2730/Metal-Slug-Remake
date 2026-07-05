#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

class Scoreboard
{
private:
	static const int maxScores = 10;

	struct ScoreEntry
	{
		char name[50];
		int  score;
		int  level;
	};

	ScoreEntry entries[maxScores];
	int entryCount;

	sf::Font font;
	bool fontLoaded;

	sf::Text titleText;
	sf::Text entryTexts[maxScores];
	sf::Text promptText;
	sf::Text noScoreText;

	const char* saveFile;

	void intToChar(int n, char* buf)
	{
		if (n == 0)
		{
			buf[0] = '0';
			buf[1] = '\0';
			return;
		}
		char tmp[20];
		int t = 0;
		int idx = 0;
		while (n > 0)
		{
			tmp[t++] = '0' + (n % 10);
			n /= 10;
		}
		for (int r = t - 1; r >= 0; r--)
			buf[idx++] = tmp[r];
		buf[idx] = '\0';
	}

	void sortScores()
	{
		for (int i = 1; i < entryCount; i++)
		{
			ScoreEntry key = entries[i];
			int j = i - 1;
			while (j >= 0 && entries[j].score < key.score)
			{
				entries[j + 1] = entries[j];
				j--;
			}
			entries[j + 1] = key;
		}
	}

public:
	Scoreboard()
	{
		entryCount = 0;
		fontLoaded = false;
		saveFile = "scores.dat";

		for (int i = 0; i < maxScores; i++)
		{
			entries[i].name[0] = '\0';
			entries[i].score = 0;
			entries[i].level = 0;
		}
	}

	bool loadFont(const char* path)
	{
		if (font.loadFromFile(path))
		{
			fontLoaded = true;

			titleText.setFont(font);
			titleText.setString("HIGH SCORES");
			titleText.setCharacterSize(70);
			titleText.setFillColor(sf::Color::Yellow);
			titleText.setOutlineColor(sf::Color::Black);
			titleText.setOutlineThickness(3);
			titleText.setPosition(550.0f, 60.0f);

			for (int i = 0; i < maxScores; i++)
			{
				entryTexts[i].setFont(font);
				entryTexts[i].setCharacterSize(36);
				entryTexts[i].setOutlineColor(sf::Color::Black);
				entryTexts[i].setOutlineThickness(2);
				entryTexts[i].setPosition(300.0f, 180.0f + i * 60.0f);
			}

			promptText.setFont(font);
			promptText.setCharacterSize(28);
			promptText.setFillColor(sf::Color::White);
			promptText.setOutlineColor(sf::Color::Black);
			promptText.setOutlineThickness(2);
			promptText.setString("Press Escape to return to Menu");
			promptText.setPosition(550.0f, 840.0f);

			noScoreText.setFont(font);
			noScoreText.setCharacterSize(40);
			noScoreText.setFillColor(sf::Color(180, 180, 180));
			noScoreText.setOutlineColor(sf::Color::Black);
			noScoreText.setOutlineThickness(2);
			noScoreText.setString("No scores yet. Play a game first!");
			noScoreText.setPosition(350.0f, 400.0f);

			return true;
		}
		return false;
	}

	void load()
	{
		entryCount = 0;
		std::ifstream file(saveFile, std::ios::binary);
		if (!file.is_open()) return;

		file.read(reinterpret_cast<char*>(&entryCount), sizeof(int));
		if (entryCount < 0 || entryCount > maxScores)
		{
			entryCount = 0;
			return;
		}
		for (int i = 0; i < entryCount; i++)
			file.read(reinterpret_cast<char*>(&entries[i]), sizeof(ScoreEntry));

		file.close();
		sortScores();
	}

	void save()
	{
		std::ofstream file(saveFile, std::ios::binary);
		if (!file.is_open()) return;

		file.write(reinterpret_cast<char*>(&entryCount), sizeof(int));
		for (int i = 0; i < entryCount; i++)
			file.write(reinterpret_cast<char*>(&entries[i]), sizeof(ScoreEntry));

		file.close();
	}

	void addScore(const char* playerName, int score, int level)
	{
		if (score <= 0) return;

		if (entryCount < maxScores)
		{
			int ni = 0;
			while (playerName[ni] != '\0' && ni < 49)
			{
				entries[entryCount].name[ni] = playerName[ni];
				ni++;
			}
			entries[entryCount].name[ni] = '\0';
			entries[entryCount].score = score;
			entries[entryCount].level = level;
			entryCount++;
		}
		else
		{
			int lowestIdx = 0;
			for (int i = 1; i < maxScores; i++)
			{
				if (entries[i].score < entries[lowestIdx].score)
					lowestIdx = i;
			}
			if (score > entries[lowestIdx].score)
			{
				int ni = 0;
				while (playerName[ni] != '\0' && ni < 49)
				{
					entries[lowestIdx].name[ni] = playerName[ni];
					ni++;
				}
				entries[lowestIdx].name[ni] = '\0';
				entries[lowestIdx].score = score;
				entries[lowestIdx].level = level;
			}
		}
		sortScores();
		save();
	}

	void draw(sf::RenderWindow& window)
	{
		if (!fontLoaded) return;

		window.draw(titleText);

		if (entryCount == 0)
		{
			window.draw(noScoreText);
		}
		else
		{
			for (int i = 0; i < entryCount; i++)
			{
				char line[150] = "";
				char numBuf[20];

				intToChar(i + 1, numBuf);
				strcat_s(line, numBuf);
				strcat_s(line, ".  ");

				strcat_s(line, entries[i].name);
				strcat_s(line, "     Score: ");

				intToChar(entries[i].score, numBuf);
				strcat_s(line, numBuf);
				strcat_s(line, "    ");

				if (entries[i].level == 0)
					strcat_s(line, "Campaign");
				else
				{
					strcat_s(line, "Survival Lv");
					intToChar(entries[i].level, numBuf);
					strcat_s(line, numBuf);
				}

				entryTexts[i].setString(line);

				if (i == 0)
					entryTexts[i].setFillColor(sf::Color::Yellow);
				else if (i == 1)
					entryTexts[i].setFillColor(sf::Color(192, 192, 192));
				else if (i == 2)
					entryTexts[i].setFillColor(sf::Color(205, 127, 50));
				else
					entryTexts[i].setFillColor(sf::Color::White);

				window.draw(entryTexts[i]);
			}
		}

		window.draw(promptText);
	}

	~Scoreboard()
	{
	}
};