#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include <QWidget>
#include <QStackedWidget>
#include <optional>
#include "client_connect.h"
#include "client_initview.h"
#include "client_menuView.h"
#include "client_createView.h"
#include "client_joinView.h"
#include "client_protocol.h"

class Launcher : public QWidget {
    Q_OBJECT
    private:
        QStackedWidget mainWidget;
        InitView initView;
        ConnectView connectView;
        MenuView menuView;
        CreateView createView;
        JoinView joinView;
        std::optional<ClientProtocol> clientProtocol;
        void initWidget();
        void initFont();
        void initGame(int operatorSelect);
        void initThreadsConnection();
    public:
        explicit Launcher(QWidget* parent = 0);
        virtual ~Launcher();
    Q_SIGNALS:
        void errorConnection();
    private slots:
        void goToMain();
        void goToConnect();
        void goToMenu();
        void goToCreate();
        void goToJoin();
        void createProtocol(const QString& ip, const QString& port);
        void sendCreateMatch(const QString& name, int mode, 
                            int operatorSelect);
        void sendJoinMatch(int code, int operatorSelect);

};

#endif
