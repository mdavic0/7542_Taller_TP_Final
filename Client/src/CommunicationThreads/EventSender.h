#ifndef LEFT4DEAD_EVENTSENDER_H
#define LEFT4DEAD_EVENTSENDER_H
#include "Thread.h"
#include "Queue.h"
#include "ClientProtocol.h"
#include "Socket.h"
#include <atomic>
#include <memory>

class EventSender : public Thread  {
private:
    Socket *skt;
    Queue<std::shared_ptr<EventDTO>>& sdl_events;
    ClientProtocol<Socket> protocol;
    std::atomic<bool> talking;
    std::atomic<bool> alive;
    bool& endGame;
public:
    /*
    * Constructor recibe protocolo por referencia, el cual contiene
    * el socket por el cual se envían respuestas.
    * Además, recibe una queue por referencia, de la cual obtendrá
    * las respuestas que debe enviar.
    */
    EventSender(Queue<std::shared_ptr<EventDTO>>& sdl_events,
                Socket *skt,
                bool& endGame);

    /*
    * Método que devuelve true cuando el hilo termino de ejecutarse.
    */
    bool ended();

    /*
    * Método que encapsula la ajecucion del hilo. Recibe respuestas a
    * enviar por medio de la queue, y las envia por medio del protocolo.
    */
    virtual void run() override;

    /*
    * Método para detener la iteración en la cual se envían
    * respuestas por medio del protocolo.
    */
    virtual void stop() override;

    /*
    * Destructor que realiza el join del hilo.
    */
    virtual ~EventSender();
};


#endif //LEFT4DEAD_EVENTSENDER_H
