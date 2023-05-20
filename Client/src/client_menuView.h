#ifndef MENU_VIEW_H_
#define MENU_VIEW_H_

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class MenuView : public QWidget {
    Q_OBJECT
    private:
        QPushButton createButton;
        QPushButton joinButton;
        QPushButton backButton;
        QGridLayout mainLayout;
        void initWidget();
        void initStylesheet();
        void initBackground();
    public:
        explicit MenuView(QWidget* parent = 0);
        virtual ~MenuView();
    Q_SIGNALS:
        void createClicked();
        void joinClicked();
        void backClicked();
    public slots:
        void onCreateClicked();
        void onJoinClicked();
        void onBackClicked();
};

#endif
