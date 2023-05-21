#include "client_launcher.h"
#include "client_protocol.h"
#include "common_socket.h"
#include <QApplication>
#include <QFontDatabase>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include "client_gameSdl.h"
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
        this->clientProtocol = ClientProtocol(Socket(ip.toStdString().c_str(), port.toStdString().c_str()));
        mainWidget.setCurrentIndex(2);
    } catch (std::exception &exc){
        //  Q_EMIT errorConnection();
        QMessageBox::information(this, "Error", 
                    "Datos ingresados no validos",
                    QMessageBox::Close);
    }
}

void Launcher::sendCreateMatch(const QString& name, int mode, 
        int operatorSelect) {
    std::string nameMatch = name.toStdString();
    qDebug() << "Nombre " << name;
    qDebug() << "Seleccione operador " << operatorSelect;
    qDebug() << "Seleccione modo juego " << mode;
    qDebug() << "Creo partida";
    this->hide();
    GameSdl game(operatorSelect);
    game.run();
    this->show();
}

void Launcher::sendJoinMatch(int code, int operatorSelect) {
    qDebug() << "Me uno a partida con code: " << code;
    qDebug() << "Seleccione operador " << operatorSelect;
}

Launcher::~Launcher() {
}