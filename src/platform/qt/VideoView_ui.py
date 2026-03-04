# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'VideoView.ui'
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
from PySide6.QtWidgets import (QAbstractButton, QApplication, QButtonGroup, QCheckBox,
    QComboBox, QDialogButtonBox, QFrame, QGridLayout,
    QGroupBox, QHBoxLayout, QLabel, QLayout,
    QLineEdit, QPushButton, QRadioButton, QSizePolicy,
    QSpacerItem, QSpinBox, QVBoxLayout, QWidget)

class Ui_QGBA_VideoView(object):
    def setupUi(self, QGBA__VideoView):
        if not QGBA__VideoView.objectName():
            QGBA__VideoView.setObjectName(u"QGBA__VideoView")
        QGBA__VideoView.resize(324, 593)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(QGBA__VideoView.sizePolicy().hasHeightForWidth())
        QGBA__VideoView.setSizePolicy(sizePolicy)
        self.verticalLayout_4 = QVBoxLayout(QGBA__VideoView)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setSizeConstraint(QLayout.SetFixedSize)
        self.gridLayout = QGridLayout()
        self.gridLayout.setObjectName(u"gridLayout")
        self.start = QPushButton(QGBA__VideoView)
        self.start.setObjectName(u"start")
        self.start.setEnabled(False)
        sizePolicy.setHeightForWidth(self.start.sizePolicy().hasHeightForWidth())
        self.start.setSizePolicy(sizePolicy)

        self.gridLayout.addWidget(self.start, 1, 0, 1, 1)

        self.stop = QPushButton(QGBA__VideoView)
        self.stop.setObjectName(u"stop")
        self.stop.setEnabled(False)
        sizePolicy.setHeightForWidth(self.stop.sizePolicy().hasHeightForWidth())
        self.stop.setSizePolicy(sizePolicy)

        self.gridLayout.addWidget(self.stop, 1, 1, 1, 1)

        self.selectFile = QPushButton(QGBA__VideoView)
        self.selectFile.setObjectName(u"selectFile")
        sizePolicy.setHeightForWidth(self.selectFile.sizePolicy().hasHeightForWidth())
        self.selectFile.setSizePolicy(sizePolicy)

        self.gridLayout.addWidget(self.selectFile, 1, 3, 1, 1)

        self.filename = QLineEdit(QGBA__VideoView)
        self.filename.setObjectName(u"filename")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        sizePolicy1.setHorizontalStretch(1)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.filename.sizePolicy().hasHeightForWidth())
        self.filename.setSizePolicy(sizePolicy1)

        self.gridLayout.addWidget(self.filename, 0, 0, 1, 4)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.gridLayout.addItem(self.horizontalSpacer, 1, 2, 1, 1)


        self.verticalLayout_4.addLayout(self.gridLayout)

        self.groupBox_2 = QGroupBox(QGBA__VideoView)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.horizontalLayout_2 = QHBoxLayout(self.groupBox_2)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.presetHQ = QRadioButton(self.groupBox_2)
        self.presets = QButtonGroup(QGBA__VideoView)
        self.presets.setObjectName(u"presets")
        self.presets.addButton(self.presetHQ)
        self.presetHQ.setObjectName(u"presetHQ")

        self.verticalLayout_2.addWidget(self.presetHQ)

        self.presetYoutube = QRadioButton(self.groupBox_2)
        self.presets.addButton(self.presetYoutube)
        self.presetYoutube.setObjectName(u"presetYoutube")

        self.verticalLayout_2.addWidget(self.presetYoutube)

        self.presetWebM = QRadioButton(self.groupBox_2)
        self.presets.addButton(self.presetWebM)
        self.presetWebM.setObjectName(u"presetWebM")

        self.verticalLayout_2.addWidget(self.presetWebM)

        self.presetMP4 = QRadioButton(self.groupBox_2)
        self.presetMP4.setObjectName(u"presetMP4")

        self.verticalLayout_2.addWidget(self.presetMP4)

        self.presetLossless = QRadioButton(self.groupBox_2)
        self.presets.addButton(self.presetLossless)
        self.presetLossless.setObjectName(u"presetLossless")

        self.verticalLayout_2.addWidget(self.presetLossless)


        self.horizontalLayout_2.addLayout(self.verticalLayout_2)

        self.line = QFrame(self.groupBox_2)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.VLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.horizontalLayout_2.addWidget(self.line)

        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.preset4K = QRadioButton(self.groupBox_2)
        self.preset4K.setObjectName(u"preset4K")

        self.verticalLayout_3.addWidget(self.preset4K)

        self.preset1080 = QRadioButton(self.groupBox_2)
        self.resolutions = QButtonGroup(QGBA__VideoView)
        self.resolutions.setObjectName(u"resolutions")
        self.resolutions.addButton(self.preset1080)
        self.preset1080.setObjectName(u"preset1080")

        self.verticalLayout_3.addWidget(self.preset1080)

        self.preset720 = QRadioButton(self.groupBox_2)
        self.resolutions.addButton(self.preset720)
        self.preset720.setObjectName(u"preset720")

        self.verticalLayout_3.addWidget(self.preset720)

        self.preset480 = QRadioButton(self.groupBox_2)
        self.resolutions.addButton(self.preset480)
        self.preset480.setObjectName(u"preset480")

        self.verticalLayout_3.addWidget(self.preset480)

        self.presetNative = QRadioButton(self.groupBox_2)
        self.resolutions.addButton(self.presetNative)
        self.presetNative.setObjectName(u"presetNative")
        self.presetNative.setEnabled(False)
        self.presetNative.setChecked(True)

        self.verticalLayout_3.addWidget(self.presetNative)


        self.horizontalLayout_2.addLayout(self.verticalLayout_3)


        self.verticalLayout_4.addWidget(self.groupBox_2)

        self.advancedBox = QWidget(QGBA__VideoView)
        self.advancedBox.setObjectName(u"advancedBox")
        self.gridLayout_6 = QGridLayout(self.advancedBox)
        self.gridLayout_6.setObjectName(u"gridLayout_6")
        self.gridLayout_6.setContentsMargins(0, 0, 0, 0)
        self.formatBox = QGroupBox(self.advancedBox)
        self.formatBox.setObjectName(u"formatBox")
        self.verticalLayout_6 = QVBoxLayout(self.formatBox)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.container = QComboBox(self.formatBox)
        self.container.addItem(u"MKV")
        self.container.addItem(u"WebM")
        self.container.addItem(u"AVI")
        self.container.addItem(u"MP4")
        self.container.setObjectName(u"container")
        self.container.setEditable(True)

        self.verticalLayout_6.addWidget(self.container)

        self.video = QComboBox(self.formatBox)
        self.video.addItem(u"H.264")
        self.video.addItem(u"H.264 (NVENC)")
        self.video.addItem(u"HEVC")
        self.video.addItem(u"HEVC (NVENC)")
        self.video.addItem(u"VP8")
        self.video.addItem(u"VP9")
        self.video.addItem(u"FFV1")
        self.video.addItem(u"None")
        self.video.setObjectName(u"video")
        self.video.setEditable(True)

        self.verticalLayout_6.addWidget(self.video)

        self.audio = QComboBox(self.formatBox)
        self.audio.addItem(u"FLAC")
        self.audio.addItem(u"WavPack")
        self.audio.addItem(u"Opus")
        self.audio.addItem(u"Vorbis")
        self.audio.addItem(u"MP3")
        self.audio.addItem(u"AAC")
        self.audio.addItem(u"Uncompressed")
        self.audio.addItem(u"None")
        self.audio.setObjectName(u"audio")
        self.audio.setEditable(True)

        self.verticalLayout_6.addWidget(self.audio)


        self.gridLayout_6.addWidget(self.formatBox, 0, 0, 1, 1)

        self.bitrateBox = QGroupBox(self.advancedBox)
        self.bitrateBox.setObjectName(u"bitrateBox")
        self.gridLayout_3 = QGridLayout(self.bitrateBox)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.doVbr = QRadioButton(self.bitrateBox)
        self.ratefactor = QButtonGroup(QGBA__VideoView)
        self.ratefactor.setObjectName(u"ratefactor")
        self.ratefactor.addButton(self.doVbr)
        self.doVbr.setObjectName(u"doVbr")
        self.doVbr.setText(u"")
        self.doVbr.setChecked(True)

        self.gridLayout_3.addWidget(self.doVbr, 1, 0, 1, 1)

        self.abr = QSpinBox(self.bitrateBox)
        self.abr.setObjectName(u"abr")
        self.abr.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.abr.setMinimum(16)
        self.abr.setMaximum(320)
        self.abr.setValue(128)

        self.gridLayout_3.addWidget(self.abr, 3, 2, 1, 1)

        self.doCrf = QRadioButton(self.bitrateBox)
        self.ratefactor.addButton(self.doCrf)
        self.doCrf.setObjectName(u"doCrf")
        self.doCrf.setText(u"")

        self.gridLayout_3.addWidget(self.doCrf, 0, 0, 1, 1)

        self.label_2 = QLabel(self.bitrateBox)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_3.addWidget(self.label_2, 3, 1, 1, 1)

        self.crf = QSpinBox(self.bitrateBox)
        self.crf.setObjectName(u"crf")
        self.crf.setEnabled(False)
        self.crf.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.crf.setMaximum(50)
        self.crf.setValue(18)

        self.gridLayout_3.addWidget(self.crf, 0, 2, 1, 1)

        self.vbr = QSpinBox(self.bitrateBox)
        self.vbr.setObjectName(u"vbr")
        self.vbr.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.vbr.setMaximum(10000)

        self.gridLayout_3.addWidget(self.vbr, 1, 2, 1, 1)

        self.label = QLabel(self.bitrateBox)
        self.label.setObjectName(u"label")
        self.label.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_3.addWidget(self.label, 1, 1, 1, 1)

        self.label_5 = QLabel(self.bitrateBox)
        self.label_5.setObjectName(u"label_5")
        self.label_5.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_3.addWidget(self.label_5, 0, 1, 1, 1)


        self.gridLayout_6.addWidget(self.bitrateBox, 0, 1, 1, 1)

        self.dimensionsBox = QGroupBox(self.advancedBox)
        self.dimensionsBox.setObjectName(u"dimensionsBox")
        self.gridLayout_4 = QGridLayout(self.dimensionsBox)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.label_4 = QLabel(self.dimensionsBox)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setText(u":")
        self.label_4.setAlignment(Qt.AlignCenter)

        self.gridLayout_4.addWidget(self.label_4, 1, 2, 1, 1)

        self.label_3 = QLabel(self.dimensionsBox)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setText(u"\u00d7")
        self.label_3.setAlignment(Qt.AlignCenter)

        self.gridLayout_4.addWidget(self.label_3, 0, 2, 1, 1)

        self.height = QSpinBox(self.dimensionsBox)
        self.height.setObjectName(u"height")
        self.height.setMinimum(1)
        self.height.setMaximum(3160)

        self.gridLayout_4.addWidget(self.height, 0, 3, 1, 1)

        self.width = QSpinBox(self.dimensionsBox)
        self.width.setObjectName(u"width")
        self.width.setMinimum(1)
        self.width.setMaximum(3840)

        self.gridLayout_4.addWidget(self.width, 0, 1, 1, 1)

        self.hratio = QSpinBox(self.dimensionsBox)
        self.hratio.setObjectName(u"hratio")
        self.hratio.setMinimum(1)
        self.hratio.setMaximum(9999)

        self.gridLayout_4.addWidget(self.hratio, 1, 3, 1, 1)

        self.wratio = QSpinBox(self.dimensionsBox)
        self.wratio.setObjectName(u"wratio")
        self.wratio.setMinimum(1)
        self.wratio.setMaximum(9999)

        self.gridLayout_4.addWidget(self.wratio, 1, 1, 1, 1)

        self.lockRatio = QCheckBox(self.dimensionsBox)
        self.lockRatio.setObjectName(u"lockRatio")

        self.gridLayout_4.addWidget(self.lockRatio, 1, 4, 1, 1)


        self.gridLayout_6.addWidget(self.dimensionsBox, 1, 0, 1, 2)


        self.verticalLayout_4.addWidget(self.advancedBox)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.showAdvanced = QCheckBox(QGBA__VideoView)
        self.showAdvanced.setObjectName(u"showAdvanced")

        self.horizontalLayout.addWidget(self.showAdvanced)

        self.buttonBox = QDialogButtonBox(QGBA__VideoView)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setStandardButtons(QDialogButtonBox.Close)

        self.horizontalLayout.addWidget(self.buttonBox)


        self.verticalLayout_4.addLayout(self.horizontalLayout)

