# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'PlacementControl.ui'
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
from PySide6.QtWidgets import (QApplication, QDialog, QGridLayout, QLabel,
    QSizePolicy, QSpinBox, QWidget)

class Ui_QGBA_PlacementControl(object):
    def setupUi(self, QGBA__PlacementControl):
        if not QGBA__PlacementControl.objectName():
            QGBA__PlacementControl.setObjectName(u"QGBA__PlacementControl")
        QGBA__PlacementControl.resize(202, 72)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(QGBA__PlacementControl.sizePolicy().hasHeightForWidth())
        QGBA__PlacementControl.setSizePolicy(sizePolicy)
        self.gridLayout = QGridLayout(QGBA__PlacementControl)
        self.gridLayout.setObjectName(u"gridLayout")
        self.label = QLabel(QGBA__PlacementControl)
        self.label.setObjectName(u"label")

        self.gridLayout.addWidget(self.label, 1, 0, 1, 1, Qt.AlignRight)

        self.offsetX = QSpinBox(QGBA__PlacementControl)
        self.offsetX.setObjectName(u"offsetX")
        self.offsetX.setWrapping(True)
        self.offsetX.setAccelerated(True)
        self.offsetX.setMinimum(-128)
        self.offsetX.setMaximum(127)

        self.gridLayout.addWidget(self.offsetX, 1, 1, 1, 1)

        self.offsetY = QSpinBox(QGBA__PlacementControl)
        self.offsetY.setObjectName(u"offsetY")
        self.offsetY.setWrapping(True)
        self.offsetY.setAccelerated(True)
        self.offsetY.setMinimum(-128)
        self.offsetY.setMaximum(127)

        self.gridLayout.addWidget(self.offsetY, 1, 2, 1, 1)

        self.label_2 = QLabel(QGBA__PlacementControl)
        self.label_2.setObjectName(u"label_2")

        self.gridLayout.addWidget(self.label_2, 0, 0, 1, 1, Qt.AlignRight)

        self.label_3 = QLabel(QGBA__PlacementControl)
        self.label_3.setObjectName(u"label_3")

        self.gridLayout.addWidget(self.label_3, 0, 1, 1, 1, Qt.AlignHCenter)

        self.label_4 = QLabel(QGBA__PlacementControl)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout.addWidget(self.label_4, 0, 2, 1, 1, Qt.AlignHCenter)


        self.retranslateUi(QGBA__PlacementControl)

        QMetaObject.connectSlotsByName(QGBA__PlacementControl)
    # setupUi

    def retranslateUi(self, QGBA__PlacementControl):
        QGBA__PlacementControl.setWindowTitle(QCoreApplication.translate("QGBA::PlacementControl", u"Adjust placement", None))
        self.label.setText(QCoreApplication.translate("QGBA::PlacementControl", u"All", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::PlacementControl", u"Offset", None))
        self.label_3.setText(QCoreApplication.translate("QGBA::PlacementControl", u"X", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::PlacementControl", u"Y", None))
    # retranslateUi

