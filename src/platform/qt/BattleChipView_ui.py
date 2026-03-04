# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'BattleChipView.ui'
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
from PySide6.QtWidgets import (QAbstractButton, QAbstractItemView, QApplication, QCheckBox,
    QComboBox, QDialog, QDialogButtonBox, QFormLayout,
    QFrame, QHBoxLayout, QLabel, QListView,
    QPushButton, QRadioButton, QSizePolicy, QSpacerItem,
    QSpinBox, QVBoxLayout, QWidget)

class Ui_QGBA_BattleChipView(object):
    def setupUi(self, QGBA__BattleChipView):
        if not QGBA__BattleChipView.objectName():
            QGBA__BattleChipView.setObjectName(u"QGBA__BattleChipView")
        QGBA__BattleChipView.resize(658, 722)
        self.verticalLayout = QVBoxLayout(QGBA__BattleChipView)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.chipList = QListView(QGBA__BattleChipView)
        self.chipList.setObjectName(u"chipList")
        self.chipList.setAcceptDrops(True)
        self.chipList.setDragEnabled(True)
        self.chipList.setDragDropMode(QAbstractItemView.InternalMove)
        self.chipList.setDefaultDropAction(Qt.MoveAction)
        self.chipList.setIconSize(QSize(56, 48))
        self.chipList.setMovement(QListView.Free)
        self.chipList.setProperty(u"isWrapping", True)
        self.chipList.setResizeMode(QListView.Adjust)
        self.chipList.setGridSize(QSize(120, 72))
        self.chipList.setViewMode(QListView.IconMode)

        self.verticalLayout.addWidget(self.chipList)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.formLayout_4 = QFormLayout()
        self.formLayout_4.setObjectName(u"formLayout_4")
        self.chipName = QComboBox(QGBA__BattleChipView)
        self.chipName.setObjectName(u"chipName")

        self.formLayout_4.setWidget(0, QFormLayout.FieldRole, self.chipName)

        self.label_2 = QLabel(QGBA__BattleChipView)
        self.label_2.setObjectName(u"label_2")

        self.formLayout_4.setWidget(0, QFormLayout.LabelRole, self.label_2)


        self.horizontalLayout_2.addLayout(self.formLayout_4)

        self.insert = QPushButton(QGBA__BattleChipView)
        self.insert.setObjectName(u"insert")

        self.horizontalLayout_2.addWidget(self.insert)

        self.horizontalLayout_2.setStretch(0, 1)

        self.verticalLayout.addLayout(self.horizontalLayout_2)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.save = QPushButton(QGBA__BattleChipView)
        self.save.setObjectName(u"save")

        self.horizontalLayout_3.addWidget(self.save)

        self.load = QPushButton(QGBA__BattleChipView)
        self.load.setObjectName(u"load")

        self.horizontalLayout_3.addWidget(self.load)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer)

        self.add = QPushButton(QGBA__BattleChipView)
        self.add.setObjectName(u"add")

        self.horizontalLayout_3.addWidget(self.add)

        self.remove = QPushButton(QGBA__BattleChipView)
        self.remove.setObjectName(u"remove")

        self.horizontalLayout_3.addWidget(self.remove)


        self.verticalLayout.addLayout(self.horizontalLayout_3)

        self.advanced = QWidget(QGBA__BattleChipView)
        self.advanced.setObjectName(u"advanced")
        self.advanced.setVisible(False)
        self.horizontalLayout_4 = QHBoxLayout(self.advanced)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.formLayout_2 = QFormLayout()
        self.formLayout_2.setObjectName(u"formLayout_2")
        self.label_3 = QLabel(self.advanced)
        self.label_3.setObjectName(u"label_3")

        self.formLayout_2.setWidget(1, QFormLayout.LabelRole, self.label_3)

        self.gateBattleChip = QRadioButton(self.advanced)
        self.gateBattleChip.setObjectName(u"gateBattleChip")
        self.gateBattleChip.setText(u"Ba&ttleChip Gate")
        self.gateBattleChip.setChecked(True)

        self.formLayout_2.setWidget(1, QFormLayout.FieldRole, self.gateBattleChip)

        self.gateProgress = QRadioButton(self.advanced)
        self.gateProgress.setObjectName(u"gateProgress")
        self.gateProgress.setText(u"Progress &Gate")

        self.formLayout_2.setWidget(2, QFormLayout.FieldRole, self.gateProgress)

        self.gateBeastLink = QRadioButton(self.advanced)
        self.gateBeastLink.setObjectName(u"gateBeastLink")
        self.gateBeastLink.setText(u"Beast &Link Gate")

        self.formLayout_2.setWidget(3, QFormLayout.FieldRole, self.gateBeastLink)


        self.horizontalLayout_4.addLayout(self.formLayout_2)

        self.line = QFrame(self.advanced)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.VLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.horizontalLayout_4.addWidget(self.line)

        self.formLayout_5 = QFormLayout()
        self.formLayout_5.setObjectName(u"formLayout_5")
        self.inserted = QCheckBox(self.advanced)
        self.inserted.setObjectName(u"inserted")

        self.formLayout_5.setWidget(1, QFormLayout.FieldRole, self.inserted)

        self.chipId = QSpinBox(self.advanced)
        self.chipId.setObjectName(u"chipId")
        self.chipId.setMaximum(65535)

        self.formLayout_5.setWidget(0, QFormLayout.FieldRole, self.chipId)

        self.label_4 = QLabel(self.advanced)
        self.label_4.setObjectName(u"label_4")

        self.formLayout_5.setWidget(0, QFormLayout.LabelRole, self.label_4)

        self.updateData = QPushButton(self.advanced)
        self.updateData.setObjectName(u"updateData")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.updateData.sizePolicy().hasHeightForWidth())
        self.updateData.setSizePolicy(sizePolicy)

        self.formLayout_5.setWidget(2, QFormLayout.SpanningRole, self.updateData)


        self.horizontalLayout_4.addLayout(self.formLayout_5)


        self.verticalLayout.addWidget(self.advanced)

        self.showAdvanced = QCheckBox(QGBA__BattleChipView)
        self.showAdvanced.setObjectName(u"showAdvanced")

        self.verticalLayout.addWidget(self.showAdvanced)

        self.horizontalLayout_5 = QHBoxLayout()
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.buttonBox = QDialogButtonBox(QGBA__BattleChipView)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setStandardButtons(QDialogButtonBox.Close|QDialogButtonBox.Reset)

        self.horizontalLayout_5.addWidget(self.buttonBox)


        self.verticalLayout.addLayout(self.horizontalLayout_5)

        self.verticalLayout.setStretch(0, 1)

        self.retranslateUi(QGBA__BattleChipView)
        self.buttonBox.rejected.connect(QGBA__BattleChipView.reject)
        self.showAdvanced.toggled.connect(self.advanced.setVisible)

        QMetaObject.connectSlotsByName(QGBA__BattleChipView)
    # setupUi

    def retranslateUi(self, QGBA__BattleChipView):
        QGBA__BattleChipView.setWindowTitle(QCoreApplication.translate("QGBA::BattleChipView", u"BattleChip Gate", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Chip name", None))
        self.insert.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Insert", None))
        self.save.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Save", None))
        self.load.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Load", None))
        self.add.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Add", None))
        self.remove.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Remove", None))
        self.label_3.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Gate type", None))
        self.inserted.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Inserted", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Chip ID", None))
        self.updateData.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Update Chip data", None))
        self.showAdvanced.setText(QCoreApplication.translate("QGBA::BattleChipView", u"Show advanced", None))
    # retranslateUi

