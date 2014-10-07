/********************************************************************************
** Form generated from reading UI file 'templateCover.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemplateCovers
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *albumCoverGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *leftSpacer;
    QListWidget *currentCover;
    QListWidget *remoteCovers;
    QSpacerItem *rightSpacer;

    void setupUi(QWidget *TemplateCovers)
    {
        if (TemplateCovers->objectName().isEmpty())
            TemplateCovers->setObjectName(QStringLiteral("TemplateCovers"));
        TemplateCovers->resize(154, 100);
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

        currentCover = new QListWidget(albumCoverGroupBox);
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

        horizontalLayout_2->addWidget(currentCover);

        remoteCovers = new QListWidget(albumCoverGroupBox);
        remoteCovers->setObjectName(QStringLiteral("remoteCovers"));
        sizePolicy1.setHeightForWidth(remoteCovers->sizePolicy().hasHeightForWidth());
        remoteCovers->setSizePolicy(sizePolicy1);
        remoteCovers->setMinimumSize(QSize(32, 32));
        remoteCovers->setMaximumSize(QSize(512, 512));
        remoteCovers->setFocusPolicy(Qt::ClickFocus);
        remoteCovers->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        remoteCovers->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        remoteCovers->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        remoteCovers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        remoteCovers->setProperty("showDropIndicator", QVariant(false));
        remoteCovers->setMovement(QListView::Static);
        remoteCovers->setViewMode(QListView::IconMode);
        remoteCovers->setUniformItemSizes(true);

        horizontalLayout_2->addWidget(remoteCovers);

        rightSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(rightSpacer);


        horizontalLayout->addWidget(albumCoverGroupBox);


        retranslateUi(TemplateCovers);

        QMetaObject::connectSlotsByName(TemplateCovers);
    } // setupUi

    void retranslateUi(QWidget *TemplateCovers)
    {
        Q_UNUSED(TemplateCovers);
    } // retranslateUi

};

namespace Ui {
    class TemplateCovers: public Ui_TemplateCovers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATECOVER_H
