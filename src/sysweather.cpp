/*
 * sysweather 
 * Copyright (C) 2026 efesint ('ts)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Third-party: uses cpp-httplib (https://github.com/yhirose/cpp-httplib),
 * MIT License, Copyright (c) 2017 yhirose.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
 
#include <unistd.h>
#include <sys/utsname.h>
#include "httplib.h"
#include <cstdlib>

std::string city;

std::string home()
{
    const char* home = std::getenv("HOME");
    if (home == nullptr) {
        return "/home";   // if /home doesnt work
    }
    return std::string(home);
}

void write_config() {
std::string path = home() + "/sysweather/config.txt";
    std::cout << "Is this your first time here?\n";
    std::cout << "Write your city like 'Europe/Berlin': " << std::endl;
    std::getline(std::cin, city);

    std::ofstream ffile(path);
      if (!ffile) {
        std::cout << "warning: cannot save config to " << path << "\n";
      }
    ffile << city;
}

std::string check_config() {
  std::string path = home() + "/sysweather/config.txt";
  std::ifstream file(path);
    
    if (file && std::getline(file, city) &&
      city.find_first_not_of(" \t\r\n") != std::string::npos)
    {
        return city;
    }
    write_config();
    return city;   

}

void print_fog() {
    std::cout << "  .-.-.-.-.-.-." << std::endl;
    std::cout << " (             )" << std::endl;
    std::cout << "  '-.-.-.-.-.-'  it's foggy outside" << std::endl;
    std::cout << "   .-.-.-.-.-." << std::endl;
    std::cout << "  (             )" << std::endl;
    std::cout << "   '-.-.-.-.-.-'" << std::endl;
}

void print_rain() {
    std::cout << "      __   _" << std::endl;
    std::cout << "    _{  }_{ }_" << std::endl;
    std::cout << "   {_   _    _) it's rainy outside" << std::endl;
    std::cout << "  / /{ } {__}" << std::endl;
    std::cout << " / / / / / /" << std::endl;
    std::cout << "/ / / / / /" << std::endl;
}

void print_sun() {
    std::cout << "        ." << std::endl;
    std::cout << "      \\ | /" << std::endl;
    std::cout << "    '-.:::.-'" << std::endl;
    std::cout << "   -==::::::==- it's sunny outside" << std::endl;
    std::cout << "    .-':::'-.      (or clear)" << std::endl;
    std::cout << "      / | \\" << std::endl;
    std::cout << "        '" << std::endl;
}

void print_snow() {
    std::cout << "     .\\\\/." << std::endl;
    std::cout << "   _\\\\_)(_/_" << std::endl;
    std::cout << "     )( \\\\        .\\\\/." << std::endl;
    std::cout << "     '/\\\\'      _\\\\_\\\\/_/_  it's snowing outside" << std::endl;
    std::cout << "                 / /\\\\ \\\\" << std::endl;
    std::cout << "                   /\\\\'" << std::endl;
}

void print_cloud() {
    std::cout << "   __   _" << std::endl;
    std::cout << " _{  }_{ }_" << std::endl;
    std::cout << "{_   _    _}  it's cloudy outside" << std::endl;
    std::cout << "  {_} {__}" << std::endl;
}
void print_storm() {
    std::cout << "--_-_-_-_---" << std::endl;
    std::cout << "    _-_-_" << std::endl;
    std::cout << "    -_-_-" << std::endl;
    std::cout << "     -__-" << std::endl;
    std::cout << "    _-_" << std::endl;
    std::cout << "   _" << std::endl;
    std::cout << "   -_" << std::endl;
    std::cout << "    _-" << std::endl;
    std::cout << "There's a thunderstorm outside" << std::endl;
}

std::string hostname() {
 char buf[256];
    if(gethostname(buf, sizeof(buf)) == 0) {
      return std::string(buf);
    }

return "unknowm";
}

std::string kernel() {
    struct utsname buf;
    uname(&buf);

    std::string kernel_version = buf.release;
    return kernel_version;
}

std::string os() {
    std::ifstream f("/etc/os-release");
    std::string line;
    while (std::getline(f, line)) {
        if (line.rfind("PRETTY_NAME=", 0) == 0) {
            std::string v = line.substr(12);
            if (v.size() >= 2 && v.front() == '"' && v.back() == '"') {
                v = v.substr(1, v.size() - 2);
            }
            return v;
        }
    }
    return "unknown";
}

// i have no clue how this func work
// im so tired of debugging this 

std::string wthr() {
    httplib::Client cli("http://wttr.in");
    cli.set_default_headers({{"User-Agent", "curl/8.5.0"}});

    auto res = cli.Get("/" + city + "?format=%C");

    if (res && res->status == 200) {
        return res->body;
    }
    return "Cannot find information about weather. Check your internet connection";
}

void check_condition()
{
    std::string weather = wthr();

    if (weather == "Cannot find information about weather. Check your internet connection") {
        std::cout << "  " << weather << "\n";
        return;
    }

    // rain
    if (weather == "Light rain" ||
        weather == "Moderate rain" ||
        weather == "Heavy rain" ||
        weather == "Patchy rain nearby" ||
        weather == "Patchy rain possible" ||
        weather == "Light drizzle" ||
        weather == "Moderate drizzle" ||
        weather == "Heavy drizzle" ||
        weather == "Light rain shower" ||
        weather == "Moderate or heavy rain shower" ||
        weather == "Torrential rain shower" ||
        weather == "Light sleet" ||
        weather == "Moderate or heavy sleet" ||
        weather == "Light freezing rain" ||
        weather == "Moderate or heavy freezing rain" ||
        weather == "Light rain with thunder")
    {
        print_rain();
    }
    // snow
    else if (weather == "Light snow" ||
             weather == "Moderate snow" ||
             weather == "Heavy snow" ||
             weather == "Patchy light snow" ||
             weather == "Patchy moderate snow" ||
             weather == "Patchy heavy snow" ||
             weather == "Blizzard" ||
             weather == "Light snow showers" ||
             weather == "Moderate or heavy snow showers" ||
             weather == "Light showers of ice pellets" ||
             weather == "Moderate or heavy showers of ice pellets" ||
             weather == "Ice pellets" ||
             weather == "Freezing fog" ||
             weather == "Light freezing drizzle" ||
             weather == "Heavy freezing drizzle" ||
             weather == "Hail")
    {
        print_snow();
    }
    // storm
    else if (weather == "Thunderstorm" ||
             weather == "Patchy light rain with thunder" ||
             weather == "Moderate or heavy rain with thunder" ||
             weather == "Patchy light snow with thunder" ||
             weather == "Moderate or heavy snow with thunder")
    {
        print_storm();
    }
    // clear
    else if (weather == "Clear" ||
             weather == "Sunny")
    {
        print_sun();
    }
    // fog
    else if (weather == "Mist" ||
             weather == "Fog" ||
             weather == "Freezing fog" ||
             weather == "Smoky haze" ||
             weather == "Haze" ||
             weather == "Patches of fog" ||
             weather == "Shallow fog" ||
             weather == "Partial fog")
    {
        print_fog();
    }
    else
    {
        print_cloud();
    }
}

int main() {
std::cout << "\033[2J\033[H";
check_config();
std::string username = std::getenv("USER");

    std::cout << "_____________________" << std::endl;
    std::cout << " hello, " << username << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "        \\   ^__^" << std::endl;
    std::cout << "         \\  (oo)\\_______" << std::endl;
    std::cout << "            (__)\\       )\\/\\" << std::endl;
    std::cout << "                ||----w |" << std::endl;
    std::cout << "                ||     ||" << std::endl;
    std::cout << std::endl;
 
    std::cout << "weather" << std::endl;
    std::cout << "╔══════════════════════════════════════════╗\n";
    check_condition();              
    std::cout << "╚══════════════════════════════════════════╝\n";
    std::cout << "system info\n";
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "  hostname: " << hostname() << std::endl; 
    std::cout << "  user: " << username << std::endl;
    std::cout << "  kernel: " << kernel() << std::endl;
    std::cout << "  os: " << os() << std::endl;
    std::cout << "╚══════════════════════════════════════════╝\n\n";

return 0;
}




