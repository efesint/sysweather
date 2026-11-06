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

#define CONFIG_FILE "/.weather_city"

void print_rain() {
    printf("      __   _\n");
    printf("    _{  }_{ }_\n");
    printf("   {_   _    _) it's rainy outside\n");
    printf("  / /{ } {__}\n");
    printf(" / / / / / /\n");
    printf("/ / / / / /\n");
}

void print_sun() {
    printf("        .\n");
    printf("      \\ | /\n");
    printf("    '-.:::.-'\n");
    printf("   -==::::::==- it's sunny outside\n");
    printf("    .-':::'-.      (or clear)\n");
    printf("      / | \\\n");
    printf("       '\n");
}

void print_snow() {
    printf("     .\\\\/.\n");
    printf("   _\\\\_)(_/_\n");
    printf("     )( \\\\        .\\\\/.\n");
    printf("     '/\\\\'      _\\\\_\\\\/_/_  it's snowing outside\n");
    printf("                 / /\\\\ \\\\\n");
    printf("                   /\\\\'\n");
}

void print_cloud() {
    printf("   __   _\n");
    printf(" _{  }_{ }_\n");
    printf("{_   _    _}  it's cloudy outside\n");
    printf("  {_} {__}\n");
}

void print_storm() {
    printf("--_-_-_-_---\n");
    printf("    _-_-_\n");
    printf("    -_-_-\n");
    printf("     -__-\n");
    printf("    _-_\n");
    printf("   _\n");
    printf("   -_\n");
    printf("    _-\n");
    printf("There's a thunderstorm outside\n");
}


int main() {
std::string username = std::getenv("USER");

    std::cout << "_____________________" << std::endl;
    std::cout << " hello, " << username << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "        \\   ^__^" << std::endl;
    std::cout << "         \\  (oo)\\_______" << std::endl;
    std::cout << "            (__)\\       )\\/\\" << std::endl;
    std::cout << "                ||----w |" << std::endl;
    std::cout << "                ||     ||" << std::endl;

return 0;
}



