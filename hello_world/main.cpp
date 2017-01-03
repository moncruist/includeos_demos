#include <os>
#include <vga>

ConsoleVGA vga;

void Service::start(const std::string &) {

    OS::add_stdout(vga.get_print_handler());
    std::cout << "Hello, World!" << std::endl;
}