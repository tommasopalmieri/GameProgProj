#include "Scene.h"


class LevelA : public Scene {
public:
    
    
    float time_acc = 0;
    int ENEMY_COUNT = 1;
    int font_id;
    bool alive = true;
    
    bool gotKey = false; 
    ~LevelA();
    void checkEnemyCollision();
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
    void shootBullet(Entity* shootingEntity);
    void shootBullet(Entity* shootingEntity, glm::vec3 dir);
};
