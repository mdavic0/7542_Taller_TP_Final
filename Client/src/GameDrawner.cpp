#include "GameDrawner.h"
#include "GameSdl.h"

GameDrawner::GameDrawner(Queue<Snapshot *> &snapshot_queue,
    Queue<EventDTO *> &client_events, bool& endGame) :
    client_events(client_events), snapshot_queue(snapshot_queue),
    endGame(endGame) {
}

void GameDrawner::run() {
    GameSdl gameSdl(1, snapshot_queue, client_events, endGame);
    // try {
        gameSdl.run();
    // } catch (ClosedQueue &exc) {
    // } catch (...) {}
    /*while working
        handle_events() # popea de la queue de sdl y pushea a la queue de los sender
        ( o podría procesarlos directamente acá si son un evento que no modifica a los
        demas jugadores. Ejemplo: abrir un menu lateral, poner el juego en mute, etc.)

        process_events() #popea de la queue del receiver y procesa los eventos para
        actualizar el juego.

        render()

        sleep(delta_t)*/
}

void GameDrawner::stop() {
}
