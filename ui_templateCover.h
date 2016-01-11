/********************************************************************************
** Form generated from reading UI file 'templateCover.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemplateCovers
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *albumCoverGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QListWidget *currentCover;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QListWidget *remoteCovers;

    void setupUi(QWidget *TemplateCovers)
    {
        if (TemplateCovers->objectName().isEmpty())
            TemplateCovers->setObjectName(QStringLiteral("TemplateCovers"));
        TemplateCovers->resize(447, 192);
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
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(albumCoverGroupBox->sizePolicy().hasHeightForWidth());
        albumCoverGroupBox->setSizePolicy(sizePolicy1);
        albumCoverGroupBox->setTitle(QStringLiteral("Album"));
        albumCoverGroupBox->setFlat(true);
        horizontalLayout_2 = new QHBoxLayout(albumCoverGroupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        groupBox = new QGroupBox(albumCoverGroupBox);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        currentCover = new QListWidget(groupBox);
        currentCover->setObjectName(QStringLiteral("currentCover"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(currentCover->sizePolicy().hasHeightForWidth());
        currentCover->setSizePolicy(sizePolicy2);
        currentCover->setMinimumSize(QSize(100, 100));
        currentCover->setMaximumSize(QSize(512, 512));
        currentCover->setFocusPolicy(Qt::ClickFocus);
        currentCover->setContextMenuPolicy(Qt::NoContextMenu);
        currentCover->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        currentCover->setEditTriggers(QAbstractItemView::NoEditTriggers);
        currentCover->setProperty("showDropIndicator", QVariant(false));
        currentCover->setDragDropMode(QAbstractItemView::NoDragDrop);
        currentCover->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        currentCover->setMovement(QListView::Static);
        currentCover->setFlow(QListView::TopToBottom);
        currentCover->setResizeMode(QListView::Adjust);
        currentCover->setViewMode(QListView::IconMode);
        currentCover->setUniformItemSizes(true);

        verticalLayout->addWidget(currentCover);


        horizontalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(albumCoverGroupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        remoteCovers = new QListWidget(groupBox_2);
        remoteCovers->setObjectName(QStringLiteral("remoteCovers"));
        remoteCovers->setMinimumSize(QSize(100, 100));
        remoteCovers->setFocusPolicy(Qt::ClickFocus);
        remoteCovers->setContextMenuPolicy(Qt::NoContextMenu);
        remoteCovers->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        remoteCovers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        remoteCovers->setProperty("showDropIndicator", QVariant(false));
        remoteCovers->setDragDropMode(QAbstractItemView::NoDragDrop);
        remoteCovers->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        remoteCovers->setMovement(QListView::Static);
        remoteCovers->setFlow(QListView::TopToBottom);
        remoteCovers->setResizeMode(QListView::Adjust);
        remoteCovers->setViewMode(QListView::IconMode);
        remoteCovers->setUniformItemSizes(true);

        verticalLayout_2->addWidget(remoteCovers);


        horizontalLayout_2->addWidget(groupBox_2);


        horizontalLayout->addWidget(albumCoverGroupBox);


        retranslateUi(TemplateCovers);

        QMetaObject::connectSlotsByName(TemplateCovers);
    } // setupUi

    void retranslateUi(QWidget *TemplateCovers)
    {
        groupBox->setTitle(QApplication::translate("TemplateCovers", "GroupBox", 0));
        groupBox_2->setTitle(QApplication::translate("TemplateCovers", "GroupBox", 0));
        Q_UNUSED(TemplateCovers);
    } // retranslateUi

};

namespace Ui {
    class TemplateCovers: public Ui_TemplateCovers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATECOVER_H
