#ifndef SERVER_GAMES_CONTROLLER_H_
#define SERVER_GAMES_CONTROLLER_H_

#include "Game.h"
#include "EventDTO.h"
#include "Snapshot.h"
#include <mutex>
#include <map>

/*
 * Monitor sobre el Map que guarda
 * las instancias de Game y el contador para crear
 * un nuevo Game.
 */
class GamesController {
    private:
    uint32_t counter;  // games id
    std::map<uint32_t, Game*> games;
    std::mutex mutex;

    public:
    /*
     * Constructor público.
     */
    GamesController();

    /*
     * Este método sera el encargado de crear una nueva sala.
     * Para hacerlo debera :
     * - proteger el contador para que otro hilo no cree la misma sala.
     * - mantener el lock hasta que se haya modificado la lista de salas.
     */
    Queue<EventDTO*>* create(EventDTO* eventdto, Queue<Snapshot*>* snapshot_queue, uint32_t& code);

    /*
     * Este método sera el encargado de unir un cliente a un sala.
     * Para hacerlo debera proteger el el map de salas para que no sea
     * modificado mientras se lo esta 'iterando'.
     */
    Queue<EventDTO*>* try_join_game(EventDTO* eventdto, Queue<Snapshot*> *q);

    /*
     * Iniciar el hilo Game
     */
    void startGame(const uint32_t& code);

    ~GamesController();
};

#endif  // SERVER_GAMES_CONTROLLER_H_
