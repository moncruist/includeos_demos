#include <os>
#include <net/inet4>
#include <timers>
#include <chrono>

using namespace std::chrono;

void Service::start(const std::string &) {
    net::Inet<net::IP4>& inet = net::Inet4::ifconfig();
    // static IP in case DHCP fails
    net::Inet4::ifconfig(
            { 10,0,0,42 },     // IP
            { 255,255,255,0 }, // Netmask
            { 10,0,0,1 },      // Gateway
            { 10,0,0,1 });     // DNS
    Timers::periodic(5s, 30s, [&inet] (uint32_t) {
        printf("<Service> TCP STATUS:\n%s\n", inet.tcp().status().c_str());
    });

    auto& server = inet.tcp().bind(1234);

    server.on_connect(
        [] (auto conn) {
            printf("<Service> @on_connect: Connection %s successfully established.\n", conn->remote().to_string().c_str());

            // Async read
            conn->on_read(1024, [conn] (auto buf, size_t n) {
                printf("<Service> @on_read: %u bytes received from %s.\n", n, conn->remote().to_string().c_str());

                conn->write(buf, n, [conn] (size_t written) {
                    printf("<Service> @on_write: %u bytes written to %s.\n", written, conn->remote().to_string().c_str());
                });
            });
        }
    );
}
