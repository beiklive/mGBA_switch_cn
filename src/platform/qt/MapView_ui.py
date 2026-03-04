# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'MapView.ui'
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
from PySide6.QtWidgets import (QApplication, QGridLayout, QHBoxLayout, QLabel,
    QPushButton, QScrollArea, QSizePolicy, QSpacerItem,
    QSpinBox, QVBoxLayout, QWidget)

class Ui_QGBA_MapView(object):
    def setupUi(self, QGBA__MapView):
        if not QGBA__MapView.objectName():
            QGBA__MapView.setObjectName(u"QGBA__MapView")
        QGBA__MapView.resize(941, 617)
        self.gridLayout = QGridLayout(QGBA__MapView)
        self.gridLayout.setObjectName(u"gridLayout")
        self.bgLayout = QVBoxLayout()
        self.bgLayout.setObjectName(u"bgLayout")
        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.magnification = QSpinBox(QGBA__MapView)
        self.magnification.setObjectName(u"magnification")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.magnification.sizePolicy().hasHeightForWidth())
        self.magnification.setSizePolicy(sizePolicy)
        self.magnification.setSuffix(u"\u00d7")
        self.magnification.setMinimum(1)
        self.magnification.setMaximum(8)

        self.horizontalLayout_4.addWidget(self.magnification)

        self.label_2 = QLabel(QGBA__MapView)
        self.label_2.setObjectName(u"label_2")

        self.horizontalLayout_4.addWidget(self.label_2)


        self.bgLayout.addLayout(self.horizontalLayout_4)


        self.gridLayout.addLayout(self.bgLayout, 1, 0, 1, 1)

        self.scrollArea = QScrollArea(QGBA__MapView)
        self.scrollArea.setObjectName(u"scrollArea")
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.scrollAreaWidgetContents = QWidget()
        self.scrollAreaWidgetContents.setObjectName(u"scrollAreaWidgetContents")
        self.scrollAreaWidgetContents.setGeometry(QRect(0, 0, 613, 601))
        self.verticalLayout = QVBoxLayout(self.scrollAreaWidgetContents)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.map = QLabel(self.scrollAreaWidgetContents)
        self.map.setObjectName(u"map")

        self.verticalLayout.addWidget(self.map)

        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer_2)

        self.scrollArea.setWidget(self.scrollAreaWidgetContents)

        self.gridLayout.addWidget(self.scrollArea, 1, 1, 6, 2)

        self.tile = QGBA_AssetTile(QGBA__MapView)
        self.tile.setObjectName(u"tile")

        self.gridLayout.addWidget(self.tile, 3, 0, 1, 1)

        self.verticalSpacer = QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer, 4, 0, 1, 1)

        self.exportButton = QPushButton(QGBA__MapView)
        self.exportButton.setObjectName(u"exportButton")

        self.gridLayout.addWidget(self.exportButton, 6, 0, 1, 1)

        self.bgInfo = QGBA_AssetInfo(QGBA__MapView)
        self.bgInfo.setObjectName(u"bgInfo")
        self.verticalLayout_2 = QVBoxLayout(self.bgInfo)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")

        self.gridLayout.addWidget(self.bgInfo, 2, 0, 1, 1)

        self.copyButton = QPushButton(QGBA__MapView)
        self.copyButton.setObjectName(u"copyButton")

        self.gridLayout.addWidget(self.copyButton, 5, 0, 1, 1)


        self.retranslateUi(QGBA__MapView)

        QMetaObject.connectSlotsByName(QGBA__MapView)
    # setupUi

    def retranslateUi(self, QGBA__MapView):
        QGBA__MapView.setWindowTitle(QCoreApplication.translate("QGBA::MapView", u"Maps", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::MapView", u"Magnification", None))
        self.map.setText("")
        self.exportButton.setText(QCoreApplication.translate("QGBA::MapView", u"Export", None))
        self.bgInfo.setTitle("")
        self.copyButton.setText(QCoreApplication.translate("QGBA::MapView", u"Copy", None))
    # retranslateUi

