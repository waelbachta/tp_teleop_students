/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *layout_robots;
    QGroupBox *Ro_box;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *Ro_layout;
    QVBoxLayout *Ro_layout_boutons;
    QPushButton *Ro_bouton_demarrer;
    QPushButton *Ro_bouton_calibrer;
    QPushButton *Ro_bouton_connecter;
    QPushButton *Ro_bouton_identifier;
    QVBoxLayout *Ro_layout_etat;
    QGroupBox *Ro_box_q;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *Ro_layout_q;
    QHBoxLayout *Ro_layout_q1;
    QLabel *Ro_label_q1;
    QSpacerItem *Ro_horizontalSpacer_q1;
    QLineEdit *Ro_q1;
    QHBoxLayout *Ro_layout_q2;
    QLabel *Ro_label_q2;
    QSpacerItem *Ro_horizontalSpacer_q2;
    QLineEdit *Ro_q2;
    QGroupBox *Ro_box_pos;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *Ro_layout_pos;
    QHBoxLayout *Ro_layout_x;
    QLabel *Ro_label_x;
    QSpacerItem *Ro_horizontalSpacer_x;
    QLineEdit *Ro_x;
    QHBoxLayout *Ro_layout_y;
    QLabel *Ro_label_y;
    QSpacerItem *Ro_horizontalSpacer_y;
    QLineEdit *Ro_y;
    QSpacerItem *verticalSpacer;
    QGroupBox *Rt_box;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *Rt_layout;
    QVBoxLayout *Rt_layout_boutons;
    QPushButton *Rt_bouton_demarrer;
    QPushButton *Rt_bouton_calibrer;
    QPushButton *Rt_bouton_connecter;
    QPushButton *Rt_bouton_identifier;
    QVBoxLayout *Rt_layout_etat;
    QGroupBox *Rt_box_q;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *Rt_layout_q;
    QHBoxLayout *Rt_layout_q1;
    QLabel *Rt_label_q1;
    QSpacerItem *Rt_horizontalSpacer_q1;
    QLineEdit *Rt_q1;
    QHBoxLayout *Rt_layout_q2;
    QLabel *Rt_label_q2;
    QSpacerItem *Rt_horizontalSpacer_q2;
    QLineEdit *Rt_q2;
    QGroupBox *Rt_box_pos;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *Rt_layout_pos;
    QHBoxLayout *Rt_layout_x;
    QLabel *Rt_label_x;
    QSpacerItem *Rt_horizontalSpacer_x;
    QLineEdit *Rt_x;
    QHBoxLayout *Rt_layout_y;
    QLabel *Rt_label_y;
    QSpacerItem *Rt_horizontalSpacer_y;
    QLineEdit *Rt_y;
    QCustomPlot *figure;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *teleop_layout;
    QLabel *teleop_label;
    QHBoxLayout *teleop_layout_boutons;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *teleop_bouton_identifier;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *teleop_bouton_lancer;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *teleop_box_ylim;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *teleop_layout_ylim;
    QSpacerItem *horizontalSpacer;
    QLabel *teleop_label_ylim;
    QDoubleSpinBox *teleop_ylim;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(840, 680);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(20, 30, 366, 588));
        layout_robots = new QVBoxLayout(verticalLayoutWidget_4);
        layout_robots->setObjectName(QStringLiteral("layout_robots"));
        layout_robots->setContentsMargins(0, 0, 0, 0);
        Ro_box = new QGroupBox(verticalLayoutWidget_4);
        Ro_box->setObjectName(QStringLiteral("Ro_box"));
        horizontalLayout_3 = new QHBoxLayout(Ro_box);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Ro_layout = new QHBoxLayout();
        Ro_layout->setObjectName(QStringLiteral("Ro_layout"));
        Ro_layout_boutons = new QVBoxLayout();
        Ro_layout_boutons->setObjectName(QStringLiteral("Ro_layout_boutons"));
        Ro_bouton_demarrer = new QPushButton(Ro_box);
        Ro_bouton_demarrer->setObjectName(QStringLiteral("Ro_bouton_demarrer"));

        Ro_layout_boutons->addWidget(Ro_bouton_demarrer);

        Ro_bouton_calibrer = new QPushButton(Ro_box);
        Ro_bouton_calibrer->setObjectName(QStringLiteral("Ro_bouton_calibrer"));
        Ro_bouton_calibrer->setEnabled(false);

        Ro_layout_boutons->addWidget(Ro_bouton_calibrer);

        Ro_bouton_connecter = new QPushButton(Ro_box);
        Ro_bouton_connecter->setObjectName(QStringLiteral("Ro_bouton_connecter"));
        Ro_bouton_connecter->setEnabled(false);

        Ro_layout_boutons->addWidget(Ro_bouton_connecter);

        Ro_bouton_identifier = new QPushButton(Ro_box);
        Ro_bouton_identifier->setObjectName(QStringLiteral("Ro_bouton_identifier"));
        Ro_bouton_identifier->setEnabled(false);

        Ro_layout_boutons->addWidget(Ro_bouton_identifier);


        Ro_layout->addLayout(Ro_layout_boutons);

        Ro_layout_etat = new QVBoxLayout();
        Ro_layout_etat->setObjectName(QStringLiteral("Ro_layout_etat"));
        Ro_box_q = new QGroupBox(Ro_box);
        Ro_box_q->setObjectName(QStringLiteral("Ro_box_q"));
        verticalLayout_4 = new QVBoxLayout(Ro_box_q);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        Ro_layout_q = new QVBoxLayout();
        Ro_layout_q->setObjectName(QStringLiteral("Ro_layout_q"));
        Ro_layout_q1 = new QHBoxLayout();
        Ro_layout_q1->setObjectName(QStringLiteral("Ro_layout_q1"));
        Ro_label_q1 = new QLabel(Ro_box_q);
        Ro_label_q1->setObjectName(QStringLiteral("Ro_label_q1"));

        Ro_layout_q1->addWidget(Ro_label_q1);

        Ro_horizontalSpacer_q1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Ro_layout_q1->addItem(Ro_horizontalSpacer_q1);

        Ro_q1 = new QLineEdit(Ro_box_q);
        Ro_q1->setObjectName(QStringLiteral("Ro_q1"));
        Ro_q1->setEnabled(true);
        Ro_q1->setReadOnly(true);

        Ro_layout_q1->addWidget(Ro_q1);


        Ro_layout_q->addLayout(Ro_layout_q1);

        Ro_layout_q2 = new QHBoxLayout();
        Ro_layout_q2->setObjectName(QStringLiteral("Ro_layout_q2"));
        Ro_label_q2 = new QLabel(Ro_box_q);
        Ro_label_q2->setObjectName(QStringLiteral("Ro_label_q2"));

        Ro_layout_q2->addWidget(Ro_label_q2);

        Ro_horizontalSpacer_q2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Ro_layout_q2->addItem(Ro_horizontalSpacer_q2);

        Ro_q2 = new QLineEdit(Ro_box_q);
        Ro_q2->setObjectName(QStringLiteral("Ro_q2"));
        Ro_q2->setReadOnly(true);

        Ro_layout_q2->addWidget(Ro_q2);


        Ro_layout_q->addLayout(Ro_layout_q2);


        verticalLayout_4->addLayout(Ro_layout_q);


        Ro_layout_etat->addWidget(Ro_box_q);

        Ro_box_pos = new QGroupBox(Ro_box);
        Ro_box_pos->setObjectName(QStringLiteral("Ro_box_pos"));
        verticalLayout_5 = new QVBoxLayout(Ro_box_pos);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        Ro_layout_pos = new QVBoxLayout();
        Ro_layout_pos->setObjectName(QStringLiteral("Ro_layout_pos"));
        Ro_layout_x = new QHBoxLayout();
        Ro_layout_x->setObjectName(QStringLiteral("Ro_layout_x"));
        Ro_label_x = new QLabel(Ro_box_pos);
        Ro_label_x->setObjectName(QStringLiteral("Ro_label_x"));

        Ro_layout_x->addWidget(Ro_label_x);

        Ro_horizontalSpacer_x = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Ro_layout_x->addItem(Ro_horizontalSpacer_x);

        Ro_x = new QLineEdit(Ro_box_pos);
        Ro_x->setObjectName(QStringLiteral("Ro_x"));
        Ro_x->setEnabled(true);
        Ro_x->setReadOnly(true);

        Ro_layout_x->addWidget(Ro_x);


        Ro_layout_pos->addLayout(Ro_layout_x);

        Ro_layout_y = new QHBoxLayout();
        Ro_layout_y->setObjectName(QStringLiteral("Ro_layout_y"));
        Ro_label_y = new QLabel(Ro_box_pos);
        Ro_label_y->setObjectName(QStringLiteral("Ro_label_y"));

        Ro_layout_y->addWidget(Ro_label_y);

        Ro_horizontalSpacer_y = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Ro_layout_y->addItem(Ro_horizontalSpacer_y);

        Ro_y = new QLineEdit(Ro_box_pos);
        Ro_y->setObjectName(QStringLiteral("Ro_y"));
        Ro_y->setReadOnly(true);

        Ro_layout_y->addWidget(Ro_y);


        Ro_layout_pos->addLayout(Ro_layout_y);


        verticalLayout_5->addLayout(Ro_layout_pos);


        Ro_layout_etat->addWidget(Ro_box_pos);


        Ro_layout->addLayout(Ro_layout_etat);


        horizontalLayout_3->addLayout(Ro_layout);


        layout_robots->addWidget(Ro_box);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layout_robots->addItem(verticalSpacer);

        Rt_box = new QGroupBox(verticalLayoutWidget_4);
        Rt_box->setObjectName(QStringLiteral("Rt_box"));
        horizontalLayout_2 = new QHBoxLayout(Rt_box);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Rt_layout = new QHBoxLayout();
        Rt_layout->setObjectName(QStringLiteral("Rt_layout"));
        Rt_layout_boutons = new QVBoxLayout();
        Rt_layout_boutons->setObjectName(QStringLiteral("Rt_layout_boutons"));
        Rt_bouton_demarrer = new QPushButton(Rt_box);
        Rt_bouton_demarrer->setObjectName(QStringLiteral("Rt_bouton_demarrer"));

        Rt_layout_boutons->addWidget(Rt_bouton_demarrer);

        Rt_bouton_calibrer = new QPushButton(Rt_box);
        Rt_bouton_calibrer->setObjectName(QStringLiteral("Rt_bouton_calibrer"));
        Rt_bouton_calibrer->setEnabled(false);

        Rt_layout_boutons->addWidget(Rt_bouton_calibrer);

        Rt_bouton_connecter = new QPushButton(Rt_box);
        Rt_bouton_connecter->setObjectName(QStringLiteral("Rt_bouton_connecter"));
        Rt_bouton_connecter->setEnabled(false);

        Rt_layout_boutons->addWidget(Rt_bouton_connecter);

        Rt_bouton_identifier = new QPushButton(Rt_box);
        Rt_bouton_identifier->setObjectName(QStringLiteral("Rt_bouton_identifier"));
        Rt_bouton_identifier->setEnabled(false);

        Rt_layout_boutons->addWidget(Rt_bouton_identifier);


        Rt_layout->addLayout(Rt_layout_boutons);

        Rt_layout_etat = new QVBoxLayout();
        Rt_layout_etat->setObjectName(QStringLiteral("Rt_layout_etat"));
        Rt_box_q = new QGroupBox(Rt_box);
        Rt_box_q->setObjectName(QStringLiteral("Rt_box_q"));
        verticalLayout = new QVBoxLayout(Rt_box_q);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Rt_layout_q = new QVBoxLayout();
        Rt_layout_q->setObjectName(QStringLiteral("Rt_layout_q"));
        Rt_layout_q1 = new QHBoxLayout();
        Rt_layout_q1->setObjectName(QStringLiteral("Rt_layout_q1"));
        Rt_label_q1 = new QLabel(Rt_box_q);
        Rt_label_q1->setObjectName(QStringLiteral("Rt_label_q1"));

        Rt_layout_q1->addWidget(Rt_label_q1);

        Rt_horizontalSpacer_q1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Rt_layout_q1->addItem(Rt_horizontalSpacer_q1);

        Rt_q1 = new QLineEdit(Rt_box_q);
        Rt_q1->setObjectName(QStringLiteral("Rt_q1"));
        Rt_q1->setEnabled(true);
        Rt_q1->setReadOnly(true);

        Rt_layout_q1->addWidget(Rt_q1);


        Rt_layout_q->addLayout(Rt_layout_q1);

        Rt_layout_q2 = new QHBoxLayout();
        Rt_layout_q2->setObjectName(QStringLiteral("Rt_layout_q2"));
        Rt_label_q2 = new QLabel(Rt_box_q);
        Rt_label_q2->setObjectName(QStringLiteral("Rt_label_q2"));

        Rt_layout_q2->addWidget(Rt_label_q2);

        Rt_horizontalSpacer_q2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Rt_layout_q2->addItem(Rt_horizontalSpacer_q2);

        Rt_q2 = new QLineEdit(Rt_box_q);
        Rt_q2->setObjectName(QStringLiteral("Rt_q2"));
        Rt_q2->setReadOnly(true);

        Rt_layout_q2->addWidget(Rt_q2);


        Rt_layout_q->addLayout(Rt_layout_q2);


        verticalLayout->addLayout(Rt_layout_q);


        Rt_layout_etat->addWidget(Rt_box_q);

        Rt_box_pos = new QGroupBox(Rt_box);
        Rt_box_pos->setObjectName(QStringLiteral("Rt_box_pos"));
        verticalLayout_3 = new QVBoxLayout(Rt_box_pos);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        Rt_layout_pos = new QVBoxLayout();
        Rt_layout_pos->setObjectName(QStringLiteral("Rt_layout_pos"));
        Rt_layout_x = new QHBoxLayout();
        Rt_layout_x->setObjectName(QStringLiteral("Rt_layout_x"));
        Rt_label_x = new QLabel(Rt_box_pos);
        Rt_label_x->setObjectName(QStringLiteral("Rt_label_x"));

        Rt_layout_x->addWidget(Rt_label_x);

        Rt_horizontalSpacer_x = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Rt_layout_x->addItem(Rt_horizontalSpacer_x);

        Rt_x = new QLineEdit(Rt_box_pos);
        Rt_x->setObjectName(QStringLiteral("Rt_x"));
        Rt_x->setEnabled(true);
        Rt_x->setReadOnly(true);

        Rt_layout_x->addWidget(Rt_x);


        Rt_layout_pos->addLayout(Rt_layout_x);

        Rt_layout_y = new QHBoxLayout();
        Rt_layout_y->setObjectName(QStringLiteral("Rt_layout_y"));
        Rt_label_y = new QLabel(Rt_box_pos);
        Rt_label_y->setObjectName(QStringLiteral("Rt_label_y"));

        Rt_layout_y->addWidget(Rt_label_y);

        Rt_horizontalSpacer_y = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Rt_layout_y->addItem(Rt_horizontalSpacer_y);

        Rt_y = new QLineEdit(Rt_box_pos);
        Rt_y->setObjectName(QStringLiteral("Rt_y"));
        Rt_y->setReadOnly(true);

        Rt_layout_y->addWidget(Rt_y);


        Rt_layout_pos->addLayout(Rt_layout_y);


        verticalLayout_3->addLayout(Rt_layout_pos);


        Rt_layout_etat->addWidget(Rt_box_pos);


        Rt_layout->addLayout(Rt_layout_etat);


        horizontalLayout_2->addLayout(Rt_layout);


        layout_robots->addWidget(Rt_box);

        figure = new QCustomPlot(centralwidget);
        figure->setObjectName(QStringLiteral("figure"));
        figure->setGeometry(QRect(410, 210, 400, 400));
        verticalLayoutWidget_5 = new QWidget(centralwidget);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(410, 30, 401, 173));
        teleop_layout = new QVBoxLayout(verticalLayoutWidget_5);
        teleop_layout->setObjectName(QStringLiteral("teleop_layout"));
        teleop_layout->setContentsMargins(0, 0, 0, 0);
        teleop_label = new QLabel(verticalLayoutWidget_5);
        teleop_label->setObjectName(QStringLiteral("teleop_label"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        teleop_label->setFont(font);

        teleop_layout->addWidget(teleop_label);

        teleop_layout_boutons = new QHBoxLayout();
        teleop_layout_boutons->setObjectName(QStringLiteral("teleop_layout_boutons"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        teleop_layout_boutons->addItem(horizontalSpacer_3);

        teleop_bouton_identifier = new QPushButton(verticalLayoutWidget_5);
        teleop_bouton_identifier->setObjectName(QStringLiteral("teleop_bouton_identifier"));
        teleop_bouton_identifier->setEnabled(false);

        teleop_layout_boutons->addWidget(teleop_bouton_identifier);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        teleop_layout_boutons->addItem(horizontalSpacer_2);

        teleop_bouton_lancer = new QPushButton(verticalLayoutWidget_5);
        teleop_bouton_lancer->setObjectName(QStringLiteral("teleop_bouton_lancer"));
        teleop_bouton_lancer->setEnabled(false);
        teleop_bouton_lancer->setCheckable(true);
        teleop_bouton_lancer->setAutoDefault(false);
        teleop_bouton_lancer->setFlat(false);

        teleop_layout_boutons->addWidget(teleop_bouton_lancer);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        teleop_layout_boutons->addItem(horizontalSpacer_4);


        teleop_layout->addLayout(teleop_layout_boutons);

        teleop_box_ylim = new QGroupBox(verticalLayoutWidget_5);
        teleop_box_ylim->setObjectName(QStringLiteral("teleop_box_ylim"));
        teleop_box_ylim->setCheckable(true);
        horizontalLayout_4 = new QHBoxLayout(teleop_box_ylim);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        teleop_layout_ylim = new QHBoxLayout();
        teleop_layout_ylim->setObjectName(QStringLiteral("teleop_layout_ylim"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        teleop_layout_ylim->addItem(horizontalSpacer);

        teleop_label_ylim = new QLabel(teleop_box_ylim);
        teleop_label_ylim->setObjectName(QStringLiteral("teleop_label_ylim"));

        teleop_layout_ylim->addWidget(teleop_label_ylim);

        teleop_ylim = new QDoubleSpinBox(teleop_box_ylim);
        teleop_ylim->setObjectName(QStringLiteral("teleop_ylim"));
        teleop_ylim->setDecimals(0);
        teleop_ylim->setMinimum(-300);
        teleop_ylim->setMaximum(-150);
        teleop_ylim->setSingleStep(10);
        teleop_ylim->setValue(-250);

        teleop_layout_ylim->addWidget(teleop_ylim);


        horizontalLayout_4->addLayout(teleop_layout_ylim);


        teleop_layout->addWidget(teleop_box_ylim);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 840, 31));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(Ro_bouton_demarrer, SIGNAL(clicked(bool)), Ro_bouton_calibrer, SLOT(setDisabled(bool)));
        QObject::connect(Ro_bouton_calibrer, SIGNAL(clicked(bool)), Ro_bouton_connecter, SLOT(setDisabled(bool)));
        QObject::connect(Rt_bouton_demarrer, SIGNAL(clicked(bool)), Rt_bouton_calibrer, SLOT(setDisabled(bool)));
        QObject::connect(Rt_bouton_calibrer, SIGNAL(clicked(bool)), Rt_bouton_connecter, SLOT(setDisabled(bool)));
        QObject::connect(teleop_bouton_identifier, SIGNAL(toggled(bool)), teleop_bouton_lancer, SLOT(setEnabled(bool)));

        teleop_bouton_lancer->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Ro_box->setTitle(QApplication::translate("MainWindow", "Robot op\303\251rateur (orange)", 0));
        Ro_bouton_demarrer->setText(QApplication::translate("MainWindow", "D\303\251marrer", 0));
        Ro_bouton_calibrer->setText(QApplication::translate("MainWindow", "Calibrer", 0));
        Ro_bouton_connecter->setText(QApplication::translate("MainWindow", "Connecter", 0));
        Ro_bouton_identifier->setText(QApplication::translate("MainWindow", "Identifier", 0));
        Ro_box_q->setTitle(QApplication::translate("MainWindow", "Articulations", 0));
        Ro_label_q1->setText(QApplication::translate("MainWindow", "q1 [rad] :", 0));
        Ro_label_q2->setText(QApplication::translate("MainWindow", "q2 [rad] :", 0));
        Ro_box_pos->setTitle(QApplication::translate("MainWindow", "Position", 0));
        Ro_label_x->setText(QApplication::translate("MainWindow", "x [mm] :", 0));
        Ro_label_y->setText(QApplication::translate("MainWindow", "y [mm] :", 0));
        Rt_box->setTitle(QApplication::translate("MainWindow", "Robot t\303\251l\303\251op\303\251r\303\251 (bleu)", 0));
        Rt_bouton_demarrer->setText(QApplication::translate("MainWindow", "D\303\251marrer", 0));
        Rt_bouton_calibrer->setText(QApplication::translate("MainWindow", "Calibrer", 0));
        Rt_bouton_connecter->setText(QApplication::translate("MainWindow", "Connecter", 0));
        Rt_bouton_identifier->setText(QApplication::translate("MainWindow", "Identifier", 0));
        Rt_box_q->setTitle(QApplication::translate("MainWindow", "Articulations", 0));
        Rt_label_q1->setText(QApplication::translate("MainWindow", "q1 [rad] :", 0));
        Rt_label_q2->setText(QApplication::translate("MainWindow", "q2 [rad] :", 0));
        Rt_box_pos->setTitle(QApplication::translate("MainWindow", "Position", 0));
        Rt_label_x->setText(QApplication::translate("MainWindow", "x [mm] :", 0));
        Rt_label_y->setText(QApplication::translate("MainWindow", "y [mm] :", 0));
        teleop_label->setText(QApplication::translate("MainWindow", "Syst\303\250me de t\303\251l\303\251op\303\251ration", 0));
        teleop_bouton_identifier->setText(QApplication::translate("MainWindow", "Identifier", 0));
        teleop_bouton_lancer->setText(QApplication::translate("MainWindow", "Lancer/Arr\303\252ter", 0));
        teleop_box_ylim->setTitle(QApplication::translate("MainWindow", "Limite de l'espace", 0));
        teleop_label_ylim->setText(QApplication::translate("MainWindow", "ylim [mm] :", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
