//
//  LevelC.cpp
//  SDLProject
//
//  Created by Tommaso Palmieri on 09/12/23.
//  Copyright © 2023 ctg. All rights reserved.
//

#include "LevelC.hpp"
#include "Utility.h"

#define LEVEL_WIDTH 14
#define LEVEL_HEIGHT 8
#define LEVEL_C_ENEMIES 1

unsigned int LEVELC_DATA[] =
{
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2,
    2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 2, 2,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
    3, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2
};

LevelC::~LevelC()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    //Mix_FreeChunk(m_state.jump_sfx);
    //Mix_FreeMusic(m_state.bgm);
}

void LevelC::checkEnemyCollision(){


    for (int i = 0; i<LEVEL_C_ENEMIES; ++i){
        bool collisionCheck;
        collisionCheck = m_state.player->check_collision(&m_state.enemies[i]);
        if (collisionCheck){
        if (m_state.player->get_velocity().y < 0){
            m_state.enemies[i].deactivate();
        } else {
            
            if (lives>0){lives--;
                m_state.player->set_position(glm::vec3(5.0f, 0.0f, 0.0f));
            }
            else {m_state.player->deactivate();
                alive = false;
            }
            
        }
    }
    
}


}

void LevelC::initialise()
{
    m_state.next_scene_id = -1;
    font_id = Utility::load_texture("assets/font1.png");
    GLuint map_texture_id = Utility::load_texture("assets/tileset.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELC_DATA, map_texture_id, 1.0f, 4, 1);

    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
     // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(5.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->m_speed = 2.5f;
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/george_0.png");

    // Walking
    m_state.player->m_walking[m_state.player->LEFT] = new int[4] { 1, 5, 9, 13 };
    m_state.player->m_walking[m_state.player->RIGHT] = new int[4] { 3, 7, 11, 15 };
    m_state.player->m_walking[m_state.player->UP] = new int[4] { 2, 6, 10, 14 };
    m_state.player->m_walking[m_state.player->DOWN] = new int[4] { 0, 4, 8, 12 };

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index = 0;
    m_state.player->m_animation_time = 0.0f;
    m_state.player->m_animation_cols = 4;
    m_state.player->m_animation_rows = 4;
    m_state.player->set_height(0.8f);
    m_state.player->set_width(0.8f);
    m_state.player->activate();

    // Jumping
    m_state.player->m_jumping_power = 5.0f;

    /**
     Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture("assets/soph.png");

    m_state.enemies = new Entity[1];
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].set_width(0.8f);
    m_state.enemies[0].set_height(0.8f);
    m_state.enemies[0].set_ai_type(JUMPER);
    m_state.enemies[0].set_ai_state(IDLE);
    m_state.enemies[0].set_jumping_power(1.0f);
    m_state.enemies[0].m_texture_id = enemy_texture_id;
    m_state.enemies[0].set_position(glm::vec3(4.0f, 2.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_speed(0.5f);
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.enemies[0].activate();
    /**
     BGM and SFX
     */

}

void LevelC::update(float delta_time)
{
    checkEnemyCollision();
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    
    for (int i = 0; i<LEVEL_C_ENEMIES; ++i){
        
        m_state.enemies[i].update(delta_time, m_state.player, NULL, 0, m_state.map);
        
    }
    
    
    
    if (m_state.player->get_position().y < -10.0f & m_state.player->get_position().x>10.0f ) {
        won = true;
    };
}

void LevelC::render(ShaderProgram* program)
{
    m_state.map->render(program);
    
    if (m_state.player->is_active()){
        m_state.player->render(program);
    }
    
    
    for (int i = 0; i<LEVEL_C_ENEMIES; ++i){
        
        if (m_state.enemies[i].is_active()){
            m_state.enemies[i].render(program);
        }
        
    }
    
    if (!alive){
        
        Utility::draw_text(program, font_id, "YOU LOST!", 0.5, 0.00000005, m_state.player->get_position());
    }
    
    if (won){
        glm::vec3 textPos = m_state.player->get_position();
        textPos.y=-1.0f;
        Utility::draw_text(program, font_id, "YOU WON!", 0.5, 0.00000005, textPos);
    }
    

}


