#include "TCPserver.hpp"
#include "TCPsocket.hpp"
#include "include.hpp"
#include "utils.hpp"

/*
** args: av[1] = port
**       av[2] = password
*/
int main(int ac, char* av[]) {

    if (ac != 3 || !portIsValid(av[1])) {
        std::cout << "Usage: ./server <port> <password>" << std::endl;
        return EXIT_FAILURE;
    }

    TCPserver server(std::atoi(av[1]), av[2]);
    server.runServer();

    return EXIT_SUCCESS;
}

/*
** SOURCES:
** https://www.man7.org/linux/man-pages/man2/poll.2.html
** https://www.ibm.com/docs/en/i/7.3?topic=designs-using-poll-instead-select
*/