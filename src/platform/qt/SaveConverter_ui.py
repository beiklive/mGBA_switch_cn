# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'SaveConverter.ui'
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
from PySide6.QtWidgets import (QAbstractButton, QApplication, QComboBox, QDialog,
    QDialogButtonBox, QGridLayout, QGroupBox, QLineEdit,
    QPushButton, QSizePolicy, QVBoxLayout, QWidget)

class Ui_QGBA_SaveConverter(object):
    def setupUi(self, QGBA__SaveConverter):
        if not QGBA__SaveConverter.objectName():
            QGBA__SaveConverter.setObjectName(u"QGBA__SaveConverter")
        QGBA__SaveConverter.resize(546, 300)
        self.verticalLayout = QVBoxLayout(QGBA__SaveConverter)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.groupBox = QGroupBox(QGBA__SaveConverter)
        self.groupBox.setObjectName(u"groupBox")
        self.gridLayout = QGridLayout(self.groupBox)
        self.gridLayout.setObjectName(u"gridLayout")
        self.inputFile = QLineEdit(self.groupBox)
        self.inputFile.setObjectName(u"inputFile")

        self.gridLayout.addWidget(self.inputFile, 0, 0, 1, 1)

        self.inputBrowse = QPushButton(self.groupBox)
        self.inputBrowse.setObjectName(u"inputBrowse")

        self.gridLayout.addWidget(self.inputBrowse, 0, 1, 1, 1)

        self.inputType = QComboBox(self.groupBox)
        self.inputType.setObjectName(u"inputType")
        self.inputType.setEnabled(False)

        self.gridLayout.addWidget(self.inputType, 1, 0, 1, 2)


        self.verticalLayout.addWidget(self.groupBox)

        self.groupBox_2 = QGroupBox(QGBA__SaveConverter)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.gridLayout_2 = QGridLayout(self.groupBox_2)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.outputFile = QLineEdit(self.groupBox_2)
        self.outputFile.setObjectName(u"outputFile")

        self.gridLayout_2.addWidget(self.outputFile, 0, 0, 1, 1)

        self.outputBrowse = QPushButton(self.groupBox_2)
        self.outputBrowse.setObjectName(u"outputBrowse")

        self.gridLayout_2.addWidget(self.outputBrowse, 0, 1, 1, 1)

        self.outputType = QComboBox(self.groupBox_2)
        self.outputType.setObjectName(u"outputType")
        self.outputType.setEnabled(False)

        self.gridLayout_2.addWidget(self.outputType, 1, 0, 1, 2)


        self.verticalLayout.addWidget(self.groupBox_2)

        self.buttonBox = QDialogButtonBox(QGBA__SaveConverter)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setOrientation(Qt.Horizontal)
        self.buttonBox.setStandardButtons(QDialogButtonBox.Cancel|QDialogButtonBox.Save)

        self.verticalLayout.addWidget(self.buttonBox)

        QWidget.setTabOrder(self.inputFile, self.inputBrowse)
        QWidget.setTabOrder(self.inputBrowse, self.inputType)
        QWidget.setTabOrder(self.inputType, self.outputFile)
        QWidget.setTabOrder(self.outputFile, self.outputBrowse)
        QWidget.setTabOrder(self.outputBrowse, self.outputType)

        self.retranslateUi(QGBA__SaveConverter)
        self.buttonBox.accepted.connect(QGBA__SaveConverter.accept)
        self.buttonBox.rejected.connect(QGBA__SaveConverter.reject)

        QMetaObject.connectSlotsByName(QGBA__SaveConverter)
    # setupUi

    def retranslateUi(self, QGBA__SaveConverter):
        QGBA__SaveConverter.setWindowTitle(QCoreApplication.translate("QGBA::SaveConverter", u"Convert/Extract Save Game", None))
        self.groupBox.setTitle(QCoreApplication.translate("QGBA::SaveConverter", u"Input file", None))
        self.inputBrowse.setText(QCoreApplication.translate("QGBA::SaveConverter", u"Browse", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("QGBA::SaveConverter", u"Output file", None))
        self.outputBrowse.setText(QCoreApplication.translate("QGBA::SaveConverter", u"Browse", None))
    # retranslateUi

