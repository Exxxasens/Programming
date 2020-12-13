from flask import Flask, request
import datetime
import os
import openpyxl

app = Flask(__name__)

if os.path.exists('data.xlsx'):
    print("book exist")
    book = openpyxl.open('data.xlsx')
    sheet = book.active
else:
    print('book is need to create')
    book = openpyxl.Workbook()
    sheet = book.active
    sheet['A1'] = "N"
    sheet['B1'] = 'User ID'
    sheet['C1'] = 'Datetime'
    sheet['D1'] = 'Item'
    sheet['E1'] = 'Price'

sheet = book.active


addedItems = 0
count = sheet.max_row or 0
count += 1
print(count)

@app.route('/', methods=['POST'])
def index():
    if request.method == 'POST':
        result = request.get_json()
        global count
        global addedItems

        user_id = result['user_id']

        for item in result["check"]:
            sheet[count][0].value = count-1
            sheet[count][1].value = user_id
            sheet[count][2].value = datetime.datetime.now()
            sheet[count][3].value = item['name']
            sheet[count][4].value = item['price']
            count += 1
            addedItems += 1

        if addedItems >= 1000:
            book.save('data.xlsx')

        book.save('data.xlsx')

        return "OK"

if __name__ == "__main__":
    app.run()