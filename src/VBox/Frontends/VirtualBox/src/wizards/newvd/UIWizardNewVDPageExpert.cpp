/* $Id$ */
/** @file
 *
 * VBox frontends: Qt4 GUI ("VirtualBox"):
 * UIWizardNewVDPageExpert class implementation
 */

/*
 * Copyright (C) 2006-2013 Oracle Corporation
 *
 * This file is part of VirtualBox Open Source Edition (OSE), as
 * available from http://www.virtualbox.org. This file is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software
 * Foundation, in version 2 as it comes in the "COPYING" file of the
 * VirtualBox OSE distribution. VirtualBox OSE is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY of any kind.
 */

/* Qt includes: */
#include <QGridLayout>
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>

/* GUI includes: */
#include "UIWizardNewVDPageExpert.h"
#include "UIWizardNewVD.h"
#include "VBoxGlobal.h"
#include "UIMessageCenter.h"
#include "UIIconPool.h"
#include "QIRichTextLabel.h"
#include "QIToolButton.h"
#include "QILineEdit.h"

/* COM includes: */
#include "CSystemProperties.h"

UIWizardNewVDPageExpert::UIWizardNewVDPageExpert(const QString &strDefaultName, const QString &strDefaultPath, qulonglong uDefaultSize)
    : UIWizardNewVDPage3(strDefaultName, strDefaultPath)
{
    /* Create widgets: */
    QGridLayout *pMainLayout = new QGridLayout(this);
    {
        pMainLayout->setContentsMargins(8, 6, 8, 6);
        pMainLayout->setSpacing(10);
        m_pLocationCnt = new QGroupBox(this);
        {
            m_pLocationCnt->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            QHBoxLayout *pLocationCntLayout = new QHBoxLayout(m_pLocationCnt);
            {
                m_pLocationEditor = new QLineEdit(m_pLocationCnt);
                {
                    m_pLocationEditor->setText(m_strDefaultName);
                }
                m_pLocationOpenButton = new QIToolButton(m_pLocationCnt);
                {
                    m_pLocationOpenButton->setAutoRaise(true);
                    m_pLocationOpenButton->setIcon(UIIconPool::iconSet(":/select_file_16px.png", "select_file_dis_16px.png"));
                }
                pLocationCntLayout->addWidget(m_pLocationEditor);
                pLocationCntLayout->addWidget(m_pLocationOpenButton);
            }
        }
        m_pSizeCnt = new QGroupBox(this);
        {
            m_pSizeCnt->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            QGridLayout *pSizeCntLayout = new QGridLayout(m_pSizeCnt);
            {
                m_pSizeSlider = new QSlider(m_pSizeCnt);
                {
                    m_pSizeSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
                    m_pSizeSlider->setOrientation(Qt::Horizontal);
                    m_pSizeSlider->setTickPosition(QSlider::TicksBelow);
                    m_pSizeSlider->setFocusPolicy(Qt::StrongFocus);
                    m_pSizeSlider->setPageStep(m_iSliderScale);
                    m_pSizeSlider->setSingleStep(m_iSliderScale / 8);
                    m_pSizeSlider->setTickInterval(0);
                    m_pSizeSlider->setMinimum(sizeMBToSlider(m_uMediumSizeMin, m_iSliderScale));
                    m_pSizeSlider->setMaximum(sizeMBToSlider(m_uMediumSizeMax, m_iSliderScale));
                }
                m_pSizeEditor = new QILineEdit(m_pSizeCnt);
                {
                    m_pSizeEditor->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
                    m_pSizeEditor->setFixedWidthByText("88888.88 MB");
                    m_pSizeEditor->setAlignment(Qt::AlignRight);
                    m_pSizeEditor->setValidator(new QRegExpValidator(QRegExp(vboxGlobal().sizeRegexp()), this));
                }
                QLabel *m_pSizeMin = new QLabel(m_pSizeCnt);
                {
                    m_pSizeMin->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
                    m_pSizeMin->setText(vboxGlobal().formatSize(m_uMediumSizeMin));
                }
                QLabel *m_pSizeMax = new QLabel(m_pSizeCnt);
                {
                    m_pSizeMax->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
                    m_pSizeMax->setText(vboxGlobal().formatSize(m_uMediumSizeMax));
                }
                pSizeCntLayout->addWidget(m_pSizeSlider, 0, 0, 1, 3);
                pSizeCntLayout->addWidget(m_pSizeEditor, 0, 3);
                pSizeCntLayout->addWidget(m_pSizeMin, 1, 0);
                pSizeCntLayout->setColumnStretch(1, 1);
                pSizeCntLayout->addWidget(m_pSizeMax, 1, 2);
            }
        }
        m_pFormatCnt = new QGroupBox(this);
        {
            m_pFormatCnt->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            QVBoxLayout *pFormatCntLayout = new QVBoxLayout(m_pFormatCnt);
            {
                m_pFormatButtonGroup = new QButtonGroup(m_pFormatCnt);
                {
                    CSystemProperties systemProperties = vboxGlobal().virtualBox().GetSystemProperties();
                    const QVector<CMediumFormat> &medFormats = systemProperties.GetMediumFormats();
                    for (int i = 0; i < medFormats.size(); ++i)
                    {
                        const CMediumFormat &medFormat = medFormats[i];
                        if (medFormat.GetName() == "VDI")
                            addFormatButton(m_pFormatCnt, pFormatCntLayout, medFormat);
                    }
                    for (int i = 0; i < medFormats.size(); ++i)
                    {
                        const CMediumFormat &medFormat = medFormats[i];
                        if (medFormat.GetName() != "VDI")
                            addFormatButton(m_pFormatCnt, pFormatCntLayout, medFormat);
                    }
                    if (!m_pFormatButtonGroup->buttons().isEmpty())
                    {
                        m_pFormatButtonGroup->button(0)->click();
                        m_pFormatButtonGroup->button(0)->setFocus();
                    }
                }
            }
        }
        m_pVariantCnt = new QGroupBox(this);
        {
            m_pVariantCnt->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            QVBoxLayout *pVariantCntLayout = new QVBoxLayout(m_pVariantCnt);
            {
                m_pVariantButtonGroup = new QButtonGroup(m_pVariantCnt);
                {
                    m_pDynamicalButton = new QRadioButton(m_pVariantCnt);
                    {
                        m_pDynamicalButton->click();
                        m_pDynamicalButton->setFocus();
                    }
                    m_pFixedButton = new QRadioButton(m_pVariantCnt);
                    m_pVariantButtonGroup->addButton(m_pDynamicalButton, 0);
                    m_pVariantButtonGroup->addButton(m_pFixedButton, 1);
                }
                m_pSplitBox = new QCheckBox(m_pVariantCnt);
                pVariantCntLayout->addWidget(m_pDynamicalButton);
                pVariantCntLayout->addWidget(m_pFixedButton);
                pVariantCntLayout->addWidget(m_pSplitBox);
            }
        }
        pMainLayout->addWidget(m_pLocationCnt, 0, 0, 1, 2);
        pMainLayout->addWidget(m_pSizeCnt, 1, 0, 1, 2);
        pMainLayout->addWidget(m_pFormatCnt, 2, 0, Qt::AlignTop);
        pMainLayout->addWidget(m_pVariantCnt, 2, 1, Qt::AlignTop);
        setMediumSize(uDefaultSize);
        sltMediumFormatChanged();
    }

    /* Setup connections: */
    connect(m_pFormatButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(sltMediumFormatChanged()));
    connect(m_pVariantButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SIGNAL(completeChanged()));
    connect(m_pSplitBox, SIGNAL(stateChanged(int)), this, SIGNAL(completeChanged()));
    connect(m_pLocationEditor, SIGNAL(textChanged(const QString &)), this, SIGNAL(completeChanged()));
    connect(m_pLocationOpenButton, SIGNAL(clicked()), this, SLOT(sltSelectLocationButtonClicked()));
    connect(m_pSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(sltSizeSliderValueChanged(int)));
    connect(m_pSizeEditor, SIGNAL(textChanged(const QString &)), this, SLOT(sltSizeEditorTextChanged(const QString &)));

    /* Register classes: */
    qRegisterMetaType<CMediumFormat>();
    /* Register fields: */
    registerField("mediumFormat", this, "mediumFormat");
    registerField("mediumVariant", this, "mediumVariant");
    registerField("mediumPath", this, "mediumPath");
    registerField("mediumSize", this, "mediumSize");
}

