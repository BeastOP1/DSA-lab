#pragma once

#include <string>
#include<vector>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;


// Structs to hold different parts of the response
struct Coord {
    double lon;
    double lat;
};

struct Weather {
    int id;
    string main;
    string description;
    string icon;
};

struct Wind {
    double speed;
    int deg;
    double gust;
};

struct Clouds {
    int all;
};

struct Sys {
    string country;
    int sunrise;
    int sunset;
};

struct Main {
    double temp;
    double feels_like;
    double temp_min;
    double temp_max;
    int pressure;
    int humidity;
    int sea_level;
    int grnd_level;
};

struct ApiResponse {
    Coord coord;
    vector<Weather> weather;
    string base;
    Main main;
    int visibility;
    Wind wind;
    Clouds clouds;
    int dt;
    Sys sys;
    int timezone;
    int id;
    string name;
    int cod;
};


ApiResponse parse_json(const string& json_str) {
    ApiResponse final;
    
    try {
        // Parse the JSON string
        json j = json::parse(json_str);
        
        // Parse coordinates
        final.coord.lon = j["coord"]["lon"];
        final.coord.lat = j["coord"]["lat"];
        
        // Parse weather array
        for (const auto& w : j["weather"]) {
            Weather weather;
            weather.id = w["id"];
            weather.main = w["main"];
            weather.description = w["description"];
            weather.icon = w["icon"];
            final.weather.push_back(weather);
        }
        
        // Parse main weather data
        final.main.temp = j["main"]["temp"];
        final.main.feels_like = j["main"]["feels_like"];
        
        
        // Parse system data
        final.sys.country = j["sys"]["country"];
        final.sys.sunrise = j["sys"]["sunrise"];
        final.sys.sunset = j["sys"]["sunset"];
        
        // Parse remaining fields
        final.name = j["name"];
        final.cod = j["cod"];
       
        
    } catch (const exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }
    
    return final;
}

