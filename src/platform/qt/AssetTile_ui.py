# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'AssetTile.ui'
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
from PySide6.QtWidgets import (QApplication, QFrame, QHBoxLayout, QLabel,
    QSizePolicy, QVBoxLayout, QWidget)

class Ui_QGBA_AssetTile(object):
    def setupUi(self, QGBA__AssetTile):
        if not QGBA__AssetTile.objectName():
            QGBA__AssetTile.setObjectName(u"QGBA__AssetTile")
        QGBA__AssetTile.resize(241, 406)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(QGBA__AssetTile.sizePolicy().hasHeightForWidth())
        QGBA__AssetTile.setSizePolicy(sizePolicy)
        QGBA__AssetTile.setWindowTitle(u"AssetTile")
        self.verticalLayout = QVBoxLayout(QGBA__AssetTile)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.preview = QGBA_Swatch(QGBA__AssetTile)
        self.preview.setObjectName(u"preview")
        self.preview.setMinimumSize(QSize(87, 87))

        self.verticalLayout.addWidget(self.preview, 0, Qt.AlignHCenter)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.label = QLabel(QGBA__AssetTile)
        self.label.setObjectName(u"label")

        self.horizontalLayout.addWidget(self.label)

        self.tileId = QLabel(QGBA__AssetTile)
        self.tileId.setObjectName(u"tileId")
        self.tileId.setText(u"0")
        self.tileId.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.tileId.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout.addWidget(self.tileId)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.label_2 = QLabel(QGBA__AssetTile)
        self.label_2.setObjectName(u"label_2")

        self.horizontalLayout_4.addWidget(self.label_2)

        self.paletteId = QLabel(QGBA__AssetTile)
        self.paletteId.setObjectName(u"paletteId")
        self.paletteId.setText(u"0")
        self.paletteId.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.paletteId.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_4.addWidget(self.paletteId)


        self.verticalLayout.addLayout(self.horizontalLayout_4)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.label_3 = QLabel(QGBA__AssetTile)
        self.label_3.setObjectName(u"label_3")

        self.horizontalLayout_2.addWidget(self.label_3)

        self.address = QLabel(QGBA__AssetTile)
        self.address.setObjectName(u"address")
        self.address.setText(u"0x06000000")
        self.address.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.address.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.horizontalLayout_2.addWidget(self.address)


        self.verticalLayout.addLayout(self.horizontalLayout_2)

        self.line = QFrame(QGBA__AssetTile)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.verticalLayout.addWidget(self.line)

        self.color = QGBA_Swatch(QGBA__AssetTile)
        self.color.setObjectName(u"color")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Preferred)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.color.sizePolicy().hasHeightForWidth())
        self.color.setSizePolicy(sizePolicy1)
        self.color.setMinimumSize(QSize(50, 50))

        self.verticalLayout.addWidget(self.color, 0, Qt.AlignHCenter)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.verticalLayout_9 = QVBoxLayout()
        self.verticalLayout_9.setObjectName(u"verticalLayout_9")
        self.label_4 = QLabel(QGBA__AssetTile)
        self.label_4.setObjectName(u"label_4")

        self.verticalLayout_9.addWidget(self.label_4)

        self.label_5 = QLabel(QGBA__AssetTile)
        self.label_5.setObjectName(u"label_5")

        self.verticalLayout_9.addWidget(self.label_5)

        self.label_6 = QLabel(QGBA__AssetTile)
        self.label_6.setObjectName(u"label_6")

        self.verticalLayout_9.addWidget(self.label_6)


        self.horizontalLayout_3.addLayout(self.verticalLayout_9)

        self.verticalLayout_10 = QVBoxLayout()
        self.verticalLayout_10.setObjectName(u"verticalLayout_10")
        self.verticalLayout_10.setContentsMargins(8, -1, -1, -1)
        self.r = QLabel(QGBA__AssetTile)
        self.r.setObjectName(u"r")
        self.r.setText(u"0x00 (00)")
        self.r.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_10.addWidget(self.r)

        self.g = QLabel(QGBA__AssetTile)
        self.g.setObjectName(u"g")
        self.g.setText(u"0x00 (00)")
        self.g.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_10.addWidget(self.g)

        self.b = QLabel(QGBA__AssetTile)
        self.b.setObjectName(u"b")
        self.b.setText(u"0x00 (00)")
        self.b.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.verticalLayout_10.addWidget(self.b)


        self.horizontalLayout_3.addLayout(self.verticalLayout_10)


        self.verticalLayout.addLayout(self.horizontalLayout_3)


        self.retranslateUi(QGBA__AssetTile)

        QMetaObject.connectSlotsByName(QGBA__AssetTile)
    # setupUi

    def retranslateUi(self, QGBA__AssetTile):
        QGBA__AssetTile.setTitle("")
        self.label.setText(QCoreApplication.translate("QGBA::AssetTile", u"Tile #", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::AssetTile", u"Palette #", None))
        self.label_3.setText(QCoreApplication.translate("QGBA::AssetTile", u"Address", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::AssetTile", u"Red", None))
        self.label_5.setText(QCoreApplication.translate("QGBA::AssetTile", u"Green", None))
        self.label_6.setText(QCoreApplication.translate("QGBA::AssetTile", u"Blue", None))
    # retranslateUi

