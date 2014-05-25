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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemplateCovers
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *existingCoverGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *currentCover;
    QListWidget *remoteCovers;

    void setupUi(QWidget *TemplateCovers)
    {
        if (TemplateCovers->objectName().isEmpty())
            TemplateCovers->setObjectName(QStringLiteral("TemplateCovers"));
        TemplateCovers->resize(577, 248);
        horizontalLayout = new QHBoxLayout(TemplateCovers);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        existingCoverGroupBox = new QGroupBox(TemplateCovers);
        existingCoverGroupBox->setObjectName(QStringLiteral("existingCoverGroupBox"));
        horizontalLayout_2 = new QHBoxLayout(existingCoverGroupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        currentCover = new QListWidget(existingCoverGroupBox);
        currentCover->setObjectName(QStringLiteral("currentCover"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(currentCover->sizePolicy().hasHeightForWidth());
        currentCover->setSizePolicy(sizePolicy);
        currentCover->setMinimumSize(QSize(32, 32));
        currentCover->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        currentCover->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        currentCover->setEditTriggers(QAbstractItemView::NoEditTriggers);
        currentCover->setProperty("showDropIndicator", QVariant(false));
        currentCover->setViewMode(QListView::IconMode);

        horizontalLayout_2->addWidget(currentCover);

        remoteCovers = new QListWidget(existingCoverGroupBox);
        remoteCovers->setObjectName(QStringLiteral("remoteCovers"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(5);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(remoteCovers->sizePolicy().hasHeightForWidth());
        remoteCovers->setSizePolicy(sizePolicy1);
        remoteCovers->setMinimumSize(QSize(32, 32));
        remoteCovers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        remoteCovers->setProperty("showDropIndicator", QVariant(false));
        remoteCovers->setMovement(QListView::Snap);
        remoteCovers->setViewMode(QListView::IconMode);
        remoteCovers->setUniformItemSizes(true);

        horizontalLayout_2->addWidget(remoteCovers);


        horizontalLayout->addWidget(existingCoverGroupBox);


        retranslateUi(TemplateCovers);

        QMetaObject::connectSlotsByName(TemplateCovers);
    } // setupUi

    void retranslateUi(QWidget *TemplateCovers)
    {
        TemplateCovers->setWindowTitle(QApplication::translate("TemplateCovers", "Form", 0));
        existingCoverGroupBox->setTitle(QApplication::translate("TemplateCovers", "Album", 0));
    } // retranslateUi

};

namespace Ui {
    class TemplateCovers: public Ui_TemplateCovers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATECOVER_H
