//
// Created by user on 3/15/2023.
//
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#ifndef GRAVMAYBE_PLAYER_H
#define GRAVMAYBE_PLAYER_H

class Player {
private:
    sf::RectangleShape playerShape;

    int hpCurr;
    int hpMax;

    float movementSpeed;
    float velocity;

    void initVariables();
    void initShape();
public:
    Player(float x = 0.f, float y = 0.f);
    virtual ~Player();

    //Accessors
    const sf::RectangleShape& getShape() const; //For collision detection
    const int& getHp() const;
    const int& getHpMax() const;

    //Public functions.
    void takeDamage(const int damage);
    void gainHealth(const int health);

    void handleInput();
    void updateWindowBounds(const sf::RenderTarget *target);
    void update(sf::RenderTarget* target);
    void playerRender(sf::RenderTarget* target);
    void applyGravity(float gravity);
};


#endif //GRAVMAYBE_PLAYER_H
