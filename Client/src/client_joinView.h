#ifndef JOIN_VIEW_H_
#define JOIN_VIEW_H_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QPushButton>

class JoinView : public QWidget {
    Q_OBJECT
    private:
        QLabel codeGame;
        QLineEdit lineCode;
        QCheckBox idf;
        QCheckBox p90;
        QCheckBox scout;
        QButtonGroup operatorSelect;
        QGridLayout mainLayout;
        QPushButton joinButton;
        QPushButton backButton;
        QLabel operatorLabel;
        QLabel weaponLabel;
        QLabel habilityLabel;
        QLabel rateLabel;
        void initWidget();
        void initStylesheet();
        void initBackground();
    public:
        explicit JoinView(QWidget* parent = 0);
        virtual ~JoinView();
     Q_SIGNALS:
        void joinClicked(int code, int operatorSelect);
        void backClicked();
    public slots:
        void onJoinClicked();
        void onBackClicked();
    private slots:
        void viewIDF();
        void viewP90();
        void viewScout();
};

#endif
