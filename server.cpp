#include <iostream>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

int main() {
    setlocale(LC_ALL,"rus");
    const char* url = "tcp://127.0.0.1:5555";

    // Создание сокета
    int sock = nn_socket(AF_SP, NN_PULL);
    if (sock < 0) {
        std::cerr << "Socket creation error: " << nn_strerror(nn_errno()) << std::endl;
        return -1;
    }

    // Привязка сокета к адресу
    if (nn_bind(sock, url) < 0) {
        std::cerr << "Binding error: " << nn_strerror(nn_errno()) << std::endl;
        nn_close(sock);
        return -1;
    }

    std::cout << "The server is waiting for a message on " << url << std::endl;

    // Получение сообщения
    char* buf = nullptr;
    int bytes = nn_recv(sock, &buf, NN_MSG, 0);
    if (bytes < 0) {
        std::cerr << "Error receiving the message: " << nn_strerror(nn_errno()) << std::endl;
        nn_close(sock);
        return -1;
    }

    std::cout << "A message has been received: " << buf << std::endl;

    // Освобождение ресурсов
    nn_freemsg(buf);
    nn_close(sock);

    return 0;
}
