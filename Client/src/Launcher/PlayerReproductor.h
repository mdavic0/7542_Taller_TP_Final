#ifndef PLAYER_REPRODUCTOR_H_
#define PLAYER_REPRODUCTOR_H_

#include <QtWidgets>
#include <QtMultimedia>

class PlayerReproductor : public QWidget {
    private:
        QMediaPlayer player;
        QMediaPlaylist playlist;
    public:
        explicit PlayerReproductor(QWidget* parent = 0);
        ~PlayerReproductor();
        void stopMusic();
        void playMusic();
};

#endif
