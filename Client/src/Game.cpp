#include "Game.h"

Game::Game(Queue<EventDTO *> &client_events, Queue<Snapshot *> &snapshot_queue) :
    client_events(client_events), snapshot_queue(snapshot_queue) {}

void Game::run() {
    /*while working
        handle_events() # popea de la queue de sdl y pushea a la queue de los sender
        ( o podría procesarlos directamente acá si son un evento que no modifica a los
        demas jugadores. Ejemplo: abrir un menu lateral, poner el juego en mute, etc.)

        process_events() #popea de la queue del receiver y procesa los eventos para
        actualizar el juego.

        render()

        sleep(delta_t)*/
}
