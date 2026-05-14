#include <rogue.h>

/* 
Populates a monster struct with a char and their position.
monsterID is a random int 0-3 passed from map.c
*/ 
Monster CreateMonster(Position m_pos, int monsterID)
{   
    Monster monster;
    switch (monsterID) {
        /* Call functions from monsterinfo.c */
        case 0:
        AssignGoblinWarrior(&monster);
        break;
        case 1:
        AssignKoboldWarrior(&monster);
        break;
        case 2:
        AssignHobgoblinWarrior(&monster);
        break;
        case 3:
        AssignGoblinRanger(&monster);
        break;
        default:
        AssignGoblinWarrior(&monster);
        break; 
    }

    //Position pos;
    monster.pos.y = m_pos.y;
    monster.pos.x = m_pos.x;
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