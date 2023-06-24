#ifndef SERVER_GAMES_CONTROLLER_H_
#define SERVER_GAMES_CONTROLLER_H_

#include "Game.h"
#include "EventDTO.h"
#include "Snapshot.h"
#include <mutex>
#include <map>
#include <memory>

/*
 * Monitor sobre el Map que guarda
 * las instancias de Game y el contador para crear
 * un nuevo Game.
 */
class GamesController {
    private:
    uint8_t counter;       // counter
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
    Queue<std::shared_ptr<EventDTO>>* create(std::shared_ptr<EventDTO> eventdto,
                                             Queue<std::shared_ptr<Snapshot>>* snapshot_queue,
                                             Game **game);

    /*
     * Este método sera el encargado de unir un cliente a un sala.
     * Para hacerlo debera proteger el el map de salas para que no sea
     * modificado mientras se lo esta 'iterando'.
     */
    Queue<std::shared_ptr<EventDTO>>* try_join_game(std::shared_ptr<EventDTO> eventdto,
                                                    Queue<std::shared_ptr<Snapshot>> *q,
                                                    Game **game);

    /*
     * Iniciar el hilo Game
     */
    //void startGame(const uint32_t& code);

    //void clientLeave(Queue<std::shared_ptr<Snapshot>>* snapshot_queue, const uint32_t& code);

    ~GamesController();
};

#endif  // SERVER_GAMES_CONTROLLER_H_
