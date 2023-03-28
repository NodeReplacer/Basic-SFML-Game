//
// Created by user on 3/16/2023.
//

#include "Game.h"

//Private Functions
void Game::initializeVariables() {
    this->window = nullptr;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxEnemies = 20.f;
    this->points = 0;
    this->hurtNum = 0;
    this->hurtLimit = static_cast<int>(maxEnemies*0.25);

    //Initialize Font
    if (!this->font.loadFromFile("C:/Personal Projects/GravMaybe/Font/VCR_OSD_MONO_1.001.ttf")) {
        std::cout << "! ERROR::GAME::INITFONT::COULD NOT LOAD VCR_OSD_MONO_1.001.ttf" << "\n";
    }
}

void Game::InitializeText() {
    //Ensure the text has a font before it tries to display. It might be better to
    //make them separate functions to ensure it order of actions by using the stack.
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(48);

    //End Game Text
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    float textXPos = this->window->getSize().x * 0.5;
    float textYPos = this->window->getSize().y * 0.75;
    this->endGameText.setPosition(textXPos, textYPos);
    this->endGameText.setString("YOU ARE DEAD. EXIT GAME.");

}

void Game::initializeWindow() {
    this->windowDimensions.height = 1080;
    this->windowDimensions.width = 1920;
    this->window = new sf::RenderWindow(this->windowDimensions, "GravNav");
    this->window->setFramerateLimit(60);
}
//End of Private Functions

//Constructor /Destructor
Game::Game() {
    this->initializeVariables();
    this->initializeWindow(); //Window comes after because initVariables sets a window related var to null.
    //Intialize text.
    this->InitializeText();
}
Game::~Game() {
    delete this->window;
}
//End of Constructor/Destructor

//Accessor
const bool Game::running() const {
    return this->window->isOpen(); // && this->gameEnded == false;
}
//End of Accessors

//Public functions
void Game::pollEvents() {
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            // Window closed
            case sf::Event::Closed:
                this->window->close();
                break;

            // Key pressed
            case sf::Event::KeyPressed:
                // Which key was pressed?
                switch (this->event.key.code)
                {
                    case sf::Keyboard::Escape:
                        // Close the window.
                        this->window->close();
                        break;
                    // Default case (unrecognized key was pressed).
                    default:
                        break;
                } // END of switch (event.key.code)

            default:
                break;

        } // END OF switch (event.type)
    }
}

const int Game::MakeRandomBall() {
    int randomNum = rand() % 100 + 1;
    int enemType = DEFAULT;

    if (randomNum > 50 && randomNum <= 80) {
        if (this->hurtNum == this->hurtLimit) {
            std::cout << this->hurtNum;
            enemType = EnemyTypes::DEFAULT;
            this->hurtNum = this->hurtLimit;
        }
        else {
            enemType = HURTING;
            ++this->hurtNum;
        }
    }
    else if (randomNum > 80 && randomNum <= 100) {
        enemType = EnemyTypes::HEALING;
    }
    return enemType;
}

void Game::UpdatePlayer() {
    this->player.update(this->window);

    if (this->player.getHp() <= 0) {
        this->gameEnded = true;
    }
}

void Game::spawnEnemies() {
    //Timer
    if (this->spawnTimer < this->spawnTimerMax) {
        this ->spawnTimer += 1.f;
    }
    else if (this->enemyList.size() < this->maxEnemies){
        //Randomly select a type for our enemy.
        //But with a special case. If we go purely random we'll eventually have too many
        //Hurting balls. So we'll limit that in a special function.
        int enemType = MakeRandomBall();

        // emplace_back is the same as push_back
        this->enemyList.emplace_back(Enemy(*this->window, enemType));

        this->spawnTimer = 0.f;
    }
}

void Game::updateCollision() {
    //Check for collision between player and ball (enemy) and remove the ball.
    for (size_t i = 0; i < this->enemyList.size(); ++i) {
        //Long line here gets the global bounds for the playershape and checks if anything
        //in my list of enemies intersects with the player
        //In broad terms that means we check if there is a collision between the two.
        if (this->player.getShape().getGlobalBounds().intersects(this->enemyList[i].getShape().getGlobalBounds())) {
            switch(this->enemyList[i].getType()) {
                case EnemyTypes::DEFAULT:
                    this->points++;
                    break;
                case EnemyTypes::HURTING:
                    this->player.takeDamage(1);
                    this->hurtNum--;
                    std::cout << this->hurtNum << "\n";
                    break;
                case EnemyTypes::HEALING:
                    this->player.gainHealth(1);
                    break;
            }
            //The iterator is pointing at the enemy that the player has intersected with.
            //The position is held by i, so we erase the enemy located at i from the list.
            this->enemyList.erase(this->enemyList.begin() + i);
        }
    }
}

void Game::updateGUI() {
    //String Streams are very useful. They accept all types of data and pass it into a string.
    //Taking out the tedium of casting. I don't know about its efficiency though.
    std::stringstream stringStream;

    //Update the string stream with the number of points.
    //It should look something like:
    // Points: 0
    // Health: 5/5
    stringStream << "Points: " << this->points << "\n"
                 << "Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";
    this->guiText.setString(stringStream.str());
}

void Game::update() {
    //Wait for and catch keyboard/window events.
    this->pollEvents();

    if (this->gameEnded == false) {
        this->spawnEnemies();
        this->UpdatePlayer();
        //Update the player and their keyboard events.
        this->player.update(this->window);

        //Collision
        this->updateCollision();
        //So how do I create this? Should I use box2d or not?
        //I do want to make particularly interesting physics but don't know if
        //I am going to make a complex platformer here or in godot.
        //Slope handling is quite difficult to do, from what I can tell.

        this->updateGUI();
    }
}

void Game::renderGUI(sf::RenderTarget* target) {
    //NOTE: The target for rendering is what is being drawn onto, NOT WHAT IS BEING DRAWN.
    target->draw(this->guiText);
}

void Game::render() {
    /*
        - clear old frame
        - render objects (like the player)
        - display frame in window.
    */

    // clear the window and prep for drawing
    this->window->clear(sf::Color::Black);

    //render objects (like the player)
    this->player.playerRender(this->window);

    for (auto enemy : this->enemyList) {
        enemy.render(*this->window);
    }

    //Render GUI
    this->renderGUI(this->window);

    //Render End Text
    if(this->gameEnded) {
        this->window->draw(this->endGameText);
    }

    // display the window.
    this->window->display();
}