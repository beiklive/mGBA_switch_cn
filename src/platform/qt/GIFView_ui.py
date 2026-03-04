# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'GIFView.ui'
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
from PySide6.QtWidgets import (QAbstractButton, QApplication, QButtonGroup, QCheckBox,
    QDialogButtonBox, QGridLayout, QLabel, QLayout,
    QLineEdit, QPushButton, QRadioButton, QSizePolicy,
    QSpacerItem, QSpinBox, QWidget)

class Ui_QGBA_GIFView(object):
    def setupUi(self, QGBA__GIFView):
        if not QGBA__GIFView.objectName():
            QGBA__GIFView.setObjectName(u"QGBA__GIFView")
        QGBA__GIFView.resize(392, 225)
        self.gridLayout_3 = QGridLayout(QGBA__GIFView)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.gridLayout_3.setSizeConstraint(QLayout.SetFixedSize)
        self.buttonBox = QDialogButtonBox(QGBA__GIFView)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setStandardButtons(QDialogButtonBox.Close)

        self.gridLayout_3.addWidget(self.buttonBox, 4, 0, 1, 3)

        self.loop = QCheckBox(QGBA__GIFView)
        self.loop.setObjectName(u"loop")
        self.loop.setChecked(True)

        self.gridLayout_3.addWidget(self.loop, 1, 1, 1, 2)

        self.gridLayout = QGridLayout()
        self.gridLayout.setObjectName(u"gridLayout")
        self.start = QPushButton(QGBA__GIFView)
        self.start.setObjectName(u"start")
        self.start.setEnabled(False)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.start.sizePolicy().hasHeightForWidth())
        self.start.setSizePolicy(sizePolicy)

        self.gridLayout.addWidget(self.start, 1, 0, 1, 1)

        self.stop = QPushButton(QGBA__GIFView)
        self.stop.setObjectName(u"stop")
        self.stop.setEnabled(False)
        sizePolicy.setHeightForWidth(self.stop.sizePolicy().hasHeightForWidth())
        self.stop.setSizePolicy(sizePolicy)

        self.gridLayout.addWidget(self.stop, 1, 1, 1, 1)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.gridLayout.addItem(self.horizontalSpacer, 1, 2, 1, 1)

        self.selectFile = QPushButton(QGBA__GIFView)
        self.selectFile.setObjectName(u"selectFile")
        sizePolicy.setHeightForWidth(self.selectFile.sizePolicy().hasHeightForWidth())
        self.selectFile.setSizePolicy(sizePolicy)

        self.gridLayout.addWidget(self.selectFile, 1, 3, 1, 1)

        self.filename = QLineEdit(QGBA__GIFView)
        self.filename.setObjectName(u"filename")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        sizePolicy1.setHorizontalStretch(1)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.filename.sizePolicy().hasHeightForWidth())
        self.filename.setSizePolicy(sizePolicy1)

        self.gridLayout.addWidget(self.filename, 0, 0, 1, 4)


        self.gridLayout_3.addLayout(self.gridLayout, 0, 0, 1, 3)

        self.fmtApng = QRadioButton(QGBA__GIFView)
        self.format = QButtonGroup(QGBA__GIFView)
        self.format.setObjectName(u"format")
        self.format.addButton(self.fmtApng)
        self.fmtApng.setObjectName(u"fmtApng")

        self.gridLayout_3.addWidget(self.fmtApng, 3, 0, 1, 1)

        self.fmtGif = QRadioButton(QGBA__GIFView)
        self.format.addButton(self.fmtGif)
        self.fmtGif.setObjectName(u"fmtGif")
        self.fmtGif.setChecked(True)

        self.gridLayout_3.addWidget(self.fmtGif, 1, 0, 1, 1)

        self.fmtWebP = QRadioButton(QGBA__GIFView)
        self.format.addButton(self.fmtWebP)
        self.fmtWebP.setObjectName(u"fmtWebP")

        self.gridLayout_3.addWidget(self.fmtWebP, 2, 0, 1, 1)

        self.label = QLabel(QGBA__GIFView)
        self.label.setObjectName(u"label")

        self.gridLayout_3.addWidget(self.label, 2, 1, 1, 1)

        self.frameskip = QSpinBox(QGBA__GIFView)
        self.frameskip.setObjectName(u"frameskip")
        sizePolicy.setHeightForWidth(self.frameskip.sizePolicy().hasHeightForWidth())
        self.frameskip.setSizePolicy(sizePolicy)
        self.frameskip.setMaximum(9)
        self.frameskip.setValue(2)

        self.gridLayout_3.addWidget(self.frameskip, 2, 2, 1, 1)

        QWidget.setTabOrder(self.filename, self.start)
        QWidget.setTabOrder(self.start, self.stop)
        QWidget.setTabOrder(self.stop, self.selectFile)
        QWidget.setTabOrder(self.selectFile, self.fmtGif)
        QWidget.setTabOrder(self.fmtGif, self.fmtWebP)
        QWidget.setTabOrder(self.fmtWebP, self.fmtApng)
        QWidget.setTabOrder(self.fmtApng, self.loop)
        QWidget.setTabOrder(self.loop, self.frameskip)

        self.retranslateUi(QGBA__GIFView)
        self.buttonBox.rejected.connect(QGBA__GIFView.close)

        QMetaObject.connectSlotsByName(QGBA__GIFView)
    # setupUi

    def retranslateUi(self, QGBA__GIFView):
        QGBA__GIFView.setWindowTitle(QCoreApplication.translate("QGBA::GIFView", u"Record GIF/WebP/APNG", None))
        self.loop.setText(QCoreApplication.translate("QGBA::GIFView", u"Loop", None))
        self.start.setText(QCoreApplication.translate("QGBA::GIFView", u"Start", None))
        self.stop.setText(QCoreApplication.translate("QGBA::GIFView", u"Stop", None))
        self.selectFile.setText(QCoreApplication.translate("QGBA::GIFView", u"Select File", None))
        self.fmtApng.setText(QCoreApplication.translate("QGBA::GIFView", u"APNG", None))
        self.fmtGif.setText(QCoreApplication.translate("QGBA::GIFView", u"GIF", None))
        self.fmtWebP.setText(QCoreApplication.translate("QGBA::GIFView", u"WebP", None))
        self.label.setText(QCoreApplication.translate("QGBA::GIFView", u"Frameskip", None))
    # retranslateUi

