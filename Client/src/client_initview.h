#ifndef INITVIEW_H_
#define INITVIEW_H_

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class InitView : public QWidget {
    Q_OBJECT
    private:
        QPushButton buttonExit;
        QPushButton conectServer;
        QGridLayout mainLayout;
        void initWidget();
        void initStylesheet();
        void initBackground();
        void createScene();
    public:
        explicit InitView(QWidget* parent = 0);
        virtual ~InitView();
    Q_SIGNALS:
        void connectClicked();
    public slots:
        void onConnectClicked();
};

#endif
