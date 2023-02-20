#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	this->endGame = false;
	this->points = 0;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHold = false;
}

void Game::initWindow()
{
	this->videoMode.height = 680;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "Game 1!", Style::Close | Style::Resize);
	this->window->setFramerateLimit(60);

}

void Game::initFonts()
{
	if (this->font.loadFromFile("timesbd.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Fail to load font!" << "\n";
	}
}

void Game::initText()
{
	this->uitext.setFont(this->font);
	this->uitext.setCharacterSize(20);
	this->uitext.setFillColor(Color::White);
	this->uitext.setString("NONE");
}

void Game::initEnemy()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(Vector2f(100.f, 100.f));
	this->enemy.setFillColor(Color::Cyan);
	//this->enemy.setOutlineColor(Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

//Contructors & Destructors
Game::Game() 
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemy();
}
Game::~Game()
{
	delete this->window;
}


//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}


void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),0);

	//Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(Vector2f(15.f, 15.f));
		this->enemy.setFillColor(Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(Vector2f(30.f, 30.f));
		this->enemy.setFillColor(Color::Blue);
		break;
	case 2:
		this->enemy.setSize(Vector2f(50.f, 50.f));
		this->enemy.setFillColor(Color::Green);
		break;
	case 3:
		this->enemy.setSize(Vector2f(70.f, 70.f));
		this->enemy.setFillColor(Color::White);
		break;
	case 4:
		this->enemy.setSize(Vector2f(100.f, 100.f));
		this->enemy.setFillColor(Color::Red);
		break;
	default:
		this->enemy.setSize(Vector2f(100.f, 100.f));
		this->enemy.setFillColor(Color::Yellow);
		break;
	}

	this->enemies.push_back(this->enemy);
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->e))
	{
		switch (this-> e.type)
		{
		case Event::Closed:
			this-> window->close();
			break;
		case Event::KeyPressed:
			if (this->e.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;
	
	ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n";

	this->uitext.setString(ss.str());
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move and updating the enemy
	for (int i=0;i<enemies.size();i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 2.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			health -= 1;
		}
	}

	//Check if click on enemies

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->mouseHold == false)
		{
			this->mouseHold = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gain points
					if(this->enemies[i].getFillColor()== Color::Magenta)
						this->points += 10;
					if (this->enemies[i].getFillColor() == Color::Blue)
						this->points += 7;
					if (this->enemies[i].getFillColor() == Color::Green)
						this->points += 5;
					if (this->enemies[i].getFillColor() == Color::White)
						this->points += 3;
					if (this->enemies[i].getFillColor() == Color::Red)
						this->points += 1;

					//delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHold = false;
	}
}


//Functions
void Game::update()
{
	this->pollEvent();

	if (!this->endGame)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}

	//Endgame condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::renderText(RenderTarget& target)
{
	target.draw(this->uitext);
}

void Game::renderEnemies(RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	this->window->clear();

	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->display();
}
