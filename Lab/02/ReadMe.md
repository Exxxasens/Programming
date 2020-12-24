<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе 2 - Алиса<br> по дисциплине "Программирование"</h3>
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
1. Получить представления о структуре post-запроса;
2. Изучить webhooks как метод взаимодействия web-приложений;
## Постановка задачи
Регистрация и разрботка навыка для Алисы на сервисе Яндекс.Диалоги;
Создание backend веб-приложения на языке C++, которое будет выполнять следующие функции:
 - Составление продуктовой корзины:
    - Добавление продукта в корзину;
    - Удаление продукта из корзины;
    - Очистка корзины;
    - Вывод списка товаров в корзине;
    - Подсчёт стоимости товаров в корзине.
    - Вывод справочной информации по навыку;
 - Регистрация webhook-ов сторонних сервисов
 - Отправка данных на сторонние сервисы

Разработать приложение стороннего сервиса на языке Python, которое выполяет следующие функции:
 - Ожидание данных о покупке;
 - Сохранание поступивших данных в excel-документ

## Выполнение работы
Для работы серверного приложения потребуется несколько дополнительных библиотек:
 - **cpp_httplib** - используется для отправки и получения http/https запросов.
 - **nlohmann json** - используется для работы с JSON

Для установки библиотек создаем папку **include**, внутрь которой переместим заголовочные файлы этих библиотек. После этого добавим эту папку в настройки проекта, чтобы она была добавлена как дополнительный каталог.

Для взаимодействия с дургими сервисами будут использованы webhooks, которые хранятся в json файле webhooks.json, для этого реализованы следующие функции:
 - loadWebhooks - функция принимает в качестве аргумента имя файла, загружает его, если он существует, парсит json и возвращает массив строк;
 - saveWebhooks - принимает в качестве аргумента имя файла, массив строк, создает json и сохраняет его;
 - addWebhook - Добавляет вебхук (строку) в массив и сохраняет этот массив с помощью функции saveWebhooks;
 - deleteWebhook - принимает вебхук в качестве аргумента и удаляет элемент из массива и сохраняет изменный массив с помощью функции saveWebhooks;

Когда поступает запрос на адрес "/webhooks", сервер формирует ответ:
Читаем html шаблон, в котором заменяем заглушку на блок указанный, столько раз сколько webhook-ов, при этом вместо внутри блока должен быть конкретный webhook.
Читаем файл-шаблон, далее определяем блок. Для каждого вебхука применяем блок-шаблон, заменяем заглушки,
добавляем результат в общую строку, далее вставляем эту строку в шаблон. Шаблон отправляем клиенту. 

Для удаления или добавления вебхука используем POST запрос, проверяем в req объекте свойство del или set, в зависимости от которого будет вызвана соответствующая функция.

Для подготовки к работе с сервисом Яндекс.Диалоги создадим URL, это можно сделать с помощью приложение ngrok, запускаем приложение в консоли прописываем команду ngrok http 1234, где http - протоколо, 1234 - порт, по умолчанию и так используется localhost, поэтому его не нужно указывать. В результате получаем URL с помощью которого можно взаимодействовать с нашим приложением.

На сервисе Яндекс.Диалоги регистрируем навык, после чего настраиваем его. Указываем имя навыка, в моем случае "Программирование тест", указываем в качестве backend'a Webhooks URL и указываем полученный с помощью ngrok URL. Далее указываем использовать хранилище данных в навыке, для того чтобы мы могли использовать сессионное состояние. Тип доступа указываем приватный, дополнительно указываем категорию, пример запросов, описание и иконку, после этого навык настроен, теперь его нужно сохранить и опубликовать.

