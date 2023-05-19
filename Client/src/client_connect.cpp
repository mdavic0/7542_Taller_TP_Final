#include "client_connect.h"
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QMessageBox>

ConnectView ::ConnectView (QWidget* parent) : QWidget(parent),
    ipLabel("IP", this), lineIp(this), portLabel("Puerto"), linePort(this),
    mainLayout(this), connectButton("Conectar", this),
    backButton("Volver", this) {
    this->initWidget();
    lineIp.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lineIp.setPlaceholderText("000.000.000.000");
    ipLabel.setBuddy(&lineIp);
    linePort.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    linePort.setPlaceholderText("0000");
    portLabel.setBuddy(&linePort);

    QHBoxLayout *layoutIp = new QHBoxLayout;
    layoutIp->setSpacing(15);
    layoutIp->addWidget(&ipLabel);
    layoutIp->addWidget(&lineIp);

    QHBoxLayout *layoutPort = new QHBoxLayout;
    layoutPort->setSpacing(5);
    layoutPort->addWidget(&portLabel);
    layoutPort->addWidget(&linePort);

    QHBoxLayout *layoutButton = new QHBoxLayout;
    connectButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    backButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layoutButton->addWidget(&connectButton, QDialogButtonBox::ActionRole);
    layoutButton->addWidget(&backButton, QDialogButtonBox::ActionRole);

    mainLayout.setAlignment(Qt::AlignCenter);
    mainLayout.setSpacing(15);
    mainLayout.addLayout(layoutIp, 0, 0, Qt::AlignCenter | Qt::AlignHCenter);
    mainLayout.addLayout(layoutPort, 1, 0, Qt::AlignCenter);
    mainLayout.addLayout(layoutButton, 2, 0, Qt::AlignCenter);

    connect(&connectButton, &QPushButton::clicked, this, 
            &ConnectView::connectToServer);
    connect(&backButton, &QPushButton::clicked, this, &ConnectView::goBack);

    this->setLayout(&mainLayout);

}

void ConnectView::goBack() {
    Q_EMIT backConnect();
}

void ConnectView::connectToServer() {
    QString ip = lineIp.text();
    QString port = linePort.text();
    if (!ip.isEmpty() && !port.isEmpty()) {
        Q_EMIT createConnection(ip, port);
    } else {
        QMessageBox::information(this, "Error", 
                    "Complete los datos correctamente",
                    QMessageBox::Close);
    }
}

void ConnectView::initWidget() {
    this->setObjectName("Connect");
    this->setWindowTitle("Left 2 Dead");
    this->setFixedSize(800, 600);
}

ConnectView::~ConnectView() {
}
