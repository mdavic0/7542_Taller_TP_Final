#include "client_initview.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QFontDatabase>
#include <QFont>
#include <QFile>
#include <QDebug>

InitView::InitView(QWidget* parent) : QWidget(parent),
    buttonExit("Salir", this), conectServer("Iniciar", this),
    mainLayout(this) {
    this->initWidget();
    this->createScene();
}

void InitView::initWidget() {
    this->setObjectName("Init");
    this->setWindowTitle("Left 2 Dead");
    this->setFixedSize(800, 600);
    QFile file(QString("assets/css/init.qss"));
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
}

void InitView::createScene() {
    QVBoxLayout *buttonBox = new QVBoxLayout;
    buttonBox->setAlignment(Qt::AlignRight);
    buttonBox->addWidget(&conectServer);
    buttonBox->addWidget(&buttonExit);

    connect(&conectServer, &QPushButton::clicked, this, 
            &InitView::onConnectClicked);
    connect(&buttonExit, &QPushButton::clicked, this, QApplication::quit);
    mainLayout.addLayout(buttonBox, 0, 0, Qt::AlignCenter);
    this->setLayout(&mainLayout);
}

void InitView::onConnectClicked() {
    Q_EMIT connectClicked();
}

InitView::~InitView() {
}