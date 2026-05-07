#include <rogue.h>

// Pass the position of the room center.
Monster CreateMonster(Position m_pos, char monsterChar)
{   
    Monster monster;
    //Position pos;
    monster.pos.y = m_pos.y;
    monster.pos.x = m_pos.x;
    monster.ch = monsterChar;
    monster.color = COLOR_PAIR(SEEN_COLOR);
    monster.visible = true;
    monster.seen = false;
    return monster;
}

// void MoveMonster(Position newPos)
// { 
//   if (map[newPos.y][newPos.x].noCollision)
//   {
//     monster.pos.y = newPos.y;
//     monster.pos.x = newPos.x;
//   }
// }