# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'IOViewer.ui'
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
    QDialogButtonBox, QFrame, QGridLayout, QLabel,
    QLayout, QSizePolicy, QVBoxLayout, QWidget)

class Ui_QGBA_IOViewer(object):
    def setupUi(self, QGBA__IOViewer):
        if not QGBA__IOViewer.objectName():
            QGBA__IOViewer.setObjectName(u"QGBA__IOViewer")
        QGBA__IOViewer.resize(343, 342)
        self.verticalLayout_2 = QVBoxLayout(QGBA__IOViewer)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setSizeConstraint(QLayout.SetFixedSize)
        self.regSelect = QComboBox(QGBA__IOViewer)
        self.regSelect.setObjectName(u"regSelect")

        self.verticalLayout_2.addWidget(self.regSelect)

        self.regValue = QLabel(QGBA__IOViewer)
        self.regValue.setObjectName(u"regValue")
        self.regValue.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_2.addWidget(self.regValue, 0, Qt.AlignRight|Qt.AlignTop)

        self.gridLayout = QGridLayout()
        self.gridLayout.setObjectName(u"gridLayout")
        self.b3 = QCheckBox(QGBA__IOViewer)
        self.b3.setObjectName(u"b3")

        self.gridLayout.addWidget(self.b3, 0, 12, 1, 1, Qt.AlignHCenter)

        self.b4 = QCheckBox(QGBA__IOViewer)
        self.b4.setObjectName(u"b4")

        self.gridLayout.addWidget(self.b4, 0, 11, 1, 1, Qt.AlignHCenter)

        self.b2 = QCheckBox(QGBA__IOViewer)
        self.b2.setObjectName(u"b2")

        self.gridLayout.addWidget(self.b2, 0, 13, 1, 1, Qt.AlignHCenter)

        self.b0 = QCheckBox(QGBA__IOViewer)
        self.b0.setObjectName(u"b0")

        self.gridLayout.addWidget(self.b0, 0, 15, 1, 1, Qt.AlignHCenter)

        self.l2 = QLabel(QGBA__IOViewer)
        self.l2.setObjectName(u"l2")
        self.l2.setMaximumSize(QSize(16777215, 80))
        font = QFont()
        font.setPointSize(10)
        self.l2.setFont(font)
        self.l2.setText(u"2")

        self.gridLayout.addWidget(self.l2, 1, 13, 1, 1, Qt.AlignHCenter|Qt.AlignTop)

        self.b5 = QCheckBox(QGBA__IOViewer)
        self.b5.setObjectName(u"b5")

        self.gridLayout.addWidget(self.b5, 0, 10, 1, 1, Qt.AlignHCenter)

        self.b1 = QCheckBox(QGBA__IOViewer)
        self.b1.setObjectName(u"b1")

        self.gridLayout.addWidget(self.b1, 0, 14, 1, 1, Qt.AlignHCenter)

        self.l5 = QLabel(QGBA__IOViewer)
        self.l5.setObjectName(u"l5")
        self.l5.setMaximumSize(QSize(16777215, 80))
        self.l5.setFont(font)
        self.l5.setText(u"5")

        self.gridLayout.addWidget(self.l5, 1, 10, 1, 1, Qt.AlignHCenter|Qt.AlignTop)

        self.l4 = QLabel(QGBA__IOViewer)
        self.l4.setObjectName(u"l4")
        self.l4.setMaximumSize(QSize(16777215, 80))
        self.l4.setFont(font)
        self.l4.setText(u"4")

        self.gridLayout.addWidget(self.l4, 1, 11, 1, 1, Qt.AlignHCenter|Qt.AlignTop)

        self.l7 = QLabel(QGBA__IOViewer)
        self.l7.setObjectName(u"l7")
        self.l7.setMaximumSize(QSize(16777215, 80))
        self.l7.setFont(font)
        self.l7.setText(u"7")

        self.gridLayout.addWidget(self.l7, 1, 8, 1, 1, Qt.AlignHCenter|Qt.AlignTop)

        self.l0 = QLabel(QGBA__IOViewer)
        self.l0.setObjectName(u"l0")
        self.l0.setMaximumSize(QSize(16777215, 80))
        self.l0.setFont(font)
        self.l0.setText(u"0")

        self.gridLayout.addWidget(self.l0, 1, 15, 1, 1, Qt.AlignHCenter|Qt.AlignTop)

        self.b6 = QCheckBox(QGBA__IOViewer)
        self.b6.setObjectName(u"b6")

        self.gridLayout.addWidget(self.b6, 0, 9, 1, 1, Qt.AlignHCenter)

        self.l9 = QLabel(QGBA__IOViewer)
        self.l9.setObjectName(u"l9")
        self.l9.setMaximumSize(QSize(16777215, 80))
        self.l9.setFont(font)
        self.l9.setText(u"9")

        self.gridLayout.addWidget(self.l9, 1, 6, 1, 1, Qt.AlignHCenter)

        self.b9 = QCheckBox(QGBA__IOViewer)
        self.b9.setObjectName(u"b9")

        self.gridLayout.addWidget(self.b9, 0, 6, 1, 1, Qt.AlignHCenter)

        self.l1 = QLabel(QGBA__IOViewer)
        self.l1.setObjectName(u"l1")
        self.l1.setMaximumSize(QSize(16777215, 80))
        self.l1.setFont(font)
        self.l1.setText(u"1")

        self.gridLayout.addWidget(self.l1, 1, 14, 1, 1, Qt.AlignHCenter|Qt.AlignTop)

        self.l3 = QLabel(QGBA__IOViewer)
        self.l3.setObjectName(u"l3")
        self.l3.setMaximumSize(QSize(16777215, 80))
        self.l3.setFont(font)
        self.l3.setText(u"3")

        self.gridLayout.addWidget(self.l3, 1, 12, 1, 1, Qt.AlignHCenter|Qt.AlignTop)

        self.bF = QCheckBox(QGBA__IOViewer)
        self.bF.setObjectName(u"bF")

        self.gridLayout.addWidget(self.bF, 0, 0, 1, 1, Qt.AlignHCenter)

        self.l8 = QLabel(QGBA__IOViewer)
        self.l8.setObjectName(u"l8")
        self.l8.setMaximumSize(QSize(16777215, 80))
        self.l8.setFont(font)
        self.l8.setText(u"8")

        self.gridLayout.addWidget(self.l8, 1, 7, 1, 1, Qt.AlignHCenter)

        self.bD = QCheckBox(QGBA__IOViewer)
        self.bD.setObjectName(u"bD")

        self.gridLayout.addWidget(self.bD, 0, 2, 1, 1, Qt.AlignHCenter)

        self.bE = QCheckBox(QGBA__IOViewer)
        self.bE.setObjectName(u"bE")

        self.gridLayout.addWidget(self.bE, 0, 1, 1, 1, Qt.AlignHCenter)

        self.lC = QLabel(QGBA__IOViewer)
        self.lC.setObjectName(u"lC")
        self.lC.setMaximumSize(QSize(16777215, 80))
        self.lC.setFont(font)
        self.lC.setText(u"C")

        self.gridLayout.addWidget(self.lC, 1, 3, 1, 1, Qt.AlignHCenter)

        self.lE = QLabel(QGBA__IOViewer)
        self.lE.setObjectName(u"lE")
        self.lE.setMaximumSize(QSize(16777215, 80))
        self.lE.setFont(font)
        self.lE.setText(u"E")

        self.gridLayout.addWidget(self.lE, 1, 1, 1, 1, Qt.AlignHCenter)

        self.bC = QCheckBox(QGBA__IOViewer)
        self.bC.setObjectName(u"bC")

        self.gridLayout.addWidget(self.bC, 0, 3, 1, 1, Qt.AlignHCenter)

        self.bA = QCheckBox(QGBA__IOViewer)
        self.bA.setObjectName(u"bA")

        self.gridLayout.addWidget(self.bA, 0, 5, 1, 1)

        self.l6 = QLabel(QGBA__IOViewer)
        self.l6.setObjectName(u"l6")
        self.l6.setMaximumSize(QSize(16777215, 80))
        self.l6.setFont(font)
        self.l6.setText(u"6")

        self.gridLayout.addWidget(self.l6, 1, 9, 1, 1, Qt.AlignHCenter|Qt.AlignTop)

        self.b8 = QCheckBox(QGBA__IOViewer)
        self.b8.setObjectName(u"b8")

        self.gridLayout.addWidget(self.b8, 0, 7, 1, 1, Qt.AlignHCenter)

        self.bB = QCheckBox(QGBA__IOViewer)
        self.bB.setObjectName(u"bB")

        self.gridLayout.addWidget(self.bB, 0, 4, 1, 1, Qt.AlignHCenter)

        self.b7 = QCheckBox(QGBA__IOViewer)
        self.b7.setObjectName(u"b7")

        self.gridLayout.addWidget(self.b7, 0, 8, 1, 1, Qt.AlignHCenter)

        self.lD = QLabel(QGBA__IOViewer)
        self.lD.setObjectName(u"lD")
        self.lD.setMaximumSize(QSize(16777215, 80))
        self.lD.setFont(font)
        self.lD.setText(u"D")

        self.gridLayout.addWidget(self.lD, 1, 2, 1, 1, Qt.AlignHCenter)

        self.lF = QLabel(QGBA__IOViewer)
        self.lF.setObjectName(u"lF")
        self.lF.setMaximumSize(QSize(16777215, 80))
        self.lF.setFont(font)
        self.lF.setText(u"F")

        self.gridLayout.addWidget(self.lF, 1, 0, 1, 1, Qt.AlignHCenter)

        self.lA = QLabel(QGBA__IOViewer)
        self.lA.setObjectName(u"lA")
        self.lA.setMaximumSize(QSize(16777215, 80))
        self.lA.setFont(font)
        self.lA.setText(u"A")

        self.gridLayout.addWidget(self.lA, 1, 5, 1, 1, Qt.AlignHCenter)

        self.lB = QLabel(QGBA__IOViewer)
        self.lB.setObjectName(u"lB")
        self.lB.setMaximumSize(QSize(16777215, 80))
        self.lB.setFont(font)

        self.gridLayout.addWidget(self.lB, 1, 4, 1, 1, Qt.AlignHCenter)


        self.verticalLayout_2.addLayout(self.gridLayout)

        self.line = QFrame(QGBA__IOViewer)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.verticalLayout_2.addWidget(self.line)

        self.regDescription = QWidget(QGBA__IOViewer)
        self.regDescription.setObjectName(u"regDescription")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.MinimumExpanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.regDescription.sizePolicy().hasHeightForWidth())
        self.regDescription.setSizePolicy(sizePolicy)

        self.verticalLayout_2.addWidget(self.regDescription)

        self.buttonBox = QDialogButtonBox(QGBA__IOViewer)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setStandardButtons(QDialogButtonBox.Apply|QDialogButtonBox.Close|QDialogButtonBox.Reset)

        self.verticalLayout_2.addWidget(self.buttonBox)

        QWidget.setTabOrder(self.regSelect, self.b0)
        QWidget.setTabOrder(self.b0, self.b1)
        QWidget.setTabOrder(self.b1, self.b2)
        QWidget.setTabOrder(self.b2, self.b3)
        QWidget.setTabOrder(self.b3, self.b4)
        QWidget.setTabOrder(self.b4, self.b5)
        QWidget.setTabOrder(self.b5, self.b6)
        QWidget.setTabOrder(self.b6, self.b7)
        QWidget.setTabOrder(self.b7, self.bE)
        QWidget.setTabOrder(self.bE, self.b8)
        QWidget.setTabOrder(self.b8, self.b9)
        QWidget.setTabOrder(self.b9, self.bA)
        QWidget.setTabOrder(self.bA, self.bB)
        QWidget.setTabOrder(self.bB, self.bC)
        QWidget.setTabOrder(self.bC, self.bD)
        QWidget.setTabOrder(self.bD, self.bF)

        self.retranslateUi(QGBA__IOViewer)

        QMetaObject.connectSlotsByName(QGBA__IOViewer)
    # setupUi

    def retranslateUi(self, QGBA__IOViewer):
        QGBA__IOViewer.setWindowTitle(QCoreApplication.translate("QGBA::IOViewer", u"I/O Viewer", None))
        self.regValue.setText(QCoreApplication.translate("QGBA::IOViewer", u"0x0000", None))
        self.lB.setText(QCoreApplication.translate("QGBA::IOViewer", u"B", None))
    # retranslateUi

