# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'MemorySearch.ui'
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
from PySide6.QtWidgets import (QAbstractButton, QAbstractItemView, QApplication, QButtonGroup,
    QCheckBox, QDialogButtonBox, QFormLayout, QFrame,
    QGridLayout, QHBoxLayout, QHeaderView, QLabel,
    QLineEdit, QPushButton, QRadioButton, QSizePolicy,
    QTableWidget, QTableWidgetItem, QWidget)

class Ui_QGBA_MemorySearch(object):
    def setupUi(self, QGBA__MemorySearch):
        if not QGBA__MemorySearch.objectName():
            QGBA__MemorySearch.setObjectName(u"QGBA__MemorySearch")
        QGBA__MemorySearch.resize(725, 813)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Minimum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(QGBA__MemorySearch.sizePolicy().hasHeightForWidth())
        QGBA__MemorySearch.setSizePolicy(sizePolicy)
        QGBA__MemorySearch.setMinimumSize(QSize(540, 400))
        self.gridLayout = QGridLayout(QGBA__MemorySearch)
        self.gridLayout.setObjectName(u"gridLayout")
        self.results = QTableWidget(QGBA__MemorySearch)
        if (self.results.columnCount() < 3):
            self.results.setColumnCount(3)
        __qtablewidgetitem = QTableWidgetItem()
        self.results.setHorizontalHeaderItem(0, __qtablewidgetitem)
        __qtablewidgetitem1 = QTableWidgetItem()
        self.results.setHorizontalHeaderItem(1, __qtablewidgetitem1)
        __qtablewidgetitem2 = QTableWidgetItem()
        self.results.setHorizontalHeaderItem(2, __qtablewidgetitem2)
        self.results.setObjectName(u"results")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.MinimumExpanding, QSizePolicy.Policy.MinimumExpanding)
        sizePolicy1.setHorizontalStretch(1)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.results.sizePolicy().hasHeightForWidth())
        self.results.setSizePolicy(sizePolicy1)
        self.results.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.results.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.results.setShowGrid(False)
        self.results.verticalHeader().setVisible(False)

        self.gridLayout.addWidget(self.results, 0, 1, 1, 1)

        self.formLayout = QFormLayout()
        self.formLayout.setObjectName(u"formLayout")
        self.label = QLabel(QGBA__MemorySearch)
        self.label.setObjectName(u"label")

        self.formLayout.setWidget(0, QFormLayout.LabelRole, self.label)

        self.value = QLineEdit(QGBA__MemorySearch)
        self.value.setObjectName(u"value")

        self.formLayout.setWidget(0, QFormLayout.FieldRole, self.value)

        self.label_2 = QLabel(QGBA__MemorySearch)
        self.label_2.setObjectName(u"label_2")

        self.formLayout.setWidget(1, QFormLayout.LabelRole, self.label_2)

        self.typeNum = QRadioButton(QGBA__MemorySearch)
        self.type = QButtonGroup(QGBA__MemorySearch)
        self.type.setObjectName(u"type")
        self.type.addButton(self.typeNum)
        self.typeNum.setObjectName(u"typeNum")
        self.typeNum.setChecked(True)

        self.formLayout.setWidget(1, QFormLayout.FieldRole, self.typeNum)

        self.typeStr = QRadioButton(QGBA__MemorySearch)
        self.type.addButton(self.typeStr)
        self.typeStr.setObjectName(u"typeStr")

        self.formLayout.setWidget(2, QFormLayout.FieldRole, self.typeStr)

        self.line = QFrame(QGBA__MemorySearch)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout.setWidget(4, QFormLayout.SpanningRole, self.line)

        self.label_3 = QLabel(QGBA__MemorySearch)
        self.label_3.setObjectName(u"label_3")

        self.formLayout.setWidget(5, QFormLayout.LabelRole, self.label_3)

        self.bitsGuess = QRadioButton(QGBA__MemorySearch)
        self.width = QButtonGroup(QGBA__MemorySearch)
        self.width.setObjectName(u"width")
        self.width.addButton(self.bitsGuess)
        self.bitsGuess.setObjectName(u"bitsGuess")
        self.bitsGuess.setChecked(True)

        self.formLayout.setWidget(5, QFormLayout.FieldRole, self.bitsGuess)

        self.bits8 = QRadioButton(QGBA__MemorySearch)
        self.width.addButton(self.bits8)
        self.bits8.setObjectName(u"bits8")

        self.formLayout.setWidget(6, QFormLayout.FieldRole, self.bits8)

        self.bits16 = QRadioButton(QGBA__MemorySearch)
        self.width.addButton(self.bits16)
        self.bits16.setObjectName(u"bits16")

        self.formLayout.setWidget(7, QFormLayout.FieldRole, self.bits16)

        self.bits32 = QRadioButton(QGBA__MemorySearch)
        self.width.addButton(self.bits32)
        self.bits32.setObjectName(u"bits32")
        self.bits32.setChecked(False)

        self.formLayout.setWidget(8, QFormLayout.FieldRole, self.bits32)

        self.line_2 = QFrame(QGBA__MemorySearch)
        self.line_2.setObjectName(u"line_2")
        self.line_2.setFrameShape(QFrame.Shape.HLine)
        self.line_2.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout.setWidget(9, QFormLayout.SpanningRole, self.line_2)

        self.label_4 = QLabel(QGBA__MemorySearch)
        self.label_4.setObjectName(u"label_4")

        self.formLayout.setWidget(10, QFormLayout.LabelRole, self.label_4)

        self.numGuess = QRadioButton(QGBA__MemorySearch)
        self.numGuess.setObjectName(u"numGuess")
        self.numGuess.setChecked(True)

        self.formLayout.setWidget(10, QFormLayout.FieldRole, self.numGuess)

        self.numDec = QRadioButton(QGBA__MemorySearch)
        self.numDec.setObjectName(u"numDec")

        self.formLayout.setWidget(11, QFormLayout.FieldRole, self.numDec)

        self.numHex = QRadioButton(QGBA__MemorySearch)
        self.numHex.setObjectName(u"numHex")

        self.formLayout.setWidget(12, QFormLayout.FieldRole, self.numHex)

        self.line_3 = QFrame(QGBA__MemorySearch)
        self.line_3.setObjectName(u"line_3")
        self.line_3.setFrameShape(QFrame.Shape.HLine)
        self.line_3.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout.setWidget(13, QFormLayout.SpanningRole, self.line_3)

        self.label_5 = QLabel(QGBA__MemorySearch)
        self.label_5.setObjectName(u"label_5")

        self.formLayout.setWidget(14, QFormLayout.LabelRole, self.label_5)

        self.opEqual = QRadioButton(QGBA__MemorySearch)
        self.op = QButtonGroup(QGBA__MemorySearch)
        self.op.setObjectName(u"op")
        self.op.addButton(self.opEqual)
        self.opEqual.setObjectName(u"opEqual")
        self.opEqual.setChecked(True)

        self.formLayout.setWidget(14, QFormLayout.FieldRole, self.opEqual)

        self.opGreater = QRadioButton(QGBA__MemorySearch)
        self.op.addButton(self.opGreater)
        self.opGreater.setObjectName(u"opGreater")

        self.formLayout.setWidget(15, QFormLayout.FieldRole, self.opGreater)

        self.opLess = QRadioButton(QGBA__MemorySearch)
        self.op.addButton(self.opLess)
        self.opLess.setObjectName(u"opLess")

        self.formLayout.setWidget(16, QFormLayout.FieldRole, self.opLess)

        self.opUnknown = QRadioButton(QGBA__MemorySearch)
        self.op.addButton(self.opUnknown)
        self.opUnknown.setObjectName(u"opUnknown")

        self.formLayout.setWidget(17, QFormLayout.FieldRole, self.opUnknown)

        self.opDelta = QRadioButton(QGBA__MemorySearch)
        self.op.addButton(self.opDelta)
        self.opDelta.setObjectName(u"opDelta")
        self.opDelta.setEnabled(False)

        self.formLayout.setWidget(18, QFormLayout.FieldRole, self.opDelta)

        self.opDelta0 = QRadioButton(QGBA__MemorySearch)
        self.op.addButton(self.opDelta0)
        self.opDelta0.setObjectName(u"opDelta0")
        self.opDelta0.setEnabled(False)

        self.formLayout.setWidget(21, QFormLayout.FieldRole, self.opDelta0)

        self.opDeltaPositive = QRadioButton(QGBA__MemorySearch)
        self.op.addButton(self.opDeltaPositive)
        self.opDeltaPositive.setObjectName(u"opDeltaPositive")
        self.opDeltaPositive.setEnabled(False)

        self.formLayout.setWidget(19, QFormLayout.FieldRole, self.opDeltaPositive)

        self.opDeltaNegative = QRadioButton(QGBA__MemorySearch)
        self.op.addButton(self.opDeltaNegative)
        self.opDeltaNegative.setObjectName(u"opDeltaNegative")
        self.opDeltaNegative.setEnabled(False)

        self.formLayout.setWidget(20, QFormLayout.FieldRole, self.opDeltaNegative)

        self.searchROM = QCheckBox(QGBA__MemorySearch)
        self.searchROM.setObjectName(u"searchROM")

        self.formLayout.setWidget(3, QFormLayout.FieldRole, self.searchROM)


        self.gridLayout.addLayout(self.formLayout, 0, 0, 1, 1)

        self.buttonBox = QDialogButtonBox(QGBA__MemorySearch)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setStandardButtons(QDialogButtonBox.Close)

        self.gridLayout.addWidget(self.buttonBox, 2, 0, 1, 2)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.search = QPushButton(QGBA__MemorySearch)
        self.search.setObjectName(u"search")

        self.horizontalLayout_2.addWidget(self.search)

        self.searchWithin = QPushButton(QGBA__MemorySearch)
        self.searchWithin.setObjectName(u"searchWithin")

        self.horizontalLayout_2.addWidget(self.searchWithin)

        self.viewMem = QPushButton(QGBA__MemorySearch)
        self.viewMem.setObjectName(u"viewMem")

        self.horizontalLayout_2.addWidget(self.viewMem)

        self.refresh = QPushButton(QGBA__MemorySearch)
        self.refresh.setObjectName(u"refresh")

        self.horizontalLayout_2.addWidget(self.refresh)


        self.gridLayout.addLayout(self.horizontalLayout_2, 1, 0, 1, 2)


        self.retranslateUi(QGBA__MemorySearch)
        self.buttonBox.rejected.connect(QGBA__MemorySearch.close)
        self.opDelta0.toggled.connect(self.value.setDisabled)

        QMetaObject.connectSlotsByName(QGBA__MemorySearch)
    # setupUi

    def retranslateUi(self, QGBA__MemorySearch):
        QGBA__MemorySearch.setWindowTitle(QCoreApplication.translate("QGBA::MemorySearch", u"Memory Search", None))
        ___qtablewidgetitem = self.results.horizontalHeaderItem(0)
        ___qtablewidgetitem.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Address", None));
        ___qtablewidgetitem1 = self.results.horizontalHeaderItem(1)
        ___qtablewidgetitem1.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Current Value", None));
        ___qtablewidgetitem2 = self.results.horizontalHeaderItem(2)
        ___qtablewidgetitem2.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Type", None));
        self.label.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Value", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Type", None))
        self.typeNum.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Numeric", None))
        self.typeStr.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Text", None))
        self.label_3.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Width", None))
        self.bitsGuess.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Guess", None))
        self.bits8.setText(QCoreApplication.translate("QGBA::MemorySearch", u"1 Byte (8-bit)", None))
        self.bits16.setText(QCoreApplication.translate("QGBA::MemorySearch", u"2 Bytes (16-bit)", None))
        self.bits32.setText(QCoreApplication.translate("QGBA::MemorySearch", u"4 Bytes (32-bit)", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Number type", None))
        self.numGuess.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Guess", None))
        self.numDec.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Decimal", None))
        self.numHex.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Hexadecimal", None))
        self.label_5.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Search type", None))
        self.opEqual.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Equal to value", None))
        self.opGreater.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Greater than value", None))
        self.opLess.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Less than value", None))
        self.opUnknown.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Unknown/changed", None))
        self.opDelta.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Changed by value", None))
        self.opDelta0.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Unchanged", None))
        self.opDeltaPositive.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Increased", None))
        self.opDeltaNegative.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Decreased", None))
        self.searchROM.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Search ROM", None))
        self.search.setText(QCoreApplication.translate("QGBA::MemorySearch", u"New Search", None))
        self.searchWithin.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Search Within", None))
        self.viewMem.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Open in Memory Viewer", None))
        self.refresh.setText(QCoreApplication.translate("QGBA::MemorySearch", u"Refresh", None))
    # retranslateUi

