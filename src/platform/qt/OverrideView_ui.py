# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'OverrideView.ui'
##
## Created by: Qt User Interface Compiler version 6.8.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QAbstractButton, QApplication, QCheckBox, QComboBox,
    QDialogButtonBox, QFormLayout, QFrame, QGridLayout,
    QGroupBox, QHBoxLayout, QLabel, QLineEdit,
    QSizePolicy, QSpacerItem, QTabWidget, QVBoxLayout,
    QWidget)

class Ui_QGBA_OverrideView(object):
    def setupUi(self, QGBA__OverrideView):
        if not QGBA__OverrideView.objectName():
            QGBA__OverrideView.setObjectName(u"QGBA__OverrideView")
        QGBA__OverrideView.resize(444, 288)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(QGBA__OverrideView.sizePolicy().hasHeightForWidth())
        QGBA__OverrideView.setSizePolicy(sizePolicy)
        self.verticalLayout = QVBoxLayout(QGBA__OverrideView)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.tabWidget = QTabWidget(QGBA__OverrideView)
        self.tabWidget.setObjectName(u"tabWidget")
        self.tabGBA = QWidget()
        self.tabGBA.setObjectName(u"tabGBA")
        self.gridLayout = QGridLayout(self.tabGBA)
        self.gridLayout.setObjectName(u"gridLayout")
        self.groupBox = QGroupBox(self.tabGBA)
        self.groupBox.setObjectName(u"groupBox")
        self.verticalLayout_2 = QVBoxLayout(self.groupBox)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.hwAutodetect = QCheckBox(self.groupBox)
        self.hwAutodetect.setObjectName(u"hwAutodetect")
        self.hwAutodetect.setChecked(True)

        self.verticalLayout_2.addWidget(self.hwAutodetect)

        self.hwRTC = QCheckBox(self.groupBox)
        self.hwRTC.setObjectName(u"hwRTC")
        self.hwRTC.setEnabled(False)

        self.verticalLayout_2.addWidget(self.hwRTC)

        self.hwGyro = QCheckBox(self.groupBox)
        self.hwGyro.setObjectName(u"hwGyro")
        self.hwGyro.setEnabled(False)

        self.verticalLayout_2.addWidget(self.hwGyro)

        self.hwTilt = QCheckBox(self.groupBox)
        self.hwTilt.setObjectName(u"hwTilt")
        self.hwTilt.setEnabled(False)

        self.verticalLayout_2.addWidget(self.hwTilt)

        self.hwLight = QCheckBox(self.groupBox)
        self.hwLight.setObjectName(u"hwLight")
        self.hwLight.setEnabled(False)

        self.verticalLayout_2.addWidget(self.hwLight)

        self.hwRumble = QCheckBox(self.groupBox)
        self.hwRumble.setObjectName(u"hwRumble")
        self.hwRumble.setEnabled(False)

        self.verticalLayout_2.addWidget(self.hwRumble)


        self.gridLayout.addWidget(self.groupBox, 0, 0, 3, 1)

        self.groupBox_2 = QGroupBox(self.tabGBA)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.verticalLayout_3 = QVBoxLayout(self.groupBox_2)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.formLayout = QFormLayout()
        self.formLayout.setObjectName(u"formLayout")
        self.label = QLabel(self.groupBox_2)
        self.label.setObjectName(u"label")

        self.formLayout.setWidget(0, QFormLayout.LabelRole, self.label)

        self.savetype = QComboBox(self.groupBox_2)
        self.savetype.addItem("")
        self.savetype.addItem("")
        self.savetype.addItem("")
        self.savetype.addItem("")
        self.savetype.addItem("")
        self.savetype.addItem("")
        self.savetype.addItem("")
        self.savetype.addItem("")
        self.savetype.setObjectName(u"savetype")

        self.formLayout.setWidget(0, QFormLayout.FieldRole, self.savetype)

        self.label_3 = QLabel(self.groupBox_2)
        self.label_3.setObjectName(u"label_3")

        self.formLayout.setWidget(2, QFormLayout.LabelRole, self.label_3)

        self.idleLoop = QLineEdit(self.groupBox_2)
        self.idleLoop.setObjectName(u"idleLoop")

        self.formLayout.setWidget(2, QFormLayout.FieldRole, self.idleLoop)

        self.line = QFrame(self.groupBox_2)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout.setWidget(1, QFormLayout.SpanningRole, self.line)


        self.verticalLayout_3.addLayout(self.formLayout)

        self.line_2 = QFrame(self.groupBox_2)
        self.line_2.setObjectName(u"line_2")
        self.line_2.setFrameShape(QFrame.Shape.HLine)
        self.line_2.setFrameShadow(QFrame.Shadow.Sunken)

        self.verticalLayout_3.addWidget(self.line_2)

        self.hwGBPlayer = QCheckBox(self.groupBox_2)
        self.hwGBPlayer.setObjectName(u"hwGBPlayer")

        self.verticalLayout_3.addWidget(self.hwGBPlayer)

        self.vbaBugCompat = QCheckBox(self.groupBox_2)
        self.vbaBugCompat.setObjectName(u"vbaBugCompat")
        self.vbaBugCompat.setTristate(True)
        self.vbaBugCompat.setCheckState(Qt.PartiallyChecked)

        self.verticalLayout_3.addWidget(self.vbaBugCompat)


        self.gridLayout.addWidget(self.groupBox_2, 0, 1, 1, 1)

        self.verticalSpacer = QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer, 1, 1, 1, 1)

        self.tabWidget.addTab(self.tabGBA, "")
        self.tabGB = QWidget()
        self.tabGB.setObjectName(u"tabGB")
        self.formLayout_3 = QFormLayout(self.tabGB)
        self.formLayout_3.setObjectName(u"formLayout_3")
        self.label_2 = QLabel(self.tabGB)
        self.label_2.setObjectName(u"label_2")

        self.formLayout_3.setWidget(0, QFormLayout.LabelRole, self.label_2)

        self.gbModel = QComboBox(self.tabGB)
        self.gbModel.addItem("")
        self.gbModel.setObjectName(u"gbModel")

        self.formLayout_3.setWidget(0, QFormLayout.FieldRole, self.gbModel)

        self.label_4 = QLabel(self.tabGB)
        self.label_4.setObjectName(u"label_4")

        self.formLayout_3.setWidget(1, QFormLayout.LabelRole, self.label_4)

        self.mbc = QComboBox(self.tabGB)
        self.mbc.addItem("")
        self.mbc.setObjectName(u"mbc")

        self.formLayout_3.setWidget(1, QFormLayout.FieldRole, self.mbc)

        self.label_5 = QLabel(self.tabGB)
        self.label_5.setObjectName(u"label_5")

        self.formLayout_3.setWidget(3, QFormLayout.LabelRole, self.label_5)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.color0 = QFrame(self.tabGB)
        self.color0.setObjectName(u"color0")
        self.color0.setMinimumSize(QSize(30, 30))
        self.color0.setAutoFillBackground(True)
        self.color0.setFrameShape(QFrame.StyledPanel)
        self.color0.setFrameShadow(QFrame.Raised)

        self.horizontalLayout.addWidget(self.color0)

        self.color1 = QFrame(self.tabGB)
        self.color1.setObjectName(u"color1")
        self.color1.setMinimumSize(QSize(30, 30))
        self.color1.setAutoFillBackground(True)
        self.color1.setFrameShape(QFrame.StyledPanel)
        self.color1.setFrameShadow(QFrame.Raised)

        self.horizontalLayout.addWidget(self.color1)

        self.color2 = QFrame(self.tabGB)
        self.color2.setObjectName(u"color2")
        self.color2.setMinimumSize(QSize(30, 30))
        self.color2.setAutoFillBackground(True)
        self.color2.setFrameShape(QFrame.StyledPanel)
        self.color2.setFrameShadow(QFrame.Raised)

        self.horizontalLayout.addWidget(self.color2)

        self.color3 = QFrame(self.tabGB)
        self.color3.setObjectName(u"color3")
        self.color3.setMinimumSize(QSize(30, 30))
        self.color3.setAutoFillBackground(True)
        self.color3.setFrameShape(QFrame.StyledPanel)
        self.color3.setFrameShadow(QFrame.Raised)

        self.horizontalLayout.addWidget(self.color3)


        self.formLayout_3.setLayout(3, QFormLayout.FieldRole, self.horizontalLayout)

        self.label_6 = QLabel(self.tabGB)
        self.label_6.setObjectName(u"label_6")

        self.formLayout_3.setWidget(4, QFormLayout.LabelRole, self.label_6)

        self.label_7 = QLabel(self.tabGB)
        self.label_7.setObjectName(u"label_7")

        self.formLayout_3.setWidget(5, QFormLayout.LabelRole, self.label_7)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.color4 = QFrame(self.tabGB)
        self.color4.setObjectName(u"color4")
        self.color4.setMinimumSize(QSize(30, 30))
        self.color4.setAutoFillBackground(True)
        self.color4.setFrameShape(QFrame.StyledPanel)
        self.color4.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_3.addWidget(self.color4)

        self.color5 = QFrame(self.tabGB)
        self.color5.setObjectName(u"color5")
        self.color5.setMinimumSize(QSize(30, 30))
        self.color5.setAutoFillBackground(True)
        self.color5.setFrameShape(QFrame.StyledPanel)
        self.color5.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_3.addWidget(self.color5)

        self.color6 = QFrame(self.tabGB)
        self.color6.setObjectName(u"color6")
        self.color6.setMinimumSize(QSize(30, 30))
        self.color6.setAutoFillBackground(True)
        self.color6.setFrameShape(QFrame.StyledPanel)
        self.color6.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_3.addWidget(self.color6)

        self.color7 = QFrame(self.tabGB)
        self.color7.setObjectName(u"color7")
        self.color7.setMinimumSize(QSize(30, 30))
        self.color7.setAutoFillBackground(True)
        self.color7.setFrameShape(QFrame.StyledPanel)
        self.color7.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_3.addWidget(self.color7)


        self.formLayout_3.setLayout(4, QFormLayout.FieldRole, self.horizontalLayout_3)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.color8 = QFrame(self.tabGB)
        self.color8.setObjectName(u"color8")
        self.color8.setMinimumSize(QSize(30, 30))
        self.color8.setAutoFillBackground(True)
        self.color8.setFrameShape(QFrame.StyledPanel)
        self.color8.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_4.addWidget(self.color8)

        self.color9 = QFrame(self.tabGB)
        self.color9.setObjectName(u"color9")
        self.color9.setMinimumSize(QSize(30, 30))
        self.color9.setAutoFillBackground(True)
        self.color9.setFrameShape(QFrame.StyledPanel)
        self.color9.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_4.addWidget(self.color9)

        self.color10 = QFrame(self.tabGB)
        self.color10.setObjectName(u"color10")
        self.color10.setMinimumSize(QSize(30, 30))
        self.color10.setAutoFillBackground(True)
        self.color10.setFrameShape(QFrame.StyledPanel)
        self.color10.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_4.addWidget(self.color10)

        self.color11 = QFrame(self.tabGB)
        self.color11.setObjectName(u"color11")
        self.color11.setMinimumSize(QSize(30, 30))
        self.color11.setAutoFillBackground(True)
        self.color11.setFrameShape(QFrame.StyledPanel)
        self.color11.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_4.addWidget(self.color11)


        self.formLayout_3.setLayout(5, QFormLayout.FieldRole, self.horizontalLayout_4)

        self.colorPreset = QComboBox(self.tabGB)
        self.colorPreset.setObjectName(u"colorPreset")

        self.formLayout_3.setWidget(2, QFormLayout.FieldRole, self.colorPreset)

        self.label_15 = QLabel(self.tabGB)
        self.label_15.setObjectName(u"label_15")

        self.formLayout_3.setWidget(2, QFormLayout.LabelRole, self.label_15)

        self.tabWidget.addTab(self.tabGB, "")

        self.verticalLayout.addWidget(self.tabWidget)

        self.buttonBox = QDialogButtonBox(QGBA__OverrideView)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setStandardButtons(QDialogButtonBox.Close|QDialogButtonBox.Save)

        self.verticalLayout.addWidget(self.buttonBox)


        self.retranslateUi(QGBA__OverrideView)

        self.tabWidget.setCurrentIndex(0)


        QMetaObject.connectSlotsByName(QGBA__OverrideView)
    # setupUi

    def retranslateUi(self, QGBA__OverrideView):
        QGBA__OverrideView.setWindowTitle(QCoreApplication.translate("QGBA::OverrideView", u"Game Overrides", None))
        self.groupBox.setTitle("")
        self.hwAutodetect.setText(QCoreApplication.translate("QGBA::OverrideView", u"Autodetect", None))
        self.hwRTC.setText(QCoreApplication.translate("QGBA::OverrideView", u"Realtime clock", None))
        self.hwGyro.setText(QCoreApplication.translate("QGBA::OverrideView", u"Gyroscope", None))
        self.hwTilt.setText(QCoreApplication.translate("QGBA::OverrideView", u"Tilt", None))
        self.hwLight.setText(QCoreApplication.translate("QGBA::OverrideView", u"Light sensor", None))
        self.hwRumble.setText(QCoreApplication.translate("QGBA::OverrideView", u"Rumble", None))
        self.groupBox_2.setTitle("")
        self.label.setText(QCoreApplication.translate("QGBA::OverrideView", u"Save type", None))
        self.savetype.setItemText(0, QCoreApplication.translate("QGBA::OverrideView", u"Autodetect", None))
        self.savetype.setItemText(1, QCoreApplication.translate("QGBA::OverrideView", u"None", None))
        self.savetype.setItemText(2, QCoreApplication.translate("QGBA::OverrideView", u"SRAM", None))
        self.savetype.setItemText(3, QCoreApplication.translate("QGBA::OverrideView", u"Flash 512kb", None))
        self.savetype.setItemText(4, QCoreApplication.translate("QGBA::OverrideView", u"Flash 1Mb", None))
        self.savetype.setItemText(5, QCoreApplication.translate("QGBA::OverrideView", u"EEPROM 8kB", None))
        self.savetype.setItemText(6, QCoreApplication.translate("QGBA::OverrideView", u"EEPROM 512 bytes", None))
        self.savetype.setItemText(7, QCoreApplication.translate("QGBA::OverrideView", u"SRAM 64kB (bootlegs only)", None))

        self.label_3.setText(QCoreApplication.translate("QGBA::OverrideView", u"Idle loop", None))
        self.hwGBPlayer.setText(QCoreApplication.translate("QGBA::OverrideView", u"Game Boy Player features", None))
        self.vbaBugCompat.setText(QCoreApplication.translate("QGBA::OverrideView", u"VBA bug compatibility mode", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tabGBA), QCoreApplication.translate("QGBA::OverrideView", u"Game Boy Advance", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::OverrideView", u"Game Boy model", None))
        self.gbModel.setItemText(0, QCoreApplication.translate("QGBA::OverrideView", u"Autodetect", None))

        self.label_4.setText(QCoreApplication.translate("QGBA::OverrideView", u"Memory bank controller", None))
        self.mbc.setItemText(0, QCoreApplication.translate("QGBA::OverrideView", u"Autodetect", None))

        self.label_5.setText(QCoreApplication.translate("QGBA::OverrideView", u"Background Colors", None))
        self.label_6.setText(QCoreApplication.translate("QGBA::OverrideView", u"Sprite Colors 1", None))
        self.label_7.setText(QCoreApplication.translate("QGBA::OverrideView", u"Sprite Colors 2", None))
        self.label_15.setText(QCoreApplication.translate("QGBA::OverrideView", u"Palette preset", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tabGB), QCoreApplication.translate("QGBA::OverrideView", u"Game Boy", None))
    # retranslateUi

