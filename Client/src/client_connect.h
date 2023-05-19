#ifndef CLIENT_CONNECT_H_
#define CLIENT_CONNECT_H_

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class ConnectView : public QWidget  {
    Q_OBJECT
    private:
        QGridLayout mainLayout;
        QLabel ipLabel;
        QLineEdit lineIp;
        QLabel portLabel;
        QLineEdit linePort;
        QPushButton connectButton;
        QPushButton backButton;
        void initWidget();
        void initStylesheet();
        void initBackground();
    public:
        explicit ConnectView(QWidget* parent = 0);
        virtual ~ConnectView();
    Q_SIGNALS:
        void backConnect();
        void createConnection(const QString& ip, const QString& port);
    public slots:
        void goBack();
        void connectToServer();
};

#endif
