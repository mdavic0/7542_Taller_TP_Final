#include "client_launcher.h"
#include "client_protocol.h"
#include "common_socket.h"
#include <QApplication>
#include <QFontDatabase>
#include <QStringList>
#include <QFile>
#include <QDebug>

Launcher::Launcher(QWidget* parent): QWidget(parent),
    initView(), connectView(), menuView(), createView(),
    clientProtocol(std::nullopt) {
    this->initWidget();
    mainWidget.addWidget(&initView);
    mainWidget.addWidget(&connectView);
    mainWidget.addWidget(&menuView);
    mainWidget.addWidget(&createView);

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
    connect(&menuView, &MenuView::backClicked, this,
            &Launcher::goToMain);
    // Crear partida
    connect(&createView, &CreateView::createClicked, this,
            &Launcher::sendCreateMatch);
    connect(&createView, &CreateView::backClicked, this,
            &Launcher::goToMenu);

    QLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(&mainWidget);
    mainWidget.setCurrentIndex(0);
    this->setLayout(layout);
}

void Launcher::initWidget() {
    this->setObjectName("MainWidget");
    this->setWindowTitle("Left 2 Dead");
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

void Launcher::createProtocol(const QString& ip, const QString& port) {
    qDebug() << "Ip: " << ip;
    qDebug() << "port: " << port;
        mainWidget.setCurrentIndex(2);
    // try {
    //     this->clientProtocol = ClientProtocol(Socket(ip.toStdString().c_str(), port.toStdString().c_str()));
    // } catch (std::exception &exc){
    //     Q_EMIT errorConnection();
    // }
}

void Launcher::sendCreateMatch() {
}

Launcher::~Launcher() {
}