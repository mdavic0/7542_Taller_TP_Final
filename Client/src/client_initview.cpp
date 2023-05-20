#include "client_initview.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QFontDatabase>
#include <QFont>
#include <QFile>
#include <QPixmap>
#include <QPalette>
#include <QDebug>

InitView::InitView(QWidget* parent) : QWidget(parent),
    buttonExit("Salir", this), conectServer("Iniciar", this),
    mainLayout(this) {
    this->initWidget();
    this->createScene();
}

void InitView::initWidget() {
    this->setFixedSize(800, 600);
    this->setWindowTitle("Left 2 Dead");
    this->setObjectName("InitWidget");
    this->initStylesheet();
    this->initBackground();
}

void InitView::initStylesheet() {
    QFile file(QString("assets/css/init.qss"));
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
}

void InitView::initBackground() {
    this->setAutoFillBackground(true);
    QPixmap pixmap("assets/images/launcher/init.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),
        QBrush(pixmap.scaled(this->size())));
    this->setPalette(palette);
}

void InitView::createScene() {
    QVBoxLayout *buttonBox = new QVBoxLayout;
    buttonBox->setMargin(50);
    buttonBox->setAlignment(Qt::AlignCenter);
    buttonBox->addWidget(&conectServer);
    buttonBox->addWidget(&buttonExit);

    connect(&conectServer, &QPushButton::clicked, this,
            &InitView::onConnectClicked);
    connect(&buttonExit, &QPushButton::clicked, this, QApplication::quit);
    mainLayout.addLayout(buttonBox, 0, 0, Qt::AlignBottom | Qt::AlignLeft);
    this->setLayout(&mainLayout);
}

void InitView::onConnectClicked() {
    Q_EMIT connectClicked();
}

InitView::~InitView() {
}