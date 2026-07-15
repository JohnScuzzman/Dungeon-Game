#include <rogue.h>

/* 
Makes a radius around the player in which they can see.
To increase the radius, increase the variable RADIUS below.
*/
void MakeFOV(Player* player)
	{ 
	int y, x, distance;
	Position target;
	map[player->pos.y][player->pos.x].visible = true;
	map[player->pos.y][player->pos.x].seen = true;

	for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) { 
		for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) { 
		target.y = y;
		target.x = x;
		distance = GetDistance(player->pos, target);

			if (distance < RADIUS) { 
				if (IsInMap(y, x) && LineOfSight(player->pos, target)) { 
						map[y][x].visible = true;
						map[y][x].seen = true;
				}
        /* UNSTABLE*/
        /* Use for a later psychic ability*/
        // else if (IsInMap(y, x) && !LineOfSight(player->pos, target)) {
        //     map[y][x].visible = false;
        // }
			} 
		} 
	} 
} 
  
/*
Clear the player's FOV to create it again after moving.
*/
void ClearFOV(Player* player)
{ 
  int y, x;

  for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++)
  { 
    for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++)
    {
      if (IsInMap(y, x))
        map[y][x].visible = false;
    }
  } 
} 

/* 
Calculates distance between two points.
Uses the hypotenuse formula.
If floor() and sqrt() 
*/ 
int GetDistance(Position origin, Position target)
{ 
  double dy, dx;
  int distance;
  dx = target.x - origin.x;
  dy = target.y - origin.y;
  distance = floor(sqrt((dx * dx) + (dy * dy)));

  return distance;
}

/* Simple function to check if the coordinates are within our map or not.*/ 
bool IsInMap(int y, int x)
{ 
  if ((0 < y && y < MAP_HEIGHT - 1) && (0 < x && x < MAP_WIDTH - 1))
  { 
    return true;
  }

  return false;
}

/* 
This is a mind melting algorithm but I attempted to break it down below.
Based entirely off the algorithm developed by Steven Register.
https://roguebasin.com/index.php/Simple_Line_of_Sight
*/
bool LineOfSight(Position origin, Position target)
{
  int t, x, y, abs_delta_x, abs_delta_y, sign_x, sign_y, delta_x, delta_y;

  /* Delta x is the origin's x minus the target x */
  delta_x = origin.x - target.x;
  delta_y = origin.y - target.y;

  /*Absolute value of those values*/
  abs_delta_x = abs(delta_x);
  abs_delta_y = abs(delta_y);

  /*Signed version to check negative or positive*/
  sign_x = GetSign(delta_x);
  sign_y = GetSign(delta_y);

  x = target.x;
  y = target.y;

  /*if x is greater, start x dominate loop.*/
  if (abs_delta_x > abs_delta_y)
  {
    /* t = twice the absolute of y minus the absolute of x*/
    t = abs_delta_y * 2 - abs_delta_x;

    do
    {
      /* if t is greater than or equal to zero then *
      * add the sign of delta_y to y                    *
      * subtract twice the absolute of delta_x from t   */
      if (t >= 0)
      {
        y += sign_y;
        t -= abs_delta_x * 2;
      }

      /* add the sign of delta_x to x *
      * add twice the adsolute of delta_y to t  */
      x += sign_x;
      t += abs_delta_y * 2;

      /* check to see if we are at the origin's position */
      if (x == origin.x && y == origin.y)
      {
        /* return that the target can see the origin */
        return true;
      }
    }
    /* keep looping until the target's sight is blocked *
    * by an object at the updated x,y coord */
    while (map[y][x].transparent);
    /* NOTE: map[y][x].transparent returns true *
       * if an object at the x,y coord. would block the targets *
       * sight                                                    */

      /* the loop was exited because the target's sight was blocked *
       * return FALSE: the target cannot see the origin */
    return false;
  }
  /*if y is greater, start y dominate loop.*/
  else
  {
    /* Y dominate loop, basically same as above.*/
    t = abs_delta_x * 2 - abs_delta_y;

    do
    {
      if (t >= 0)
      {
        x += sign_x;
        t -= abs_delta_y * 2;
      }

      y += sign_y;
      t += abs_delta_x * 2;

      if (x == origin.x && y == origin.y)
      {
        return true;
      }
    }
    while (map[y][x].transparent);

    return false;
  }
}

int GetSign(int a)
{
  return (a < 0) ? -1 : 1;
}