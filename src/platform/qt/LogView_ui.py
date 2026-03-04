# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'LogView.ui'
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
from PySide6.QtWidgets import (QApplication, QCheckBox, QFrame, QGroupBox,
    QHBoxLayout, QLabel, QPlainTextEdit, QPushButton,
    QSizePolicy, QSpacerItem, QSpinBox, QVBoxLayout,
    QWidget)

class Ui_QGBA_LogView(object):
    def setupUi(self, QGBA__LogView):
        if not QGBA__LogView.objectName():
            QGBA__LogView.setObjectName(u"QGBA__LogView")
        QGBA__LogView.resize(600, 400)
        self.horizontalLayout = QHBoxLayout(QGBA__LogView)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.groupBox = QGroupBox(QGBA__LogView)
        self.groupBox.setObjectName(u"groupBox")
        self.verticalLayout = QVBoxLayout(self.groupBox)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.levelDebug = QCheckBox(self.groupBox)
        self.levelDebug.setObjectName(u"levelDebug")
        self.levelDebug.setChecked(False)

        self.verticalLayout.addWidget(self.levelDebug)

        self.levelStub = QCheckBox(self.groupBox)
        self.levelStub.setObjectName(u"levelStub")
        self.levelStub.setChecked(False)

        self.verticalLayout.addWidget(self.levelStub)

        self.levelInfo = QCheckBox(self.groupBox)
        self.levelInfo.setObjectName(u"levelInfo")
        self.levelInfo.setChecked(False)

        self.verticalLayout.addWidget(self.levelInfo)

        self.levelWarn = QCheckBox(self.groupBox)
        self.levelWarn.setObjectName(u"levelWarn")
        self.levelWarn.setChecked(True)

        self.verticalLayout.addWidget(self.levelWarn)

        self.levelError = QCheckBox(self.groupBox)
        self.levelError.setObjectName(u"levelError")
        self.levelError.setChecked(True)

        self.verticalLayout.addWidget(self.levelError)

        self.levelFatal = QCheckBox(self.groupBox)
        self.levelFatal.setObjectName(u"levelFatal")
        self.levelFatal.setChecked(True)

        self.verticalLayout.addWidget(self.levelFatal)

        self.line = QFrame(self.groupBox)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.verticalLayout.addWidget(self.line)

        self.levelGameError = QCheckBox(self.groupBox)
        self.levelGameError.setObjectName(u"levelGameError")
        self.levelGameError.setChecked(False)

        self.verticalLayout.addWidget(self.levelGameError)


        self.verticalLayout_2.addWidget(self.groupBox)

        self.advanced = QPushButton(QGBA__LogView)
        self.advanced.setObjectName(u"advanced")

        self.verticalLayout_2.addWidget(self.advanced)

        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer_2)

        self.clear = QPushButton(QGBA__LogView)
        self.clear.setObjectName(u"clear")

        self.verticalLayout_2.addWidget(self.clear)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.label = QLabel(QGBA__LogView)
        self.label.setObjectName(u"label")

        self.horizontalLayout_3.addWidget(self.label)

        self.maxLines = QSpinBox(QGBA__LogView)
        self.maxLines.setObjectName(u"maxLines")
        self.maxLines.setMaximum(9999)

        self.horizontalLayout_3.addWidget(self.maxLines)


        self.verticalLayout_2.addLayout(self.horizontalLayout_3)


        self.horizontalLayout.addLayout(self.verticalLayout_2)

        self.view = QPlainTextEdit(QGBA__LogView)
        self.view.setObjectName(u"view")
        self.view.setReadOnly(True)

        self.horizontalLayout.addWidget(self.view)


        self.retranslateUi(QGBA__LogView)

        QMetaObject.connectSlotsByName(QGBA__LogView)
    # setupUi

    def retranslateUi(self, QGBA__LogView):
        QGBA__LogView.setWindowTitle(QCoreApplication.translate("QGBA::LogView", u"Logs", None))
        self.groupBox.setTitle(QCoreApplication.translate("QGBA::LogView", u"Enabled Levels", None))
        self.levelDebug.setText(QCoreApplication.translate("QGBA::LogView", u"Debug", None))
        self.levelStub.setText(QCoreApplication.translate("QGBA::LogView", u"Stub", None))
        self.levelInfo.setText(QCoreApplication.translate("QGBA::LogView", u"Info", None))
        self.levelWarn.setText(QCoreApplication.translate("QGBA::LogView", u"Warning", None))
        self.levelError.setText(QCoreApplication.translate("QGBA::LogView", u"Error", None))
        self.levelFatal.setText(QCoreApplication.translate("QGBA::LogView", u"Fatal", None))
        self.levelGameError.setText(QCoreApplication.translate("QGBA::LogView", u"Game Error", None))
        self.advanced.setText(QCoreApplication.translate("QGBA::LogView", u"Advanced settings", None))
        self.clear.setText(QCoreApplication.translate("QGBA::LogView", u"Clear", None))
        self.label.setText(QCoreApplication.translate("QGBA::LogView", u"Max Lines", None))
    # retranslateUi