![alt text](https://sun9-43.userapi.com/impf/StzAqxlj3wS9XcilPkDSOWdUxnl5Pi2qlkkBzw/CjPAAFPwsdw.jpg?size=693x825&quality=96&proxy=1&sign=64f2a54e1d2598efa9bdda10b9ea983a&type=album)

Рисунок 1 - Настройки навыка

![](https://sun9-63.userapi.com/impf/sm6qm03vaE38y5fluZ8PuQnJ6PejZDoZZgmu8w/v-7nWv_XKbw.jpg?size=499x406&quality=96&proxy=1&sign=76186ee2f9f593688988f5d188133f33&type=album)

Рисунок 2 - Демонстрация работы функционала корзина

![](https://sun9-67.userapi.com/impf/96YTyvrESFrXeX2PKxkpB7RJiXIxI2bG7g9bxg/BMgkYUqZ1GA.jpg?size=506x600&quality=96&proxy=1&sign=8eedffbfe6e1ee302bccfcd5c264faf5&type=album)

Рисунок 3 - Демонстрация работы функционала помощь

![](https://sun9-53.userapi.com/impf/K3kkWb_CaKoKvNHyx6kLzWBY0veSsxfwDjQ3zQ/wcOUObjgb9A.jpg?size=658x284&quality=96&proxy=1&sign=e920ba12a7da73a72992040661c6a010&type=album)

Рисунок 4 - Страница управления webhook-ами

![](https://sun9-39.userapi.com/impf/Wnec8iAu5eMw8Epk8HVP6mjgLnVbX5dEhLB6fg/xrga59t9nYE.jpg?size=708x230&quality=96&proxy=1&sign=e4408a5f04cdb21019f20b3d4ebec09c&type=album)

Рисунок 5 - Заполненная таблица

### Исходный код серверного приложения:
```c++
#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <vector>
#include <nlohmann/json.hpp>
#include <algorithm>


using json = nlohmann::json;
using namespace httplib;

std::string replace_all(std::string str, const std::string& remove, const std::string& insert) {
    std::string::size_type pos = 0;
    while ((pos = str.find(remove, pos)) != std::string::npos)
    {
        str.replace(pos, remove.size(), insert);
        pos++;
    }

    return str;
}

std::vector<std::string> loadWebhooks(std::string fileName) {
    std::ifstream jsonFile(fileName);

    if (jsonFile.is_open()) {
        json js = json::parse(jsonFile);
        return js["webhooks"].get<std::vector<std::string>>();
    }
    else {
        std::vector<std::string> webhooks;
        return webhooks;
    }

}

void saveWebhooks(std::string fileName, std::vector<std::string> &list) {

    json js;

    js["webhooks"] = json::array();

    for (int i = 0; i < list.size(); i++) {
        js["webhooks"].push_back(list[i]);
    }

    std::ofstream file(fileName);
    file << js;

}

std::vector<std::string> webhooks = loadWebhooks("webhooks.json");

void addWebhook(std::string webhook) {
    webhooks.push_back(webhook);
    saveWebhooks("webhooks.json", webhooks);
}

void deleteWebhook(std::string webStr) {
    webhooks.erase(std::remove(webhooks.begin(), webhooks.end(), webStr), webhooks.end());
    saveWebhooks("webhooks.json", webhooks);
}


void res_webhooks(const Request& req, Response& res) {

    if (req.method == "POST") {
        if (req.has_param("del")) {
            deleteWebhook(std::string(req.get_param_value("del")));
        }

        if (req.has_param("set")) {
            addWebhook(std::string(req.get_param_value("set")));
        }
    }

    std::ifstream file("dashboard.html");
    std::string webhooksReplace;
    std::string templateStr = u8R"(
        <div class="form-row align-items-center">
            <div class="col">
              <input type="text" value="{Webhook URL}" class="form-control mb-2" disabled>
            </div>
 
            <div class="col">
                <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
            </div>
        </div>
    )";

    if (file.is_open()) {
        std::string str;
        std::getline(file, str, '\0');

        for (int i = 0; i < webhooks.size(); i++) {
            webhooksReplace += replace_all(templateStr, "{Webhook URL}", std::string(webhooks[i]));

        }
    
        res.set_header("Content-Type", "text/html");
        res.set_content(replace_all(str, "{webhooks_list}", webhooksReplace), "text/html");
    }

}

int sendRequest(std::string uri, std::string data) {

    std::size_t start = uri.find("://", 0);
    if (start == std::string::npos)
    {
        return -1;
    }
    start += 3;
    std::size_t end = uri.find("/", start + 1);
    std::string protocol = uri.substr(0, start - 3);
    std::string host = uri.substr(start, end - start);
    std::string path = uri.substr(end);

    Client cli(host.c_str());
    auto res = cli.Post(path.c_str(), data, "application/json");
    if (res) {
        if (res->status == 200) {
            std::cout << res->body << std::endl;
        }
        else {
            std::cout << "Status code: " << res->status << std::endl;
        }
    }
    else {
        auto err = res.error();
        std::cout << "Error code: " << err << std::endl;
    }

}

void emitWebhooks(std::string check) {
    std::cout << "WEBHOOKS LIST" << std::endl;
    for (int i = 0; i < webhooks.size(); i++) {
        sendRequest(webhooks[i], check);
    }
}

void gen_response(const Request& req, Response& res) {
    // Выводим на экран тело запроса
    json request = json::parse(req.body.c_str());
    json response;
    std::string command;

    if (request["request"].contains("command")) {
        command = request["request"]["command"].get<std::string>();
    }

    response["response"] = json::object();
    response["response"]["buttons"] = json::array();

    response["response"].push_back({ "end_session", false });
    response["version"] = "1.0";

    response["session_state"] = request["state"]["session"];

    if (request["session"]["new"] == true) {
        response["response"]["text"] = u8R"(Здравствуйте! Я помогу вам с покупками.)";
        response["response"]["tts"] = u8R"(Здравствуйте! Я помогу вам с покупками.)";
        response["session_state"] = json::object();
        response["session_state"].push_back({ "enable_voice", true });
        response["session_state"].push_back({ "cart", json::array() });
        response["session_state"].push_back({ "mode", "default" });
    }
    if (request["request"]["type"] == "ButtonPressed") {
        std::string action = request["request"]["payload"]["action"].get<std::string>();
        std::string str;
        if (action == "mute") {
            response["response"]["text"] = u8R"(Молчу, молчу)";
            response["session_state"]["enable_voice"] = false;
        }

        if (action == "speak") {
            response["response"]["text"] = u8R"(Хорошо)";
            response["response"]["tts"] = u8R"(Хорошо)";
            response["session_state"]["enable_voice"] = true;
        }

        if (action == "help") {
            std::string helpText = u8R"(    
                Команды:
                1) Очистить корзину
                2) Добавить в корзину
                3) Удалить из корзины
                4) Что в корзине
                5) Сумма
                6) Покупка завершена
                О чем рассказать подробнее?
            )";
            response["response"]["text"] = helpText;
            response["response"]["tts"] = helpText;
            response["session_state"]["mode"] = "help";
        }
        if (action == "exit_help") {
            std::string helpText = u8R"(    
                Обращайся ещё
            )";
            response["response"]["text"] = helpText;
            response["response"]["tts"] = helpText;
            response["session_state"]["mode"] = "default";
        }
        if (action == "info") {
            std::string info = request["request"]["payload"]["message"].get<std::string>();
            response["response"]["text"] = info;
            response["response"]["tts"] = info;
        }
    }
    if(!command.empty()) {

        response["response"]["text"] = u8R"(Неизвестная команда)";
        response["response"]["tts"] = u8R"(Неизвестная команда)";

        if (command == u8R"(очистить корзину)") {
            response["session_state"]["cart"] = json::array();
            response["response"]["text"] = u8R"(Корзина пуста)";
            response["response"]["tts"] = u8R"(Корзина пуста)";
        }

        if (command.find(u8R"(добавить в корзину)") != std::string::npos) {
            std::string answ = u8R"(Неизвестная команда)";
            auto list = request["request"]["nlu"]["tokens"].get<std::vector<std::string>>();

            if (list.size() >= 5) {
                std::string itemName = list[3];
                int itemPrice = std::stoi(list[4]);

                bool wasFound = false;

                for (int i = 0; i < response["session_state"]["cart"].size(); i++) {
                    if (response["session_state"]["cart"][i]["name"] == itemName) {
                        wasFound = true;
                    }
                }

                if (wasFound) {
                    answ = u8R"(Товар уже добавлен в корзину)";
                }
                else {
                    auto itemObject = json::object();
                    itemObject["name"] = itemName;
                    itemObject["price"] = itemPrice;
                    response["session_state"]["cart"].push_back(itemObject);
                    answ = u8R"(ОК)";
                }
                

            }
            response["response"]["tts"] = answ;
            response["response"]["text"] = answ;
        }
        if (command.find(u8R"(очистить корзину)") != std::string::npos) {
            response["session_state"]["cart"] = json::array();
            response["response"]["tts"] = u8R"(Корзина пуста)";
            response["response"]["text"] = u8R"(Корзина пуста)";
        }
        if (command.find(u8R"(удалить из корзины)") != std::string::npos) {
            std::string answ = u8R"(Неизвестная команда)";
            auto list = request["request"]["nlu"]["tokens"].get<std::vector<std::string>>();
            if (list.size() == 4) {
                std::string itemName = list[3];

                bool wasFound = false;

                for (int i = 0; i < response["session_state"]["cart"].size(); i++) {
                    if (response["session_state"]["cart"][i]["name"] == itemName) {
                        wasFound = true;
                        response["session_state"]["cart"].erase(i);
                    }
                }

                if (wasFound) {
                    answ = u8R"(OK)";
                }
                else {
                    answ = u8R"(Товар отсутствует в корзине)";
                }
            }
            response["response"]["tts"] = answ;
            response["response"]["text"] = answ;
        }

        if (command.find(u8R"(что в корзине)") != std::string::npos) {
            std::stringstream items;
            items << u8R"(Товары в корзине: )" << '\n';
            bool wasFound = false;

            for (int i = 0; i < response["session_state"]["cart"].size(); i++) {
                wasFound = true;
                items << response["session_state"]["cart"][i]["name"].get<std::string>();
                items << " - ";
                items << response["session_state"]["cart"][i]["price"].get<int>();
                items << u8R"( рублей)";
                items << '\n';
            }

            if (wasFound) {
                response["response"]["tts"] = items.str();
                response["response"]["text"] = items.str();
            }
            else {
                response["response"]["text"] = u8R"(Корзина пуста)";
                response["response"]["ttl"] = u8R"(Корзина пуста)";
            }

        }

        if (command.find(u8R"(сумма)") != std::string::npos) {
            int sum = 0;
            std::stringstream strstream;
            
            bool wasFound = false;

            for (int i = 0; i < response["session_state"]["cart"].size(); i++) {
                wasFound = true;
                sum += response["session_state"]["cart"][i]["price"].get<int>();
            }

            if (wasFound) {
                strstream << u8R"(Сумма: )" << sum << u8R"( рублей)";
                response["response"]["tts"] = strstream.str();
                response["response"]["text"] = strstream.str();
            }
            else {
                response["response"]["text"] = u8R"(Корзина пуста)";
                response["response"]["ttl"] = u8R"(Корзина пуста)";
            }

        }

        if (command.find(u8R"(покупка завершена)") != std::string::npos) {
            if (response["session_state"]["cart"].size() > 0) {
                json check;
                check["user_id"] = request["session"]["user"]["user_id"];
                check["check"] = response["session_state"]["cart"];
                emitWebhooks(check.dump());
                response["session_state"]["cart"] = json::array();
                std::cout << check.dump() << std::endl;
                response["response"]["tts"] = u8R"(Заходите ещё)";
                response["response"]["text"] = u8R"(Заходите ещё)";
            }
            else {
                response["response"]["text"] = u8R"(Корзина пуста)";
                response["response"]["ttl"] = u8R"(Корзина пуста)";
            }

        }


    }

    if (response["session_state"]["enable_voice"] == true) {
        response["response"]["tts"] = "";
    }

    if (response["session_state"]["mode"] == "help") {

        response["response"]["buttons"] = json::parse(
            u8R"(
                [
                  {
                    "title": "Как добавить в корзину?",
                    "payload": {
                      "action": "info",
                      "message": "Для того, чтобы добавить товар в корзину, нужно назвать товар (название товара не может содержать цифры), его цену. Например: Добавить в корзину картофель 100 рублей."
                    },
                    "hide": true
                  },
                  {
                    "title": "Как удалить из корзины?",
                    "payload": {
                      "action": "info",
                      "message": "Для того, чтобы удалить товар из корзины, нужно назвать команду и товар. Например: Удалить из корзины картофель."
                    },
                    "hide": true
                  },
                  {
                    "title": "Как узнать, что в корзине?",
                    "payload": {
                      "action": "info",
                      "message": "Для того, чтобы узнать, какой товар находится в корзине, нужно назвать команду: Что в корзине?"
                    },
                    "hide": true
                  },
                  {
                    "title": "Команда сумма",
                    "payload": {
                      "action": "info",
                      "message": "Сообщает пользователю суммарную стоимость всех товаров в корзине."
                    },
                    "hide": true
                  },
                  {
                    "title": "Как очистить корзину?",
                    "payload": {
                      "action": "info",
                      "message": "Для этого нужно назвать команду очистить корзину. Все товары будут удалены."
                    },
                    "hide": true
                  },
                  {
                    "title": "Как закончить покупки?",
                    "payload": {
                      "action": "info",
                      "message": "Для этого нужно назвать команду: Покупка завершена. Вы получите чек."
                    },
                    "hide": true
                  },
                    {
                    "title": "Выход из режима помощи",
                    "payload": {
                      "action": "exit_help"
                    },
                    "hide": true
                  }
                ]
            )"
        );


    }
    else {

        response["response"]["buttons"].push_back(json::parse(u8R"(                
                {
                    "title": "Помощь",
                    "payload": {
                        "action": "help"   
                    },
                    "hide": true
                }
            )"
        ));

        auto button = json::object();
        if (response["session_state"].contains("enable_voice") && response["session_state"]["enable_voice"] == true) {
            button["title"] = u8R"(Молчать)";
            button["payload"] = json::object();
            button["payload"]["action"] = "mute";
            button["hide"] = true;
        }
        else {
            button["title"] = u8R"(Говорить)";
            button["payload"] = json::object();
            button["payload"]["action"] = "speak";
            button["hide"] = true;
        }

        response["response"]["buttons"].push_back(button);

    }


    std::cout << response.dump() << std::endl;

    res.set_content(response.dump(), "text/json; charset=UTF-8");
}

void test_resp(const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain; charset=UTF-8");
}

int main() {

    setlocale(LC_ALL, "Rus");

    Server svr;
    svr.Get("/", test_resp);
    svr.Post("/", gen_response);
    svr.Get("/webhooks", res_webhooks);
    svr.Post("/webhooks", res_webhooks);
    std::cout << "Start server. OK\n";
    svr.listen("localhost", 1234);
}
```
### Исходный код клиентского приложения:
```python
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
            addedItems = 0

        return "OK"

if __name__ == "__main__":
    app.run()
```
Вывод: В результате проделанной работы, я разработал серверное и клиентское приложение. Получил представление о структуре POST запросов, изучил метод взаимодействия между веб-приложениями с помощью webhook-ов. 
