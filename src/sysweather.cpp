#include <iostream>
#include <fstream>
#include <atomic>
#include <format>
#include <optional>
#include <chrono>
#include <string>

#include <curl/curl.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/utsname.h>


std::string check_city() {
  std::string path = std::string(std::getenv("HOME")) + "/sysweather/config.txt";
   
  std::ifstream file(path);
  std::string city;
    if( file && std::getline(file, city) && !city.empty()) {
        return city;
    }
  std::cout << "Is this your first time here?\n";
  std::cout << "Write your city like 'Europe/Berlin': " << std::endl;
  std::getline(std::cin, city);

  std::ofstream ffile(path);
  ffile << city;
  return city;

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

std::string weather() {

std::string city = check_city();
std::string url = "wttr.in/" + city + "?format=%C";

}

int main() {
check_city();
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

    std::cout << "system info\n";
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "  hostname: " << hostname() << std::endl; 
    std::cout << "  user: " << username << std::endl;
    std::cout << "  kernel: " << kernel() << std::endl;
    std::cout << "  os: " << os() << std::endl;
    std::cout << "╚══════════════════════════════════════════╝\n\n";
    
return 0;
}




