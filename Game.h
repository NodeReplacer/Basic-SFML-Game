#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <sstream>


//
// Created by user on 3/16/2023.
//
/*
    Wrapper class that handles game logic and rendering the scene.
    Essentially, the game loop is located in this class. Without this class being made
    the game loop will not exist either.
*/

#ifndef GRAVMAYBE_GAME_H
#define GRAVMAYBE_GAME_H

class Game {
private:
    //Variables
    bool gameEnded;
    //Window
    sf::RenderWindow* window; //Window pointer.
                              // Dynamically allocating it lets use safely delete the window when we want.
    sf::Event event;
    sf::VideoMode windowDimensions;

    //Game Objects
    Player player;
    std::vector<Enemy> enemyList;
    int points;
    int hurtNum; // The current number of hurting balls we have spawned.
    int hurtLimit; // A hard limit for how many hurting balls we can spawn.

    sf::Font font;
    sf::Text guiText;

    //Game Over Menu Objects. May need to be in its own class but maybe not.
    sf::Text endGameText;

    //These should probably be in their own factory.
    float spawnTimerMax;
    float spawnTimer;
    int maxEnemies;

    //Private functions
    void initializeVariables();
    void InitializeText();
    void initializeWindow();
public:
    //Constructors and destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool running() const; //Tell other programs that the game is running.

    //Functions - Update handles backend, render only draws the screen.
    void pollEvents(); //Catch keyboard events, window events, player actions basically.
    void spawnEnemies();
    const int MakeRandomBall();
    void UpdatePlayer();
    void updateCollision();
    void updateGUI();
    void update();

    void renderGUI(sf::RenderTarget* target);
    void render();
};


#endif //GRAVMAYBE_GAME_H
