#include <iostream>

int checkPos(std::string maze[], int x, int y) {
    int maxWidth = maze[0].length();
    int maxHeight = 25;

    if ((maxHeight > y && y >= 0) && (maxWidth > x && x >= 0)) {
        if (maze[y][x] == ' ') return 1;
        if (maze[y][x] == '#') return 0;
        
        std::cout << maze[y][x] << " ";
        
        return 0;

    }

    return 0;

}

void findOut(std::string maze[], int x, int y, int previous) {
    int top = checkPos(maze, x, y - 1);
    int left = checkPos(maze, x - 1, y);
    int right = checkPos(maze, x + 1, y);
    int bottom = checkPos(maze, x, y + 1);

    if (top == 1 && previous != 3) {
        findOut(maze, x, y - 1, 1);
    }
    if (right == 1 && previous != 4) {
        findOut(maze, x + 1, y, 2);
    }
    if (bottom == 1 && previous != 1) {
        findOut(maze, x, y + 1, 3);
    }
    if (left == 1 && previous != 2) {
        findOut(maze, x - 1, y, 4);
    }
}

int main() {

    setlocale(LC_ALL, "Rus");

    std::string maze[25] = {
    "####B######################",
    "# #       #   #      #    #",
    "# # # ###### #### ####### #",
    "# # # #       #   #       #",
    "#   # # ######### # ##### #",
    "# # # #   #       #     # #",
    "### ### ### ############# #",
    "# #   #     # #           #",
    "# # #   ####### ###########",
    "# # # #       # #         C",
    "# # ##### ### # # ####### #",
    "# # #     ### # #       # #",
    "#   ##### ### # ######### #",
    "######### ### #           #",
    "# ####### ### #############",
    "A           #   ###   #   #",
    "# ############# ### # # # #",
    "# ###       # # ### # # # #",
    "# ######### # # ### # # # F",
    "#       ### # #     # # # #",
    "# ######### # ##### # # # #",
    "# #######   #       #   # #",
    "# ####### ######### #######",
    "#         #########       #",
    "#######E############D######"
    };

    int x, y;

    std::cin >> x >> y;

    if (maze[y][x] == '#') {
        std::cout << "Не верные кординаты";
        return 0;
    }
    
    findOut(maze, x, y, 0);

	return 0;
}

