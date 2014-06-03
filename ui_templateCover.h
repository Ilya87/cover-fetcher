/********************************************************************************
** Form generated from reading UI file 'templateCover.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
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
    QGroupBox *existingCoverGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *leftSpacer;
    QListWidget *currentCover;
    QListWidget *remoteCovers;
    QSpacerItem *rightSpacer;

    void setupUi(QWidget *TemplateCovers)
    {
        if (TemplateCovers->objectName().isEmpty())
            TemplateCovers->setObjectName(QStringLiteral("TemplateCovers"));
        TemplateCovers->resize(144, 88);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TemplateCovers->sizePolicy().hasHeightForWidth());
        TemplateCovers->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(TemplateCovers);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, 0, -1);
        existingCoverGroupBox = new QGroupBox(TemplateCovers);
        existingCoverGroupBox->setObjectName(QStringLiteral("existingCoverGroupBox"));
        existingCoverGroupBox->setTitle(QStringLiteral("Album"));
        existingCoverGroupBox->setFlat(true);
        horizontalLayout_2 = new QHBoxLayout(existingCoverGroupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        leftSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(leftSpacer);

        currentCover = new QListWidget(existingCoverGroupBox);
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
        currentCover->setDragDropMode(QAbstractItemView::DropOnly);
        currentCover->setMovement(QListView::Static);
        currentCover->setViewMode(QListView::IconMode);

        horizontalLayout_2->addWidget(currentCover);

        remoteCovers = new QListWidget(existingCoverGroupBox);
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


        horizontalLayout->addWidget(existingCoverGroupBox);


        retranslateUi(TemplateCovers);

        QMetaObject::connectSlotsByName(TemplateCovers);
    } // setupUi

    void retranslateUi(QWidget *TemplateCovers)
    {
        TemplateCovers->setWindowTitle(QApplication::translate("TemplateCovers", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class TemplateCovers: public Ui_TemplateCovers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATECOVER_H
