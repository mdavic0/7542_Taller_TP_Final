#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include <QtWidgets>
#include <QPushButton>

class Launcher : public QWidget {
    private:
        QPushButton buttonExit;
        QPushButton conectServer;
        QGridLayout mainLayout;
        void initWidget();
        void createScene();
    public:
        explicit Launcher(QWidget* parent = 0);
        virtual ~Launcher();
};

#endif
