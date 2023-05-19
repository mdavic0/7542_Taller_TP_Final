#include "client_createView.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QAbstractButton>

CreateView::CreateView(QWidget* parent) : QWidget(parent),
    nameGame("Nombre de la partida", this), lineName(this),
    clearZone("Clear the zone", this), survival("Survival", this),
    modeSelect(this), idf("IDF", this), p90("P90", this), scout("Scout", this),
    operatorSelect(this), mainLayout(this), 
    createButton("Crear partida", this), backButton("Volver", this),
    operatorLabel("Nombre: Scott", this), armaLabel("Armamento: IDF", this) {

    this->initWidget();
    nameGame.setBuddy(&lineName);
    QHBoxLayout* layoutName = new QHBoxLayout;
    layoutName->addWidget(&nameGame);
    layoutName->addWidget(&lineName);

    // Selector de modo de Juego
    clearZone.setObjectName("clearZone");
    clearZone.setChecked(true);
    survival.setObjectName("survival");
    survival.setChecked(false);
    modeSelect.addButton(&clearZone);
    modeSelect.addButton(&survival);

    QHBoxLayout* layoutMode = new QHBoxLayout;
    layoutMode->addWidget(&clearZone);
    layoutMode->addWidget(&survival);

    QHBoxLayout *layoutGroupMode = new QHBoxLayout;
    layoutGroupMode->addLayout(layoutMode, Qt::AlignCenter);

    QGroupBox* modeBox = new QGroupBox;
    modeBox->setLayout(layoutGroupMode);
    modeBox->setTitle("Selecciona Modo de juego");

    QHBoxLayout* layoutModeBox = new QHBoxLayout;
    layoutModeBox->addWidget(modeBox);

    // Selector de operador
    idf.setObjectName("IDF");
    idf.setChecked(true);
    p90.setObjectName("P90");
    p90.setChecked(false);
    scout.setObjectName("Scout");
    scout.setChecked(false);
    operatorSelect.addButton(&idf, 0x00);
    operatorSelect.addButton(&p90, 0x01);
    operatorSelect.addButton(&scout, 0x02);

    QVBoxLayout* layoutOperator = new QVBoxLayout;
    layoutOperator->addWidget(&idf);
    layoutOperator->addWidget(&p90);
    layoutOperator->addWidget(&scout);

    QVBoxLayout* layoutGroup = new QVBoxLayout;
    layoutGroup->addLayout(layoutOperator, Qt::AlignCenter); 

    QGroupBox* operatorBox = new QGroupBox;
    operatorBox->setLayout(layoutGroup);
    operatorBox->setTitle("Selecciona tu operador");
    
    //Perfile del Operador
    QVBoxLayout* profile = new QVBoxLayout;
    profile->addWidget(&operatorLabel);
    profile->addWidget(&armaLabel);

    QVBoxLayout* profileLayout = new QVBoxLayout;
    profileLayout->addLayout(profile, Qt::AlignCenter);

    QGroupBox* profileOperator = new QGroupBox;
    profileOperator->setLayout(profileLayout);
    profileOperator->setTitle("Datos del Operador");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(operatorBox);
    layout->addWidget(profileOperator);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(&createButton);
    buttonLayout->addWidget(&backButton);

    connect(&createButton, &QPushButton::clicked, this,
            &CreateView::onCreateClicked);
    connect(&backButton, &QPushButton::clicked, this,
            &CreateView::onBackClicked);
    connect(&idf, &QCheckBox::clicked, this, &CreateView::viewIDF);
    connect(&p90, &QCheckBox::clicked, this, &CreateView::viewP90);
    connect(&scout, &QCheckBox::clicked, this, &CreateView::viewScout);

    mainLayout.addLayout(layoutName, 0, 0, Qt::AlignCenter);
    mainLayout.addLayout(layoutModeBox, 1, 0,Qt::AlignCenter);
    mainLayout.addLayout(layout, 2, 0, Qt::AlignHCenter);
    mainLayout.addLayout(buttonLayout, 3, 0, Qt::AlignHCenter);
    this->setLayout(&mainLayout);
}

void CreateView::viewIDF() {
    this->armaLabel.setText("Arma: IDF");
}

void CreateView::viewP90() {
    this->armaLabel.setText("Arma: P90");
}

void CreateView::viewScout() {
    this->armaLabel.setText("Arma: Rifle");
}

void CreateView::onCreateClicked() {
    Q_EMIT createClicked();
}

void CreateView::onBackClicked() {
    Q_EMIT backClicked();
}

void CreateView::initWidget() {
    this->setObjectName("Create");
    this->setWindowTitle("Left 2 Dead");
    this->setFixedSize(800, 600);
}

CreateView::~CreateView() {
}
