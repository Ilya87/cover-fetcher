/********************************************************************************
** Form generated from reading UI file 'config.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigForm
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
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
        groupBox = new QGroupBox(ConfigForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listWidget = new QListWidget(groupBox);
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

        workInProgress = new QLabel(groupBox);
        workInProgress->setObjectName(QStringLiteral("workInProgress"));
        QFont font;
        font.setItalic(true);
        workInProgress->setFont(font);
        workInProgress->setWordWrap(true);

        verticalLayout_2->addWidget(workInProgress);


        verticalLayout->addWidget(groupBox);


        retranslateUi(ConfigForm);

        QMetaObject::connectSlotsByName(ConfigForm);
    } // setupUi

    void retranslateUi(QWidget *ConfigForm)
    {
        groupBox->setTitle(QApplication::translate("ConfigForm", "Remote Cover Art locations", 0));

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
