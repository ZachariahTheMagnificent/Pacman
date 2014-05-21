#include "Ghost.hpp"

Ghost::Ghost(Name name, sf::Texture* ghost_texture, const std::string& working_dir) :
        eatable_(false),
        name_(name),
        state_(Normal),
        paused_(false) {
    ghost_texture_ = ghost_texture;
    this->loadJsonFile(working_dir + "assets/sprites/ghosts/ghosts.json", ghost_texture_);

    switch (name_) {
        case Blinky:
            name_string_ = "blinky";
            this->setDirection(Left);
            break;
        case Inky:
            name_string_ = "inky";
            break;
        case Clyde:
            name_string_ = "clyde";
            break;
        case Pinky:
            name_string_ = "pinky";
            break; 
    }   
}

Ghost::~Ghost() {}

void Ghost::setDirection(Ghost::Direction direction) {
    if (direction_ == direction) return;

    direction_ = direction;
    this->changeAnimation(state_);
}

const Ghost::Direction& Ghost::getDirection() const {
    return direction_;
}

const sf::Vector2f& Ghost::getVelocity() const {
    return velocity_;
}

sf::FloatRect Ghost::getCollisionBox() {
    sf::FloatRect g_bounds = this->getGlobalBounds();
    return sf::FloatRect(g_bounds.left + 3.f, g_bounds.top + 3.f, 8.f, 8.f);
}

void Ghost::setState(Ghost::State state) {
    state_ = state;
    this->changeAnimation(state);
}

void Ghost::updatePos() {
    if (paused_) return;

    switch(direction_) {
        case Left:
            velocity_ = sf::Vector2f(-1.f, 0);
            break;
        case Right:
            velocity_ = sf::Vector2f(1.f, 0);
            break;
        case Up:
            velocity_ = sf::Vector2f(0, -1.f);
            break;
        case Down:
            velocity_ = sf::Vector2f(0, 1.f);
            break;
    }

    this->move(velocity_);
}

void Ghost::changeAnimation(Ghost::State state) {
    const char* animation_name;
    switch (state) {
        case Normal:
            animation_name = name_string_.c_str();
            break;
        case Frightened:
            this->setAnimation("frightened");
            return;
            break;
        case OnlyEyes:
            animation_name = "eyes";
            break;
    }

    char up[15], down[15], left[15], right[15]; 

    sprintf(up, "%s-up", animation_name);
    sprintf(down, "%s-down", animation_name);
    sprintf(left, "%s-left", animation_name);
    sprintf(right, "%s-right", animation_name);

    switch (direction_) {
        case Left:
            this->setAnimation(left);
            break;
        case Right:
            this->setAnimation(right);
            break;
        case Up:
            this->setAnimation(up);
            break;
        case Down:
            this->setAnimation(down);
            break;
    }
}

void Ghost::pause() {
    this->pauseAnimation();
    paused_ = true;
}

void Ghost::resume() {
    this->resumeAnimation();
    paused_ = false;
}

bool Ghost::is_paused() {
    return paused_;
}
