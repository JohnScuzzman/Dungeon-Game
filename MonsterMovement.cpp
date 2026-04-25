int MoveMonsters (int **room, int floorMax) {
    for (int i = 0; i < floorMax; i++) {
        for (int j = 0; j < floorMax; j++){ 
            if(room[i][j] == 1) {
                return 1;
            } 
        }  
    }
    return 1;
}