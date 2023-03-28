//
// Created by user on 3/20/2023.
//

#include "Enemy.h"

void Enemy::initShape(const sf::RenderWindow& window) {
    this->shape.setRadius(static_cast<float>(rand()%10+15));
    //Ball color
    sf::Color color;
    //Set random color for circle
    switch(this->type) {
        case DEFAULT:
            color = sf::Color(rand()%255,rand()%255,rand()%255,rand()%255 + 1);
            break;
        case HURTING:
            color = sf::Color::Red;
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2.f);
            break;
        case HEALING:
            color = sf::Color::Green;
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2.f);
            break;
    }

    this-> shape.setFillColor(color);
    this->shape.setPosition(
        sf::Vector2f(
            static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
            static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
        )
    );

}

void Enemy::initVariables() {

}

Enemy::Enemy(const sf::RenderWindow& window, int type) : type(type) {
    //If you're confused about : type(type) up there, remember it's the same as doing:
    //this->type = type;
    //in this code block.

    this->initVariables();
    this->initShape(window);
}

Enemy::~Enemy() {

}

const sf::CircleShape Enemy::getShape() const {
    //Return enemy shape to check collision.
    return this->shape;
}

const int &Enemy::getType() const {
    return this->type;
}

void Enemy::update() {

}

void Enemy::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}


