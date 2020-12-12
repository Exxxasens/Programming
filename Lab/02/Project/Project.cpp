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
    auto res = cli.Post(path.c_str(), data, "text/json");
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