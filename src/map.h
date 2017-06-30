#ifndef MAP_H
#define MAP_H

/** MAP is used to save and read maps.
*/
struct MAP{
	int speed; //!< speed defines how fast OBJECTs move
	int attacker_num; //!< number of attackers that can be on screen at once 
	int asteroid_num; //!< number of asteroids that can be on screen at once
	int friend_num; //!< number of friends that can be on screen at once
	int rock_num; //!< number of rocks that can be on screen at once
	int attacker_lives; //!< number of lives attackers get
};

#endif // MAP_H