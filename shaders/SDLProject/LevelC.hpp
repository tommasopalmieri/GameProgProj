//
//  LevelC.hpp
//  SDLProject
//
//  Created by Tommaso Palmieri on 09/12/23.
//  Copyright © 2023 ctg. All rights reserved.
//

#ifndef LevelC_hpp
#define LevelC_hpp

#include "Scene.h"

class LevelC : public Scene {
public:
    int ENEMY_COUNT = 1;
    int font_id;
    bool alive = true;
    bool won = false;
    ~LevelC();
    void checkEnemyCollision();
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};

#endif /* LevelC_hpp */
