
#include "LevelC.hpp"
#include "Utility.h"

#define LEVEL_WIDTH 35
#define LEVEL_HEIGHT 8
#define LEVEL_A_ENEMIES 2


unsigned int LevelC_DATA[] =
{
    2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,1,0,0,0,0,1,0,1,1,1,1,1,0,0,1,1,1,0,1,
    3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
    2, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
    3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 2, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 1,1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,1,1,1,0,1,
    3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    3, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};


LevelC::~LevelC()
{
    delete[] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}


void LevelC::shootBullet(Entity* shootingEntity){
    
    
    if (shootingEntity->is_active()){
        
        m_state.enemies_v.push_back(new Entity);
        
        glm::vec3 pos;
        pos = shootingEntity->get_position();
        pos.y -= 0.5f;
        
        m_state.enemies_v.back()->set_entity_type(BULLET);
        m_state.enemies_v.back()->set_width(0.2f);
        m_state.enemies_v.back()->set_height(0.2f);
        m_state.enemies_v.back()->set_jumping_power(1.0f);
        m_state.enemies_v.back()->m_texture_id = Utility::load_texture("assets/bullet.png");;
        m_state.enemies_v.back()->set_position(shootingEntity->get_position());
        m_state.enemies_v.back()->set_movement(glm::vec3(0.0f));
        m_state.enemies_v.back()->set_speed(10.0f);
        m_state.enemies_v.back()->set_acceleration(glm::vec3(-8.0f, 0.0f, 0.0f));
        m_state.enemies_v.back()->activate();
        
        shootingEntity->bullets.push_back(m_state.enemies_v.back());
    }

}

void LevelC::shootBulletUp(Entity* shootingEntity){
    
    
    if (shootingEntity->is_active()){
        
        m_state.enemies_v.push_back(new Entity);
        
        glm::vec3 pos;
        pos = shootingEntity->get_position();
        pos.y -= 0.5f;
        
        m_state.enemies_v.back()->set_entity_type(BULLET);
        m_state.enemies_v.back()->set_width(0.2f);
        m_state.enemies_v.back()->set_height(0.2f);
        m_state.enemies_v.back()->set_jumping_power(1.0f);
        m_state.enemies_v.back()->m_texture_id = Utility::load_texture("assets/bullet.png");;
        m_state.enemies_v.back()->set_position(shootingEntity->get_position());
        m_state.enemies_v.back()->set_movement(glm::vec3(0.0f));
        m_state.enemies_v.back()->set_speed(10.0f);
        m_state.enemies_v.back()->set_acceleration(glm::vec3(0.0f, 4.0f, 0.0f));
        m_state.enemies_v.back()->activate();
        
        shootingEntity->bullets.push_back(m_state.enemies_v.back());
    }

}




void LevelC::checkEnemyCollision(){


    for (size_t i = 0; i<m_state.enemies_v.size(); ++i){
        bool collisionCheck;
        collisionCheck = m_state.player->check_collision(m_state.enemies_v[i]);
        if (collisionCheck){
        if (m_state.player->get_velocity().y < 0){
            m_state.enemies_v[i]->deactivate();
        } else {
            
            if (lives>0){lives--;
                m_state.player->set_position(glm::vec3(2.0f, -1.0f, 0.0f));
            }
            else {m_state.player->deactivate();
                alive = false;
            }
            
        }
    }
        
        for (size_t j = 0; j<m_state.playerBullet.size(); ++j){
            
            if (m_state.playerBullet[j]->check_collision(m_state.enemies_v[i])){
                m_state.enemies_v[i]->deactivate();
                m_state.playerBullet[j]->deactivate();
                
            };
        }

    
}


}

