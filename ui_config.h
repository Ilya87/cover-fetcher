/********************************************************************************
** Form generated from reading UI file 'config.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigForm
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxIntegrate;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelIntegrateCover;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonIntegrateCover;
    QRadioButton *radioButtonDontIntegrate;
    QGroupBox *groupBoxRemoteLocations;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QLabel *workInProgress;

    void setupUi(QWidget *ConfigForm)
    {
        if (ConfigForm->objectName().isEmpty())
            ConfigForm->setObjectName(QStringLiteral("ConfigForm"));
        ConfigForm->resize(400, 300);
        ConfigForm->setWindowTitle(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(ConfigForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBoxIntegrate = new QGroupBox(ConfigForm);
        groupBoxIntegrate->setObjectName(QStringLiteral("groupBoxIntegrate"));
        verticalLayout_3 = new QVBoxLayout(groupBoxIntegrate);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        labelIntegrateCover = new QLabel(groupBoxIntegrate);
        labelIntegrateCover->setObjectName(QStringLiteral("labelIntegrateCover"));
        QFont font;
        font.setItalic(true);
        labelIntegrateCover->setFont(font);
        labelIntegrateCover->setWordWrap(true);

        verticalLayout_3->addWidget(labelIntegrateCover);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioButtonIntegrateCover = new QRadioButton(groupBoxIntegrate);
        radioButtonIntegrateCover->setObjectName(QStringLiteral("radioButtonIntegrateCover"));
        radioButtonIntegrateCover->setChecked(true);

        horizontalLayout->addWidget(radioButtonIntegrateCover);

        radioButtonDontIntegrate = new QRadioButton(groupBoxIntegrate);
        radioButtonDontIntegrate->setObjectName(QStringLiteral("radioButtonDontIntegrate"));

        horizontalLayout->addWidget(radioButtonDontIntegrate);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBoxIntegrate);

        groupBoxRemoteLocations = new QGroupBox(ConfigForm);
        groupBoxRemoteLocations->setObjectName(QStringLiteral("groupBoxRemoteLocations"));
        verticalLayout_2 = new QVBoxLayout(groupBoxRemoteLocations);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listWidget = new QListWidget(groupBoxRemoteLocations);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setText(QStringLiteral("MusicBrainz"));
        __qlistwidgetitem->setCheckState(Qt::Checked);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setText(QStringLiteral("Discogs"));
        __qlistwidgetitem1->setCheckState(Qt::Unchecked);
        __qlistwidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setText(QStringLiteral("Amazon"));
        __qlistwidgetitem2->setCheckState(Qt::Unchecked);
        __qlistwidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setText(QStringLiteral("Last.FM"));
        __qlistwidgetitem3->setCheckState(Qt::Unchecked);
        __qlistwidgetitem3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        workInProgress = new QLabel(groupBoxRemoteLocations);
        workInProgress->setObjectName(QStringLiteral("workInProgress"));
        workInProgress->setFont(font);
        workInProgress->setWordWrap(true);

        verticalLayout_2->addWidget(workInProgress);


        verticalLayout->addWidget(groupBoxRemoteLocations);


        retranslateUi(ConfigForm);

        QMetaObject::connectSlotsByName(ConfigForm);
    } // setupUi

    void retranslateUi(QWidget *ConfigForm)
    {
        groupBoxIntegrate->setTitle(QApplication::translate("ConfigForm", "About downloaded covers", 0));
        labelIntegrateCover->setText(QApplication::translate("ConfigForm", "When it is possible, should I try to incorporate the cover inside the file?", 0));
        radioButtonIntegrateCover->setText(QApplication::translate("ConfigForm", "Yes", 0));
        radioButtonDontIntegrate->setText(QApplication::translate("ConfigForm", "No", 0));
        groupBoxRemoteLocations->setTitle(QApplication::translate("ConfigForm", "Remote Cover Art locations", 0));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        listWidget->setSortingEnabled(__sortingEnabled);

        workInProgress->setText(QApplication::translate("ConfigForm", "This plugin is under development, therefore only MusicBrainz Repository is implemented.", 0));
        Q_UNUSED(ConfigForm);
    } // retranslateUi

};

namespace Ui {
    class ConfigForm: public Ui_ConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
