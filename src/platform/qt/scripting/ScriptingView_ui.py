# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ScriptingView.ui'
##
## Created by: Qt User Interface Compiler version 6.8.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QAction, QBrush, QColor, QConicalGradient,
    QCursor, QFont, QFontDatabase, QGradient,
    QIcon, QImage, QKeySequence, QLinearGradient,
    QPainter, QPalette, QPixmap, QRadialGradient,
    QTransform)
from PySide6.QtWidgets import (QApplication, QGridLayout, QLineEdit, QListView,
    QMainWindow, QMenu, QMenuBar, QPlainTextEdit,
    QPushButton, QSizePolicy, QSplitter, QStatusBar,
    QWidget)

class Ui_QGBA_ScriptingView(object):
    def setupUi(self, QGBA__ScriptingView):
        if not QGBA__ScriptingView.objectName():
            QGBA__ScriptingView.setObjectName(u"QGBA__ScriptingView")
        QGBA__ScriptingView.resize(843, 637)
        self.load = QAction(QGBA__ScriptingView)
        self.load.setObjectName(u"load")
        self.reset = QAction(QGBA__ScriptingView)
        self.reset.setObjectName(u"reset")
        self.action0 = QAction(QGBA__ScriptingView)
        self.action0.setObjectName(u"action0")
        self.centralwidget = QWidget(QGBA__ScriptingView)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout = QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.splitter = QSplitter(self.centralwidget)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Horizontal)
        self.buffers = QListView(self.splitter)
        self.buffers.setObjectName(u"buffers")
        self.buffers.setMinimumSize(QSize(90, 0))
        self.buffers.setMaximumSize(QSize(200, 16777215))
        self.splitter.addWidget(self.buffers)
        self.verticalLayoutWidget = QWidget(self.splitter)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.gridLayout_3 = QGridLayout(self.verticalLayoutWidget)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.gridLayout_3.setContentsMargins(0, 0, 0, 0)
        self.prompt = QLineEdit(self.verticalLayoutWidget)
        self.prompt.setObjectName(u"prompt")

        self.gridLayout_3.addWidget(self.prompt, 1, 0, 1, 1)

        self.runButton = QPushButton(self.verticalLayoutWidget)
        self.runButton.setObjectName(u"runButton")

        self.gridLayout_3.addWidget(self.runButton, 1, 1, 1, 1)

        self.splitter_1 = QSplitter(self.verticalLayoutWidget)
        self.splitter_1.setObjectName(u"splitter_1")
        self.splitter_1.setOrientation(Qt.Vertical)
        self.buffer = QPlainTextEdit(self.splitter_1)
        self.buffer.setObjectName(u"buffer")
        self.buffer.setLineWrapMode(QPlainTextEdit.NoWrap)
        self.buffer.setReadOnly(True)
        self.splitter_1.addWidget(self.buffer)
        self.log = QGBA_LogWidget(self.splitter_1)
        self.log.setObjectName(u"log")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.MinimumExpanding, QSizePolicy.Policy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.log.sizePolicy().hasHeightForWidth())
        self.log.setSizePolicy(sizePolicy)
        self.log.setReadOnly(True)
        self.splitter_1.addWidget(self.log)

        self.gridLayout_3.addWidget(self.splitter_1, 0, 0, 1, 2)

        self.splitter.addWidget(self.verticalLayoutWidget)

        self.gridLayout.addWidget(self.splitter, 0, 0, 3, 1)

        QGBA__ScriptingView.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(QGBA__ScriptingView)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 800, 29))
        self.menuFile = QMenu(self.menubar)
        self.menuFile.setObjectName(u"menuFile")
        self.mru = QMenu(self.menuFile)
        self.mru.setObjectName(u"mru")
        QGBA__ScriptingView.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(QGBA__ScriptingView)
        self.statusbar.setObjectName(u"statusbar")
        QGBA__ScriptingView.setStatusBar(self.statusbar)

        self.menubar.addAction(self.menuFile.menuAction())
        self.menuFile.addAction(self.load)
        self.menuFile.addAction(self.mru.menuAction())
        self.menuFile.addSeparator()
        self.menuFile.addAction(self.reset)

        self.retranslateUi(QGBA__ScriptingView)

        QMetaObject.connectSlotsByName(QGBA__ScriptingView)
    # setupUi

    def retranslateUi(self, QGBA__ScriptingView):
        QGBA__ScriptingView.setWindowTitle(QCoreApplication.translate("QGBA::ScriptingView", u"Scripting", None))
        self.load.setText(QCoreApplication.translate("QGBA::ScriptingView", u"Load script...", None))
        self.reset.setText(QCoreApplication.translate("QGBA::ScriptingView", u"&Reset", None))
        self.action0.setText(QCoreApplication.translate("QGBA::ScriptingView", u"0", None))
        self.runButton.setText(QCoreApplication.translate("QGBA::ScriptingView", u"Run", None))
        self.menuFile.setTitle(QCoreApplication.translate("QGBA::ScriptingView", u"File", None))
        self.mru.setTitle(QCoreApplication.translate("QGBA::ScriptingView", u"Load recent script", None))
    # retranslateUi

