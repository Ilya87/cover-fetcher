/********************************************************************************
** Form generated from reading UI file 'config.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
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
    QCheckBox *musicbrainzCheckBox;
    QCheckBox *amazonCheckBox;
    QCheckBox *discogsCheckBox;
    QCheckBox *lastfmCheckBox;
    QLabel *workInProgress;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ConfigForm)
    {
        if (ConfigForm->objectName().isEmpty())
            ConfigForm->setObjectName(QStringLiteral("ConfigForm"));
        ConfigForm->resize(400, 315);
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
        musicbrainzCheckBox = new QCheckBox(groupBoxRemoteLocations);
        musicbrainzCheckBox->setObjectName(QStringLiteral("musicbrainzCheckBox"));
        musicbrainzCheckBox->setText(QStringLiteral("MusicBrainz"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/musicBrainz_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        musicbrainzCheckBox->setIcon(icon);
        musicbrainzCheckBox->setIconSize(QSize(46, 32));
        musicbrainzCheckBox->setCheckable(true);
        musicbrainzCheckBox->setChecked(true);
        musicbrainzCheckBox->setProperty("type", QVariant(0));

        verticalLayout_2->addWidget(musicbrainzCheckBox);

        amazonCheckBox = new QCheckBox(groupBoxRemoteLocations);
        amazonCheckBox->setObjectName(QStringLiteral("amazonCheckBox"));
        amazonCheckBox->setText(QStringLiteral("Amazon"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/amazon_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        amazonCheckBox->setIcon(icon1);
        amazonCheckBox->setIconSize(QSize(87, 32));
        amazonCheckBox->setChecked(true);
        amazonCheckBox->setProperty("type", QVariant(1));

        verticalLayout_2->addWidget(amazonCheckBox);

        discogsCheckBox = new QCheckBox(groupBoxRemoteLocations);
        discogsCheckBox->setObjectName(QStringLiteral("discogsCheckBox"));
        discogsCheckBox->setEnabled(false);
        discogsCheckBox->setText(QStringLiteral("Discogs"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/discogs_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        discogsCheckBox->setIcon(icon2);
        discogsCheckBox->setIconSize(QSize(89, 32));
        discogsCheckBox->setProperty("type", QVariant(2));

        verticalLayout_2->addWidget(discogsCheckBox);

        lastfmCheckBox = new QCheckBox(groupBoxRemoteLocations);
        lastfmCheckBox->setObjectName(QStringLiteral("lastfmCheckBox"));
        lastfmCheckBox->setEnabled(false);
        lastfmCheckBox->setText(QStringLiteral("Last.FM"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/lastfm_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        lastfmCheckBox->setIcon(icon3);
        lastfmCheckBox->setIconSize(QSize(101, 32));
        lastfmCheckBox->setProperty("type", QVariant(3));

        verticalLayout_2->addWidget(lastfmCheckBox);

        workInProgress = new QLabel(groupBoxRemoteLocations);
        workInProgress->setObjectName(QStringLiteral("workInProgress"));
        workInProgress->setFont(font);
        workInProgress->setWordWrap(true);

        verticalLayout_2->addWidget(workInProgress);


        verticalLayout->addWidget(groupBoxRemoteLocations);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


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
        workInProgress->setText(QApplication::translate("ConfigForm", "This plugin is under development, therefore Discogs and Last.FM are not yet implemented.", 0));
        Q_UNUSED(ConfigForm);
    } // retranslateUi

};

namespace Ui {
    class ConfigForm: public Ui_ConfigForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
