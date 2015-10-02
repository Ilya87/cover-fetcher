/********************************************************************************
** Form generated from reading UI file 'fetchdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FETCHDIALOG_H
#define UI_FETCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FetchDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *previewSizeLabel;
    QSlider *previewSizeSlider;
    QLabel *previewSizeValue;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FetchDialog)
    {
        if (FetchDialog->objectName().isEmpty())
            FetchDialog->setObjectName(QStringLiteral("FetchDialog"));
        FetchDialog->resize(640, 275);
        verticalLayout = new QVBoxLayout(FetchDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        previewSizeLabel = new QLabel(FetchDialog);
        previewSizeLabel->setObjectName(QStringLiteral("previewSizeLabel"));

        horizontalLayout->addWidget(previewSizeLabel);

        previewSizeSlider = new QSlider(FetchDialog);
        previewSizeSlider->setObjectName(QStringLiteral("previewSizeSlider"));
        previewSizeSlider->setMinimumSize(QSize(200, 0));
        previewSizeSlider->setMaximumSize(QSize(400, 16777215));
        previewSizeSlider->setMaximum(4);
        previewSizeSlider->setPageStep(1);
        previewSizeSlider->setSliderPosition(1);
        previewSizeSlider->setOrientation(Qt::Horizontal);
        previewSizeSlider->setTickPosition(QSlider::TicksBelow);

        horizontalLayout->addWidget(previewSizeSlider);

        previewSizeValue = new QLabel(FetchDialog);
        previewSizeValue->setObjectName(QStringLiteral("previewSizeValue"));
        previewSizeValue->setMinimumSize(QSize(40, 0));
        previewSizeValue->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(previewSizeValue);


        verticalLayout->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(FetchDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 620, 181));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        verticalLayout_3->addLayout(verticalLayout_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(FetchDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FetchDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FetchDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FetchDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FetchDialog);
    } // setupUi

    void retranslateUi(QDialog *FetchDialog)
    {
        FetchDialog->setWindowTitle(QApplication::translate("FetchDialog", "Fetch Covers", 0));
        previewSizeLabel->setText(QApplication::translate("FetchDialog", "Preview size:", 0));
        previewSizeValue->setText(QApplication::translate("FetchDialog", "64px", 0));
    } // retranslateUi

};

namespace Ui {
    class FetchDialog: public Ui_FetchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FETCHDIALOG_H
