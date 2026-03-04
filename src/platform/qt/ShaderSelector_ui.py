# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ShaderSelector.ui'
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
    QFrame, QGridLayout, QHBoxLayout, QLabel,
    QPushButton, QSizePolicy, QTabWidget, QVBoxLayout,
    QWidget)

class Ui_QGBA_ShaderSelector(object):
    def setupUi(self, QGBA__ShaderSelector):
        if not QGBA__ShaderSelector.objectName():
            QGBA__ShaderSelector.setObjectName(u"QGBA__ShaderSelector")
        QGBA__ShaderSelector.resize(386, 350)
        self.verticalLayout = QVBoxLayout(QGBA__ShaderSelector)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.label = QLabel(QGBA__ShaderSelector)
        self.label.setObjectName(u"label")
        font = QFont()
        font.setBold(True)
        self.label.setFont(font)

        self.horizontalLayout.addWidget(self.label)

        self.shaderName = QLabel(QGBA__ShaderSelector)
        self.shaderName.setObjectName(u"shaderName")
        self.shaderName.setAlignment(Qt.AlignCenter)

        self.horizontalLayout.addWidget(self.shaderName)

        self.author = QLabel(QGBA__ShaderSelector)
        self.author.setObjectName(u"author")
        self.author.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout.addWidget(self.author)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.description = QLabel(QGBA__ShaderSelector)
        self.description.setObjectName(u"description")
        font1 = QFont()
        font1.setItalic(True)
        self.description.setFont(font1)
        self.description.setWordWrap(True)

        self.verticalLayout.addWidget(self.description)

        self.line = QFrame(QGBA__ShaderSelector)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.verticalLayout.addWidget(self.line)

        self.passes = QTabWidget(QGBA__ShaderSelector)
        self.passes.setObjectName(u"passes")

        self.verticalLayout.addWidget(self.passes)

        self.gridLayout = QGridLayout()
        self.gridLayout.setObjectName(u"gridLayout")
        self.unload = QPushButton(QGBA__ShaderSelector)
        self.unload.setObjectName(u"unload")

        self.gridLayout.addWidget(self.unload, 0, 0, 1, 1)

        self.load = QPushButton(QGBA__ShaderSelector)
        self.load.setObjectName(u"load")

        self.gridLayout.addWidget(self.load, 0, 1, 1, 1)

        self.buttonBox = QDialogButtonBox(QGBA__ShaderSelector)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setOrientation(Qt.Horizontal)
        self.buttonBox.setStandardButtons(QDialogButtonBox.Reset|QDialogButtonBox.RestoreDefaults)
        self.buttonBox.setCenterButtons(True)

        self.gridLayout.addWidget(self.buttonBox, 1, 0, 1, 2)


        self.verticalLayout.addLayout(self.gridLayout)


        self.retranslateUi(QGBA__ShaderSelector)

        self.passes.setCurrentIndex(-1)


        QMetaObject.connectSlotsByName(QGBA__ShaderSelector)
    # setupUi

    def retranslateUi(self, QGBA__ShaderSelector):
        QGBA__ShaderSelector.setWindowTitle(QCoreApplication.translate("QGBA::ShaderSelector", u"Shaders", None))
        self.label.setText(QCoreApplication.translate("QGBA::ShaderSelector", u"Active Shader:", None))
        self.shaderName.setText(QCoreApplication.translate("QGBA::ShaderSelector", u"Name", None))
        self.author.setText(QCoreApplication.translate("QGBA::ShaderSelector", u"Author", None))
        self.description.setText(QCoreApplication.translate("QGBA::ShaderSelector", u"Description", None))
        self.unload.setText(QCoreApplication.translate("QGBA::ShaderSelector", u"Unload Shader", None))
        self.load.setText(QCoreApplication.translate("QGBA::ShaderSelector", u"Load New Shader", None))
    # retranslateUi

