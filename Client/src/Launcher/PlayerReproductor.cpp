#include "PlayerReproductor.h"
#include "Defines.h"

PlayerReproductor::PlayerReproductor(QWidget* parent) : QWidget(parent),
    playlist(this), player() {
    QDir directorio(QDir::currentPath());
    directorio.cd(PATH_MUSIC_LAUNCHER);
    directorio.setNameFilters(QStringList({"*.wav"}));
    QStringList lista = directorio.entryList();
    for(QString file: lista)
        this->playlist.addMedia(QUrl::fromLocalFile(directorio.path() + "/" + file));
    this->playlist.setPlaybackMode(QMediaPlaylist::Loop);
    this->player.setPlaylist(&this->playlist);
    this->player.setVolume(15);
    this->player.play();
}

void PlayerReproductor::stopMusic() {
    this->player.stop();
}

void PlayerReproductor::playMusic() {
    this->player.play();
}

PlayerReproductor::~PlayerReproductor() {
}
