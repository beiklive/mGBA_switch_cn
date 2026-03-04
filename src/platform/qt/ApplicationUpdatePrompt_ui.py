# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ApplicationUpdatePrompt.ui'
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
from PySide6.QtWidgets import (QAbstractButton, QApplication, QDialog, QDialogButtonBox,
    QLabel, QLayout, QProgressBar, QSizePolicy,
    QVBoxLayout, QWidget)

class Ui_QGBA_ApplicationUpdatePrompt(object):
    def setupUi(self, QGBA__ApplicationUpdatePrompt):
        if not QGBA__ApplicationUpdatePrompt.objectName():
            QGBA__ApplicationUpdatePrompt.setObjectName(u"QGBA__ApplicationUpdatePrompt")
        QGBA__ApplicationUpdatePrompt.resize(186, 127)
        self.verticalLayout = QVBoxLayout(QGBA__ApplicationUpdatePrompt)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setSizeConstraint(QLayout.SetFixedSize)
        self.text = QLabel(QGBA__ApplicationUpdatePrompt)
        self.text.setObjectName(u"text")
        self.text.setText(u"{text}")
        self.text.setWordWrap(True)

        self.verticalLayout.addWidget(self.text)

        self.details = QLabel(QGBA__ApplicationUpdatePrompt)
        self.details.setObjectName(u"details")
        self.details.setText(u"{details}")

        self.verticalLayout.addWidget(self.details)

        self.progressBar = QProgressBar(QGBA__ApplicationUpdatePrompt)
        self.progressBar.setObjectName(u"progressBar")
        self.progressBar.setValue(0)

        self.verticalLayout.addWidget(self.progressBar)

        self.buttonBox = QDialogButtonBox(QGBA__ApplicationUpdatePrompt)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setOrientation(Qt.Horizontal)
        self.buttonBox.setStandardButtons(QDialogButtonBox.Cancel|QDialogButtonBox.Ok)

        self.verticalLayout.addWidget(self.buttonBox)


        self.retranslateUi(QGBA__ApplicationUpdatePrompt)
        self.buttonBox.rejected.connect(QGBA__ApplicationUpdatePrompt.reject)

        QMetaObject.connectSlotsByName(QGBA__ApplicationUpdatePrompt)
    # setupUi

    def retranslateUi(self, QGBA__ApplicationUpdatePrompt):
        QGBA__ApplicationUpdatePrompt.setWindowTitle(QCoreApplication.translate("QGBA::ApplicationUpdatePrompt", u"An update is available", None))
    # retranslateUi

