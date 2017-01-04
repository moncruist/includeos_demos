#include <iostream>
#include <unistd.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

int main() {
    try {
        std::cout << "IncludeOS network demo client" << std::endl;

        io_service io_service;
        tcp::endpoint ep(address::from_string("10.0.0.42"), 1234);

        ip::tcp::socket socket(io_service);
        boost::system::error_code error = error::host_not_found;
        socket.connect(ep, error);

        if (error) {
            throw boost::system::system_error(error);
        }

        for (;;) {
            boost::array<char, 1024> buf;

            socket.write_some(buffer("ping\n"));
            size_t len = socket.read_some(buffer(buf), error);
            std::cout << "Readed " << len << " bytes" << std::endl;
            usleep(1000000);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}