#if QT_CONFIG(shortcut)
        self.label_2.setBuddy(self.abr)
        self.label.setBuddy(self.vbr)
        self.label_5.setBuddy(self.crf)
#endif // QT_CONFIG(shortcut)
        QWidget.setTabOrder(self.filename, self.start)
        QWidget.setTabOrder(self.start, self.stop)
        QWidget.setTabOrder(self.stop, self.selectFile)
        QWidget.setTabOrder(self.selectFile, self.presetHQ)
        QWidget.setTabOrder(self.presetHQ, self.presetYoutube)
        QWidget.setTabOrder(self.presetYoutube, self.presetWebM)
        QWidget.setTabOrder(self.presetWebM, self.presetMP4)
        QWidget.setTabOrder(self.presetMP4, self.presetLossless)
        QWidget.setTabOrder(self.presetLossless, self.preset4K)
        QWidget.setTabOrder(self.preset4K, self.preset1080)
        QWidget.setTabOrder(self.preset1080, self.preset720)
        QWidget.setTabOrder(self.preset720, self.preset480)
        QWidget.setTabOrder(self.preset480, self.presetNative)
        QWidget.setTabOrder(self.presetNative, self.showAdvanced)
        QWidget.setTabOrder(self.showAdvanced, self.container)
        QWidget.setTabOrder(self.container, self.video)
        QWidget.setTabOrder(self.video, self.audio)
        QWidget.setTabOrder(self.audio, self.doCrf)
        QWidget.setTabOrder(self.doCrf, self.doVbr)
        QWidget.setTabOrder(self.doVbr, self.crf)
        QWidget.setTabOrder(self.crf, self.vbr)
        QWidget.setTabOrder(self.vbr, self.abr)
        QWidget.setTabOrder(self.abr, self.width)
        QWidget.setTabOrder(self.width, self.height)
        QWidget.setTabOrder(self.height, self.wratio)
        QWidget.setTabOrder(self.wratio, self.hratio)
        QWidget.setTabOrder(self.hratio, self.lockRatio)

        self.retranslateUi(QGBA__VideoView)
        self.doCrf.toggled.connect(self.crf.setEnabled)
        self.doVbr.toggled.connect(self.vbr.setEnabled)

        QMetaObject.connectSlotsByName(QGBA__VideoView)
    # setupUi

    def retranslateUi(self, QGBA__VideoView):
        QGBA__VideoView.setWindowTitle(QCoreApplication.translate("QGBA::VideoView", u"Record Video", None))
        self.start.setText(QCoreApplication.translate("QGBA::VideoView", u"Start", None))
        self.stop.setText(QCoreApplication.translate("QGBA::VideoView", u"Stop", None))
        self.selectFile.setText(QCoreApplication.translate("QGBA::VideoView", u"Select File", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("QGBA::VideoView", u"Presets", None))
        self.presetHQ.setText(QCoreApplication.translate("QGBA::VideoView", u"High &Quality", None))
        self.presetYoutube.setText(QCoreApplication.translate("QGBA::VideoView", u"&YouTube", None))
        self.presetWebM.setText(QCoreApplication.translate("QGBA::VideoView", u"WebM", None))
        self.presetMP4.setText(QCoreApplication.translate("QGBA::VideoView", u"MP4", None))
        self.presetLossless.setText(QCoreApplication.translate("QGBA::VideoView", u"&Lossless", None))
        self.preset4K.setText(QCoreApplication.translate("QGBA::VideoView", u"4K", None))
        self.preset1080.setText(QCoreApplication.translate("QGBA::VideoView", u"&1080p", None))
        self.preset720.setText(QCoreApplication.translate("QGBA::VideoView", u"&720p", None))
        self.preset480.setText(QCoreApplication.translate("QGBA::VideoView", u"&480p", None))
        self.presetNative.setText(QCoreApplication.translate("QGBA::VideoView", u"&Native", None))
        self.formatBox.setTitle(QCoreApplication.translate("QGBA::VideoView", u"Format", None))



        self.bitrateBox.setTitle(QCoreApplication.translate("QGBA::VideoView", u" Bitrate (kbps)", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::VideoView", u"ABR", None))
        self.crf.setSuffix("")
        self.vbr.setSuffix("")
        self.label.setText(QCoreApplication.translate("QGBA::VideoView", u"VBR", None))
        self.label_5.setText(QCoreApplication.translate("QGBA::VideoView", u"CRF", None))
        self.dimensionsBox.setTitle(QCoreApplication.translate("QGBA::VideoView", u"Dimensions", None))
        self.lockRatio.setText(QCoreApplication.translate("QGBA::VideoView", u"Lock aspect ratio", None))
        self.showAdvanced.setText(QCoreApplication.translate("QGBA::VideoView", u"Show advanced", None))
    # retranslateUi

