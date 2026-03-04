# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'PaletteView.ui'
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
from PySide6.QtWidgets import (QApplication, QFrame, QGroupBox, QHBoxLayout,
    QLabel, QLayout, QPushButton, QSizePolicy,
    QSpacerItem, QVBoxLayout, QWidget)

class Ui_QGBA_PaletteView(object):
    def setupUi(self, QGBA__PaletteView):
        if not QGBA__PaletteView.objectName():
            QGBA__PaletteView.setObjectName(u"QGBA__PaletteView")
        QGBA__PaletteView.resize(500, 397)
        self.verticalLayout = QVBoxLayout(QGBA__PaletteView)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setSizeConstraint(QLayout.SetFixedSize)
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalSpacer_2 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer_2)

        self.groupBox = QGroupBox(QGBA__PaletteView)
        self.groupBox.setObjectName(u"groupBox")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy)
        self.verticalLayout_3 = QVBoxLayout(self.groupBox)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.bgGrid = QGBA_Swatch(self.groupBox)
        self.bgGrid.setObjectName(u"bgGrid")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.MinimumExpanding, QSizePolicy.Policy.MinimumExpanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.bgGrid.sizePolicy().hasHeightForWidth())
        self.bgGrid.setSizePolicy(sizePolicy1)

        self.verticalLayout_3.addWidget(self.bgGrid)


        self.horizontalLayout.addWidget(self.groupBox)

        self.horizontalSpacer = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer)

        self.groupBox_2 = QGroupBox(QGBA__PaletteView)
        self.groupBox_2.setObjectName(u"groupBox_2")
        sizePolicy.setHeightForWidth(self.groupBox_2.sizePolicy().hasHeightForWidth())
        self.groupBox_2.setSizePolicy(sizePolicy)
        self.verticalLayout_4 = QVBoxLayout(self.groupBox_2)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.objGrid = QGBA_Swatch(self.groupBox_2)
        self.objGrid.setObjectName(u"objGrid")
        sizePolicy1.setHeightForWidth(self.objGrid.sizePolicy().hasHeightForWidth())
        self.objGrid.setSizePolicy(sizePolicy1)

        self.verticalLayout_4.addWidget(self.objGrid)


        self.horizontalLayout.addWidget(self.groupBox_2)

        self.horizontalSpacer_3 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer_3)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.verticalSpacer = QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer)

        self.groupBox_3 = QGroupBox(QGBA__PaletteView)
        self.groupBox_3.setObjectName(u"groupBox_3")
        self.horizontalLayout_4 = QHBoxLayout(self.groupBox_3)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.selected = QGBA_Swatch(self.groupBox_3)
        self.selected.setObjectName(u"selected")
        sizePolicy.setHeightForWidth(self.selected.sizePolicy().hasHeightForWidth())
        self.selected.setSizePolicy(sizePolicy)
        self.selected.setMinimumSize(QSize(64, 64))

        self.horizontalLayout_4.addWidget(self.selected)

        self.line_3 = QFrame(self.groupBox_3)
        self.line_3.setObjectName(u"line_3")
        self.line_3.setFrameShape(QFrame.Shape.VLine)
        self.line_3.setFrameShadow(QFrame.Shadow.Sunken)

        self.horizontalLayout_4.addWidget(self.line_3)

        self.verticalLayout_9 = QVBoxLayout()
        self.verticalLayout_9.setObjectName(u"verticalLayout_9")
        self.label_4 = QLabel(self.groupBox_3)
        self.label_4.setObjectName(u"label_4")

        self.verticalLayout_9.addWidget(self.label_4)

        self.label_5 = QLabel(self.groupBox_3)
        self.label_5.setObjectName(u"label_5")

        self.verticalLayout_9.addWidget(self.label_5)

        self.label_6 = QLabel(self.groupBox_3)
        self.label_6.setObjectName(u"label_6")

        self.verticalLayout_9.addWidget(self.label_6)


        self.horizontalLayout_4.addLayout(self.verticalLayout_9)

        self.verticalLayout_10 = QVBoxLayout()
        self.verticalLayout_10.setObjectName(u"verticalLayout_10")
        self.verticalLayout_10.setContentsMargins(8, -1, -1, -1)
        self.r = QLabel(self.groupBox_3)
        self.r.setObjectName(u"r")
        self.r.setText(u"0x00 (00)")
        self.r.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_10.addWidget(self.r)

        self.g = QLabel(self.groupBox_3)
        self.g.setObjectName(u"g")
        self.g.setText(u"0x00 (00)")
        self.g.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_10.addWidget(self.g)

        self.b = QLabel(self.groupBox_3)
        self.b.setObjectName(u"b")
        self.b.setText(u"0x00 (00)")
        self.b.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_10.addWidget(self.b)


        self.horizontalLayout_4.addLayout(self.verticalLayout_10)

        self.line_4 = QFrame(self.groupBox_3)
        self.line_4.setObjectName(u"line_4")
        self.line_4.setFrameShape(QFrame.Shape.VLine)
        self.line_4.setFrameShadow(QFrame.Shadow.Sunken)

        self.horizontalLayout_4.addWidget(self.line_4)

        self.verticalLayout_11 = QVBoxLayout()
        self.verticalLayout_11.setObjectName(u"verticalLayout_11")
        self.label_14 = QLabel(self.groupBox_3)
        self.label_14.setObjectName(u"label_14")

        self.verticalLayout_11.addWidget(self.label_14)

        self.label_15 = QLabel(self.groupBox_3)
        self.label_15.setObjectName(u"label_15")

        self.verticalLayout_11.addWidget(self.label_15)

        self.label_16 = QLabel(self.groupBox_3)
        self.label_16.setObjectName(u"label_16")

        self.verticalLayout_11.addWidget(self.label_16)


        self.horizontalLayout_4.addLayout(self.verticalLayout_11)

        self.verticalLayout_12 = QVBoxLayout()
        self.verticalLayout_12.setObjectName(u"verticalLayout_12")
        self.verticalLayout_12.setContentsMargins(8, -1, -1, -1)
        self.value = QLabel(self.groupBox_3)
        self.value.setObjectName(u"value")
        self.value.setText(u"0x0000")
        self.value.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.value.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_12.addWidget(self.value)

        self.hexcode = QLabel(self.groupBox_3)
        self.hexcode.setObjectName(u"hexcode")
        self.hexcode.setText(u"#000000")
        self.hexcode.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.hexcode.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_12.addWidget(self.hexcode)

        self.index = QLabel(self.groupBox_3)
        self.index.setObjectName(u"index")
        self.index.setText(u"0x000 (000)")
        self.index.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.index.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_12.addWidget(self.index)


        self.horizontalLayout_4.addLayout(self.verticalLayout_12)


        self.verticalLayout.addWidget(self.groupBox_3)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalSpacer_4 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_4)

        self.exportBG = QPushButton(QGBA__PaletteView)
        self.exportBG.setObjectName(u"exportBG")

        self.horizontalLayout_3.addWidget(self.exportBG)

        self.horizontalSpacer_5 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_5)

        self.exportOBJ = QPushButton(QGBA__PaletteView)
        self.exportOBJ.setObjectName(u"exportOBJ")

        self.horizontalLayout_3.addWidget(self.exportOBJ)

        self.horizontalSpacer_6 = QSpacerItem(0, 0, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_6)


        self.verticalLayout.addLayout(self.horizontalLayout_3)


        self.retranslateUi(QGBA__PaletteView)

        QMetaObject.connectSlotsByName(QGBA__PaletteView)
    # setupUi

    def retranslateUi(self, QGBA__PaletteView):
        QGBA__PaletteView.setWindowTitle(QCoreApplication.translate("QGBA::PaletteView", u"Palette", None))
        self.groupBox.setTitle(QCoreApplication.translate("QGBA::PaletteView", u"Background", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("QGBA::PaletteView", u"Objects", None))
        self.groupBox_3.setTitle(QCoreApplication.translate("QGBA::PaletteView", u"Selection", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::PaletteView", u"Red", None))
        self.label_5.setText(QCoreApplication.translate("QGBA::PaletteView", u"Green", None))
        self.label_6.setText(QCoreApplication.translate("QGBA::PaletteView", u"Blue", None))
        self.label_14.setText(QCoreApplication.translate("QGBA::PaletteView", u"16-bit value", None))
        self.label_15.setText(QCoreApplication.translate("QGBA::PaletteView", u"Hex code", None))
        self.label_16.setText(QCoreApplication.translate("QGBA::PaletteView", u"Palette index", None))
        self.exportBG.setText(QCoreApplication.translate("QGBA::PaletteView", u"Export BG", None))
        self.exportOBJ.setText(QCoreApplication.translate("QGBA::PaletteView", u"Export OBJ", None))
    # retranslateUi

