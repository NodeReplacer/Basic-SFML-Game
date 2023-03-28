#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

//Private functions
void Player::initVariables() {
    this->movementSpeed = 5.f;
    this->hpMax = 10;
    this->hpCurr = hpMax;
}

void Player::initShape() {
    this->playerShape.setFillColor(sf::Color::Green);
    this->playerShape.setSize(sf::Vector2f(50.f,80.f));
}

//Public functions
Player::Player(float x, float y) {
    /*
        Constructor function for the player class.
        We set the initial position here though because initVariables
        is supposed to initialize special variables like being alive and stuff.
        The position is something that needs to be established before everything.
    */
    this->playerShape.setPosition(x, y);

    //Establish variables that are outside of scope.
    this->initVariables();
    this->initShape();
}

Player::~Player() {

}

//Accessors -
const sf::RectangleShape & Player::getShape() const {
    //Very simple. Returns the shape of the player. For collision detection
    return this->playerShape;
}
const int &Player::getHp() const {
    return this->hpCurr;
}
const int &Player::getHpMax() const {
    return this->hpMax;
}

//Public functions (other objects, like Game.h, will use these occasionally)
void Player::takeDamage(const int damage) {
    //Game overs are handled elsewhere.

    //Ensure hpCurr is above 0
    if (this->hpCurr > 0) {
        //Ensure that hp is above 0 before doing anything.
        this->hpCurr -= damage;
    }
    else if (this->hpCurr < 0) {
        //Prevent health from going below 0.
        this->hpCurr = 0;
    }
}

void Player::gainHealth(const int health) {
    if (this->hpCurr < this->hpMax) {
        this->hpCurr += health;
    }

    if (this->hpCurr > this->hpMax) {
        //Limit current hp to within hpMax
        this->hpCurr = this->hpMax;
    }
}

void Player::handleInput() {
    //Keyboard Input
    //Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->playerShape.move(-this->movementSpeed, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->playerShape.move(this->movementSpeed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->playerShape.move(0.f, -this->movementSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->playerShape.move(0.f, this->movementSpeed);
    }
    /*
    //Debug text to kill yourself.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->hpCurr = 0;
    }
    */
}

void Player::updateWindowBounds(const sf::RenderTarget *target) {
    //getGlobalBounds stores 4 values that give us our x, y, width, and height.
    //Good for finding our rectangle size.
    //It comes as left, top, width, and height.x`

    //Left window boundary collision
    if (this->playerShape.getGlobalBounds().left <= 0.f) {
        this->playerShape.setPosition(0.f, this->playerShape.getGlobalBounds().top);
    }
    // Right Windows Boundary Collision
    // this->playerShape.getGlobalBounds().left is the coordinates of the left side (it's all we have)
    // So on the right side of window we need to add the width of the player rectangle
    // for the right side of the player to be correctly known by the window bounds collision.
    if (this->playerShape.getGlobalBounds().left + this->playerShape.getGlobalBounds().width >= target-> getSize().x) {
        this->playerShape.setPosition(target->getSize().x - this->playerShape.getGlobalBounds().width, this->playerShape.getGlobalBounds().top);
    }

    //Top Bounds collision
    if (this->playerShape.getGlobalBounds().top <= 0.f) {
        this->playerShape.setPosition(this->playerShape.getGlobalBounds().left, 0.f);
    }
    //Bottom Bounds collision
    if (this->playerShape.getGlobalBounds().top + this->playerShape.getGlobalBounds().height >= target->getSize().y) {
        this->playerShape.setPosition(this->playerShape.getGlobalBounds().left, target->getSize().y - this->playerShape.getGlobalBounds().height);
    }
}

void Player::update(sf::RenderTarget* target) {
    /*
        Update the player in game logic terms not rendering terms.
        But we take a RenderTarget pointer anyway because we
        need the window to calculate the window collision bounds.

        Perhaps target should be renamed gameWindow.
    */

    //Player input handling. Game handling also exists in game.cpp.
    this->handleInput();

    //Window bounds collision
    this->updateWindowBounds(target);
}

void Player::playerRender(sf::RenderTarget* target) {
    //We need to pass in a RenderTarget to tell this function where we are
    //rendering our Player to. A pointer will be better because we don't need
    //the window in front of us we just need directions.
    target->draw(this->playerShape);
}

void Player::applyGravity(float gravity) {
    /*
        Move the player down at a rate determined by gravity. Or by deltaTime.
        Whichever.
    */

}
