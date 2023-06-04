#include "Launcher.h"
#include "Event.h"
#include "TypeGame.h"
#include "TypeOperator.h"
#include "Socket.h"
#include "Defines.h"
#include "Liberror.h"
#include "SdlException.h"
#include "GameDrawner.h"
#include <QApplication>
#include <QFontDatabase>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

Launcher::Launcher(QWidget* parent): QWidget(parent),
    initView(), connectView(), menuView(), createView(), joinView(),
    clientProtocol(std::nullopt) {
    this->initWidget();
    mainWidget.addWidget(&initView);
    mainWidget.addWidget(&connectView);
    mainWidget.addWidget(&menuView);
    mainWidget.addWidget(&createView);
    mainWidget.addWidget(&joinView);

    connect(&initView, &InitView::connectClicked, this,
            &Launcher::goToConnect);
    // Conectar al server
    connect(&connectView, &ConnectView::createConnection, this,
            &Launcher::createProtocol);
    connect(&connectView, &ConnectView::backConnect, this,
            &Launcher::goToMain);
    // Menu de seleccion
    connect(&menuView, &MenuView::createClicked, this,
            &Launcher::goToCreate);
    connect(&menuView, &MenuView::joinClicked, this,
            &Launcher::goToJoin);
    connect(&menuView, &MenuView::backClicked, this,
            &Launcher::goToMain);
    // Crear partida
    connect(&createView, &CreateView::createClicked, this,
            &Launcher::sendCreateMatch);
    connect(&createView, &CreateView::backClicked, this,
            &Launcher::goToMenu);
    // Unirse a partida
    connect(&joinView, &JoinView::joinClicked, this, &Launcher::sendJoinMatch);
    connect(&joinView, &JoinView::backClicked, this, &Launcher::goToMenu);


    QLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(&mainWidget);
    mainWidget.setCurrentIndex(0);
    this->setLayout(layout);
}

void Launcher::initWidget() {
    this->setObjectName("MainWidget");
    this->setWindowTitle("Left 4 Dead");
    this->setFixedSize(800, 600);
    this->initFont();
}

void Launcher::initFont() {
    QFontDatabase fontdata;
    int fontId = fontdata.addApplicationFont("assets/font/Futurot.ttf");
    if (fontId != -1) {
        QStringList fontFamilies = fontdata.applicationFontFamilies(fontId);
        if (!fontFamilies.empty())
            qApp->setFont(fontFamilies.at(0));
    }
}

void Launcher::goToMain() {
    mainWidget.setCurrentIndex(0);
}

void Launcher::goToConnect() {
    mainWidget.setCurrentIndex(1);
}

void Launcher::goToMenu() {
    mainWidget.setCurrentIndex(2);
}

void Launcher::goToCreate() {
    mainWidget.setCurrentIndex(3);
}

void Launcher::goToJoin() {
    mainWidget.setCurrentIndex(4);
}

void Launcher::createProtocol(const QString& ip, const QString& port) {
    qDebug() << "Ip: " << ip;
    qDebug() << "port: " << port;
    try {
        this->clientProtocol = ClientProtocol(
            Socket(ip.toStdString().c_str(), port.toStdString().c_str()));
        mainWidget.setCurrentIndex(2);
    } catch (std::exception &exc){
        QMessageBox::information(this, "Error", 
                    "Datos ingresados no validos",
                    QMessageBox::Close);
    }
}

void Launcher::sendCreateMatch(const QString& name, int mode, 
        int operatorSelect) {
    std::string nameMatch = name.toStdString();
    qDebug() << "Nombre " << name;
    qDebug() << "Seleccione modo juego " << mode;
    qDebug() << "Seleccione operador " << operatorSelect;
    EventDTO eventCreate(nameMatch, TypeGame(mode), TypeOperator(operatorSelect));
    clientProtocol->sendEvent(eventCreate);
    Snapshot receive = clientProtocol->getSnapshot();
    if (receive.getCode() >= 0) {
        std::string message = "Partida creada con codigo: " + 
            std::to_string(receive.getCode());
        QMessageBox::information(this, "Exito", message.c_str(),
            QMessageBox::Close);
        this->hide();
        this->initGame();
        qDebug() << "termine juego";
        this->show();
    } else {
        QMessageBox::information(this, "Error", 
                    "No se pudo crear la partida",
                    QMessageBox::Close);
    }
}

void Launcher::sendJoinMatch(int code, int operatorSelect) {
    qDebug() << "Me uno a partida con code: " << code;
    qDebug() << "Seleccione operador " << operatorSelect;
    EventDTO eventCreate(code, TypeOperator(operatorSelect));
    clientProtocol->sendEvent(eventCreate);
    Snapshot receive = clientProtocol->getSnapshot();
     if (receive.getOk() == 0) {
        QMessageBox::information(this, "Exito", "Union Exitosa",
            QMessageBox::Close);
        this->hide();
        this->initGame();
        this->show();
    } else {
        QMessageBox::information(this, "Error", 
                    "No se pudo crear la partida",
                    QMessageBox::Close);
    }
}

void Launcher::initGame() {
    bool endGame = false;
    Queue<std::shared_ptr<Snapshot>> snapshotQueue(SIZE_QUEUE);
    Queue<std::shared_ptr<EventDTO>> eventQueue(SIZE_QUEUE);
    GameDrawner gameDrawner(snapshotQueue, eventQueue, endGame);
    SnapshotReceiver snapshotReceiver(clientProtocol.value(), snapshotQueue, endGame);
    EventSender eventSender(eventQueue, clientProtocol.value(), endGame);
    try {
        gameDrawner.start();
        snapshotReceiver.start();
        eventSender.start();
    } catch (ClosedQueue &exc) {
        this->clientProtocol->stop();
    } catch (const SdlException &exc) {
        std::cerr << exc.what() << std::endl;
    }
}

Launcher::~Launcher() {
    // clientProtocol->stop();
}