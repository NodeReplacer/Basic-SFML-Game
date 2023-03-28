//
// Created by user on 3/20/2023.
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#ifndef GRAVMAYBE_ENEMY_H
#define GRAVMAYBE_ENEMY_H

//They're not enemies anymore they're just points being collected right now.
enum EnemyTypes {
    DEFAULT = 0,
    HURTING,
    HEALING,
    NROFTYPES,
};

class Enemy {
private:
    sf::CircleShape shape;
    int type;

    //Initialization functions
    void initShape(const sf::RenderWindow& window); //I could use a pointer here instead of a reference.
    void initVariables();
public:
    //Constructor/Destructor
    Enemy(const sf::RenderWindow& window, int type);
    virtual ~Enemy();

    //Accessor
    const sf::CircleShape getShape() const; //For collision detection.
    const int& getType() const;

    //Public functions.
    void update();
    void render(sf::RenderTarget &target);
};


#endif //GRAVMAYBE_ENEMY_H
