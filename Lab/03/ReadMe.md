<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе 3 - Игра "Lines"<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-202(1)<br>
Окатьев Олег Анатольевич<br>
направления подготовки 09.03.04 "Программная инженерия"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>

## Цель:
1. Закрепить навыки разработки программ с простым графическим интерфейсом пользователя на зыке Python при помощи библиотеки Tkinter;
2. Получить представление о разработке простых игровых приложений.
## Постановка задачи
1. Используя стандартный модуль для разработки программ с графическим интерфейсом Tkinter реализуйте игру Lines на зыке Python.
2. В качестве образца графического интерфейса используйте [данную игру.](http://game-shariki.ru/linii-2)

## Выполнение работы
ДДля создание внешнего визуального интерфейса игры потребовались несколько библиотек:
 - **Tkinter** - используется для создания вншенго графического интерфейса игры.
 - **PIL** - используется для работы с изображениями (наложения друг на друга)

Для создания игрового поля (9*9), используется упаковщик grid, который позволяет создать сетку. Для каждого элемента сетки добавлены несколько дополнительных свойств (selected, filledColor, filledImg), которые помогают сохранять состояние каждой клетки поля.
#### Действие Инициализация игры:

1. Если на экране была надпись "Игра окончена", она убирается.
2. Игровое поле очищается от шариков;
3. Все плитки игрового поля становятся вида: плитка не выбрана (стандартный);
4. Выбранного шарика нет;
5. Счёт равен нулю;
6. Выполнение действия Добавление шариков на игровое поле.
7. Игра переходит в состояние Шарик не выбран;

Для этого была реализована функция initGame.

#### Действие Добавление шариков на игровое поле:
1. Проверяется буфер подсказки. В этом буфере хранятся цвета шариков которые появятся на поле на следующем ходе. Если буфер подсказки пустой, то генерируется 3 шарика случайного цвета и помещаются в буфер.
2. Из буфера подсказки достаются три шарика и добавляются на игровое поле в случайные места;
3. Если в процессе добавления очередного шарика на игровое поле для него НЕ оказывается свободного места:
    - Переход к действию Завершение игры.
4. После добавления всех шариков на игровое поле генерируется 3 новых шарика случайного цвета и помещаются в буфер подсказки.

Для выполнения данных действий реализована функция addBalls, которая в случае, если существуют пустые клетки добавляет 3 шарика, иначе завершает игру. Для реализации буфера реализована функция genNextColors, которая генерирует и добавляет в буфер 3 цвета, также работает с интерфейсом и отображает добавленные в буфер цвета.

#### Действие Проверка линий
1. Проверяем поле на присутствие линии из шариков одного цвета (линия - 5 элементов). Они могут быть расположены горизонтально, вертикально, по диагонали.
2. Линий найдены:
    - Шарики входящие в данную линий удаляются.
    - Выбранной клетки нет.
    - Шарик не выбран.
    - За каждый шарик добавляется по 2 очка.
3. Линии не найдены:
    - Шарик не выбран.
    - Добавляются шарики на игровое поле.
    - Выполняется проверка линий

Для реализации данного алгоритма реализована функция clearCells, которая для каждой клетки ищет горизонтальную, вертикальную или диагональную линию из 5 или более шаров. Если линия найдена, тогда она удалятся и выполняется функция addScore, которая добавляет счет и обновляет его.
 
#### Действие Перемещение шарика
1. Если шарик не выбран:
    - Пользователь кликает по пустой клетке:
        - Состояние не изменяется.
    - Пользователь кликает по шарику:
        - Плитка под шариком меняет свой цвет.
        - Шарик становится выбранным
2. Шарик выбран:
    - Пользователь кликает по пустой доступной плитке (на которой нет шаров, а так же если можно переместить шарик с текущий на указанную двигаясь только по пустым клеткам):
        - Плитка под шариком становится стандартного цвета.
        - Шарик перемещается на выбранную плитку.
        - Выбранного шарика нет.
        - Проверяются линии
    - Пользователь кликает по одному и тому же шарику:
        - Состояние не изменяется.
    - Пользователь кликает по другому шарику:
        - Другой шарик становится выбранным.
        - Плитка под текущим становится стандартной

Для реализации этой задачи реализована функция placeCell, которая перемещает шарик из одного элемента в другой. Перед этим происходит проверка, можно ли переместить шарик, если двигаться по пустым клеткам. Для этого реализована функция checkPath, которая рекурсивно пытается найти путь от одной клетки к другой.

#### Действие Завершение игры:
1. На экране появляется надпись: "Игра окончена".
2. Игра переходит в состояние Игра окончена.

Для выполнения данных действий реализована функция endGame, которая добавляет надпись, изменяет значений глобальной переменной isGameEnd на True.

![](https://sun9-26.userapi.com/impf/jMRJv7Tu2s46F4mS0zeuaxpVAGPnaJxnT6ve0A/ZXKgFyWyYzI.jpg?size=1694x1318&quality=96&proxy=1&sign=6edcd0b3b8b1f4c3b24e17606d24c401&type=album)

Рисунок 1 - Графический интерфейс игры

```python
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

    isGameEnd = True
    endGameLabel.configure(text="Игра окончена")


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
            diagonal = True

            rightCounter = 0
            bottomCounter = 0
            diagonalCounter = 0

            counter = 1

            while right or bottom or diagonal:

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

                if not (diagonal and isSafe(i + counter, j + counter, matrix) and matrix[i + counter][
                    j + counter].filledColor
                        and cellColor == matrix[i + counter][j + counter].filledColor):
                    diagonal = False
                else:
                    diagonalCounter = counter + 1

                if not right and not bottom and not diagonal:
                    break

                counter += 1

            if rightCounter >= 5:

                for k in range(counter):
                    c = matrix[i][j + k]
                    c.selected = False
                    c.filledColor = None
                    setDefaultBg(c)

                addScore(rightCounter * 2)

            elif bottomCounter >= 5:

                for k in range(counter):
                    c = matrix[i + k][j]
                    c.selected = False
                    c.filledColor = None
                    setDefaultBg(c)

                addScore(bottomCounter * 2)

            elif diagonalCounter >= 5:
                for k in range(counter):
                    c = matrix[i + k][j + k]
                    c.selected = False
                    c.filledColor = None
                    setDefaultBg(c)
                addScore(diagonalCounter * 2)

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

```
Вывод: В результате проделанной работы, я разработал игру с визуальным интерфейсом. Получил представление о способах разработки визуальных интерфейсов. Получил опыт использования библиотеки Tkinter.
