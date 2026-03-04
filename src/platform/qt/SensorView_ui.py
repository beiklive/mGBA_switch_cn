# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'SensorView.ui'
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
from PySide6.QtWidgets import (QAbstractSpinBox, QApplication, QButtonGroup, QDateTimeEdit,
    QDoubleSpinBox, QGridLayout, QGroupBox, QHBoxLayout,
    QLabel, QLayout, QPushButton, QRadioButton,
    QSizePolicy, QSlider, QSpinBox, QVBoxLayout,
    QWidget)

class Ui_QGBA_SensorView(object):
    def setupUi(self, QGBA__SensorView):
        if not QGBA__SensorView.objectName():
            QGBA__SensorView.setObjectName(u"QGBA__SensorView")
        QGBA__SensorView.resize(448, 332)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(QGBA__SensorView.sizePolicy().hasHeightForWidth())
        QGBA__SensorView.setSizePolicy(sizePolicy)
        self.horizontalLayout = QHBoxLayout(QGBA__SensorView)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setSizeConstraint(QLayout.SetFixedSize)
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.groupBox = QGroupBox(QGBA__SensorView)
        self.groupBox.setObjectName(u"groupBox")
        self.gridLayout_4 = QGridLayout(self.groupBox)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.timeNoOverride = QRadioButton(self.groupBox)
        self.timeButtons = QButtonGroup(QGBA__SensorView)
        self.timeButtons.setObjectName(u"timeButtons")
        self.timeButtons.addButton(self.timeNoOverride)
        self.timeNoOverride.setObjectName(u"timeNoOverride")
        self.timeNoOverride.setChecked(True)

        self.gridLayout_4.addWidget(self.timeNoOverride, 0, 0, 1, 1)

        self.timeFixed = QRadioButton(self.groupBox)
        self.timeButtons.addButton(self.timeFixed)
        self.timeFixed.setObjectName(u"timeFixed")

        self.gridLayout_4.addWidget(self.timeFixed, 1, 0, 1, 1)

        self.timeNow = QPushButton(self.groupBox)
        self.timeNow.setObjectName(u"timeNow")

        self.gridLayout_4.addWidget(self.timeNow, 1, 1, 1, 1)

        self.timeOffset = QRadioButton(self.groupBox)
        self.timeButtons.addButton(self.timeOffset)
        self.timeOffset.setObjectName(u"timeOffset")

        self.gridLayout_4.addWidget(self.timeOffset, 2, 0, 1, 1)

        self.offsetSeconds = QSpinBox(self.groupBox)
        self.offsetSeconds.setObjectName(u"offsetSeconds")
        self.offsetSeconds.setAccelerated(True)
        self.offsetSeconds.setMinimum(-99999999)
        self.offsetSeconds.setMaximum(99999999)
        self.offsetSeconds.setSingleStep(1)

        self.gridLayout_4.addWidget(self.offsetSeconds, 2, 1, 1, 1)

        self.timeFakeEpoch = QRadioButton(self.groupBox)
        self.timeButtons.addButton(self.timeFakeEpoch)
        self.timeFakeEpoch.setObjectName(u"timeFakeEpoch")

        self.gridLayout_4.addWidget(self.timeFakeEpoch, 3, 0, 1, 1)

        self.time = QDateTimeEdit(self.groupBox)
        self.time.setObjectName(u"time")
        self.time.setWrapping(True)
        self.time.setMaximumDate(QDate(2099, 12, 31))
        self.time.setMinimumDate(QDate(2000, 1, 1))
        self.time.setCurrentSection(QDateTimeEdit.MonthSection)

        self.gridLayout_4.addWidget(self.time, 4, 0, 1, 2)


        self.verticalLayout_2.addWidget(self.groupBox)

        self.groupBox_2 = QGroupBox(QGBA__SensorView)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.gridLayout_6 = QGridLayout(self.groupBox_2)
        self.gridLayout_6.setObjectName(u"gridLayout_6")
        self.label_4 = QLabel(self.groupBox_2)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout_6.addWidget(self.label_4, 0, 0, 1, 1)

        self.lightSpin = QSpinBox(self.groupBox_2)
        self.lightSpin.setObjectName(u"lightSpin")
        self.lightSpin.setMaximum(255)

        self.gridLayout_6.addWidget(self.lightSpin, 0, 1, 1, 1)

        self.lightSlide = QSlider(self.groupBox_2)
        self.lightSlide.setObjectName(u"lightSlide")
        self.lightSlide.setMaximum(255)
        self.lightSlide.setOrientation(Qt.Horizontal)
        self.lightSlide.setTickPosition(QSlider.TicksBelow)
        self.lightSlide.setTickInterval(16)

        self.gridLayout_6.addWidget(self.lightSlide, 1, 0, 1, 2)


        self.verticalLayout_2.addWidget(self.groupBox_2)


        self.horizontalLayout.addLayout(self.verticalLayout_2)

        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.tilt = QGroupBox(QGBA__SensorView)
        self.tilt.setObjectName(u"tilt")
        self.gridLayout_10 = QGridLayout(self.tilt)
        self.gridLayout_10.setObjectName(u"gridLayout_10")
        self.gridLayout_11 = QGridLayout()
        self.gridLayout_11.setObjectName(u"gridLayout_11")
        self.tiltSetY = QPushButton(self.tilt)
        self.tiltSetY.setObjectName(u"tiltSetY")
        self.tiltSetY.setCheckable(True)

        self.gridLayout_11.addWidget(self.tiltSetY, 0, 1, 1, 1)

        self.tiltSetX = QPushButton(self.tilt)
        self.tiltSetX.setObjectName(u"tiltSetX")
        self.tiltSetX.setCheckable(True)

        self.gridLayout_11.addWidget(self.tiltSetX, 0, 0, 1, 1)

        self.tiltX = QDoubleSpinBox(self.tilt)
        self.tiltX.setObjectName(u"tiltX")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Ignored, QSizePolicy.Policy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.tiltX.sizePolicy().hasHeightForWidth())
        self.tiltX.setSizePolicy(sizePolicy1)
        self.tiltX.setAlignment(Qt.AlignCenter)
        self.tiltX.setReadOnly(True)
        self.tiltX.setButtonSymbols(QAbstractSpinBox.NoButtons)
        self.tiltX.setMinimum(-1.000000000000000)
        self.tiltX.setMaximum(1.000000000000000)
        self.tiltX.setSingleStep(0.010000000000000)

        self.gridLayout_11.addWidget(self.tiltX, 1, 0, 1, 1, Qt.AlignHCenter)

        self.tiltY = QDoubleSpinBox(self.tilt)
        self.tiltY.setObjectName(u"tiltY")
        sizePolicy1.setHeightForWidth(self.tiltY.sizePolicy().hasHeightForWidth())
        self.tiltY.setSizePolicy(sizePolicy1)
        self.tiltY.setAlignment(Qt.AlignCenter)
        self.tiltY.setReadOnly(True)
        self.tiltY.setButtonSymbols(QAbstractSpinBox.NoButtons)
        self.tiltY.setMinimum(-1.000000000000000)
        self.tiltY.setMaximum(1.000000000000000)
        self.tiltY.setSingleStep(0.010000000000000)

        self.gridLayout_11.addWidget(self.tiltY, 1, 1, 1, 1, Qt.AlignHCenter)


        self.gridLayout_10.addLayout(self.gridLayout_11, 0, 0, 1, 2)


        self.verticalLayout_3.addWidget(self.tilt)

        self.gyro = QGroupBox(QGBA__SensorView)
        self.gyro.setObjectName(u"gyro")
        self.gridLayout_12 = QGridLayout(self.gyro)
        self.gridLayout_12.setObjectName(u"gridLayout_12")
        self.gridLayout_17 = QGridLayout()
        self.gridLayout_17.setObjectName(u"gridLayout_17")
        self.gyroSetY = QPushButton(self.gyro)
        self.gyroSetY.setObjectName(u"gyroSetY")
        self.gyroSetY.setCheckable(True)

        self.gridLayout_17.addWidget(self.gyroSetY, 0, 1, 1, 1)

        self.gyroSetX = QPushButton(self.gyro)
        self.gyroSetX.setObjectName(u"gyroSetX")
        self.gyroSetX.setCheckable(True)

        self.gridLayout_17.addWidget(self.gyroSetX, 0, 0, 1, 1)

        self.label_2 = QLabel(self.gyro)
        self.label_2.setObjectName(u"label_2")

        self.gridLayout_17.addWidget(self.label_2, 2, 0, 1, 1)

        self.gyroSensitivity = QDoubleSpinBox(self.gyro)
        self.gyroSensitivity.setObjectName(u"gyroSensitivity")
        self.gyroSensitivity.setDecimals(0)
        self.gyroSensitivity.setMaximum(1000.000000000000000)

        self.gridLayout_17.addWidget(self.gyroSensitivity, 2, 1, 1, 1)

        self.gyroView = QSlider(self.gyro)
        self.gyroView.setObjectName(u"gyroView")
        self.gyroView.setEnabled(False)
        self.gyroView.setMinimum(-1073741823)
        self.gyroView.setMaximum(1073741823)
        self.gyroView.setValue(0)
        self.gyroView.setTracking(False)
        self.gyroView.setOrientation(Qt.Horizontal)

        self.gridLayout_17.addWidget(self.gyroView, 1, 0, 1, 2)


        self.gridLayout_12.addLayout(self.gridLayout_17, 0, 0, 1, 2)


        self.verticalLayout_3.addWidget(self.gyro)


        self.horizontalLayout.addLayout(self.verticalLayout_3)


        self.retranslateUi(QGBA__SensorView)

        QMetaObject.connectSlotsByName(QGBA__SensorView)
    # setupUi

    def retranslateUi(self, QGBA__SensorView):
        QGBA__SensorView.setWindowTitle(QCoreApplication.translate("QGBA::SensorView", u"Sensors", None))
        self.groupBox.setTitle(QCoreApplication.translate("QGBA::SensorView", u"Realtime clock", None))
        self.timeNoOverride.setText(QCoreApplication.translate("QGBA::SensorView", u"System time", None))
        self.timeFixed.setText(QCoreApplication.translate("QGBA::SensorView", u"Fixed time", None))
        self.timeNow.setText(QCoreApplication.translate("QGBA::SensorView", u"Now", None))
        self.timeOffset.setText(QCoreApplication.translate("QGBA::SensorView", u"Offset time", None))
        self.offsetSeconds.setSuffix(QCoreApplication.translate("QGBA::SensorView", u" sec", None))
        self.timeFakeEpoch.setText(QCoreApplication.translate("QGBA::SensorView", u"Start time at", None))
        self.time.setDisplayFormat(QCoreApplication.translate("QGBA::SensorView", u"MM/dd/yy hh:mm:ss AP", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("QGBA::SensorView", u"Light sensor", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::SensorView", u"Brightness", None))
        self.tilt.setTitle(QCoreApplication.translate("QGBA::SensorView", u"Tilt sensor", None))
        self.tiltSetY.setText(QCoreApplication.translate("QGBA::SensorView", u"Set Y", None))
        self.tiltSetX.setText(QCoreApplication.translate("QGBA::SensorView", u"Set X", None))
        self.gyro.setTitle(QCoreApplication.translate("QGBA::SensorView", u"Gyroscope", None))
        self.gyroSetY.setText(QCoreApplication.translate("QGBA::SensorView", u"Set Y", None))
        self.gyroSetX.setText(QCoreApplication.translate("QGBA::SensorView", u"Set X", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::SensorView", u"Sensitivity", None))
    # retranslateUi

