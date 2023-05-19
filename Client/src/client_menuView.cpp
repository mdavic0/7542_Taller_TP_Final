#include "client_menuView.h"
#include <QVBoxLayout>

MenuView::MenuView(QWidget* parent) : QWidget(parent),
    createButton("Crear Partida", this), joinButton("Unirse a Partida", this),
    backButton("Volver", this), mainLayout(this) {
    this->initWidget();

    QVBoxLayout* buttonLayout = new QVBoxLayout;
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

    mainLayout.addLayout(buttonLayout, 0, 0, Qt::AlignCenter);
    this->setLayout(&mainLayout);
}

void MenuView::initWidget() {
    this->setObjectName("Menu");
    this->setWindowTitle("Left 2 Dead");
    this->setFixedSize(800, 600);
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


