#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_

#include <string.h>

class MockSocket {
    private:
    char array[30]; 

    public:
    MockSocket() = default;

MockSocket(const MockSocket&) = delete;
MockSocket& operator=(const MockSocket&) = delete;

MockSocket(MockSocket&&);
MockSocket& operator=(MockSocket&&);


/*
 * `Socket::sendall` envía exactamente `sz` bytes leídos del buffer, ni más,
 * ni menos. `Socket::recvall` recibe exactamente sz bytes.
 *
 * Si hay un error se lanza una excepción.
 *
 * Si no hubo un error pero el socket se cerro durante el envio/recibo
 * de los bytes y algunos bytes fueron enviados/recibidos,
 * se lanza también una excepción.
 *
 * Si en cambio ningún byte se pudo enviar/recibir, se retorna 0.
 *
 * En ambos casos, donde el socket se cerró, `was_closed` es puesto a `true`.
 *
 * En caso de éxito se retorna la misma cantidad de bytes pedidos
 * para envio/recibo, lease `sz`.
 *
 * */
int sendall(
        const void *data,
        unsigned int sz,
        bool *was_closed);
int recvall(
        void *data,
        unsigned int sz,
        bool *was_closed);

};
#endif  // COMMON_SOCKET_H_