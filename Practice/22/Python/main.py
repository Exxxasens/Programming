maze = [
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
]

x, y = map(int, input().split())


def checkPos(maze, x, y):
    maxWidth = len(maze[0])
    maxHeight = len(maze)

    if maxHeight > y >= 0 and maxWidth > x >= 0:
        if maze[y][x] == " ":
            return 1
        if maze[y][x] == "#":
            return 0

        print(maze[y][x], end='')

    return 0


def findOut(maze, x, y, previous):
    top = checkPos(maze, x, y - 1)
    left = checkPos(maze, x - 1, y)
    right = checkPos(maze, x + 1, y)
    bottom = checkPos(maze, x, y + 1)

    if top == 1 and previous != 3:
        findOut(maze, x, y - 1, 1)
    if right == 1 and previous != 4:
        findOut(maze, x + 1, y, 2)
    if bottom == 1 and previous != 1:
        findOut(maze, x, y + 1, 3)
    if left == 1 and previous != 2:
        findOut(maze, x - 1, y, 4)


if maze[y][x] == "#":
    print("Не верные кординаты")
else:
    findOut(maze, x, y, 0)
