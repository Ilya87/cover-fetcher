/********************************************************************************
** Form generated from reading UI file 'templateCover.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATECOVER_H
#define UI_TEMPLATECOVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemplateCovers
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *albumCoverGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *leftSpacer;
    QGroupBox *currentCoverGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *currentCover;
    QGroupBox *remoteCoversGroupBox;
    QVBoxLayout *verticalLayout;
    QStackedWidget *remoteCovers;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *previousCoverButton;
    QSpacerItem *rightSpacer_2;
    QPushButton *nextCoverButton;
    QSpacerItem *rightSpacer;

    void setupUi(QWidget *TemplateCovers)
    {
        if (TemplateCovers->objectName().isEmpty())
            TemplateCovers->setObjectName(QStringLiteral("TemplateCovers"));
        TemplateCovers->resize(504, 287);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TemplateCovers->sizePolicy().hasHeightForWidth());
        TemplateCovers->setSizePolicy(sizePolicy);
        TemplateCovers->setWindowTitle(QStringLiteral("Form"));
        horizontalLayout = new QHBoxLayout(TemplateCovers);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        albumCoverGroupBox = new QGroupBox(TemplateCovers);
        albumCoverGroupBox->setObjectName(QStringLiteral("albumCoverGroupBox"));
        albumCoverGroupBox->setTitle(QStringLiteral("Album"));
        albumCoverGroupBox->setFlat(true);
        horizontalLayout_2 = new QHBoxLayout(albumCoverGroupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        leftSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(leftSpacer);

        currentCoverGroupBox = new QGroupBox(albumCoverGroupBox);
        currentCoverGroupBox->setObjectName(QStringLiteral("currentCoverGroupBox"));
        horizontalLayout_4 = new QHBoxLayout(currentCoverGroupBox);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        currentCover = new QListWidget(currentCoverGroupBox);
        currentCover->setObjectName(QStringLiteral("currentCover"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(currentCover->sizePolicy().hasHeightForWidth());
        currentCover->setSizePolicy(sizePolicy1);
        currentCover->setMinimumSize(QSize(32, 32));
        currentCover->setMaximumSize(QSize(512, 512));
        currentCover->setFocusPolicy(Qt::ClickFocus);
        currentCover->setContextMenuPolicy(Qt::NoContextMenu);
        currentCover->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        currentCover->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        currentCover->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        currentCover->setEditTriggers(QAbstractItemView::NoEditTriggers);
        currentCover->setProperty("showDropIndicator", QVariant(false));
        currentCover->setDragDropMode(QAbstractItemView::NoDragDrop);
        currentCover->setMovement(QListView::Static);
        currentCover->setViewMode(QListView::IconMode);

        horizontalLayout_4->addWidget(currentCover);


        horizontalLayout_2->addWidget(currentCoverGroupBox);

        remoteCoversGroupBox = new QGroupBox(albumCoverGroupBox);
        remoteCoversGroupBox->setObjectName(QStringLiteral("remoteCoversGroupBox"));
        verticalLayout = new QVBoxLayout(remoteCoversGroupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        remoteCovers = new QStackedWidget(remoteCoversGroupBox);
        remoteCovers->setObjectName(QStringLiteral("remoteCovers"));

        verticalLayout->addWidget(remoteCovers);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        previousCoverButton = new QPushButton(remoteCoversGroupBox);
        previousCoverButton->setObjectName(QStringLiteral("previousCoverButton"));

        horizontalLayout_5->addWidget(previousCoverButton);

        rightSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(rightSpacer_2);

        nextCoverButton = new QPushButton(remoteCoversGroupBox);
        nextCoverButton->setObjectName(QStringLiteral("nextCoverButton"));

        horizontalLayout_5->addWidget(nextCoverButton);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_2->addWidget(remoteCoversGroupBox);

        rightSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(rightSpacer);


        horizontalLayout->addWidget(albumCoverGroupBox);


        retranslateUi(TemplateCovers);

        QMetaObject::connectSlotsByName(TemplateCovers);
    } // setupUi

    void retranslateUi(QWidget *TemplateCovers)
    {
        currentCoverGroupBox->setTitle(QApplication::translate("TemplateCovers", "Cover in your files", 0));
        remoteCoversGroupBox->setTitle(QApplication::translate("TemplateCovers", "Remote cover", 0));
        previousCoverButton->setText(QApplication::translate("TemplateCovers", "<", 0));
        nextCoverButton->setText(QApplication::translate("TemplateCovers", ">", 0));
        Q_UNUSED(TemplateCovers);
    } // retranslateUi

};

namespace Ui {
    class TemplateCovers: public Ui_TemplateCovers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATECOVER_H
