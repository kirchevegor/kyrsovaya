#include <iostream>
#include <cstring> // Добавлено для strlen
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

int main() {
    setlocale(LC_ALL,"rus");
    const char* url = "tcp://127.0.0.1:5555";
    const char* message = "Hello, nanomsg!";

    // Создание сокета
    int sock = nn_socket(AF_SP, NN_PUSH);
    if (sock < 0) {
        std::cerr << "Socket creation error: " << nn_strerror(nn_errno()) << std::endl;
        return -1;
    }

    // Подключение к серверу
    if (nn_connect(sock, url) < 0) {
        std::cerr << "Binding error: " << nn_strerror(nn_errno()) << std::endl;
        nn_close(sock);
        return -1;
    }

    std::cout << "The client sends a message: " << message << std::endl;

    // Отправка сообщения
    int bytes = nn_send(sock, message, strlen(message) + 1, 0);
    if (bytes < 0) {
        std::cerr << "Error sending the message: " << nn_strerror(nn_errno()) << std::endl;
        nn_close(sock);
        return -1;
    }

    nn_close(sock);

    return 0;
}
