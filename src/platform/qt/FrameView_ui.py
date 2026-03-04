# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'FrameView.ui'
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
from PySide6.QtWidgets import (QApplication, QCheckBox, QFrame, QGridLayout,
    QHBoxLayout, QLabel, QListWidget, QListWidgetItem,
    QPushButton, QScrollArea, QSizePolicy, QSpacerItem,
    QSpinBox, QVBoxLayout, QWidget)

class Ui_QGBA_FrameView(object):
    def setupUi(self, QGBA__FrameView):
        if not QGBA__FrameView.objectName():
            QGBA__FrameView.setObjectName(u"QGBA__FrameView")
        QGBA__FrameView.resize(869, 875)
        self.gridLayout = QGridLayout(QGBA__FrameView)
        self.gridLayout.setObjectName(u"gridLayout")
        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.magnification = QSpinBox(QGBA__FrameView)
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

        self.label_2 = QLabel(QGBA__FrameView)
        self.label_2.setObjectName(u"label_2")

        self.horizontalLayout_4.addWidget(self.label_2)


        self.gridLayout.addLayout(self.horizontalLayout_4, 0, 0, 1, 1)

        self.freeze = QCheckBox(QGBA__FrameView)
        self.freeze.setObjectName(u"freeze")

        self.gridLayout.addWidget(self.freeze, 1, 0, 1, 1)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.backdrop = QFrame(QGBA__FrameView)
        self.backdrop.setObjectName(u"backdrop")
        sizePolicy.setHeightForWidth(self.backdrop.sizePolicy().hasHeightForWidth())
        self.backdrop.setSizePolicy(sizePolicy)
        self.backdrop.setMinimumSize(QSize(32, 32))
        self.backdrop.setAutoFillBackground(True)
        self.backdrop.setFrameShape(QFrame.StyledPanel)
        self.backdrop.setFrameShadow(QFrame.Raised)

        self.horizontalLayout.addWidget(self.backdrop)

        self.label = QLabel(QGBA__FrameView)
        self.label.setObjectName(u"label")

        self.horizontalLayout.addWidget(self.label)


        self.gridLayout.addLayout(self.horizontalLayout, 3, 0, 1, 1)

        self.compositedArea = QScrollArea(QGBA__FrameView)
        self.compositedArea.setObjectName(u"compositedArea")
        self.compositedArea.setWidgetResizable(True)
        self.scrollAreaWidgetContents_2 = QWidget()
        self.scrollAreaWidgetContents_2.setObjectName(u"scrollAreaWidgetContents_2")
        self.scrollAreaWidgetContents_2.setGeometry(QRect(0, 0, 567, 382))
        self.verticalLayout_2 = QVBoxLayout(self.scrollAreaWidgetContents_2)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.compositedView = QLabel(self.scrollAreaWidgetContents_2)
        self.compositedView.setObjectName(u"compositedView")

        self.verticalLayout_2.addWidget(self.compositedView)

        self.verticalSpacer_3 = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer_3)

        self.compositedArea.setWidget(self.scrollAreaWidgetContents_2)

        self.gridLayout.addWidget(self.compositedArea, 0, 1, 9, 1)

        self.disableScanline = QCheckBox(QGBA__FrameView)
        self.disableScanline.setObjectName(u"disableScanline")

        self.gridLayout.addWidget(self.disableScanline, 2, 0, 1, 1)

        self.queue = QListWidget(QGBA__FrameView)
        self.queue.setObjectName(u"queue")

        self.gridLayout.addWidget(self.queue, 5, 0, 2, 1)

        self.exportButton = QPushButton(QGBA__FrameView)
        self.exportButton.setObjectName(u"exportButton")
        self.exportButton.setEnabled(False)

        self.gridLayout.addWidget(self.exportButton, 8, 0, 1, 1)

        self.reset = QPushButton(QGBA__FrameView)
        self.reset.setObjectName(u"reset")

        self.gridLayout.addWidget(self.reset, 7, 0, 1, 1)

        self.gridLayout.setRowStretch(5, 1)
        self.gridLayout.setColumnStretch(1, 1)

        self.retranslateUi(QGBA__FrameView)

        QMetaObject.connectSlotsByName(QGBA__FrameView)
    # setupUi

    def retranslateUi(self, QGBA__FrameView):
        QGBA__FrameView.setWindowTitle(QCoreApplication.translate("QGBA::FrameView", u"Inspect frame", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::FrameView", u"Magnification", None))
        self.freeze.setText(QCoreApplication.translate("QGBA::FrameView", u"Freeze frame", None))
        self.label.setText(QCoreApplication.translate("QGBA::FrameView", u"Backdrop color", None))
        self.compositedView.setText("")
        self.disableScanline.setText(QCoreApplication.translate("QGBA::FrameView", u"Disable scanline effects", None))
        self.exportButton.setText(QCoreApplication.translate("QGBA::FrameView", u"Export", None))
        self.reset.setText(QCoreApplication.translate("QGBA::FrameView", u"Reset", None))
    # retranslateUi

