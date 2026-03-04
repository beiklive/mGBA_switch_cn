# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ROMInfo.ui'
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
from PySide6.QtWidgets import (QApplication, QDialog, QFormLayout, QLabel,
    QLayout, QSizePolicy, QWidget)

class Ui_QGBA_ROMInfo(object):
    def setupUi(self, QGBA__ROMInfo):
        if not QGBA__ROMInfo.objectName():
            QGBA__ROMInfo.setObjectName(u"QGBA__ROMInfo")
        QGBA__ROMInfo.resize(236, 146)
        self.formLayout = QFormLayout(QGBA__ROMInfo)
        self.formLayout.setObjectName(u"formLayout")
        self.formLayout.setSizeConstraint(QLayout.SetFixedSize)
        self.formLayout.setFieldGrowthPolicy(QFormLayout.FieldsStayAtSizeHint)
        self.label_5 = QLabel(QGBA__ROMInfo)
        self.label_5.setObjectName(u"label_5")

        self.formLayout.setWidget(0, QFormLayout.LabelRole, self.label_5)

        self.name = QLabel(QGBA__ROMInfo)
        self.name.setObjectName(u"name")
        self.name.setText(u"{NAME}")
        self.name.setWordWrap(True)
        self.name.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.formLayout.setWidget(0, QFormLayout.FieldRole, self.name)

        self.label = QLabel(QGBA__ROMInfo)
        self.label.setObjectName(u"label")

        self.formLayout.setWidget(1, QFormLayout.LabelRole, self.label)

        self.title = QLabel(QGBA__ROMInfo)
        self.title.setObjectName(u"title")
        self.title.setText(u"{TITLE}")
        self.title.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.formLayout.setWidget(1, QFormLayout.FieldRole, self.title)

        self.label_2 = QLabel(QGBA__ROMInfo)
        self.label_2.setObjectName(u"label_2")

        self.formLayout.setWidget(2, QFormLayout.LabelRole, self.label_2)

        self.id = QLabel(QGBA__ROMInfo)
        self.id.setObjectName(u"id")
        self.id.setText(u"{ID}")
        self.id.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.formLayout.setWidget(2, QFormLayout.FieldRole, self.id)

        self.label_3 = QLabel(QGBA__ROMInfo)
        self.label_3.setObjectName(u"label_3")

        self.formLayout.setWidget(3, QFormLayout.LabelRole, self.label_3)

        self.size = QLabel(QGBA__ROMInfo)
        self.size.setObjectName(u"size")
        self.size.setText(u"{SIZE}")
        self.size.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.formLayout.setWidget(3, QFormLayout.FieldRole, self.size)

        self.label_4 = QLabel(QGBA__ROMInfo)
        self.label_4.setObjectName(u"label_4")

        self.formLayout.setWidget(4, QFormLayout.LabelRole, self.label_4)

        self.crc = QLabel(QGBA__ROMInfo)
        self.crc.setObjectName(u"crc")
        self.crc.setText(u"{CRC}")
        self.crc.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.formLayout.setWidget(4, QFormLayout.FieldRole, self.crc)


        self.retranslateUi(QGBA__ROMInfo)

        QMetaObject.connectSlotsByName(QGBA__ROMInfo)
    # setupUi

    def retranslateUi(self, QGBA__ROMInfo):
        QGBA__ROMInfo.setWindowTitle(QCoreApplication.translate("QGBA::ROMInfo", u"ROM Info", None))
        self.label_5.setText(QCoreApplication.translate("QGBA::ROMInfo", u"Game name:", None))
        self.label.setText(QCoreApplication.translate("QGBA::ROMInfo", u"Internal name:", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::ROMInfo", u"Game ID:", None))
        self.label_3.setText(QCoreApplication.translate("QGBA::ROMInfo", u"File size:", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::ROMInfo", u"CRC32:", None))
    # retranslateUi

