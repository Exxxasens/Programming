def bmi(weight: float, height: float) -> float:
    return weight / (height**2)


def print_bmi(bmi: float):
    if bmi < 18.5:
        print("Underweight")
    elif 18.5 <= bmi < 25:
        print("Normal")
    elif 25 <= bmi < 30:
        print("Overweight")
    else:
        print("Obesity")


w, h = map(float, input().split())
h = h / 100
print_bmi(bmi(w, h))
