#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Utility.h"
#include "Entity.h"
#include "Map.h"

#define PLAYER_H 0.5f
#define PLAYER_W 0.5f

struct GameState
{
    Map* map;
    Entity* player;
    Entity* enemies;
    std::vector<Entity*> enemies_v;
    std::vector<Entity*> playerBullet;
    
    Entity* key;
    
    

    Mix_Music* bgm;
    Mix_Chunk* jump_sfx;

    int next_scene_id;
};


class Scene {
public:
    int m_number_of_enemies = 1;

    int lives = 3;
    GameState m_state;
    
    virtual void initialise() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(ShaderProgram* program) = 0;
    
    void playerBullet(){
        m_state.playerBullet.push_back(new Entity);
        m_state.playerBullet.back()->set_entity_type(ENEMY);
        m_state.playerBullet.back()->set_width(0.2f);
        m_state.playerBullet.back()->set_height(0.2f);
        m_state.playerBullet.back()->set_jumping_power(1.0f);
        m_state.playerBullet.back()->m_texture_id = Utility::load_texture("assets/bullet.png");;
        m_state.playerBullet.back()->set_position(m_state.player->get_position());
        m_state.playerBullet.back()->set_movement(glm::vec3(0.0f));
        m_state.playerBullet.back()->set_speed(2.0f);
        m_state.playerBullet.back()->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
        m_state.playerBullet.back()->set_movement(glm::vec3(2.0f, 0.0f, 0.0f));
        m_state.playerBullet.back()->activate();
    }
    GameState const get_state() const { return m_state; }
};
