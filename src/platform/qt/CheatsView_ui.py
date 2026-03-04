# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'CheatsView.ui'
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
from PySide6.QtWidgets import (QAbstractItemView, QApplication, QFrame, QGridLayout,
    QGroupBox, QHeaderView, QPlainTextEdit, QPushButton,
    QSizePolicy, QTreeView, QVBoxLayout, QWidget)

class Ui_QGBA_CheatsView(object):
    def setupUi(self, QGBA__CheatsView):
        if not QGBA__CheatsView.objectName():
            QGBA__CheatsView.setObjectName(u"QGBA__CheatsView")
        QGBA__CheatsView.resize(520, 455)
        self.gridLayout = QGridLayout(QGBA__CheatsView)
        self.gridLayout.setObjectName(u"gridLayout")
        self.cheatList = QTreeView(QGBA__CheatsView)
        self.cheatList.setObjectName(u"cheatList")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.MinimumExpanding, QSizePolicy.Policy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cheatList.sizePolicy().hasHeightForWidth())
        self.cheatList.setSizePolicy(sizePolicy)
        self.cheatList.setDefaultDropAction(Qt.MoveAction)
        self.cheatList.setSelectionMode(QAbstractItemView.ExtendedSelection)
        self.cheatList.setHeaderHidden(True)

        self.gridLayout.addWidget(self.cheatList, 0, 0, 7, 1)

        self.addSet = QPushButton(QGBA__CheatsView)
        self.addSet.setObjectName(u"addSet")

        self.gridLayout.addWidget(self.addSet, 0, 1, 1, 2)

        self.load = QPushButton(QGBA__CheatsView)
        self.load.setObjectName(u"load")

        self.gridLayout.addWidget(self.load, 1, 1, 1, 1)

        self.save = QPushButton(QGBA__CheatsView)
        self.save.setObjectName(u"save")

        self.gridLayout.addWidget(self.save, 1, 2, 1, 1)

        self.remove = QPushButton(QGBA__CheatsView)
        self.remove.setObjectName(u"remove")

        self.gridLayout.addWidget(self.remove, 2, 1, 1, 2)

        self.line = QFrame(QGBA__CheatsView)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.gridLayout.addWidget(self.line, 3, 1, 1, 2)

        self.codeEntry = QPlainTextEdit(QGBA__CheatsView)
        self.codeEntry.setObjectName(u"codeEntry")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Expanding)
        sizePolicy1.setHorizontalStretch(1)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.codeEntry.sizePolicy().hasHeightForWidth())
        self.codeEntry.setSizePolicy(sizePolicy1)
        self.codeEntry.setTabChangesFocus(True)
        self.codeEntry.setLineWrapMode(QPlainTextEdit.NoWrap)

        self.gridLayout.addWidget(self.codeEntry, 4, 1, 1, 2)

        self.add = QPushButton(QGBA__CheatsView)
        self.add.setObjectName(u"add")

        self.gridLayout.addWidget(self.add, 5, 1, 1, 2)

        self.typeBox = QGroupBox(QGBA__CheatsView)
        self.typeBox.setObjectName(u"typeBox")
        self.typeLayout = QVBoxLayout(self.typeBox)
        self.typeLayout.setObjectName(u"typeLayout")

        self.gridLayout.addWidget(self.typeBox, 6, 1, 1, 2)

        self.gridLayout.setRowStretch(4, 1)
        self.gridLayout.setColumnStretch(0, 4)
        QWidget.setTabOrder(self.addSet, self.load)
        QWidget.setTabOrder(self.load, self.save)
        QWidget.setTabOrder(self.save, self.remove)
        QWidget.setTabOrder(self.remove, self.codeEntry)
        QWidget.setTabOrder(self.codeEntry, self.add)

        self.retranslateUi(QGBA__CheatsView)

        QMetaObject.connectSlotsByName(QGBA__CheatsView)
    # setupUi

    def retranslateUi(self, QGBA__CheatsView):
        QGBA__CheatsView.setWindowTitle(QCoreApplication.translate("QGBA::CheatsView", u"Cheats", None))
        self.addSet.setText(QCoreApplication.translate("QGBA::CheatsView", u"Add New Code", None))
        self.load.setText(QCoreApplication.translate("QGBA::CheatsView", u"Load", None))
        self.save.setText(QCoreApplication.translate("QGBA::CheatsView", u"Save", None))
        self.remove.setText(QCoreApplication.translate("QGBA::CheatsView", u"Remove", None))
        self.codeEntry.setPlaceholderText(QCoreApplication.translate("QGBA::CheatsView", u"Enter codes here...", None))
        self.add.setText(QCoreApplication.translate("QGBA::CheatsView", u"Add Lines", None))
        self.typeBox.setTitle(QCoreApplication.translate("QGBA::CheatsView", u"Code type", None))
    # retranslateUi

