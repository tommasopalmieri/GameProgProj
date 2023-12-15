//
//  LevelC.hpp
//  SDLProject
//
//  Created by Tommaso Palmieri on 09/12/23.
//  Copyright © 2023 ctg. All rights reserved.
//

#include "Scene.h"


class LevelC : public Scene {
public:
    
    
    float time_acc = 0;
    float time_acc_bis = 0;
    int ENEMY_COUNT = 1;
    int font_id;
    bool alive = true;
    
    bool gotKey = false;
    ~LevelC();
    void checkEnemyCollision();
    void shootBulletUp(Entity* shootingEntity);
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
    void shootBullet(Entity* shootingEntity);
};
