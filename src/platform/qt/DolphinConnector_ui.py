# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'DolphinConnector.ui'
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
from PySide6.QtWidgets import (QApplication, QButtonGroup, QCheckBox, QDialog,
    QGridLayout, QHBoxLayout, QLayout, QLineEdit,
    QPushButton, QRadioButton, QSizePolicy, QWidget)

class Ui_QGBA_DolphinConnector(object):
    def setupUi(self, QGBA__DolphinConnector):
        if not QGBA__DolphinConnector.objectName():
            QGBA__DolphinConnector.setObjectName(u"QGBA__DolphinConnector")
        QGBA__DolphinConnector.resize(306, 123)
        self.gridLayout = QGridLayout(QGBA__DolphinConnector)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setSizeConstraint(QLayout.SetFixedSize)
        self.specLocal = QRadioButton(QGBA__DolphinConnector)
        self.buttonGroup = QButtonGroup(QGBA__DolphinConnector)
        self.buttonGroup.setObjectName(u"buttonGroup")
        self.buttonGroup.addButton(self.specLocal)
        self.specLocal.setObjectName(u"specLocal")
        self.specLocal.setChecked(True)

        self.gridLayout.addWidget(self.specLocal, 0, 0, 1, 1)

        self.specIPAddr = QRadioButton(QGBA__DolphinConnector)
        self.buttonGroup.addButton(self.specIPAddr)
        self.specIPAddr.setObjectName(u"specIPAddr")

        self.gridLayout.addWidget(self.specIPAddr, 0, 1, 1, 1)

        self.ipAddr = QLineEdit(QGBA__DolphinConnector)
        self.ipAddr.setObjectName(u"ipAddr")
        self.ipAddr.setEnabled(False)

        self.gridLayout.addWidget(self.ipAddr, 2, 1, 1, 1)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.connect = QPushButton(QGBA__DolphinConnector)
        self.connect.setObjectName(u"connect")
        icon = QIcon(QIcon.fromTheme(u"network-connect"))
        self.connect.setIcon(icon)

        self.horizontalLayout.addWidget(self.connect)

        self.disconnect = QPushButton(QGBA__DolphinConnector)
        self.disconnect.setObjectName(u"disconnect")
        self.disconnect.setEnabled(False)
        icon1 = QIcon(QIcon.fromTheme(u"network-disconnect"))
        self.disconnect.setIcon(icon1)

        self.horizontalLayout.addWidget(self.disconnect)

        self.close = QPushButton(QGBA__DolphinConnector)
        self.close.setObjectName(u"close")
        icon2 = QIcon(QIcon.fromTheme(u"window-close"))
        self.close.setIcon(icon2)

        self.horizontalLayout.addWidget(self.close)


        self.gridLayout.addLayout(self.horizontalLayout, 3, 0, 1, 2)

        self.doReset = QCheckBox(QGBA__DolphinConnector)
        self.doReset.setObjectName(u"doReset")

        self.gridLayout.addWidget(self.doReset, 2, 0, 1, 1)


        self.retranslateUi(QGBA__DolphinConnector)
        self.close.clicked.connect(QGBA__DolphinConnector.close)
        self.specIPAddr.toggled.connect(self.ipAddr.setEnabled)

        QMetaObject.connectSlotsByName(QGBA__DolphinConnector)
    # setupUi

    def retranslateUi(self, QGBA__DolphinConnector):
        QGBA__DolphinConnector.setWindowTitle(QCoreApplication.translate("QGBA::DolphinConnector", u"Connect to Dolphin", None))
        self.specLocal.setText(QCoreApplication.translate("QGBA::DolphinConnector", u"Local computer", None))
        self.specIPAddr.setText(QCoreApplication.translate("QGBA::DolphinConnector", u"IP address", None))
        self.connect.setText(QCoreApplication.translate("QGBA::DolphinConnector", u"Connect", None))
        self.disconnect.setText(QCoreApplication.translate("QGBA::DolphinConnector", u"Disconnect", None))
        self.close.setText(QCoreApplication.translate("QGBA::DolphinConnector", u"Close", None))
        self.doReset.setText(QCoreApplication.translate("QGBA::DolphinConnector", u"Reset on connect", None))
    # retranslateUi

