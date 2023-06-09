#include "JoinView.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFile>

JoinView::JoinView(QWidget* parent) : QWidget(parent),
	codeGame("Codigo de la partida", this), lineCode(this),
	idf("", this), p90("", this), scout("", this),
	operatorSelect(this), mainLayout(this), 
	joinButton("Unirse", this), backButton("Volver", this),
	operatorLabel("", this), weaponLabel("", this),
	habilityLabel("", this), rateLabel("", this) {

	this->initWidget();
	codeGame.setBuddy(&lineCode);
	QHBoxLayout* layoutCode = new QHBoxLayout;
	layoutCode->addWidget(&codeGame);
	layoutCode->addWidget(&lineCode);

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
	buttonLayout->addWidget(&joinButton);
	buttonLayout->addWidget(&backButton);

	this->viewIDF();
	connect(&joinButton, &QPushButton::clicked, this,
			&JoinView::onJoinClicked);
	connect(&backButton, &QPushButton::clicked, this, 
			&JoinView::onBackClicked);
	connect(&idf, &QCheckBox::clicked, this, &JoinView::viewIDF);
	connect(&p90, &QCheckBox::clicked, this, &JoinView::viewP90);
	connect(&scout, &QCheckBox::clicked, this, &JoinView::viewScout);

    mainLayout.setSpacing(20);
	mainLayout.addLayout(layoutCode, 0, 0, Qt::AlignCenter);
	mainLayout.addLayout(layout, 1, 0,Qt::AlignLeft);
	mainLayout.addLayout(buttonLayout, 2, 0, Qt::AlignHCenter);
	this->setLayout(&mainLayout);
}

void JoinView::viewIDF() {
    this->operatorLabel.setText("Nombre: Scott");
    this->weaponLabel.setText("Arma: Rifle de asalto IDF");
    this->rateLabel.setText(
        "Cadencia: Rafaga de 20 balas.\n Mucho danio a corta distancia");
    this->habilityLabel.setText("Habilidad: Granadas");
}

void JoinView::viewP90() {
    this->operatorLabel.setText("Nombre: James");
    this->weaponLabel.setText("Arma: Subfusil P90");
    this->rateLabel.setText(
		"Cadencia: Rafaga de 10 balas.\n Danio Equilibrado");
    this->habilityLabel.setText("Habilidad: Bombardeo Aereo");
}

void JoinView::viewScout() {
    this->operatorLabel.setText("Nombre: Harry");
    this->weaponLabel.setText("Arma: Rifle francotirador");
    this->rateLabel.setText("Cadencia: 1 bala.\n Dania todo a su paso");
    this->habilityLabel.setText("Habilidad: Granadas");
}

void JoinView::onJoinClicked() {
    Q_EMIT joinClicked(this->lineCode.text().toInt(),
						this->operatorSelect.checkedId());
}

void JoinView::onBackClicked() {
    Q_EMIT backClicked();
}

void JoinView::initWidget() {
    this->setObjectName("Create");
    this->setWindowTitle("Left 4 Dead");
    this->setFixedSize(800, 600);
    this->initStylesheet();
    this->initBackground();
}

void JoinView::initStylesheet() {
    QFile file(QString("assets/css/match.qss"));
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
}

void JoinView::initBackground() {
    this->setAutoFillBackground(true);
    QPixmap pixmap("assets/images/launcher/match.jpg");
    QPalette palette;
    palette.setBrush(this->backgroundRole(),
        QBrush(pixmap.scaled(this->size())));
    this->setPalette(palette);
}

JoinView::~JoinView() {
}


