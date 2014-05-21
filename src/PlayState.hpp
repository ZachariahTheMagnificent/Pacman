#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include "STP/TMXLoader.hpp"

#include "Engine/GameState.hpp"
#include "Engine/Utils/Clock.hpp"

#include "Pacman.hpp"
#include "Ghost.hpp"

class PlayState : public GameState {
 public:
    void init(ResourceManager* resources, Settings* settings);
    void exit(ResourceManager* resources);
    void pause();
    void resume();

    void handleEvents(GameEngine* game);

    // Update state
    void frameStarted(GameEngine* game);
    void frameEnded(GameEngine* game);

    void draw(GameEngine* game);

    static PlayState* Instance() {
        return &PlayState_;
    }

 protected:
    PlayState();

 private:
    static PlayState PlayState_;

    Pacman* pacman_;
    Ghost* blinky_;
    tmx::TileMap* map_;

    Pacman::Direction next_dir_;

 private:
    bool AABBCollision(const sf::FloatRect& obj1, const sf::FloatRect& obj2);

    // Update pacman and verify collisions
    void updatePacman();
    void updateGhost(Ghost* ghost);

    bool checkMapCollision(const sf::FloatRect& collision_box);
    bool checkFoodCollision();
};

#endif  // PLAY_STATE_HPP
