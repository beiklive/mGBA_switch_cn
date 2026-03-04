# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'LoadSaveState.ui'
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
from PySide6.QtWidgets import (QApplication, QGridLayout, QLabel, QPushButton,
    QSizePolicy, QWidget)

class Ui_QGBA_LoadSaveState(object):
    def setupUi(self, QGBA__LoadSaveState):
        if not QGBA__LoadSaveState.objectName():
            QGBA__LoadSaveState.setObjectName(u"QGBA__LoadSaveState")
        QGBA__LoadSaveState.resize(760, 560)
        self.gridLayout_2 = QGridLayout(QGBA__LoadSaveState)
        self.gridLayout_2.setSpacing(2)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout_2.setContentsMargins(6, 6, 6, 6)
        self.state5 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state5.setObjectName(u"state5")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Maximum, QSizePolicy.Policy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.state5.sizePolicy().hasHeightForWidth())
        self.state5.setSizePolicy(sizePolicy)
        self.state5.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state5, 2, 1, 1, 1)

        self.lsLabel = QLabel(QGBA__LoadSaveState)
        self.lsLabel.setObjectName(u"lsLabel")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Maximum)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.lsLabel.sizePolicy().hasHeightForWidth())
        self.lsLabel.setSizePolicy(sizePolicy1)
        self.lsLabel.setStyleSheet(u"font-size: 30pt; font-weight: bold; color: white;")
        self.lsLabel.setScaledContents(False)
        self.lsLabel.setAlignment(Qt.AlignCenter)

        self.gridLayout_2.addWidget(self.lsLabel, 0, 0, 1, 3)

        self.state6 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state6.setObjectName(u"state6")
        sizePolicy.setHeightForWidth(self.state6.sizePolicy().hasHeightForWidth())
        self.state6.setSizePolicy(sizePolicy)
        self.state6.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state6, 2, 2, 1, 1)

        self.state8 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state8.setObjectName(u"state8")
        sizePolicy.setHeightForWidth(self.state8.sizePolicy().hasHeightForWidth())
        self.state8.setSizePolicy(sizePolicy)
        self.state8.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state8, 3, 1, 1, 1)

        self.state4 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state4.setObjectName(u"state4")
        sizePolicy.setHeightForWidth(self.state4.sizePolicy().hasHeightForWidth())
        self.state4.setSizePolicy(sizePolicy)
        self.state4.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state4, 2, 0, 1, 1)

        self.state1 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state1.setObjectName(u"state1")
        sizePolicy.setHeightForWidth(self.state1.sizePolicy().hasHeightForWidth())
        self.state1.setSizePolicy(sizePolicy)
        self.state1.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state1, 1, 0, 1, 1)

        self.state3 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state3.setObjectName(u"state3")
        sizePolicy.setHeightForWidth(self.state3.sizePolicy().hasHeightForWidth())
        self.state3.setSizePolicy(sizePolicy)
        self.state3.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state3, 1, 2, 1, 1)

        self.state7 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state7.setObjectName(u"state7")
        sizePolicy.setHeightForWidth(self.state7.sizePolicy().hasHeightForWidth())
        self.state7.setSizePolicy(sizePolicy)
        self.state7.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state7, 3, 0, 1, 1)

        self.state9 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state9.setObjectName(u"state9")
        sizePolicy.setHeightForWidth(self.state9.sizePolicy().hasHeightForWidth())
        self.state9.setSizePolicy(sizePolicy)
        self.state9.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state9, 3, 2, 1, 1)

        self.state2 = QGBA_SavestateButton(QGBA__LoadSaveState)
        self.state2.setObjectName(u"state2")
        sizePolicy.setHeightForWidth(self.state2.sizePolicy().hasHeightForWidth())
        self.state2.setSizePolicy(sizePolicy)
        self.state2.setIconSize(QSize(240, 160))

        self.gridLayout_2.addWidget(self.state2, 1, 1, 1, 1)

        self.cancel = QPushButton(QGBA__LoadSaveState)
        self.cancel.setObjectName(u"cancel")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.cancel.sizePolicy().hasHeightForWidth())
        self.cancel.setSizePolicy(sizePolicy2)

        self.gridLayout_2.addWidget(self.cancel, 4, 1, 1, 1, Qt.AlignHCenter)

        self.gridLayout_2.setRowStretch(0, 1)
        QWidget.setTabOrder(self.state1, self.state2)
        QWidget.setTabOrder(self.state2, self.state3)
        QWidget.setTabOrder(self.state3, self.state4)
        QWidget.setTabOrder(self.state4, self.state5)
        QWidget.setTabOrder(self.state5, self.state6)
        QWidget.setTabOrder(self.state6, self.state7)
        QWidget.setTabOrder(self.state7, self.state8)
        QWidget.setTabOrder(self.state8, self.state9)

        self.retranslateUi(QGBA__LoadSaveState)

        QMetaObject.connectSlotsByName(QGBA__LoadSaveState)
    # setupUi

    def retranslateUi(self, QGBA__LoadSaveState):
        QGBA__LoadSaveState.setWindowTitle(QCoreApplication.translate("QGBA::LoadSaveState", u"%1 State", None))
        self.state5.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state5.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"5", None))
#endif // QT_CONFIG(shortcut)
        self.lsLabel.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"%1 State", None))
        self.state6.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state6.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"6", None))
#endif // QT_CONFIG(shortcut)
        self.state8.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state8.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"8", None))
#endif // QT_CONFIG(shortcut)
        self.state4.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state4.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"4", None))
#endif // QT_CONFIG(shortcut)
        self.state1.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state1.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"1", None))
#endif // QT_CONFIG(shortcut)
        self.state3.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state3.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"3", None))
#endif // QT_CONFIG(shortcut)
        self.state7.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state7.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"7", None))
#endif // QT_CONFIG(shortcut)
        self.state9.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state9.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"9", None))
#endif // QT_CONFIG(shortcut)
        self.state2.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"No Save", None))
#if QT_CONFIG(shortcut)
        self.state2.setShortcut(QCoreApplication.translate("QGBA::LoadSaveState", u"2", None))
#endif // QT_CONFIG(shortcut)
        self.cancel.setText(QCoreApplication.translate("QGBA::LoadSaveState", u"Cancel", None))
    # retranslateUi

