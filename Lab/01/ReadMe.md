<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе 1 - Погода<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ПИ-б-о-202(1)<br>
Окатьев Олег Анатольевич<br>
направления подготовки 09.03.02 Программная инженерия</p>
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
1. Закрепить навыки разработки многофайловыx приложений;
2. Изучить способы работы с API web-сервиса;
3. Изучить процесс сериализации/десериализации данных в/из json;
4. Получить базовое представление о сетевом взаимодействии приложений;
## Постановка задачи
Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса.  В качестве источника данных о погоде используйте: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С++ и клиентское приложение на языке Python.

Серверное приложение (далее Сервер) предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность получения данных в формате JSON и виде html виджета (для вставки виджета на страницу будет использоваться iframe).

Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.

## Выполнение работы
### Работа с сервсом openweathermap.org
 Для работы с  сервисом openweathermap.org нужно получить api ключ. Для этого регистрируемся на сервисе. Переходим в раздел API keys, где уже будет сгенерирован ключ, который можно использовать.
 
 Полученный api ключ: 
 ```
 d5b675a76430a03a2cef0129b194dc8c
 ```
  Псоле изучения api сервиса, можно создать запрос для получения погоды в Симферополе с почасовым интервалом, на русском языке, в градусах цельсия.
```
http://api.openweathermap.org/data/2.5/onecall?lat=44.5725&lon=34.6388&exclude=daily,minutely,current,alerts&appid=d5b675a76430a03a2cef0129b194dc8c&lang=ru&units=metric
```
Для этого были использованы следующие параметры запроса.
 - **lat=44.5715** - географическая широта города Симферополь
 - **lon=34.6388** - географическая высота города Симферополь
 - **exclude=daily,minutely,current,alerts** - исключаем лишние данные из запроса, потому что для проекта нужена погода с почасовым интервалом, остальное можно исключить.
 - **appid=d5b675a76430a03a2cef0129b194dc8c** - api ключ
 - **lang=ru** - указываем русский язык для ответа.
 - **units=metric** - указываем, что данные должны быть в метрической системе

Далее делем get запрос и получаем в ответ JSON, внутри которго нас интересует поле **hourly**, которое является массивом из 48 элементов, потому что мы получаем прогноз на следующие 48 часов.

### Работа с сервисом worldtimeapi.org

Создаем запрос для получения времени в Симферополе:
```
http://worldtimeapi.org/api/timezone/Europe/Simferopol
```
Отправляем get запрос и получем в ответ JSON, который содержит поле **unixtime**, которое содержит целое число секунд, прошедших с полуночи (00:00:00 UTC) 1 января 1970 года.

### Подготовка серверного приложения
Для работы серверного приложения потребуется несколько дополнительных библиотек:
 - **cpp_httplib** - используется для отправки и получения http/https запросов.
 - **nlohmann json** - используется для работы с JSON

Для установки библиотек создаем папку **include**, внутрь которой переместим заголовочные файлы этих библиотек. После этого добавим эту папку в настройки проекта, чтобы она была добавлена как дополнительный каталог.

Если серверу приходит запрос по адресу /, сервер подготавливает html виджет и отправляет его клиенту. Для оптимизации количества запросов к сервису openweathermap, они кэшируются в переменную cachedWeather, которая хранит полученный JSON ответ от сервиса. Для того чтобы проверить был ли вообще осуществлен запрос к сервису, используется переменная bool типа isWeatherLoaded.

Для того чтобы отдать правильный прогноз на следующий час, нужно сделать запрос на сервис worldtimeapi.org и получить текущее время в формате **unixtime**. Каждый ответ от сервиса openweathermap содержит массив **hourly**, внутри которого каждый элемент содержит временную метку, с которой мы будем сравнивать полученное текущее время, начиная с первого элемента, мы находим первый элемент, чья временная метка будет больше чем текущее значение **unixtime**, таким образом можно найти прогноз на ближайший час, если ни один элемент не будет найден, значит кэш устарел и нужно заново сделать запрос на сервис openweathermap. Записываем номер найденного элемента в переменную **cachedIndex**. Для этого была реализована функция **checkCache**. А для получения данных с сервиса openweathermap реализована функция **refreshCache**. 

Для формирования html шаблона виджета, читаем html шаблон, внутри которого есть фрагменты, которые будут заменены на реальные данные. Для этого реализована функция **findAndReplace**. После того как шаблон будет заполнен, отправляем его клиенту с указанным **Content-Type: text/html**

Если серверу пришел запрос по адресу /raw, тогда мы проверяем кэш, если нужно обновляем его, затем формируем JSON объект внутри которого будет 2 поля:
 - **description**
 - **temp**

После этого отправляем ответ клиенту, с указанным **Content-Type: application/json**

