def run_game():
    tries = 5
    counter = 0
    random_num = 55
    user_win = False

    print("У вас есть " + str(tries) + " попыток отгадать загаданное число от  0 до 100")

    while tries > counter:
        n = int(input())
        counter += 1

        if n > random_num:
            print("Загаданное число меньше")
        elif n < random_num:
            print("Загаданное число больше")
        else:
            user_win = True
            break

    if user_win:
        print("Поздравляю! Вы угадали")
    else:
        print('Вы проиграли. Было загадано: ' + str(random_num))

    restart = int(input("Хотите начать сначала? (1 - ДА )\n"))
    if restart == 1:
        return run_game()


run_game()
