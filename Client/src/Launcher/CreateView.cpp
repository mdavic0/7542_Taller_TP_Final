#include "CreateView.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFile>

CreateView::CreateView(QWidget* parent) : QWidget(parent),
    nameGame("Nombre de la partida", this), lineName(this),
    clearZone("Clear the zone", this), survival("Survival", this),
    modeSelect(this), idf("", this), p90("", this), scout("", this),
    operatorSelect(this), mainLayout(this), 
    createButton("Crear", this), backButton("Volver", this),
    operatorLabel("", this), weaponLabel("", this),
    habilityLabel("", this), rateLabel("", this),
    difficultyLabel("Dificultad", this), difficultyBox(this) {

    this->initWidget();
    nameGame.setBuddy(&lineName);
    QHBoxLayout* layoutName = new QHBoxLayout;
    layoutName->addWidget(&nameGame);
    layoutName->addWidget(&lineName);

    // Selector de modo de Juego
    survival.setObjectName("survival");
    survival.setChecked(false);
    clearZone.setObjectName("clearZone");
    clearZone.setChecked(true);
    modeSelect.addButton(&survival, 0x01);
    modeSelect.addButton(&clearZone, 0x02);

    QHBoxLayout* layoutMode = new QHBoxLayout;
    layoutMode->addWidget(&clearZone);
    layoutMode->addWidget(&survival);

    QStringList difficulty = {"Easy", "Normal", "Hard", "God"};
    difficultyBox.addItems(difficulty);
    QHBoxLayout *layoutDifficulty = new QHBoxLayout;
    layoutDifficulty->addWidget(&difficultyLabel);
    layoutDifficulty->addWidget(&difficultyBox);

    QHBoxLayout *layoutGroupMode = new QHBoxLayout;
    layoutGroupMode->addLayout(layoutMode, Qt::AlignCenter);

    QGroupBox* modeBox = new QGroupBox;
    modeBox->setLayout(layoutGroupMode);
    modeBox->setTitle("Modo de juego");

    QHBoxLayout* layoutModeBox = new QHBoxLayout;
    layoutModeBox->addWidget(modeBox);

    QVBoxLayout* layoutOptions = new QVBoxLayout;
    layoutOptions->addLayout(layoutModeBox);
    layoutOptions->addLayout(layoutDifficulty);

    // Selector de operador
    idf.setObjectName("IDF");
    idf.setChecked(true);
    p90.setObjectName("P90");
    p90.setChecked(false);
    scout.setObjectName("Scout");
    scout.setChecked(false);
    operatorSelect.addButton(&idf, 0x01);
    operatorSelect.addButton(&p90, 0x02);
    operatorSelect.addButton(&scout, 0x03);

    QVBoxLayout* layoutOperator = new QVBoxLayout;
    layoutOperator->setSpacing(30);
    layoutOperator->addWidget(&idf);
    layoutOperator->addWidget(&p90);
    layoutOperator->addWidget(&scout);

    QVBoxLayout* layoutGroup = new QVBoxLayout;
    layoutGroup->addLayout(layoutOperator, Qt::AlignCenter); 

    QGroupBox* operatorBox = new QGroupBox;
    operatorBox->setLayout(layoutGroup);
    operatorBox->setTitle("Operador");
    
    //Perfile del Operador
    QVBoxLayout* profile = new QVBoxLayout;
    profile->addWidget(&operatorLabel);
    profile->addWidget(&weaponLabel);
    profile->addWidget(&rateLabel);
    profile->addWidget(&habilityLabel);

    QVBoxLayout* profileLayout = new QVBoxLayout;
    profileLayout->addLayout(profile, Qt::AlignAbsolute);

    QGroupBox* profileOperator = new QGroupBox;
    profileOperator->setObjectName("Profile");
    profileOperator->setLayout(profileLayout);
    profileOperator->setTitle("Datos del Operador");

    QHBoxLayout *layout = new QHBoxLayout;
    // layout->setSpacing(40);
    layout->addWidget(operatorBox);
    layout->addWidget(profileOperator);
    // layout->addWidget(profileOperator);    

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(&createButton);
    buttonLayout->addWidget(&backButton);

    this->viewIDF();
    connect(&createButton, &QPushButton::clicked, this,
            &CreateView::onCreateClicked);
    connect(&backButton, &QPushButton::clicked, this,
            &CreateView::onBackClicked);
    connect(&idf, &QCheckBox::clicked, this, &CreateView::viewIDF);
    connect(&p90, &QCheckBox::clicked, this, &CreateView::viewP90);
    connect(&scout, &QCheckBox::clicked, this, &CreateView::viewScout);

    mainLayout.addLayout(layoutName, 0, 0, Qt::AlignCenter);
    mainLayout.addLayout(layoutOptions, 1, 0,Qt::AlignCenter);
    mainLayout.addLayout(layout, 2, 0,Qt::AlignLeft);
    mainLayout.addLayout(buttonLayout, 3, 0, Qt::AlignHCenter);
    this->setLayout(&mainLayout);
}

void CreateView::viewIDF() {
    this->operatorLabel.setText("Nombre: Scott");
    this->weaponLabel.setText("Arma: Rifle de asalto IDF");
    this->rateLabel.setText(
        "Cadencia: Rafaga de 20 balas.\n Danio considerable a corta distancia");
    this->habilityLabel.setText("Habilidad: Granadas");
}

void CreateView::viewP90() {
    this->operatorLabel.setText("Nombre: James");
    this->weaponLabel.setText("Arma: Subfusil P90");
    this->rateLabel.setText("Cadencia: Rafaga de 10 balas.\n Danio Equilibrado");
    this->habilityLabel.setText("Habilidad: Bombardeo Aereo");
}

void CreateView::viewScout() {
    this->operatorLabel.setText("Nombre: Harry");
    this->weaponLabel.setText("Arma: Rifle francotirador");
    this->rateLabel.setText("Cadencia: 1 bala.\n Dania todo a su paso");
    this->habilityLabel.setText("Habilidad: Granadas");
}

void CreateView::onCreateClicked() {
    TypeDifficulty difficulty;
    switch (this->difficultyBox.currentIndex()) {
        case 0:
            difficulty = TypeDifficulty::difficulty_easy;
            break;
        case 1:
            difficulty = TypeDifficulty::difficulty_normal;
            break;
        case 2:
            difficulty = TypeDifficulty::difficulty_hard;
            break;
        case 3:
            difficulty = TypeDifficulty::difficulty_god;
            break;
        default:
            difficulty = TypeDifficulty::difficulty_normal;
            break;
    }
    Q_EMIT createClicked(this->lineName.text(), this->modeSelect.checkedId(),
                this->operatorSelect.checkedId(), difficulty);
    // enviar los datos al launcher;
}

void CreateView::onBackClicked() {
    Q_EMIT backClicked();
}

void CreateView::initWidget() {
    this->setObjectName("Create");
    this->setWindowTitle("Left 4 Dead");
    this->setFixedSize(800, 600);
    this->initStylesheet();
    this->initBackground();
}

void CreateView::initStylesheet() {
    QFile file(QString("assets/css/match.qss"));
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
}

void CreateView::initBackground() {
    this->setAutoFillBackground(true);
    QPixmap pixmap("assets/images/launcher/match.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),
        QBrush(pixmap.scaled(this->size())));
    this->setPalette(palette);
}

CreateView::~CreateView() {
}
