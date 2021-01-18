from tkinter import *
from PIL import Image, ImageTk
from random import randint

ballSet = {
    'aqua': Image.open('resources/ball-aqua.png').convert('RGBA'),
    'blue': Image.open('resources/ball-blue.png').convert('RGBA'),
    'red': Image.open('resources/ball-red.png').convert('RGBA'),
    'yellow': Image.open('resources/ball-yellow.png').convert('RGBA'),
    'violet': Image.open('resources/ball-violet.png').convert('RGBA'),
    'green': Image.open('resources/ball-green.png').convert('RGBA'),
    'pink': Image.open('resources/ball-pink.png').convert('RGBA')
}

root = Tk()
root.configure(background='#444444')
root.title('Lines')
matrix = []
nextColors = []
nextColorsLabels = []
score = 0
isGameEnd = False

cell_img = Image.open('resources/cell-bgr.png').convert('RGBA')
cell_bg = ImageTk.PhotoImage(cell_img.crop((1, 0, 67, 66)))

selectedCellBg = ImageTk.PhotoImage(cell_img.crop((1, 69, 67, 135)))


def endGame():
    global isGameEnd
    global score

    isGameEnd = True
    endGameLabel.configure(text="Игра окончена")
    score = 0


def countEmptyCells():
    counter = 0
    for i in matrix:
        for c in i:
            if not c.filledColor:
                counter += 1
    return counter


def addScore(value):
    global score
    global scoreLabel
    score += value
    if scoreLabel:
        scoreLabel.configure(text="Счет: " + str(score))


def findFirstSelected():
    for i in matrix:
        for j in i:
            if j.selected:
                return j
    return None


def click(event):
    selectCell(event.widget)


def getImgSmall(color):
    cell_bg = ImageTk.PhotoImage(ballSet[color].crop((11, 131, 44, 131 + 35)))
    return cell_bg


def genNextColors():
    global nextColors
    for i in range(3):
        rColor = randomColor()
        nextColors.append(rColor)
        nextColorsLabels[i].filledColor = rColor
        nextColorsLabels[i].filledImg = getImgSmall(rColor)
        nextColorsLabels[i].configure(image=nextColorsLabels[i].filledImg)


def addBalls():
    if isGameEnd:
        return

    if len(nextColors) < 3:
        genNextColors()

    c = 0

    while c < 3:
        cell = matrix[randint(0, 8)][randint(0, 8)]
        if not cell.filledColor:
            cell.filledColor = nextColors.pop()
            fillCell(cell)
            c += 1
            if countEmptyCells() == 0:
                break

    cleanCells()

    genNextColors()


def setDefaultBg(cell):
    cell.configure(image=cell_bg)


def unselectAll():
    for i in matrix:
        for j in i:
            if j.selected:
                j.selected = False
                fillCell(j)


def fillCell(cell):
    if not cell.filledColor:
        return

    if cell.selected:
        pastePos = (8, 75)
        cropPos = (1, 69, 67, 135)
    else:
        pastePos = (8, 6)
        cropPos = (1, 0, 67, 66)

    pic_size_same_as_bgr = Image.new("RGBA", cell_img.size)
    pic_size_same_as_bgr.paste(ballSet[cell.filledColor], pastePos)
    ball_over_bgr = Image.alpha_composite(cell_img, pic_size_same_as_bgr)
    img = ImageTk.PhotoImage(ball_over_bgr.crop(cropPos))
    cell.configure(image=img)
    cell.filledImg = img


def isPath(fromCell, toCell):
    n = len(matrix)
    visited = [[False for x in range(n)]
               for y in range(n)]
    return checkPath(matrix, fromCell.row, fromCell.column, toCell.row, toCell.column, visited)


def isSafe(i, j, matrix):
    if 0 <= i < len(matrix) and j >= 0 and j < len(matrix[0]):
        return True
    return False


def checkPath(matrix, i, j, toI, toJ, visited):
    if i == toI and j == toJ:
        return True
    if isSafe(i, j, matrix) and not matrix[i][j].filledColor and not visited[i][j]:
        visited[i][j] = True

        if checkPath(matrix, i - 1, j, toI, toJ, visited):
            return True

        if checkPath(matrix, i, j - 1, toI, toJ, visited):
            return True

        if checkPath(matrix, i + 1, j, toI, toJ, visited):
            return True

        if checkPath(matrix, i, j + 1, toI, toJ, visited):
            return True

    return False


