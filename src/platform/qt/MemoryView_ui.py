# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'MemoryView.ui'
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
from PySide6.QtWidgets import (QApplication, QComboBox, QGridLayout, QHBoxLayout,
    QLabel, QLineEdit, QPushButton, QRadioButton,
    QSizePolicy, QSpacerItem, QSpinBox, QVBoxLayout,
    QWidget)

class Ui_QGBA_MemoryView(object):
    def setupUi(self, QGBA__MemoryView):
        if not QGBA__MemoryView.objectName():
            QGBA__MemoryView.setObjectName(u"QGBA__MemoryView")
        QGBA__MemoryView.resize(874, 900)
        self.verticalLayout = QVBoxLayout(QGBA__MemoryView)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.regions = QComboBox(QGBA__MemoryView)
        self.regions.setObjectName(u"regions")

        self.horizontalLayout.addWidget(self.regions)

        self.horizontalSpacer = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer)

        self.label = QLabel(QGBA__MemoryView)
        self.label.setObjectName(u"label")

        self.horizontalLayout.addWidget(self.label)

        self.segments = QSpinBox(QGBA__MemoryView)
        self.segments.setObjectName(u"segments")
        self.segments.setMinimum(-1)
        self.segments.setMaximum(0)
        self.segments.setDisplayIntegerBase(16)

        self.horizontalLayout.addWidget(self.segments)

        self.segmentColon = QLabel(QGBA__MemoryView)
        self.segmentColon.setObjectName(u"segmentColon")
        self.segmentColon.setText(u":")

        self.horizontalLayout.addWidget(self.segmentColon)

        self.setAddress = QSpinBox(QGBA__MemoryView)
        self.setAddress.setObjectName(u"setAddress")
        self.setAddress.setAccelerated(True)
        self.setAddress.setPrefix(u"0x")
        self.setAddress.setMaximum(268435455)
        self.setAddress.setSingleStep(16)
        self.setAddress.setDisplayIntegerBase(16)

        self.horizontalLayout.addWidget(self.setAddress)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.label_2 = QLabel(QGBA__MemoryView)
        self.label_2.setObjectName(u"label_2")

        self.horizontalLayout_3.addWidget(self.label_2)

        self.horizontalSpacer_2 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_2)

        self.width8 = QRadioButton(QGBA__MemoryView)
        self.width8.setObjectName(u"width8")
        self.width8.setChecked(True)

        self.horizontalLayout_3.addWidget(self.width8)

        self.horizontalSpacer_4 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_4)

        self.width16 = QRadioButton(QGBA__MemoryView)
        self.width16.setObjectName(u"width16")

        self.horizontalLayout_3.addWidget(self.width16)

        self.horizontalSpacer_5 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_5)

        self.width32 = QRadioButton(QGBA__MemoryView)
        self.width32.setObjectName(u"width32")

        self.horizontalLayout_3.addWidget(self.width32)

        self.horizontalSpacer_3 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_3)


        self.verticalLayout.addLayout(self.horizontalLayout_3)

        self.hexfield = QGBA_MemoryModel(QGBA__MemoryView)
        self.hexfield.setObjectName(u"hexfield")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.hexfield.sizePolicy().hasHeightForWidth())
        self.hexfield.setSizePolicy(sizePolicy)

        self.verticalLayout.addWidget(self.hexfield)

        self.gridLayout = QGridLayout()
        self.gridLayout.setObjectName(u"gridLayout")
        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.label_4 = QLabel(QGBA__MemoryView)
        self.label_4.setObjectName(u"label_4")

        self.horizontalLayout_6.addWidget(self.label_4)

        self.uintVal = QLineEdit(QGBA__MemoryView)
        self.uintVal.setObjectName(u"uintVal")
        self.uintVal.setMaxLength(10)
        self.uintVal.setReadOnly(True)

        self.horizontalLayout_6.addWidget(self.uintVal)


        self.gridLayout.addLayout(self.horizontalLayout_6, 0, 1, 1, 1)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.label_3 = QLabel(QGBA__MemoryView)
        self.label_3.setObjectName(u"label_3")

        self.horizontalLayout_2.addWidget(self.label_3)

        self.sintVal = QLineEdit(QGBA__MemoryView)
        self.sintVal.setObjectName(u"sintVal")
        self.sintVal.setMaxLength(11)
        self.sintVal.setReadOnly(True)

        self.horizontalLayout_2.addWidget(self.sintVal)


        self.gridLayout.addLayout(self.horizontalLayout_2, 0, 0, 1, 1)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.label_5 = QLabel(QGBA__MemoryView)
        self.label_5.setObjectName(u"label_5")

        self.horizontalLayout_4.addWidget(self.label_5)

        self.stringVal = QLineEdit(QGBA__MemoryView)
        self.stringVal.setObjectName(u"stringVal")
        self.stringVal.setReadOnly(True)

        self.horizontalLayout_4.addWidget(self.stringVal)

        self.loadTBL = QPushButton(QGBA__MemoryView)
        self.loadTBL.setObjectName(u"loadTBL")

        self.horizontalLayout_4.addWidget(self.loadTBL)


        self.gridLayout.addLayout(self.horizontalLayout_4, 1, 0, 1, 2)


        self.verticalLayout.addLayout(self.gridLayout)

        self.horizontalLayout_5 = QHBoxLayout()
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.copy = QPushButton(QGBA__MemoryView)
        self.copy.setObjectName(u"copy")

        self.horizontalLayout_5.addWidget(self.copy)

        self.paste = QPushButton(QGBA__MemoryView)
        self.paste.setObjectName(u"paste")

        self.horizontalLayout_5.addWidget(self.paste)

        self.horizontalSpacer_7 = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_5.addItem(self.horizontalSpacer_7)

        self.save = QPushButton(QGBA__MemoryView)
        self.save.setObjectName(u"save")

        self.horizontalLayout_5.addWidget(self.save)

        self.saveRange = QPushButton(QGBA__MemoryView)
        self.saveRange.setObjectName(u"saveRange")

        self.horizontalLayout_5.addWidget(self.saveRange)

        self.load = QPushButton(QGBA__MemoryView)
        self.load.setObjectName(u"load")

        self.horizontalLayout_5.addWidget(self.load)


        self.verticalLayout.addLayout(self.horizontalLayout_5)

        QWidget.setTabOrder(self.regions, self.segments)
        QWidget.setTabOrder(self.segments, self.setAddress)
        QWidget.setTabOrder(self.setAddress, self.width8)
        QWidget.setTabOrder(self.width8, self.width16)
        QWidget.setTabOrder(self.width16, self.width32)
        QWidget.setTabOrder(self.width32, self.sintVal)
        QWidget.setTabOrder(self.sintVal, self.uintVal)
        QWidget.setTabOrder(self.uintVal, self.stringVal)
        QWidget.setTabOrder(self.stringVal, self.loadTBL)
        QWidget.setTabOrder(self.loadTBL, self.copy)
        QWidget.setTabOrder(self.copy, self.paste)
        QWidget.setTabOrder(self.paste, self.save)
        QWidget.setTabOrder(self.save, self.saveRange)
        QWidget.setTabOrder(self.saveRange, self.load)

        self.retranslateUi(QGBA__MemoryView)

        QMetaObject.connectSlotsByName(QGBA__MemoryView)
    # setupUi

    def retranslateUi(self, QGBA__MemoryView):
        QGBA__MemoryView.setWindowTitle(QCoreApplication.translate("QGBA::MemoryView", u"Memory", None))
        self.label.setText(QCoreApplication.translate("QGBA::MemoryView", u"Inspect Address:", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::MemoryView", u"Set Alignment:", None))
        self.width8.setText(QCoreApplication.translate("QGBA::MemoryView", u"&1 Byte", None))
        self.width16.setText(QCoreApplication.translate("QGBA::MemoryView", u"&2 Bytes", None))
        self.width32.setText(QCoreApplication.translate("QGBA::MemoryView", u"&4 Bytes", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::MemoryView", u"Unsigned Integer:", None))
        self.label_3.setText(QCoreApplication.translate("QGBA::MemoryView", u"Signed Integer:", None))
        self.label_5.setText(QCoreApplication.translate("QGBA::MemoryView", u"String:", None))
        self.loadTBL.setText(QCoreApplication.translate("QGBA::MemoryView", u"Load TBL", None))
        self.copy.setText(QCoreApplication.translate("QGBA::MemoryView", u"Copy Selection", None))
        self.paste.setText(QCoreApplication.translate("QGBA::MemoryView", u"Paste", None))
        self.save.setText(QCoreApplication.translate("QGBA::MemoryView", u"Save Selection", None))
        self.saveRange.setText(QCoreApplication.translate("QGBA::MemoryView", u"Save Range", None))
        self.load.setText(QCoreApplication.translate("QGBA::MemoryView", u"Load", None))
    # retranslateUi

