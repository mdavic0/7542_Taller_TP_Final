#ifndef LEFT4DEAD_EVENTSENDER_H
#define LEFT4DEAD_EVENTSENDER_H
#include "common_thread.h"
#include "common_queue.h"
#include "client_protocol.h"
#include <atomic>

class EventSender : public Thread  {
    private:
        Queue<EventDTO*>& sdl_events;
        ClientProtocol& protocol;
        std::atomic<bool> talking;
        std::atomic<bool> alive;

    public:
        /*
        * Constructor recibe protocolo por referencia, el cual contiene
        * el socket por el cual se envían respuestas.
        * Además, recibe una queue por referencia, de la cual obtendrá
        * las respuestas que debe enviar.
        */
        EventSender(Queue<EventDTO*>& sdl_events, ClientProtocol& protocol);

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
