#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace sf;

class Game
{
private:
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event e;

	//Mouse position
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Resourse
	Font font;

	//Text
	Text uitext;

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHold;

	//Game object
	std::vector<RectangleShape>  enemies;
	RectangleShape enemy;

	//Functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemy();


public:
	//Contructors & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();

	void pollEvent();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();
};

