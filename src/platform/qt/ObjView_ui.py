# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ObjView.ui'
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
from PySide6.QtWidgets import (QApplication, QCheckBox, QFrame, QGridLayout,
    QGroupBox, QHBoxLayout, QLabel, QListView,
    QListWidget, QListWidgetItem, QPushButton, QSizePolicy,
    QSpacerItem, QSpinBox, QWidget)

class Ui_QGBA_ObjView(object):
    def setupUi(self, QGBA__ObjView):
        if not QGBA__ObjView.objectName():
            QGBA__ObjView.setObjectName(u"QGBA__ObjView")
        QGBA__ObjView.resize(800, 730)
        self.gridLayout = QGridLayout(QGBA__ObjView)
        self.gridLayout.setObjectName(u"gridLayout")
        self.frame = QFrame(QGBA__ObjView)
        self.frame.setObjectName(u"frame")
        self.frame.setFrameShape(QFrame.StyledPanel)
        self.gridLayout_2 = QGridLayout(self.frame)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.tiles = QGBA_TilePainter(self.frame)
        self.tiles.setObjectName(u"tiles")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.tiles.sizePolicy().hasHeightForWidth())
        self.tiles.setSizePolicy(sizePolicy)
        self.tiles.setMinimumSize(QSize(8, 8))

        self.gridLayout_2.addWidget(self.tiles, 0, 0, 1, 1, Qt.AlignHCenter|Qt.AlignVCenter)


        self.gridLayout.addWidget(self.frame, 0, 2, 4, 2)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.objId = QSpinBox(QGBA__ObjView)
        self.objId.setObjectName(u"objId")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Maximum, QSizePolicy.Policy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.objId.sizePolicy().hasHeightForWidth())
        self.objId.setSizePolicy(sizePolicy1)
        self.objId.setMaximum(127)

        self.horizontalLayout_2.addWidget(self.objId)

        self.label_3 = QLabel(QGBA__ObjView)
        self.label_3.setObjectName(u"label_3")

        self.horizontalLayout_2.addWidget(self.label_3)

        self.address = QLabel(QGBA__ObjView)
        self.address.setObjectName(u"address")
        self.address.setText(u"0x07000000")
        self.address.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.address.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_2.addWidget(self.address)


        self.gridLayout.addLayout(self.horizontalLayout_2, 0, 0, 1, 1)

        self.copyButton = QPushButton(QGBA__ObjView)
        self.copyButton.setObjectName(u"copyButton")

        self.gridLayout.addWidget(self.copyButton, 4, 3, 1, 1)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.magnification = QSpinBox(QGBA__ObjView)
        self.magnification.setObjectName(u"magnification")
        sizePolicy.setHeightForWidth(self.magnification.sizePolicy().hasHeightForWidth())
        self.magnification.setSizePolicy(sizePolicy)
        self.magnification.setSuffix(u"\u00d7")
        self.magnification.setMinimum(1)
        self.magnification.setMaximum(8)

        self.horizontalLayout_4.addWidget(self.magnification)

        self.label_2 = QLabel(QGBA__ObjView)
        self.label_2.setObjectName(u"label_2")

        self.horizontalLayout_4.addWidget(self.label_2)


        self.gridLayout.addLayout(self.horizontalLayout_4, 1, 0, 1, 1)

        self.groupBox = QGroupBox(QGBA__ObjView)
        self.groupBox.setObjectName(u"groupBox")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy2)
        self.gridLayout_4 = QGridLayout(self.groupBox)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.label = QLabel(self.groupBox)
        self.label.setObjectName(u"label")

        self.horizontalLayout.addWidget(self.label)

        self.horizontalSpacer = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer)

        self.x = QLabel(self.groupBox)
        self.x.setObjectName(u"x")
        self.x.setMinimumSize(QSize(20, 0))
        self.x.setText(u"0")
        self.x.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.x.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout.addWidget(self.x)

        self.tileId_3 = QLabel(self.groupBox)
        self.tileId_3.setObjectName(u"tileId_3")
        self.tileId_3.setText(u", ")
        self.tileId_3.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout.addWidget(self.tileId_3)

        self.y = QLabel(self.groupBox)
        self.y.setObjectName(u"y")
        self.y.setMinimumSize(QSize(20, 0))
        self.y.setText(u"0")
        self.y.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.y.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout.addWidget(self.y)


        self.gridLayout_4.addLayout(self.horizontalLayout, 0, 0, 1, 1)

        self.line_2 = QFrame(self.groupBox)
        self.line_2.setObjectName(u"line_2")
        self.line_2.setFrameShape(QFrame.Shape.VLine)
        self.line_2.setFrameShadow(QFrame.Shadow.Sunken)

        self.gridLayout_4.addWidget(self.line_2, 0, 1, 2, 1)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.label_4 = QLabel(self.groupBox)
        self.label_4.setObjectName(u"label_4")

        self.horizontalLayout_3.addWidget(self.label_4)

        self.horizontalSpacer_2 = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_2)

        self.w = QLabel(self.groupBox)
        self.w.setObjectName(u"w")
        self.w.setMinimumSize(QSize(20, 0))
        self.w.setText(u"8")
        self.w.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.w.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_3.addWidget(self.w)

        self.tileId_5 = QLabel(self.groupBox)
        self.tileId_5.setObjectName(u"tileId_5")
        self.tileId_5.setText(u"\u00d7")
        self.tileId_5.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_3.addWidget(self.tileId_5)

        self.h = QLabel(self.groupBox)
        self.h.setObjectName(u"h")
        self.h.setMinimumSize(QSize(20, 0))
        self.h.setText(u"8")
        self.h.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.h.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_3.addWidget(self.h)


        self.gridLayout_4.addLayout(self.horizontalLayout_3, 1, 0, 1, 1)

        self.gridLayout_5 = QGridLayout()
        self.gridLayout_5.setObjectName(u"gridLayout_5")
        self.xformPC = QLabel(self.groupBox)
        self.xformPC.setObjectName(u"xformPC")
        self.xformPC.setText(u"+0.00")
        self.xformPC.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.gridLayout_5.addWidget(self.xformPC, 0, 3, 1, 1)

        self.xformPA = QLabel(self.groupBox)
        self.xformPA.setObjectName(u"xformPA")
        self.xformPA.setText(u"+1.00")
        self.xformPA.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.gridLayout_5.addWidget(self.xformPA, 0, 2, 1, 1)

        self.label_10 = QLabel(self.groupBox)
        self.label_10.setObjectName(u"label_10")

        self.gridLayout_5.addWidget(self.label_10, 0, 0, 1, 1)

        self.xformPD = QLabel(self.groupBox)
        self.xformPD.setObjectName(u"xformPD")
        self.xformPD.setText(u"+1.00")
        self.xformPD.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.gridLayout_5.addWidget(self.xformPD, 1, 3, 1, 1)

        self.horizontalSpacer_8 = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.gridLayout_5.addItem(self.horizontalSpacer_8, 0, 1, 1, 1)

        self.xformPB = QLabel(self.groupBox)
        self.xformPB.setObjectName(u"xformPB")
        self.xformPB.setText(u"+0.00")
        self.xformPB.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.gridLayout_5.addWidget(self.xformPB, 1, 2, 1, 1)


        self.gridLayout_4.addLayout(self.gridLayout_5, 0, 2, 2, 1)


        self.gridLayout.addWidget(self.groupBox, 2, 0, 1, 1)

        self.objList = QListWidget(QGBA__ObjView)
        self.objList.setObjectName(u"objList")
        self.objList.setIconSize(QSize(64, 64))
        self.objList.setFlow(QListView.LeftToRight)
        self.objList.setResizeMode(QListView.Adjust)
        self.objList.setGridSize(QSize(64, 96))
        self.objList.setViewMode(QListView.IconMode)
        self.objList.setUniformItemSizes(True)

        self.gridLayout.addWidget(self.objList, 5, 0, 1, 4)

        self.exportButton = QPushButton(QGBA__ObjView)
        self.exportButton.setObjectName(u"exportButton")

        self.gridLayout.addWidget(self.exportButton, 4, 2, 1, 1)

        self.groupBox_2 = QGroupBox(QGBA__ObjView)
        self.groupBox_2.setObjectName(u"groupBox_2")
        sizePolicy2.setHeightForWidth(self.groupBox_2.sizePolicy().hasHeightForWidth())
        self.groupBox_2.setSizePolicy(sizePolicy2)
        self.gridLayout_3 = QGridLayout(self.groupBox_2)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.label_6 = QLabel(self.groupBox_2)
        self.label_6.setObjectName(u"label_6")

        self.horizontalLayout_6.addWidget(self.label_6)

        self.horizontalSpacer_4 = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_6.addItem(self.horizontalSpacer_4)

        self.transform = QLabel(self.groupBox_2)
        self.transform.setObjectName(u"transform")
        self.transform.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_6.addWidget(self.transform)


        self.gridLayout_3.addLayout(self.horizontalLayout_6, 2, 0, 1, 1)

        self.horizontalLayout_16 = QHBoxLayout()
        self.horizontalLayout_16.setObjectName(u"horizontalLayout_16")
        self.label_16 = QLabel(self.groupBox_2)
        self.label_16.setObjectName(u"label_16")

        self.horizontalLayout_16.addWidget(self.label_16)

        self.horizontalSpacer_13 = QSpacerItem(10, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_16.addItem(self.horizontalSpacer_13)

        self.palette = QLabel(self.groupBox_2)
        self.palette.setObjectName(u"palette")
        self.palette.setText(u"0")
        self.palette.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.palette.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_16.addWidget(self.palette)


        self.gridLayout_3.addLayout(self.horizontalLayout_16, 1, 0, 1, 1)

        self.horizontalLayout_18 = QHBoxLayout()
        self.horizontalLayout_18.setObjectName(u"horizontalLayout_18")
        self.label_18 = QLabel(self.groupBox_2)
        self.label_18.setObjectName(u"label_18")

        self.horizontalLayout_18.addWidget(self.label_18)

        self.horizontalSpacer_15 = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_18.addItem(self.horizontalSpacer_15)

        self.doubleSize = QCheckBox(self.groupBox_2)
        self.doubleSize.setObjectName(u"doubleSize")
        self.doubleSize.setEnabled(False)

        self.horizontalLayout_18.addWidget(self.doubleSize)


        self.gridLayout_3.addLayout(self.horizontalLayout_18, 2, 2, 1, 1)

        self.line = QFrame(self.groupBox_2)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.VLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.gridLayout_3.addWidget(self.line, 0, 1, 4, 1)

        self.horizontalLayout_5 = QHBoxLayout()
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.label_5 = QLabel(self.groupBox_2)
        self.label_5.setObjectName(u"label_5")

        self.horizontalLayout_5.addWidget(self.label_5)

        self.horizontalSpacer_3 = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_5.addItem(self.horizontalSpacer_3)

        self.flippedH = QCheckBox(self.groupBox_2)
        self.flippedH.setObjectName(u"flippedH")
        self.flippedH.setEnabled(False)

        self.horizontalLayout_5.addWidget(self.flippedH)

        self.flippedV = QCheckBox(self.groupBox_2)
        self.flippedV.setObjectName(u"flippedV")
        self.flippedV.setEnabled(False)

        self.horizontalLayout_5.addWidget(self.flippedV)


        self.gridLayout_3.addLayout(self.horizontalLayout_5, 0, 2, 1, 1)

        self.horizontalLayout_7 = QHBoxLayout()
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.label_7 = QLabel(self.groupBox_2)
        self.label_7.setObjectName(u"label_7")

        self.horizontalLayout_7.addWidget(self.label_7)

        self.horizontalSpacer_5 = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_7.addItem(self.horizontalSpacer_5)

        self.mode = QLabel(self.groupBox_2)
        self.mode.setObjectName(u"mode")
        self.mode.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_7.addWidget(self.mode)


        self.gridLayout_3.addLayout(self.horizontalLayout_7, 3, 0, 1, 1)

        self.horizontalLayout_15 = QHBoxLayout()
        self.horizontalLayout_15.setObjectName(u"horizontalLayout_15")
        self.label_15 = QLabel(self.groupBox_2)
        self.label_15.setObjectName(u"label_15")

        self.horizontalLayout_15.addWidget(self.label_15)

        self.horizontalSpacer_12 = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_15.addItem(self.horizontalSpacer_12)

        self.mosaic = QCheckBox(self.groupBox_2)
        self.mosaic.setObjectName(u"mosaic")
        self.mosaic.setEnabled(False)

        self.horizontalLayout_15.addWidget(self.mosaic)


        self.gridLayout_3.addLayout(self.horizontalLayout_15, 3, 2, 1, 1)

        self.horizontalLayout_14 = QHBoxLayout()
        self.horizontalLayout_14.setObjectName(u"horizontalLayout_14")
        self.label_14 = QLabel(self.groupBox_2)
        self.label_14.setObjectName(u"label_14")

        self.horizontalLayout_14.addWidget(self.label_14)

        self.horizontalSpacer_11 = QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_14.addItem(self.horizontalSpacer_11)

        self.enabled = QCheckBox(self.groupBox_2)
        self.enabled.setObjectName(u"enabled")
        self.enabled.setEnabled(False)

        self.horizontalLayout_14.addWidget(self.enabled)


        self.gridLayout_3.addLayout(self.horizontalLayout_14, 1, 2, 1, 1)

        self.horizontalLayout_17 = QHBoxLayout()
        self.horizontalLayout_17.setObjectName(u"horizontalLayout_17")
        self.label_17 = QLabel(self.groupBox_2)
        self.label_17.setObjectName(u"label_17")

        self.horizontalLayout_17.addWidget(self.label_17)

        self.horizontalSpacer_14 = QSpacerItem(10, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_17.addItem(self.horizontalSpacer_14)

        self.priority = QLabel(self.groupBox_2)
        self.priority.setObjectName(u"priority")
        self.priority.setText(u"0")
        self.priority.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.priority.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_17.addWidget(self.priority)


        self.gridLayout_3.addLayout(self.horizontalLayout_17, 0, 0, 1, 1)


        self.gridLayout.addWidget(self.groupBox_2, 3, 0, 2, 1)

        self.tile = QGBA_AssetTile(QGBA__ObjView)
        self.tile.setObjectName(u"tile")

        self.gridLayout.addWidget(self.tile, 0, 1, 5, 1)

        self.gridLayout.setColumnStretch(3, 1)

        self.retranslateUi(QGBA__ObjView)
        self.magnification.valueChanged.connect(self.tiles.setTileMagnification)

        QMetaObject.connectSlotsByName(QGBA__ObjView)
    # setupUi

    def retranslateUi(self, QGBA__ObjView):
        QGBA__ObjView.setWindowTitle(QCoreApplication.translate("QGBA::ObjView", u"Sprites", None))
        self.label_3.setText(QCoreApplication.translate("QGBA::ObjView", u"Address", None))
        self.copyButton.setText(QCoreApplication.translate("QGBA::ObjView", u"Copy", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::ObjView", u"Magnification", None))
        self.groupBox.setTitle(QCoreApplication.translate("QGBA::ObjView", u"Geometry", None))
        self.label.setText(QCoreApplication.translate("QGBA::ObjView", u"Position", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::ObjView", u"Dimensions", None))
        self.label_10.setText(QCoreApplication.translate("QGBA::ObjView", u"Matrix", None))
        self.exportButton.setText(QCoreApplication.translate("QGBA::ObjView", u"Export", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("QGBA::ObjView", u"Attributes", None))
        self.label_6.setText(QCoreApplication.translate("QGBA::ObjView", u"Transform", None))
        self.transform.setText(QCoreApplication.translate("QGBA::ObjView", u"Off", None))
        self.label_16.setText(QCoreApplication.translate("QGBA::ObjView", u"Palette", None))
        self.label_18.setText(QCoreApplication.translate("QGBA::ObjView", u"Double Size", None))
        self.doubleSize.setText("")
        self.label_5.setText(QCoreApplication.translate("QGBA::ObjView", u"Flipped", None))
        self.flippedH.setText(QCoreApplication.translate("QGBA::ObjView", u"H", None))
#if QT_CONFIG(shortcut)
        self.flippedH.setShortcut(QCoreApplication.translate("QGBA::ObjView", u"Return, Ctrl+R", None))
#endif // QT_CONFIG(shortcut)
        self.flippedV.setText(QCoreApplication.translate("QGBA::ObjView", u"V", None))
#if QT_CONFIG(shortcut)
        self.flippedV.setShortcut(QCoreApplication.translate("QGBA::ObjView", u"Return, Ctrl+R", None))
#endif // QT_CONFIG(shortcut)
        self.label_7.setText(QCoreApplication.translate("QGBA::ObjView", u"Mode", None))
        self.mode.setText(QCoreApplication.translate("QGBA::ObjView", u"Normal", None))
        self.label_15.setText(QCoreApplication.translate("QGBA::ObjView", u"Mosaic", None))
        self.mosaic.setText("")
#if QT_CONFIG(shortcut)
        self.mosaic.setShortcut(QCoreApplication.translate("QGBA::ObjView", u"Return, Ctrl+R", None))
#endif // QT_CONFIG(shortcut)
        self.label_14.setText(QCoreApplication.translate("QGBA::ObjView", u"Enabled", None))
        self.enabled.setText("")
        self.label_17.setText(QCoreApplication.translate("QGBA::ObjView", u"Priority", None))
        self.tile.setTitle(QCoreApplication.translate("QGBA::ObjView", u"Tile", None))
    # retranslateUi

