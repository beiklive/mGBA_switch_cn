# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'TileView.ui'
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
from PySide6.QtWidgets import (QApplication, QButtonGroup, QCheckBox, QFormLayout,
    QFrame, QGridLayout, QGroupBox, QLabel,
    QPushButton, QRadioButton, QScrollArea, QSizePolicy,
    QSpinBox, QVBoxLayout, QWidget)

class Ui_QGBA_TileView(object):
    def setupUi(self, QGBA__TileView):
        if not QGBA__TileView.objectName():
            QGBA__TileView.setObjectName(u"QGBA__TileView")
        QGBA__TileView.resize(680, 450)
        self.gridLayout = QGridLayout(QGBA__TileView)
        self.gridLayout.setObjectName(u"gridLayout")
        self.groupBox_2 = QGroupBox(QGBA__TileView)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.formLayout_2 = QFormLayout(self.groupBox_2)
        self.formLayout_2.setObjectName(u"formLayout_2")
        self.paletteId = QSpinBox(self.groupBox_2)
        self.paletteId.setObjectName(u"paletteId")
        self.paletteId.setMaximum(15)

        self.formLayout_2.setWidget(0, QFormLayout.LabelRole, self.paletteId)

        self.label_3 = QLabel(self.groupBox_2)
        self.label_3.setObjectName(u"label_3")

        self.formLayout_2.setWidget(0, QFormLayout.FieldRole, self.label_3)

        self.palette256 = QCheckBox(self.groupBox_2)
        self.palette256.setObjectName(u"palette256")

        self.formLayout_2.setWidget(1, QFormLayout.SpanningRole, self.palette256)

        self.line = QFrame(self.groupBox_2)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_2.setWidget(2, QFormLayout.SpanningRole, self.line)

        self.magnification = QSpinBox(self.groupBox_2)
        self.magnification.setObjectName(u"magnification")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.magnification.sizePolicy().hasHeightForWidth())
        self.magnification.setSizePolicy(sizePolicy)
        self.magnification.setSuffix(u"\u00d7")
        self.magnification.setMinimum(1)
        self.magnification.setMaximum(8)

        self.formLayout_2.setWidget(3, QFormLayout.LabelRole, self.magnification)

        self.label_2 = QLabel(self.groupBox_2)
        self.label_2.setObjectName(u"label_2")

        self.formLayout_2.setWidget(3, QFormLayout.FieldRole, self.label_2)

        self.tilesPerRow = QSpinBox(self.groupBox_2)
        self.tilesPerRow.setObjectName(u"tilesPerRow")
        self.tilesPerRow.setEnabled(False)
        self.tilesPerRow.setMinimum(1)
        self.tilesPerRow.setMaximum(64)
        self.tilesPerRow.setValue(32)

        self.formLayout_2.setWidget(4, QFormLayout.LabelRole, self.tilesPerRow)

        self.label = QLabel(self.groupBox_2)
        self.label.setObjectName(u"label")

        self.formLayout_2.setWidget(4, QFormLayout.FieldRole, self.label)

        self.tileFit = QCheckBox(self.groupBox_2)
        self.tileFit.setObjectName(u"tileFit")
        self.tileFit.setChecked(True)

        self.formLayout_2.setWidget(5, QFormLayout.SpanningRole, self.tileFit)


        self.gridLayout.addWidget(self.groupBox_2, 0, 0, 1, 1)

        self.tile = QGBA_AssetTile(QGBA__TileView)
        self.tile.setObjectName(u"tile")

        self.gridLayout.addWidget(self.tile, 0, 1, 2, 1)

        self.groupBox = QGroupBox(QGBA__TileView)
        self.groupBox.setObjectName(u"groupBox")
        self.verticalLayout_2 = QVBoxLayout(self.groupBox)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.tilesBg = QRadioButton(self.groupBox)
        self.tilesSelector = QButtonGroup(QGBA__TileView)
        self.tilesSelector.setObjectName(u"tilesSelector")
        self.tilesSelector.addButton(self.tilesBg)
        self.tilesBg.setObjectName(u"tilesBg")

        self.verticalLayout_2.addWidget(self.tilesBg)

        self.tilesObj = QRadioButton(self.groupBox)
        self.tilesSelector.addButton(self.tilesObj)
        self.tilesObj.setObjectName(u"tilesObj")

        self.verticalLayout_2.addWidget(self.tilesObj)

        self.tilesBoth = QRadioButton(self.groupBox)
        self.tilesSelector.addButton(self.tilesBoth)
        self.tilesBoth.setObjectName(u"tilesBoth")
        self.tilesBoth.setChecked(True)

        self.verticalLayout_2.addWidget(self.tilesBoth)


        self.gridLayout.addWidget(self.groupBox, 1, 0, 1, 1)

        self.gridLayout_2 = QGridLayout()
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.copyOne = QPushButton(QGBA__TileView)
        self.copyOne.setObjectName(u"copyOne")

        self.gridLayout_2.addWidget(self.copyOne, 0, 0, 1, 1)

        self.exportOne = QPushButton(QGBA__TileView)
        self.exportOne.setObjectName(u"exportOne")

        self.gridLayout_2.addWidget(self.exportOne, 1, 0, 1, 1)

        self.copyAll = QPushButton(QGBA__TileView)
        self.copyAll.setObjectName(u"copyAll")

        self.gridLayout_2.addWidget(self.copyAll, 0, 1, 1, 1)

        self.exportAll = QPushButton(QGBA__TileView)
        self.exportAll.setObjectName(u"exportAll")

        self.gridLayout_2.addWidget(self.exportAll, 1, 1, 1, 1)


        self.gridLayout.addLayout(self.gridLayout_2, 3, 0, 1, 2)

        self.scrollArea = QScrollArea(QGBA__TileView)
        self.scrollArea.setObjectName(u"scrollArea")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.scrollArea.sizePolicy().hasHeightForWidth())
        self.scrollArea.setSizePolicy(sizePolicy1)
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.scrollAreaWidgetContents = QWidget()
        self.scrollAreaWidgetContents.setObjectName(u"scrollAreaWidgetContents")
        self.scrollAreaWidgetContents.setGeometry(QRect(0, 0, 441, 768))
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Maximum)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.scrollAreaWidgetContents.sizePolicy().hasHeightForWidth())
        self.scrollAreaWidgetContents.setSizePolicy(sizePolicy2)
        self.verticalLayout = QVBoxLayout(self.scrollAreaWidgetContents)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.tiles = QGBA_TilePainter(self.scrollAreaWidgetContents)
        self.tiles.setObjectName(u"tiles")
        sizePolicy3 = QSizePolicy(QSizePolicy.Policy.MinimumExpanding, QSizePolicy.Policy.Fixed)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.tiles.sizePolicy().hasHeightForWidth())
        self.tiles.setSizePolicy(sizePolicy3)
        self.tiles.setMinimumSize(QSize(256, 768))

        self.verticalLayout.addWidget(self.tiles)

        self.scrollArea.setWidget(self.scrollAreaWidgetContents)

        self.gridLayout.addWidget(self.scrollArea, 0, 2, 4, 1)

        self.gridLayout.setRowStretch(2, 1)
        self.gridLayout.setColumnStretch(2, 1)
        QWidget.setTabOrder(self.paletteId, self.palette256)
        QWidget.setTabOrder(self.palette256, self.magnification)
        QWidget.setTabOrder(self.magnification, self.tilesPerRow)
        QWidget.setTabOrder(self.tilesPerRow, self.tileFit)
        QWidget.setTabOrder(self.tileFit, self.tilesBg)
        QWidget.setTabOrder(self.tilesBg, self.tilesObj)
        QWidget.setTabOrder(self.tilesObj, self.tilesBoth)
        QWidget.setTabOrder(self.tilesBoth, self.copyOne)
        QWidget.setTabOrder(self.copyOne, self.copyAll)
        QWidget.setTabOrder(self.copyAll, self.exportOne)
        QWidget.setTabOrder(self.exportOne, self.exportAll)
        QWidget.setTabOrder(self.exportAll, self.scrollArea)

        self.retranslateUi(QGBA__TileView)
        self.tileFit.toggled.connect(self.tilesPerRow.setDisabled)
        self.magnification.valueChanged.connect(self.tiles.setTileMagnification)
        self.palette256.toggled.connect(self.paletteId.setDisabled)

        QMetaObject.connectSlotsByName(QGBA__TileView)
    # setupUi

    def retranslateUi(self, QGBA__TileView):
        QGBA__TileView.setWindowTitle(QCoreApplication.translate("QGBA::TileView", u"Tiles", None))
        self.groupBox_2.setTitle("")
        self.label_3.setText(QCoreApplication.translate("QGBA::TileView", u"Palette", None))
        self.palette256.setText(QCoreApplication.translate("QGBA::TileView", u"256 colors", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::TileView", u"Magnification", None))
        self.label.setText(QCoreApplication.translate("QGBA::TileView", u"Tiles per row", None))
        self.tileFit.setText(QCoreApplication.translate("QGBA::TileView", u"Fit to window", None))
        self.groupBox.setTitle(QCoreApplication.translate("QGBA::TileView", u"Displayed tiles", None))
        self.tilesBg.setText(QCoreApplication.translate("QGBA::TileView", u"Only BG tiles", None))
        self.tilesObj.setText(QCoreApplication.translate("QGBA::TileView", u"Only OBJ tiles", None))
        self.tilesBoth.setText(QCoreApplication.translate("QGBA::TileView", u"Both", None))
        self.copyOne.setText(QCoreApplication.translate("QGBA::TileView", u"Copy Selected", None))
        self.exportOne.setText(QCoreApplication.translate("QGBA::TileView", u"Export Selected", None))
        self.copyAll.setText(QCoreApplication.translate("QGBA::TileView", u"Copy All", None))
        self.exportAll.setText(QCoreApplication.translate("QGBA::TileView", u"Export All", None))
    # retranslateUi