def placeCell(fromCell, toCell):
    if toCell.filledColor:
        return

    toCell.filledColor = fromCell.filledColor
    fromCell.filledColor = None
    fillCell(toCell)
    setDefaultBg(fromCell)


def cleanCells():
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            cellColor = matrix[i][j].filledColor

            if not cellColor:
                continue

            right = True
            bottom = True
            rightCounter = 0
            bottomCounter = 0
            counter = 1

            while right or bottom:

                if not (right and
                        isSafe(i, j + counter, matrix) and
                        matrix[i][j + counter].filledColor and
                        cellColor == matrix[i][j + counter].filledColor):
                    right = False
                else:
                    rightCounter = counter + 1

                if not (bottom and
                        isSafe(i + counter, j, matrix) and
                        matrix[i + counter][j].filledColor and
                        cellColor == matrix[i + counter][j].filledColor):
                    bottom = False
                else:
                    bottomCounter = counter + 1

                if not right and not bottom:
                    break

                counter += 1

            if rightCounter >= 5:

                for k in range(counter):
                    c = matrix[i][j + k]
                    c.selected = False
                    c.filledColor = None
                    setDefaultBg(c)

                addScore(rightCounter * 2)

            if bottomCounter >= 5:

                for k in range(counter):
                    c = matrix[i + k][j]
                    c.selected = False
                    c.filledColor = None
                    setDefaultBg(c)

                addScore(bottomCounter * 2)
    if countEmptyCells() == 0:
        endGame()
        return


def selectCell(cell):
    if cell.selected and cell.filledColor:
        cell.selected = False
        fillCell(cell)
    elif (not cell.selected) and not cell.filledColor:
        selected = findFirstSelected()
        if selected:
            isCanPlace = isPath(cell, selected)
            if isCanPlace:
                placeCell(selected, cell)
                addBalls()
                unselectAll()
    else:
        unselectAll()
        cell.selected = True
        fillCell(cell)


def randomColor():
    colorList = [
        'aqua', 'blue', 'red', 'yellow', 'violet', 'green', 'pink'
    ]
    return colorList[randint(0, len(colorList) - 1)]


for i in range(9):
    row = []
    for j in range(9):
        lbl = Label(root, image=cell_bg, borderwidth=0, bg='#444444')

        lbl.grid(row=i,
                 column=j,
                 padx=1,
                 pady=1)

        lbl.filledImg = None
        lbl.filledColor = None
        lbl.selected = False
        lbl.row = i
        lbl.column = j
        lbl.bind('<Button-1>', click)

        row.append(lbl)

    matrix.append(row)


def cleanField():
    for i in matrix:
        for j in i:
            j.selected = False
            j.filledColor = None
            j.filledImg = None
            setDefaultBg(j)


def initGame():
    global isGameEnd
    global score

    cleanField()
    score = 0
    addBalls()
    isGameEnd = False
    if endGameLabel:
        endGameLabel.configure(text="")
    if scoreLabel:
        scoreLabel.configure(text="Счет: " + str(score))


scoreLabel = Label(root, text="Счет: 0", bd=0, bg='#444444', fg='#ffffff', font=("Arial", 32))
scoreLabel.grid(row=0, column=9, padx=50, pady=1)

skipBtn = Button(root, text="Сделать ход", bd=0, bg='#444444', fg='#ffffff', font=("Arial", 18), command=addBalls)
skipBtn.grid(row=1, column=9, padx=50, pady=1)

endGameLabel = Label(root, borderwidth=0, bg='#444444', fg='#ffffff', font=("Arial", 32))
endGameLabel.grid(row=4, column=9, padx=50, pady=1)

restartGameBtn = Button(root, text="Новая игра", bd=0, bg='#444444', fg='#ffffff', font=("Arial", 18), command=initGame)
restartGameBtn.grid(row=3, column=9, padx=50, pady=1)

nextColorsLabel = Label(root, bd=0, bg='#444444', fg='#ffffff')
nextColorsLabel.grid(row=2, column=9, padx=20, pady=1)

for i in range(3):
    lbl = Label(nextColorsLabel, image=cell_bg, borderwidth=0, bg='#444444')
    lbl.grid(row=0,
             column=i,
             padx=5,
             pady=1)

    lbl.filledImg = None
    lbl.filledColor = None
    lbl.row = i
    lbl.column = j
    nextColorsLabels.append(lbl)

initGame()
root.mainloop()