void UIWizardNewVDPageExpert::sltMediumFormatChanged()
{
    /* Get medium format: */
    CMediumFormat mf = mediumFormat();
    if (mf.isNull())
    {
        AssertMsgFailed(("No medium format set!"));
        return;
    }

    /* Enable/disable widgets: */
    ULONG uCapabilities = 0;
    QVector<KMediumFormatCapabilities> capabilities;
    capabilities = mf.GetCapabilities();
    for (int i = 0; i < capabilities.size(); i++)
        uCapabilities |= capabilities[i];

    bool fIsCreateDynamicPossible = uCapabilities & KMediumFormatCapabilities_CreateDynamic;
    bool fIsCreateFixedPossible = uCapabilities & KMediumFormatCapabilities_CreateFixed;
    bool fIsCreateSplitPossible = uCapabilities & KMediumFormatCapabilities_CreateSplit2G;
    m_pDynamicalButton->setEnabled(fIsCreateDynamicPossible);
    m_pFixedButton->setEnabled(fIsCreateFixedPossible);
    m_pSplitBox->setEnabled(fIsCreateSplitPossible);

    /* Compose virtual-disk extension: */
    m_strDefaultExtension = defaultExtension(mf);

    /* Broadcast complete-change: */
    completeChanged();
}

void UIWizardNewVDPageExpert::sltSelectLocationButtonClicked()
{
    /* Call to base-class: */
    onSelectLocationButtonClicked();
}

