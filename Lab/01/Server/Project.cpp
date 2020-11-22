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


void refreshCache() {
    Client cli("http://api.openweathermap.org");
    auto res = cli.Get("/data/2.5/onecall?lat=44.5725&lon=34.6388&exclude=daily,minutely,current,alerts&appid=d5b675a76430a03a2cef0129b194dc8c&lang=ru&units=metric");
    if (res) {

        if (res->status == 200) {
            cachedWeather = json::parse(res->body);
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

void checkCache() {

    if (!isWeatherLoaded) {
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