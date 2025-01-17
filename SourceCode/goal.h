#ifndef GOAL_H
#define GOAL_H

#define GOAL_MAX   (9)

#define GOAL_TEX_W        (80.0f)   
#define GOAL_TEX_H        (80.0f)   
#define GOAL_PIVOT_X      (40.0f)    
#define GOAL_PIVOT_Y      (80.0f)  

void goal_init();
void goal_deinit();
void goal_update();
void goal_render();
void moveGoal0(OBJ2D* obj);




#endif