void UIWizardNewVDPageExpert::sltSizeSliderValueChanged(int iValue)
{
    onSizeSliderValueChanged(iValue);

    emit completeChanged();
}

void UIWizardNewVDPageExpert::sltSizeEditorTextChanged(const QString &strValue)
{
    onSizeEditorTextChanged(strValue);

    emit completeChanged();
}

void UIWizardNewVDPageExpert::retranslateUi()
{
    /* Translate widgets: */
    m_pLocationCnt->setTitle(UIWizardNewVD::tr("File &location"));
    m_pLocationOpenButton->setToolTip(UIWizardNewVD::tr("Choose a location for new virtual hard drive file..."));
    m_pSizeCnt->setTitle(UIWizardNewVD::tr("File &size"));
    m_pFormatCnt->setTitle(UIWizardNewVD::tr("Hard drive file &type"));
    QList<QAbstractButton*> buttons = m_pFormatButtonGroup->buttons();
    for (int i = 0; i < buttons.size(); ++i)
    {
        QAbstractButton *pButton = buttons[i];
        pButton->setText(VBoxGlobal::fullMediumFormatName(m_formatNames[m_pFormatButtonGroup->id(pButton)]));
    }
    m_pVariantCnt->setTitle(UIWizardNewVD::tr("Storage on physical hard drive"));
    m_pDynamicalButton->setText(UIWizardNewVD::tr("&Dynamically allocated"));
    m_pFixedButton->setText(UIWizardNewVD::tr("&Fixed size"));
    m_pSplitBox->setText(UIWizardNewVD::tr("&Split into files of less than 2GB"));
}

void UIWizardNewVDPageExpert::initializePage()
{
    /* Translate page: */
    retranslateUi();
}

bool UIWizardNewVDPageExpert::isComplete() const
{
    /* Make sure medium format/variant is correct,
     * current name is not empty and current size feats the bounds: */
    return !mediumFormat().isNull() &&
           mediumVariant() != (qulonglong)KMediumVariant_Max &&
           !m_pLocationEditor->text().trimmed().isEmpty() &&
           mediumSize() >= m_uMediumSizeMin && mediumSize() <= m_uMediumSizeMax;
}

bool UIWizardNewVDPageExpert::validatePage()
{
    /* Initial result: */
    bool fResult = true;

    /* Lock finish button: */
    startProcessing();

    /* Make sure such virtual-disk doesn't exists: */
    QString strMediumPath(mediumPath());
    fResult = !QFileInfo(strMediumPath).exists();
    if (!fResult)
        msgCenter().cannotOverwriteHardDiskStorage(strMediumPath, this);

    /* Try to create virtual-disk: */
    if (fResult)
        fResult = qobject_cast<UIWizardNewVD*>(wizard())->createVirtualDisk();

    /* Unlock finish button: */
    endProcessing();

    /* Return result: */
    return fResult;
}

