# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ShortcutView.ui'
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
from PySide6.QtWidgets import (QApplication, QHBoxLayout, QHeaderView, QPushButton,
    QRadioButton, QSizePolicy, QSpacerItem, QTreeView,
    QVBoxLayout, QWidget)

class Ui_QGBA_ShortcutView(object):
    def setupUi(self, QGBA__ShortcutView):
        if not QGBA__ShortcutView.objectName():
            QGBA__ShortcutView.setObjectName(u"QGBA__ShortcutView")
        QGBA__ShortcutView.resize(432, 443)
        self.verticalLayout = QVBoxLayout(QGBA__ShortcutView)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.shortcutTable = QTreeView(QGBA__ShortcutView)
        self.shortcutTable.setObjectName(u"shortcutTable")
        self.shortcutTable.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.shortcutTable.header().setDefaultSectionSize(120)

        self.verticalLayout.addWidget(self.shortcutTable)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.keyboardButton = QRadioButton(QGBA__ShortcutView)
        self.keyboardButton.setObjectName(u"keyboardButton")
        self.keyboardButton.setChecked(True)

        self.horizontalLayout.addWidget(self.keyboardButton)

        self.gamepadButton = QRadioButton(QGBA__ShortcutView)
        self.gamepadButton.setObjectName(u"gamepadButton")

        self.horizontalLayout.addWidget(self.gamepadButton)

        self.clearButton = QPushButton(QGBA__ShortcutView)
        self.clearButton.setObjectName(u"clearButton")

        self.horizontalLayout.addWidget(self.clearButton)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer_2)

        self.keyEdit = QGBA_KeyEditor(QGBA__ShortcutView)
        self.keyEdit.setObjectName(u"keyEdit")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.keyEdit.sizePolicy().hasHeightForWidth())
        self.keyEdit.setSizePolicy(sizePolicy)

        self.horizontalLayout.addWidget(self.keyEdit)


        self.verticalLayout.addLayout(self.horizontalLayout)


        self.retranslateUi(QGBA__ShortcutView)

        QMetaObject.connectSlotsByName(QGBA__ShortcutView)
    # setupUi

    def retranslateUi(self, QGBA__ShortcutView):
        QGBA__ShortcutView.setWindowTitle(QCoreApplication.translate("QGBA::ShortcutView", u"Edit Shortcuts", None))
        self.keyboardButton.setText(QCoreApplication.translate("QGBA::ShortcutView", u"Keyboard", None))
        self.gamepadButton.setText(QCoreApplication.translate("QGBA::ShortcutView", u"Gamepad", None))
        self.clearButton.setText(QCoreApplication.translate("QGBA::ShortcutView", u"Clear", None))
    # retranslateUi

