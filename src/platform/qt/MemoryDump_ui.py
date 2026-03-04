# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'MemoryDump.ui'
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
from PySide6.QtWidgets import (QAbstractButton, QApplication, QCheckBox, QDialog,
    QDialogButtonBox, QFormLayout, QHBoxLayout, QLabel,
    QSizePolicy, QSpinBox, QWidget)

class Ui_QGBA_MemoryDump(object):
    def setupUi(self, QGBA__MemoryDump):
        if not QGBA__MemoryDump.objectName():
            QGBA__MemoryDump.setObjectName(u"QGBA__MemoryDump")
        QGBA__MemoryDump.resize(448, 208)
        self.formLayout = QFormLayout(QGBA__MemoryDump)
        self.formLayout.setObjectName(u"formLayout")
        self.label = QLabel(QGBA__MemoryDump)
        self.label.setObjectName(u"label")

        self.formLayout.setWidget(0, QFormLayout.LabelRole, self.label)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.segment = QSpinBox(QGBA__MemoryDump)
        self.segment.setObjectName(u"segment")
        self.segment.setMinimum(-1)
        self.segment.setMaximum(511)
        self.segment.setDisplayIntegerBase(16)

        self.horizontalLayout.addWidget(self.segment)

        self.label_3 = QLabel(QGBA__MemoryDump)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setText(u":")

        self.horizontalLayout.addWidget(self.label_3)

        self.address = QSpinBox(QGBA__MemoryDump)
        self.address.setObjectName(u"address")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.MinimumExpanding, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.address.sizePolicy().hasHeightForWidth())
        self.address.setSizePolicy(sizePolicy)
        self.address.setAccelerated(True)
        self.address.setPrefix(u"0x")
        self.address.setMaximum(268435455)
        self.address.setSingleStep(16)
        self.address.setDisplayIntegerBase(16)

        self.horizontalLayout.addWidget(self.address)


        self.formLayout.setLayout(0, QFormLayout.FieldRole, self.horizontalLayout)

        self.label_2 = QLabel(QGBA__MemoryDump)
        self.label_2.setObjectName(u"label_2")

        self.formLayout.setWidget(1, QFormLayout.LabelRole, self.label_2)

        self.bytes = QSpinBox(QGBA__MemoryDump)
        self.bytes.setObjectName(u"bytes")
        sizePolicy.setHeightForWidth(self.bytes.sizePolicy().hasHeightForWidth())
        self.bytes.setSizePolicy(sizePolicy)
        self.bytes.setPrefix(u"0x")
        self.bytes.setMinimum(1)
        self.bytes.setMaximum(268435456)
        self.bytes.setValue(256)
        self.bytes.setDisplayIntegerBase(16)

        self.formLayout.setWidget(1, QFormLayout.FieldRole, self.bytes)

        self.spanSegments = QCheckBox(QGBA__MemoryDump)
        self.spanSegments.setObjectName(u"spanSegments")

        self.formLayout.setWidget(2, QFormLayout.SpanningRole, self.spanSegments)

        self.buttonBox = QDialogButtonBox(QGBA__MemoryDump)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setOrientation(Qt.Horizontal)
        self.buttonBox.setStandardButtons(QDialogButtonBox.Cancel|QDialogButtonBox.Save)

        self.formLayout.setWidget(3, QFormLayout.SpanningRole, self.buttonBox)


        self.retranslateUi(QGBA__MemoryDump)
        self.buttonBox.accepted.connect(QGBA__MemoryDump.accept)
        self.buttonBox.rejected.connect(QGBA__MemoryDump.reject)

        QMetaObject.connectSlotsByName(QGBA__MemoryDump)
    # setupUi

    def retranslateUi(self, QGBA__MemoryDump):
        QGBA__MemoryDump.setWindowTitle(QCoreApplication.translate("QGBA::MemoryDump", u"Save Memory Range", None))
        self.label.setText(QCoreApplication.translate("QGBA::MemoryDump", u"Start Address:", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::MemoryDump", u"Byte Count:", None))
        self.spanSegments.setText(QCoreApplication.translate("QGBA::MemoryDump", u"Dump across banks", None))
    # retranslateUi

