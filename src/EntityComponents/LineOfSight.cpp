//Provides ability for enemy to have line of sight
#include "EntityComponents/LineOfSight.hpp"
// header hasn't been written yet!

/*
LineOfSight::LineOfSight() {}

bool LineOfSight::entityInSight(Entity enemy, Entity player){
	float dist = sqrt(pow(enemy.x-player.x,2)+pow(enemy.y-player.y,2));
	if(dist<=enemySightDistance){
		float x3 = enemy.x+cos(enemyAngle);
		float y3 = enemy.y+sin(enemyAngle);
		float a = pow(enemy.x-player.x,2)+pow(enemy.y-player.y,2);
		float b = pow(enemy.x-x3,2)+pow(enemy.y-y3,2);
		float c = pow(x3-player.x,2)+pow(y3-player.x,2);
		float angle = acos((a+b-c)/sqrt(4*a*b));
		if(angle<=enemySightAngle){
			//still need to write a check for walls here
			return true
		}
	}
	return false;
}
*/

