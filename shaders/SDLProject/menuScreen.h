//
//  menuScreen.h
//  SDLProject
//
//  Created by Tommaso Palmieri on 09/12/23.
//  Copyright © 2023 ctg. All rights reserved.
//
#include "Scene.h"

#ifndef menuScreen_h
#define menuScreen_h



class MenuScreen : public Scene {
    
public:
    int ENEMY_COUNT = 0;

    ~MenuScreen();
    GLuint font_id;

    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};


#endif /* menuScreen_h */