### Исходный код серверного приложения:
```c++
#include <iostream>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <iomanip>

using json = nlohmann::json;
using namespace httplib;

json cachedWeather;
int cachedIndex;
bool isWeatherLoaded = false;

void findAndReplace(std::string& source, const char* find, const char* replace){
    size_t findLen = strlen(find);
    size_t replaceLen = strlen(replace);
    size_t pos = 0;

    while ((pos = source.find(find, pos)) != std::string::npos){
        source.replace(pos, findLen, replace);
        pos += replaceLen;
    }
}


void refreshCache() { // функция для обновления кэша
    Client cli("http://api.openweathermap.org"); 
    auto res = cli.Get("/data/2.5/onecall?lat=44.5725&lon=34.6388&exclude=daily,minutely,current,alerts&appid=d5b675a76430a03a2cef0129b194dc8c&lang=ru&units=metric"); // делаем get запрос для получения данных о текущей погоде.
    if (res) { 

        if (res->status == 200) { // проверка, что запрос успешно выполнен.
            cachedWeather = json::parse(res->body); // сохраняем результат в переменную.
            std::cout << "Weather is refreshed" << std::endl;
        }
        else {
            std::cout << "Status code: " << res->status << std::endl; 
        }

    }
    else {
        auto err = res.error();
        std::cout << "Weather request error code: " << err << std::endl;
    }
}

void checkCache() { // Функция для проверки кэша, и в случаее необходимости для его обновления
    if (!isWeatherLoaded) { // проверяем кэш 
        refreshCache();
        isWeatherLoaded = true;
    }

    Client cli("http://worldtimeapi.org");
    auto timeRequest = cli.Get("/api/timezone/Europe/Simferopol");

    if (timeRequest) {
        if (timeRequest->status == 200) {
            int unixtime = json::parse(timeRequest->body)["unixtime"];
            bool found = false;
            for (int i = 0; i < 48; i++) {
                int timestamp = cachedWeather["hourly"][i]["dt"];
                if (timestamp > unixtime) {
                    cachedIndex = i;
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cout << "NOT FOUND IN CACHE" << std::endl;
                refreshCache();
            }
        }
        else {
            std::cout << "Time request status code: " << timeRequest->status << std::endl;
        }
    }
}
void gen_response(const Request& req, Response& res) {
    checkCache();
    std::string path = "index.html";
    std::ifstream file(path); // Файловая переменная
    if (file.is_open()) {
        std::string str;                 // Буфер. Тут будет текст файла
        std::getline(file, str, '\0');

        std::string description = cachedWeather["hourly"][cachedIndex]["weather"][0]["description"];
        std::string icon = cachedWeather["hourly"][cachedIndex]["weather"][0]["icon"];
        double temp = cachedWeather["hourly"][cachedIndex]["temp"];

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << temp;
        std::string temp_str = stream.str();

        findAndReplace(str, "{hourly[i].weather[0].description}", description.c_str());
        findAndReplace(str, "{hourly[i].temp}", temp_str.c_str());
        findAndReplace(str, "{hourly[i].weather[0].icon}", icon.c_str());

        res.set_header("Content-Type", "text/html");
        res.set_content(str, "text/html");
    }
    else {
        res.set_content("Unable to open file", "text/html");
    }
}


void send_json(const Request& req, Response& res) {
    checkCache();
    json response;
    response["temp"] = cachedWeather["hourly"][cachedIndex]["temp"];
    response["description"] = cachedWeather["hourly"][cachedIndex]["weather"][0]["description"];
    res.set_content(response.dump(), "application/json");
}

int main() {
    setlocale(LC_ALL, "Russian");
	Server server;
	server.Get("/", gen_response);
    server.Get("/raw", send_json);
	std::cout << "Starting server... OK\n";
	server.listen("localhost", 3000);

}
```
### Подготовка клиентского приложения
Клиентское приложение реализовано с помощью стандартого модуля **Python Tkinter** и модуля **requests**. 
Для получения данных реализована функция **fetch**, внутри которой выполняется запрос по адресу http:localhost:3000/raw, мы получем JSON, который и возвращает функция.
Графический интерфейс приложения реализован с помощью трех элементов **Label**. Для обновления отображаемых значеий реализована функция **refresh_data**, которая получает данные с сервера, после чего изменяет параметр **text** для элементов **Label**. Для обновления данных по клику мышки, установлен **bind** на главный элемент **root**, при клике будет осуществлен запрос на сервер и данные будут обновлены.



### Исходный код клиентского приложения: 
```python
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
```
### Интерфейс клиентского приложения:
![alt text](https://sun9-22.userapi.com/impf/MWfKxkkh6QVXlRLDpL1_t9eXPU9RUHTLBXrZrQ/JjKkVeoR9NY.jpg?size=307x277&quality=96&proxy=1&sign=5887fb484b266aecb338e905cfd3e8ca)
### Загруженный виджет
![alt text](https://sun9-50.userapi.com/impf/tl-Pk2FIcLZzqpT8oMyJR9j9ltWs5hlvN1Y0-A/VqKuDDXaTp0.jpg?size=1918x1039&quality=96&proxy=1&sign=dea6a32b1af48b95bc099ef92ad0087b)
