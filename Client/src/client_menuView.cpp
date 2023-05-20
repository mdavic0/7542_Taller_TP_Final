#include "client_menuView.h"
#include <QVBoxLayout>
#include <QFile>

MenuView::MenuView(QWidget* parent) : QWidget(parent),
    createButton("Crear Partida", this), joinButton("Unirse a Partida", this),
    backButton("Volver", this), mainLayout(this) {
    this->initWidget();

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->setMargin(40);
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(&createButton);
    buttonLayout->addWidget(&joinButton);
    buttonLayout->addWidget(&backButton);

    connect(&createButton, &QPushButton::clicked, this,
            &MenuView::onCreateClicked);
    connect(&joinButton, &QPushButton::clicked, this,
            &MenuView::onJoinClicked);
    connect(&backButton, &QPushButton::clicked, this, 
            &MenuView::onBackClicked);

    mainLayout.addLayout(buttonLayout, 0, 0, Qt::AlignBottom | Qt::AlignLeft);
    this->setLayout(&mainLayout);
}

void MenuView::initWidget() {
    this->setObjectName("Menu");
    this->setWindowTitle("Left 2 Dead");
    this->setFixedSize(800, 600);
    this->initStylesheet();
    this->initBackground();
}

void MenuView::initStylesheet() {
    QFile file(QString("assets/css/init.qss"));
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
}

void MenuView::initBackground() {
    this->setAutoFillBackground(true);
    QPixmap pixmap("assets/images/launcher/init.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),
            QBrush(pixmap.scaled(this->size())));
    this->setPalette(palette);
}

void MenuView::onCreateClicked() {
    Q_EMIT createClicked();
}

void MenuView::onJoinClicked() {
    Q_EMIT joinClicked();
}

void MenuView::onBackClicked() {
    Q_EMIT backClicked();
}

MenuView::~MenuView() {
}