void LevelC::initialise()
{
    const char  BGM_FILEPATH[]          = "assets/dooblydoo.mp3",
                BOUNCING_SFX_FILEPATH[] = "assets/bounce.wav";
    m_state.next_scene_id = -1;
    font_id = Utility::load_texture("assets/font1.png");
    GLuint map_texture_id = Utility::load_texture("assets/tileset.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LevelC_DATA, map_texture_id, 1.0f, 4, 1);

    // Code from main.cpp's initialise()
    /**
     George's Stuff
     */
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(1.3f, -0.8f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->m_speed = 2.0f;
    m_state.player->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
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
    m_state.player->set_height(PLAYER_H);
    m_state.player->set_width(PLAYER_W);
    m_state.player->activate();

    // Jumping
    m_state.player->m_jumping_power = 5.0f;

    /**
     Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture("assets/soph.png");

    m_state.enemies = new Entity[2];
    
    m_state.enemies_v.push_back(new Entity);
    
    m_state.enemies_v[0]->set_entity_type(ENEMY);
    m_state.enemies_v[0]->set_width(0.8f);
    m_state.enemies_v[0]->set_height(0.8f);
    m_state.enemies_v[0]->set_ai_type(GUARD);
    m_state.enemies_v[0]->set_ai_state(IDLE);
    m_state.enemies_v[0]->ai_activate(m_state.player);
    m_state.enemies_v[0]->set_jumping_power(1.0f);
    m_state.enemies_v[0]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[0]->set_position(glm::vec3(4.0f, -5.0f, 0.0f));
    m_state.enemies_v[0]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[0]->set_speed(0.5f);
    m_state.enemies_v[0]->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.enemies_v[0]->activate();
    
    
    m_state.enemies_v.push_back(new Entity);
    m_state.enemies_v[1]->set_entity_type(ENEMY);
    m_state.enemies_v[1]->set_width(0.8f);
    m_state.enemies_v[1]->set_height(0.8f);
//    m_state.enemies_v[1]->set_ai_type(WALKER);
//    m_state.enemies_v[1]->set_ai_state(IDLE);
    m_state.enemies_v[1]->set_jumping_power(1.0f);
    m_state.enemies_v[1]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[1]->set_position(glm::vec3(2.0f, -3.8f, 0.0f));
    m_state.enemies_v[1]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[1]->set_speed(0.5f);
    m_state.enemies_v[1]->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.enemies_v[1]->activate();
    
    
    m_state.enemies_v.push_back(new Entity);
    m_state.enemies_v[2]->set_entity_type(ENEMY);
    m_state.enemies_v[2]->set_width(0.8f);
    m_state.enemies_v[2]->set_height(0.8f);
    m_state.enemies_v[2]->set_ai_type(JUMPER);
    m_state.enemies_v[2]->set_ai_state(IDLE);
    m_state.enemies_v[2]->ai_activate(m_state.player);
    m_state.enemies_v[2]->set_jumping_power(1.0f);
    m_state.enemies_v[2]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[2]->set_position(glm::vec3(7.0f, -5.0f, 0.0f));
    m_state.enemies_v[2]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[2]->set_speed(-0.5f);
    m_state.enemies_v[2]->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.enemies_v[2]->activate();
    
    
    m_state.enemies_v.push_back(new Entity);
    m_state.enemies_v[3]->set_entity_type(ENEMY);
    m_state.enemies_v[3]->set_width(0.8f);
    m_state.enemies_v[3]->set_height(0.8f);
    m_state.enemies_v[3]->set_ai_type(JUMPER);
    m_state.enemies_v[3]->set_ai_state(IDLE);
    m_state.enemies_v[3]->ai_activate(m_state.player);
    m_state.enemies_v[3]->set_jumping_power(1.0f);
    m_state.enemies_v[3]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[3]->set_position(glm::vec3(13.0f, -3.0f, 0.0f));
    m_state.enemies_v[3]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[3]->set_speed(0.5f);
    m_state.enemies_v[3]->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.enemies_v[3]->activate();
    
    
    
    m_state.enemies_v.push_back(new Entity);
    m_state.enemies_v[4]->set_entity_type(ENEMY);
    m_state.enemies_v[4]->set_width(0.8f);
    m_state.enemies_v[4]->set_height(0.8f);
    m_state.enemies_v[4]->set_jumping_power(1.0f);
    m_state.enemies_v[4]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[4]->set_position(glm::vec3(15.0f, -4.0f, 0.0f));
    m_state.enemies_v[4]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[4]->set_speed(0.5f);
    m_state.enemies_v[4]->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.enemies_v[4]->activate();
    
    
    m_state.enemies_v.push_back(new Entity);
    m_state.enemies_v[5]->set_entity_type(ENEMY);
    m_state.enemies_v[5]->set_width(0.8f);
    m_state.enemies_v[5]->set_height(0.8f);
    m_state.enemies_v[5]->set_jumping_power(1.0f);
    m_state.enemies_v[5]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[5]->set_position(glm::vec3(17.0f, -3.0f, 0.0f));
    m_state.enemies_v[5]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[5]->set_speed(0.5f);
    m_state.enemies_v[5]->set_ai_type(JUMPER);
    m_state.enemies_v[5]->set_ai_state(IDLE);
    m_state.enemies_v[5]->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.enemies_v[5]->activate();
    
    m_state.enemies_v.push_back(new Entity);
    m_state.enemies_v[6]->set_entity_type(ENEMY);
    m_state.enemies_v[6]->set_width(0.8f);
    m_state.enemies_v[6]->set_height(0.8f);
    m_state.enemies_v[6]->set_jumping_power(1.0f);
    m_state.enemies_v[6]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[6]->set_ai_type(GUARD);
    m_state.enemies_v[6]->set_ai_state(IDLE);
    m_state.enemies_v[6]->set_position(glm::vec3(22.0f, -5.0f, 0.0f));
    m_state.enemies_v[6]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[6]->set_speed(0.5f);
    m_state.enemies_v[6]->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.enemies_v[6]->activate();
    
    m_state.enemies_v.push_back(new Entity);
    m_state.enemies_v[7]->set_entity_type(ENEMY);
    m_state.enemies_v[7]->set_width(0.8f);
    m_state.enemies_v[7]->set_height(0.8f);
    m_state.enemies_v[7]->set_jumping_power(1.0f);
    m_state.enemies_v[7]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[7]->set_position(glm::vec3(26.0f, -5.0f, 0.0f));
    m_state.enemies_v[7]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[7]->set_speed(0.5f);
    m_state.enemies_v[7]->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.enemies_v[7]->activate();
    
    m_state.enemies_v.push_back(new Entity);
    m_state.enemies_v[8]->set_entity_type(ENEMY);
    m_state.enemies_v[8]->set_width(0.8f);
    m_state.enemies_v[8]->set_height(0.8f);
    m_state.enemies_v[8]->set_jumping_power(1.0f);
    m_state.enemies_v[8]->m_texture_id = enemy_texture_id;
    m_state.enemies_v[8]->set_position(glm::vec3(31.0f, -4.0f, 0.0f));
    m_state.enemies_v[8]->set_movement(glm::vec3(0.0f));
    m_state.enemies_v[8]->set_speed(0.5f);
    m_state.enemies_v[8]->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.enemies_v[8]->activate();
    
    m_state.key = new Entity();
    m_state.key->set_entity_type(KEY);
    m_state.key->set_width(0.3f);
    m_state.key->set_height(0.3f);
    m_state.key->set_jumping_power(1.0f);
    
    m_state.key->m_texture_id = Utility::load_texture("assets/key.png");;
    m_state.key->set_position(glm::vec3(33.0f, -2.0f, 0.0f));
    m_state.key->set_movement(glm::vec3(0.0f));
    m_state.key->set_speed(0.5f);
    m_state.key->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_state.key->activate();
    

    
    //shootBullet(m_state.enemies_v[1]);
    
    
    /**
     BGM and SFX
     */

    
    
    
    
    
    // ––––– AUDIO STUFF ––––– //
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4.0f);

    m_state.jump_sfx = Mix_LoadWAV(BOUNCING_SFX_FILEPATH);
}

void LevelC::update(float delta_time)
{
    time_acc += delta_time;
    time_acc_bis += delta_time;
    
    checkEnemyCollision();
    

    // Check if player killed anyone
    
    for (size_t i = 0; i<m_state.playerBullet.size(); ++i){

        m_state.playerBullet[i]->update(delta_time, m_state.player, NULL, 0, m_state.map);

    }
    
    if (m_state.key->check_collision(m_state.player)){
        gotKey = true;
        m_state.key->deactivate();
    }
    
    m_state.player->update(delta_time, m_state.player, NULL, 0, m_state.map);
    
    for (size_t i = 0; i<m_state.enemies_v.size(); ++i){
        
        m_state.enemies_v[i]->update(delta_time, m_state.player, NULL, 0, m_state.map);
        
    }

    
    m_state.key->update(delta_time, m_state.player, NULL, 0, m_state.map);
    
    m_state.enemies_v[0]->ai_guard(m_state.player, HORIZONTAL);
    
    int random = rand() % 10;
    
    if (time_acc > (float(random)/float(10)+1.8) ){
        //playerBullet();
        shootBullet(m_state.enemies_v[1]);
        shootBullet(m_state.enemies_v[0]);
        shootBullet(m_state.enemies_v[3]);
        shootBullet(m_state.enemies_v[4]);
        
        time_acc = 0;
    }
    
    if (time_acc_bis > (float(random)/float(10)+0.5) ) {
        //playerBullet();
        
        shootBulletUp(m_state.enemies_v[4]);
        shootBulletUp(m_state.enemies_v[7]);
        shootBulletUp(m_state.enemies_v[8]);
        time_acc_bis = 0;
    }
    
    if (m_state.enemies_v[1]->get_position().y<-4.0f){
        m_state.enemies_v[1]->set_movement(glm::vec3(0.0f, 4.0f, 0.0f));
    }
    if (m_state.enemies_v[1]->get_position().y>-1.0f){
        m_state.enemies_v[1]->set_movement(glm::vec3(0.0f, -4.0f, 0.0f));
    }
    

    if (m_state.enemies_v[5]->get_position().x>=18.0){
        m_state.enemies_v[5]->set_movement(glm::vec3(-2.0f, 0.0f, 0.0f));
    }
    if (m_state.enemies_v[5]->get_position().y<16.0f){
        m_state.enemies_v[5]->set_movement(glm::vec3(2.0f, 0.0f, 0.0f));
    }
}

void LevelC::render(ShaderProgram* program)
{
    m_state.map->render(program);
    
    if (m_state.player->is_active()){
        m_state.player->render(program);
    }
    
    
    for (size_t i = 0; i<m_state.enemies_v.size(); ++i){
        
        if (m_state.enemies_v[i]->is_active()){
            m_state.enemies_v[i]->render(program);
        }
        
    }
    
    
    for (size_t i = 0; i<m_state.playerBullet.size(); ++i){
        
        if (m_state.playerBullet[i]->is_active()){
            m_state.playerBullet[i]->render(program);
        }
        
    }
    
    if (!alive){
        
        Utility::draw_text(program, font_id, "YOU LOST!", 0.5, 0.00000005, m_state.player->get_position());
    }
    
    
    if (m_state.key->is_active()) m_state.key->render(program);
    if (!m_state.key->is_active()) {Utility::draw_text(program, font_id, "YOU WON!", 0.5, 0.00000005, m_state.player->get_position());};
    

}
