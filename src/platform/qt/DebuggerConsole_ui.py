# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'DebuggerConsole.ui'
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
from PySide6.QtWidgets import (QApplication, QGridLayout, QLineEdit, QPushButton,
    QSizePolicy, QWidget)

class Ui_QGBA_DebuggerConsole(object):
    def setupUi(self, QGBA__DebuggerConsole):
        if not QGBA__DebuggerConsole.objectName():
            QGBA__DebuggerConsole.setObjectName(u"QGBA__DebuggerConsole")
        QGBA__DebuggerConsole.resize(480, 500)
        self.gridLayout = QGridLayout(QGBA__DebuggerConsole)
        self.gridLayout.setObjectName(u"gridLayout")
        self.prompt = QLineEdit(QGBA__DebuggerConsole)
        self.prompt.setObjectName(u"prompt")

        self.gridLayout.addWidget(self.prompt, 1, 0, 1, 1)

        self.breakpoint = QPushButton(QGBA__DebuggerConsole)
        self.breakpoint.setObjectName(u"breakpoint")

        self.gridLayout.addWidget(self.breakpoint, 1, 1, 1, 1)

        self.log = QGBA_LogWidget(QGBA__DebuggerConsole)
        self.log.setObjectName(u"log")
        self.log.setReadOnly(True)

        self.gridLayout.addWidget(self.log, 0, 0, 1, 2)


        self.retranslateUi(QGBA__DebuggerConsole)

        QMetaObject.connectSlotsByName(QGBA__DebuggerConsole)
    # setupUi

    def retranslateUi(self, QGBA__DebuggerConsole):
        QGBA__DebuggerConsole.setWindowTitle(QCoreApplication.translate("QGBA::DebuggerConsole", u"Debugger", None))
        self.prompt.setPlaceholderText(QCoreApplication.translate("QGBA::DebuggerConsole", u"Enter command (try `help` for more info)", None))
        self.breakpoint.setText(QCoreApplication.translate("QGBA::DebuggerConsole", u"Break", None))
    # retranslateUi

