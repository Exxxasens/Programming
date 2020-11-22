from tkinter import *
import requests
root = Tk()

def fetch():
    resp = requests.get("http://localhost:3000/raw")
    if(resp.ok):
        return resp.json()

    return False


Label(root, text="Симферополь", bg="#FEB92F", fg="#333333", font=("Helvetica", 12, 'bold'), width=30, height=1).pack(fill=X)
description_label = Label(root, bg="#FEB92F", fg="#333333", font=("Helvetica", 10, 'normal'), width=30, height=2)
description_label.pack(fill=X)
temp_label = Label(root, fg="#333333", font=("Helvetica", 32, "bold"), height=3)
temp_label.pack(expand=1)

Label(root, bg="#FEB92F", height=3).pack(fill=X)

def refresh_data():
    data = fetch()

    if data:
        description_label["text"] = data["description"]
        temp_label["text"] = str(data["temp"]) + "°C"

        print(data["description"])
        print(data["temp"])

    else:
        description_label["text"] = "Невозможно загрузить данные"
        temp_label["font"] = ("Helvetica", 24, "bold")
        temp_label["text"] = "Невозможно загрузить данные"

def on_click(event):
    refresh_data()

root.bind("<Button-1>", on_click)
refresh_data()

root.mainloop()
