#include "clientLauncher.h"

Launcher::Launcher(QWidget* parent) : QWidget(parent),
    conectServer("Conectar", this), buttonExit("Salir", this),
    mainLayout(this) {
    this->initWidget();
    this->createScene();
}

Launcher::~Launcher(){
}

void Launcher::initWidget() {
    this->setObjectName("Main");
    this->setWindowTitle("Left 2 Dead");
    this->setFixedSize(800, 600);
}

void Launcher::createScene() {
    buttonExit.setDefault(true);
    QVBoxLayout *buttonBox = new QVBoxLayout;
    buttonBox->setAlignment(Qt::AlignCenter);
    buttonBox->addWidget(&conectServer);
    buttonBox->addWidget(&buttonExit);

    connect(&buttonExit, &QAbstractButton::clicked, this, QApplication::quit);
    mainLayout.addLayout(buttonBox, 0, 0, Qt::AlignRight);
    this->setLayout(&mainLayout);
}
