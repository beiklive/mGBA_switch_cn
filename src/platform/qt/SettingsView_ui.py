# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'SettingsView.ui'
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
    QComboBox, QDialogButtonBox, QDoubleSpinBox, QFormLayout,
    QFrame, QGridLayout, QGroupBox, QHBoxLayout,
    QHeaderView, QLabel, QLayout, QLineEdit,
    QListWidget, QListWidgetItem, QPushButton, QRadioButton,
    QSizePolicy, QSlider, QSpacerItem, QSpinBox,
    QStackedWidget, QTableView, QVBoxLayout, QWidget)

class Ui_QGBA_SettingsView(object):
    def setupUi(self, QGBA__SettingsView):
        if not QGBA__SettingsView.objectName():
            QGBA__SettingsView.setObjectName(u"QGBA__SettingsView")
        QGBA__SettingsView.resize(880, 700)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(QGBA__SettingsView.sizePolicy().hasHeightForWidth())
        QGBA__SettingsView.setSizePolicy(sizePolicy)
        self.gridLayout = QGridLayout(QGBA__SettingsView)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setSizeConstraint(QLayout.SetFixedSize)
        self.tabs = QListWidget(QGBA__SettingsView)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        QListWidgetItem(self.tabs)
        self.tabs.setObjectName(u"tabs")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.tabs.sizePolicy().hasHeightForWidth())
        self.tabs.setSizePolicy(sizePolicy1)
        self.tabs.setMaximumSize(QSize(180, 16777215))

        self.gridLayout.addWidget(self.tabs, 1, 0, 1, 1)

        self.stackedWidget = QStackedWidget(QGBA__SettingsView)
        self.stackedWidget.setObjectName(u"stackedWidget")
        self.av = QWidget()
        self.av.setObjectName(u"av")
        self.formLayout = QVBoxLayout(self.av)
        self.formLayout.setObjectName(u"formLayout")
        self.groupBox_4 = QGroupBox(self.av)
        self.groupBox_4.setObjectName(u"groupBox_4")
        self.formLayout_12 = QFormLayout(self.groupBox_4)
        self.formLayout_12.setObjectName(u"formLayout_12")
        self.label_14 = QLabel(self.groupBox_4)
        self.label_14.setObjectName(u"label_14")

        self.formLayout_12.setWidget(0, QFormLayout.LabelRole, self.label_14)

        self.audioDriver = QComboBox(self.groupBox_4)
        self.audioDriver.setObjectName(u"audioDriver")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.audioDriver.sizePolicy().hasHeightForWidth())
        self.audioDriver.setSizePolicy(sizePolicy2)

        self.formLayout_12.setWidget(0, QFormLayout.FieldRole, self.audioDriver)

        self.audioBufferSizeLabel = QLabel(self.groupBox_4)
        self.audioBufferSizeLabel.setObjectName(u"audioBufferSizeLabel")

        self.formLayout_12.setWidget(1, QFormLayout.LabelRole, self.audioBufferSizeLabel)

        self.horizontalLayout_11 = QHBoxLayout()
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.audioBufferSize = QComboBox(self.groupBox_4)
        self.audioBufferSize.addItem("")
        self.audioBufferSize.addItem("")
        self.audioBufferSize.addItem("")
        self.audioBufferSize.addItem("")
        self.audioBufferSize.addItem("")
        self.audioBufferSize.addItem("")
        self.audioBufferSize.addItem("")
        self.audioBufferSize.setObjectName(u"audioBufferSize")
        self.audioBufferSize.setEditable(True)

        self.horizontalLayout_11.addWidget(self.audioBufferSize)

        self.label_16 = QLabel(self.groupBox_4)
        self.label_16.setObjectName(u"label_16")

        self.horizontalLayout_11.addWidget(self.label_16)


        self.formLayout_12.setLayout(1, QFormLayout.FieldRole, self.horizontalLayout_11)

        self.label_19 = QLabel(self.groupBox_4)
        self.label_19.setObjectName(u"label_19")

        self.formLayout_12.setWidget(2, QFormLayout.LabelRole, self.label_19)

        self.horizontalLayout_14 = QHBoxLayout()
        self.horizontalLayout_14.setObjectName(u"horizontalLayout_14")
        self.sampleRate = QComboBox(self.groupBox_4)
        self.sampleRate.addItem("")
        self.sampleRate.addItem("")
        self.sampleRate.addItem("")
        self.sampleRate.addItem("")
        self.sampleRate.setObjectName(u"sampleRate")
        self.sampleRate.setEditable(True)

        self.horizontalLayout_14.addWidget(self.sampleRate)

        self.label_20 = QLabel(self.groupBox_4)
        self.label_20.setObjectName(u"label_20")

        self.horizontalLayout_14.addWidget(self.label_20)


        self.formLayout_12.setLayout(2, QFormLayout.FieldRole, self.horizontalLayout_14)

        self.label_17 = QLabel(self.groupBox_4)
        self.label_17.setObjectName(u"label_17")

        self.formLayout_12.setWidget(4, QFormLayout.LabelRole, self.label_17)

        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.volume = QSlider(self.groupBox_4)
        self.volume.setObjectName(u"volume")
        self.volume.setMinimumSize(QSize(128, 0))
        self.volume.setMaximum(256)
        self.volume.setPageStep(16)
        self.volume.setValue(256)
        self.volume.setOrientation(Qt.Horizontal)

        self.horizontalLayout_6.addWidget(self.volume)

        self.mute = QCheckBox(self.groupBox_4)
        self.mute.setObjectName(u"mute")

        self.horizontalLayout_6.addWidget(self.mute)


        self.formLayout_12.setLayout(4, QFormLayout.FieldRole, self.horizontalLayout_6)

        self.label_34 = QLabel(self.groupBox_4)
        self.label_34.setObjectName(u"label_34")

        self.formLayout_12.setWidget(5, QFormLayout.LabelRole, self.label_34)

        self.horizontalLayout_17 = QHBoxLayout()
        self.horizontalLayout_17.setObjectName(u"horizontalLayout_17")
        self.volumeFf = QSlider(self.groupBox_4)
        self.volumeFf.setObjectName(u"volumeFf")
        self.volumeFf.setMinimumSize(QSize(128, 0))
        self.volumeFf.setMaximum(256)
        self.volumeFf.setPageStep(16)
        self.volumeFf.setValue(256)
        self.volumeFf.setOrientation(Qt.Horizontal)

        self.horizontalLayout_17.addWidget(self.volumeFf)

        self.muteFf = QCheckBox(self.groupBox_4)
        self.muteFf.setObjectName(u"muteFf")

        self.horizontalLayout_17.addWidget(self.muteFf)


        self.formLayout_12.setLayout(5, QFormLayout.FieldRole, self.horizontalLayout_17)

        self.label_43 = QLabel(self.groupBox_4)
        self.label_43.setObjectName(u"label_43")

        self.formLayout_12.setWidget(7, QFormLayout.LabelRole, self.label_43)

        self.multiplayerAudioAll = QRadioButton(self.groupBox_4)
        self.multiplayerAudio = QButtonGroup(QGBA__SettingsView)
        self.multiplayerAudio.setObjectName(u"multiplayerAudio")
        self.multiplayerAudio.addButton(self.multiplayerAudioAll)
        self.multiplayerAudioAll.setObjectName(u"multiplayerAudioAll")
        self.multiplayerAudioAll.setChecked(True)

        self.formLayout_12.setWidget(7, QFormLayout.FieldRole, self.multiplayerAudioAll)

        self.multiplayerAudio1 = QRadioButton(self.groupBox_4)
        self.multiplayerAudio.addButton(self.multiplayerAudio1)
        self.multiplayerAudio1.setObjectName(u"multiplayerAudio1")

        self.formLayout_12.setWidget(8, QFormLayout.FieldRole, self.multiplayerAudio1)

        self.multiplayerAudioActive = QRadioButton(self.groupBox_4)
        self.multiplayerAudio.addButton(self.multiplayerAudioActive)
        self.multiplayerAudioActive.setObjectName(u"multiplayerAudioActive")

        self.formLayout_12.setWidget(9, QFormLayout.FieldRole, self.multiplayerAudioActive)

        self.line_4 = QFrame(self.groupBox_4)
        self.line_4.setObjectName(u"line_4")
        self.line_4.setFrameShape(QFrame.Shape.HLine)
        self.line_4.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_12.setWidget(3, QFormLayout.SpanningRole, self.line_4)

        self.line_5 = QFrame(self.groupBox_4)
        self.line_5.setObjectName(u"line_5")
        self.line_5.setFrameShape(QFrame.Shape.HLine)
        self.line_5.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_12.setWidget(6, QFormLayout.SpanningRole, self.line_5)


        self.formLayout.addWidget(self.groupBox_4)

        self.groupBox_5 = QGroupBox(self.av)
        self.groupBox_5.setObjectName(u"groupBox_5")
        self.formLayout_13 = QFormLayout(self.groupBox_5)
        self.formLayout_13.setObjectName(u"formLayout_13")
        self.label_10 = QLabel(self.groupBox_5)
        self.label_10.setObjectName(u"label_10")

        self.formLayout_13.setWidget(0, QFormLayout.LabelRole, self.label_10)

        self.displayDriver = QComboBox(self.groupBox_5)
        self.displayDriver.setObjectName(u"displayDriver")
        sizePolicy2.setHeightForWidth(self.displayDriver.sizePolicy().hasHeightForWidth())
        self.displayDriver.setSizePolicy(sizePolicy2)

        self.formLayout_13.setWidget(0, QFormLayout.FieldRole, self.displayDriver)

        self.label_9 = QLabel(self.groupBox_5)
        self.label_9.setObjectName(u"label_9")

        self.formLayout_13.setWidget(1, QFormLayout.LabelRole, self.label_9)

        self.horizontalLayout_16 = QHBoxLayout()
        self.horizontalLayout_16.setObjectName(u"horizontalLayout_16")
        self.label_12 = QLabel(self.groupBox_5)
        self.label_12.setObjectName(u"label_12")

        self.horizontalLayout_16.addWidget(self.label_12)

        self.frameskip = QSpinBox(self.groupBox_5)
        self.frameskip.setObjectName(u"frameskip")

        self.horizontalLayout_16.addWidget(self.frameskip)

        self.label_13 = QLabel(self.groupBox_5)
        self.label_13.setObjectName(u"label_13")

        self.horizontalLayout_16.addWidget(self.label_13)


        self.formLayout_13.setLayout(1, QFormLayout.FieldRole, self.horizontalLayout_16)

        self.lockAspectRatio = QCheckBox(self.groupBox_5)
        self.lockAspectRatio.setObjectName(u"lockAspectRatio")

        self.formLayout_13.setWidget(3, QFormLayout.FieldRole, self.lockAspectRatio)

        self.lockIntegerScaling = QCheckBox(self.groupBox_5)
        self.lockIntegerScaling.setObjectName(u"lockIntegerScaling")

        self.formLayout_13.setWidget(4, QFormLayout.FieldRole, self.lockIntegerScaling)

        self.interframeBlending = QCheckBox(self.groupBox_5)
        self.interframeBlending.setObjectName(u"interframeBlending")

        self.formLayout_13.setWidget(5, QFormLayout.FieldRole, self.interframeBlending)

        self.resampleVideo = QCheckBox(self.groupBox_5)
        self.resampleVideo.setObjectName(u"resampleVideo")

        self.formLayout_13.setWidget(6, QFormLayout.FieldRole, self.resampleVideo)

        self.line_12 = QFrame(self.groupBox_5)
        self.line_12.setObjectName(u"line_12")
        self.line_12.setFrameShape(QFrame.Shape.HLine)
        self.line_12.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_13.setWidget(2, QFormLayout.SpanningRole, self.line_12)


        self.formLayout.addWidget(self.groupBox_5)

        self.stackedWidget.addWidget(self.av)
        self.gameplay = QWidget()
        self.gameplay.setObjectName(u"gameplay")
        self.formLayout_14 = QFormLayout(self.gameplay)
        self.formLayout_14.setObjectName(u"formLayout_14")
        self.label_3 = QLabel(self.gameplay)
        self.label_3.setObjectName(u"label_3")

        self.formLayout_14.setWidget(0, QFormLayout.LabelRole, self.label_3)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.fpsTarget = QDoubleSpinBox(self.gameplay)
        self.fpsTarget.setObjectName(u"fpsTarget")
        self.fpsTarget.setDecimals(4)
        self.fpsTarget.setMinimum(0.010000000000000)
        self.fpsTarget.setMaximum(240.000000000000000)
        self.fpsTarget.setValue(60.000000000000000)

        self.horizontalLayout_2.addWidget(self.fpsTarget)

        self.label_11 = QLabel(self.gameplay)
        self.label_11.setObjectName(u"label_11")

        self.horizontalLayout_2.addWidget(self.label_11)


        self.formLayout_14.setLayout(0, QFormLayout.FieldRole, self.horizontalLayout_2)

        self.nativeGB = QPushButton(self.gameplay)
        self.nativeGB.setObjectName(u"nativeGB")

        self.formLayout_14.setWidget(1, QFormLayout.FieldRole, self.nativeGB)

        self.label_2 = QLabel(self.gameplay)
        self.label_2.setObjectName(u"label_2")

        self.formLayout_14.setWidget(2, QFormLayout.LabelRole, self.label_2)

        self.horizontalLayout_10 = QHBoxLayout()
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.videoSync = QCheckBox(self.gameplay)
        self.videoSync.setObjectName(u"videoSync")

        self.horizontalLayout_10.addWidget(self.videoSync)

        self.audioSync = QCheckBox(self.gameplay)
        self.audioSync.setObjectName(u"audioSync")

        self.horizontalLayout_10.addWidget(self.audioSync)


        self.formLayout_14.setLayout(2, QFormLayout.FieldRole, self.horizontalLayout_10)

        self.line_16 = QFrame(self.gameplay)
        self.line_16.setObjectName(u"line_16")
        self.line_16.setFrameShape(QFrame.Shape.HLine)
        self.line_16.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_14.setWidget(3, QFormLayout.SpanningRole, self.line_16)

        self.label_24 = QLabel(self.gameplay)
        self.label_24.setObjectName(u"label_24")

        self.formLayout_14.setWidget(4, QFormLayout.LabelRole, self.label_24)

        self.autoload = QCheckBox(self.gameplay)
        self.autoload.setObjectName(u"autoload")
        self.autoload.setChecked(True)

        self.formLayout_14.setWidget(4, QFormLayout.FieldRole, self.autoload)

        self.cheatAutoload = QCheckBox(self.gameplay)
        self.cheatAutoload.setObjectName(u"cheatAutoload")
        self.cheatAutoload.setChecked(True)

        self.formLayout_14.setWidget(5, QFormLayout.FieldRole, self.cheatAutoload)

        self.line_9 = QFrame(self.gameplay)
        self.line_9.setObjectName(u"line_9")
        self.line_9.setFrameShape(QFrame.Shape.HLine)
        self.line_9.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_14.setWidget(6, QFormLayout.SpanningRole, self.line_9)

        self.autosave = QCheckBox(self.gameplay)
        self.autosave.setObjectName(u"autosave")
        self.autosave.setChecked(True)

        self.formLayout_14.setWidget(7, QFormLayout.FieldRole, self.autosave)

        self.cheatAutosave = QCheckBox(self.gameplay)
        self.cheatAutosave.setObjectName(u"cheatAutosave")
        self.cheatAutosave.setChecked(True)

        self.formLayout_14.setWidget(8, QFormLayout.FieldRole, self.cheatAutosave)

        self.line_21 = QFrame(self.gameplay)
        self.line_21.setObjectName(u"line_21")
        self.line_21.setFrameShape(QFrame.Shape.HLine)
        self.line_21.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_14.setWidget(9, QFormLayout.SpanningRole, self.line_21)

        self.label_51 = QLabel(self.gameplay)
        self.label_51.setObjectName(u"label_51")

        self.formLayout_14.setWidget(10, QFormLayout.LabelRole, self.label_51)

        self.saveStateScreenshot = QCheckBox(self.gameplay)
        self.saveStateScreenshot.setObjectName(u"saveStateScreenshot")
        self.saveStateScreenshot.setChecked(True)

        self.formLayout_14.setWidget(10, QFormLayout.FieldRole, self.saveStateScreenshot)

        self.saveStateSave = QCheckBox(self.gameplay)
        self.saveStateSave.setObjectName(u"saveStateSave")
        self.saveStateSave.setChecked(True)

        self.formLayout_14.setWidget(11, QFormLayout.FieldRole, self.saveStateSave)

        self.saveStateCheats = QCheckBox(self.gameplay)
        self.saveStateCheats.setObjectName(u"saveStateCheats")
        self.saveStateCheats.setChecked(True)

        self.formLayout_14.setWidget(12, QFormLayout.FieldRole, self.saveStateCheats)

        self.line_22 = QFrame(self.gameplay)
        self.line_22.setObjectName(u"line_22")
        self.line_22.setFrameShape(QFrame.Shape.HLine)
        self.line_22.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_14.setWidget(13, QFormLayout.SpanningRole, self.line_22)

        self.label_52 = QLabel(self.gameplay)
        self.label_52.setObjectName(u"label_52")

        self.formLayout_14.setWidget(14, QFormLayout.LabelRole, self.label_52)

        self.loadStateScreenshot = QCheckBox(self.gameplay)
        self.loadStateScreenshot.setObjectName(u"loadStateScreenshot")
        self.loadStateScreenshot.setChecked(True)

        self.formLayout_14.setWidget(14, QFormLayout.FieldRole, self.loadStateScreenshot)

        self.loadStateSave = QCheckBox(self.gameplay)
        self.loadStateSave.setObjectName(u"loadStateSave")

        self.formLayout_14.setWidget(15, QFormLayout.FieldRole, self.loadStateSave)

        self.loadStateCheats = QCheckBox(self.gameplay)
        self.loadStateCheats.setObjectName(u"loadStateCheats")

        self.formLayout_14.setWidget(16, QFormLayout.FieldRole, self.loadStateCheats)

        self.line_2 = QFrame(self.gameplay)
        self.line_2.setObjectName(u"line_2")
        self.line_2.setFrameShape(QFrame.Shape.HLine)
        self.line_2.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_14.setWidget(17, QFormLayout.SpanningRole, self.line_2)

        self.useDiscordPresence = QCheckBox(self.gameplay)
        self.useDiscordPresence.setObjectName(u"useDiscordPresence")

        self.formLayout_14.setWidget(18, QFormLayout.FieldRole, self.useDiscordPresence)

        self.stackedWidget.addWidget(self.gameplay)
        self.interface_2 = QWidget()
        self.interface_2.setObjectName(u"interface_2")
        self.formLayout_4 = QFormLayout(self.interface_2)
        self.formLayout_4.setObjectName(u"formLayout_4")
        self.label_26 = QLabel(self.interface_2)
        self.label_26.setObjectName(u"label_26")

        self.formLayout_4.setWidget(0, QFormLayout.LabelRole, self.label_26)

        self.languages = QComboBox(self.interface_2)
        self.languages.setObjectName(u"languages")

        self.formLayout_4.setWidget(0, QFormLayout.FieldRole, self.languages)

        self.line_10 = QFrame(self.interface_2)
        self.line_10.setObjectName(u"line_10")
        self.line_10.setFrameShape(QFrame.Shape.HLine)
        self.line_10.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_4.setWidget(1, QFormLayout.SpanningRole, self.line_10)

        self.label_6 = QLabel(self.interface_2)
        self.label_6.setObjectName(u"label_6")

        self.formLayout_4.setWidget(2, QFormLayout.LabelRole, self.label_6)

        self.libraryStyle = QComboBox(self.interface_2)
        self.libraryStyle.addItem("")
        self.libraryStyle.addItem("")
        self.libraryStyle.setObjectName(u"libraryStyle")

        self.formLayout_4.setWidget(2, QFormLayout.FieldRole, self.libraryStyle)

        self.showLibrary = QCheckBox(self.interface_2)
        self.showLibrary.setObjectName(u"showLibrary")
        self.showLibrary.setChecked(True)

        self.formLayout_4.setWidget(3, QFormLayout.FieldRole, self.showLibrary)

        self.showFilenameInLibrary = QCheckBox(self.interface_2)
        self.showFilenameInLibrary.setObjectName(u"showFilenameInLibrary")

        self.formLayout_4.setWidget(4, QFormLayout.FieldRole, self.showFilenameInLibrary)

        self.clearCache = QPushButton(self.interface_2)
        self.clearCache.setObjectName(u"clearCache")

        self.formLayout_4.setWidget(5, QFormLayout.FieldRole, self.clearCache)

        self.line_8 = QFrame(self.interface_2)
        self.line_8.setObjectName(u"line_8")
        self.line_8.setFrameShape(QFrame.Shape.HLine)
        self.line_8.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_4.setWidget(6, QFormLayout.SpanningRole, self.line_8)

        self.allowOpposingDirections = QCheckBox(self.interface_2)
        self.allowOpposingDirections.setObjectName(u"allowOpposingDirections")

        self.formLayout_4.setWidget(7, QFormLayout.FieldRole, self.allowOpposingDirections)

        self.suspendScreensaver = QCheckBox(self.interface_2)
        self.suspendScreensaver.setObjectName(u"suspendScreensaver")
        self.suspendScreensaver.setChecked(True)

        self.formLayout_4.setWidget(8, QFormLayout.FieldRole, self.suspendScreensaver)

        self.label_41 = QLabel(self.interface_2)
        self.label_41.setObjectName(u"label_41")

        self.formLayout_4.setWidget(9, QFormLayout.LabelRole, self.label_41)

        self.horizontalLayout_21 = QHBoxLayout()
        self.horizontalLayout_21.setObjectName(u"horizontalLayout_21")
        self.pauseOnFocusLost = QCheckBox(self.interface_2)
        self.pauseOnFocusLost.setObjectName(u"pauseOnFocusLost")

        self.horizontalLayout_21.addWidget(self.pauseOnFocusLost)

        self.muteOnFocusLost = QCheckBox(self.interface_2)
        self.muteOnFocusLost.setObjectName(u"muteOnFocusLost")

        self.horizontalLayout_21.addWidget(self.muteOnFocusLost)


        self.formLayout_4.setLayout(9, QFormLayout.FieldRole, self.horizontalLayout_21)

        self.label_42 = QLabel(self.interface_2)
        self.label_42.setObjectName(u"label_42")

        self.formLayout_4.setWidget(10, QFormLayout.LabelRole, self.label_42)

        self.horizontalLayout_24 = QHBoxLayout()
        self.horizontalLayout_24.setObjectName(u"horizontalLayout_24")
        self.pauseOnMinimize = QCheckBox(self.interface_2)
        self.pauseOnMinimize.setObjectName(u"pauseOnMinimize")

        self.horizontalLayout_24.addWidget(self.pauseOnMinimize)

        self.muteOnMinimize = QCheckBox(self.interface_2)
        self.muteOnMinimize.setObjectName(u"muteOnMinimize")

        self.horizontalLayout_24.addWidget(self.muteOnMinimize)


        self.formLayout_4.setLayout(10, QFormLayout.FieldRole, self.horizontalLayout_24)

        self.line_17 = QFrame(self.interface_2)
        self.line_17.setObjectName(u"line_17")
        self.line_17.setFrameShape(QFrame.Shape.HLine)
        self.line_17.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_4.setWidget(11, QFormLayout.SpanningRole, self.line_17)

        self.dynamicTitle = QCheckBox(self.interface_2)
        self.dynamicTitle.setObjectName(u"dynamicTitle")
        self.dynamicTitle.setChecked(True)

        self.formLayout_4.setWidget(12, QFormLayout.FieldRole, self.dynamicTitle)

        self.showFps = QCheckBox(self.interface_2)
        self.showFps.setObjectName(u"showFps")
        self.showFps.setChecked(True)

        self.formLayout_4.setWidget(13, QFormLayout.FieldRole, self.showFps)

        self.showFilename = QCheckBox(self.interface_2)
        self.showFilename.setObjectName(u"showFilename")
        self.showFilename.setChecked(True)

        self.formLayout_4.setWidget(14, QFormLayout.FieldRole, self.showFilename)

        self.line_18 = QFrame(self.interface_2)
        self.line_18.setObjectName(u"line_18")
        self.line_18.setFrameShape(QFrame.Shape.HLine)
        self.line_18.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_4.setWidget(15, QFormLayout.SpanningRole, self.line_18)

        self.showOSD = QCheckBox(self.interface_2)
        self.showOSD.setObjectName(u"showOSD")
        self.showOSD.setChecked(True)

        self.formLayout_4.setWidget(16, QFormLayout.FieldRole, self.showOSD)

        self.osdDisplay = QVBoxLayout()
        self.osdDisplay.setObjectName(u"osdDisplay")
        self.osdDisplay.setContentsMargins(20, -1, -1, -1)
        self.showFrameCounter = QCheckBox(self.interface_2)
        self.showFrameCounter.setObjectName(u"showFrameCounter")

        self.osdDisplay.addWidget(self.showFrameCounter)

        self.showResetInfo = QCheckBox(self.interface_2)
        self.showResetInfo.setObjectName(u"showResetInfo")

        self.osdDisplay.addWidget(self.showResetInfo)


        self.formLayout_4.setLayout(17, QFormLayout.FieldRole, self.osdDisplay)

        self.stackedWidget.addWidget(self.interface_2)
        self.update = QWidget()
        self.update.setObjectName(u"update")
        self.formLayout_11 = QFormLayout(self.update)
        self.formLayout_11.setObjectName(u"formLayout_11")
        self.label_46 = QLabel(self.update)
        self.label_46.setObjectName(u"label_46")

        self.formLayout_11.setWidget(0, QFormLayout.LabelRole, self.label_46)

        self.currentChannel = QLabel(self.update)
        self.currentChannel.setObjectName(u"currentChannel")
        self.currentChannel.setText(u"None")

        self.formLayout_11.setWidget(0, QFormLayout.FieldRole, self.currentChannel)

        self.label_50 = QLabel(self.update)
        self.label_50.setObjectName(u"label_50")

        self.formLayout_11.setWidget(1, QFormLayout.LabelRole, self.label_50)

        self.currentVersion = QLabel(self.update)
        self.currentVersion.setObjectName(u"currentVersion")
        self.currentVersion.setText(u"0")
        self.currentVersion.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.formLayout_11.setWidget(1, QFormLayout.FieldRole, self.currentVersion)

        self.line_20 = QFrame(self.update)
        self.line_20.setObjectName(u"line_20")
        self.line_20.setFrameShape(QFrame.Shape.HLine)
        self.line_20.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_11.setWidget(2, QFormLayout.SpanningRole, self.line_20)

        self.label_45 = QLabel(self.update)
        self.label_45.setObjectName(u"label_45")

        self.formLayout_11.setWidget(3, QFormLayout.LabelRole, self.label_45)

        self.updateChannel = QComboBox(self.update)
        self.updateChannel.setObjectName(u"updateChannel")

        self.formLayout_11.setWidget(3, QFormLayout.FieldRole, self.updateChannel)

        self.label_44 = QLabel(self.update)
        self.label_44.setObjectName(u"label_44")

        self.formLayout_11.setWidget(4, QFormLayout.LabelRole, self.label_44)

        self.availVersion = QLabel(self.update)
        self.availVersion.setObjectName(u"availVersion")
        self.availVersion.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.formLayout_11.setWidget(4, QFormLayout.FieldRole, self.availVersion)

        self.label_49 = QLabel(self.update)
        self.label_49.setObjectName(u"label_49")

        self.formLayout_11.setWidget(5, QFormLayout.LabelRole, self.label_49)

        self.lastChecked = QLabel(self.update)
        self.lastChecked.setObjectName(u"lastChecked")
        self.lastChecked.setText(u"Never")

        self.formLayout_11.setWidget(5, QFormLayout.FieldRole, self.lastChecked)

        self.line_11 = QFrame(self.update)
        self.line_11.setObjectName(u"line_11")
        self.line_11.setFrameShape(QFrame.Shape.HLine)
        self.line_11.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_11.setWidget(6, QFormLayout.SpanningRole, self.line_11)

        self.updateAutoCheck = QCheckBox(self.update)
        self.updateAutoCheck.setObjectName(u"updateAutoCheck")

        self.formLayout_11.setWidget(7, QFormLayout.FieldRole, self.updateAutoCheck)

        self.checkUpdate = QPushButton(self.update)
        self.checkUpdate.setObjectName(u"checkUpdate")

        self.formLayout_11.setWidget(8, QFormLayout.FieldRole, self.checkUpdate)

        self.stackedWidget.addWidget(self.update)
        self.emulation = QWidget()
        self.emulation.setObjectName(u"emulation")
        self.formLayout_2 = QFormLayout(self.emulation)
        self.formLayout_2.setObjectName(u"formLayout_2")
        self.formLayout_2.setFieldGrowthPolicy(QFormLayout.FieldsStayAtSizeHint)
        self.label_18 = QLabel(self.emulation)
        self.label_18.setObjectName(u"label_18")

        self.formLayout_2.setWidget(0, QFormLayout.LabelRole, self.label_18)

        self.horizontalLayout_5 = QHBoxLayout()
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.fastForwardRatio = QDoubleSpinBox(self.emulation)
        self.fastForwardRatio.setObjectName(u"fastForwardRatio")
        self.fastForwardRatio.setEnabled(False)
        self.fastForwardRatio.setSuffix(u"\u00d7")
        self.fastForwardRatio.setMinimum(0.010000000000000)
        self.fastForwardRatio.setMaximum(20.000000000000000)
        self.fastForwardRatio.setSingleStep(0.500000000000000)
        self.fastForwardRatio.setValue(5.000000000000000)

        self.horizontalLayout_5.addWidget(self.fastForwardRatio)

        self.fastForwardUnbounded = QCheckBox(self.emulation)
        self.fastForwardUnbounded.setObjectName(u"fastForwardUnbounded")
        self.fastForwardUnbounded.setChecked(True)

        self.horizontalLayout_5.addWidget(self.fastForwardUnbounded)


        self.formLayout_2.setLayout(0, QFormLayout.FieldRole, self.horizontalLayout_5)

        self.label_181 = QLabel(self.emulation)
        self.label_181.setObjectName(u"label_181")

        self.formLayout_2.setWidget(1, QFormLayout.LabelRole, self.label_181)

        self.horizontalLayout_51 = QHBoxLayout()
        self.horizontalLayout_51.setObjectName(u"horizontalLayout_51")
        self.fastForwardHeldRatio = QDoubleSpinBox(self.emulation)
        self.fastForwardHeldRatio.setObjectName(u"fastForwardHeldRatio")
        self.fastForwardHeldRatio.setEnabled(False)
        self.fastForwardHeldRatio.setSuffix(u"\u00d7")
        self.fastForwardHeldRatio.setMinimum(0.010000000000000)
        self.fastForwardHeldRatio.setMaximum(20.000000000000000)
        self.fastForwardHeldRatio.setSingleStep(0.500000000000000)
        self.fastForwardHeldRatio.setValue(5.000000000000000)

        self.horizontalLayout_51.addWidget(self.fastForwardHeldRatio)

        self.fastForwardHeldUnbounded = QCheckBox(self.emulation)
        self.fastForwardHeldUnbounded.setObjectName(u"fastForwardHeldUnbounded")
        self.fastForwardHeldUnbounded.setChecked(True)

        self.horizontalLayout_51.addWidget(self.fastForwardHeldUnbounded)


        self.formLayout_2.setLayout(1, QFormLayout.FieldRole, self.horizontalLayout_51)

        self.label_31 = QLabel(self.emulation)
        self.label_31.setObjectName(u"label_31")

        self.formLayout_2.setWidget(2, QFormLayout.LabelRole, self.label_31)

        self.autofireThreshold = QSpinBox(self.emulation)
        self.autofireThreshold.setObjectName(u"autofireThreshold")
        self.autofireThreshold.setMinimum(1)
        self.autofireThreshold.setMaximum(60)

        self.formLayout_2.setWidget(2, QFormLayout.FieldRole, self.autofireThreshold)

        self.line = QFrame(self.emulation)
        self.line.setObjectName(u"line")
        self.line.setFrameShape(QFrame.Shape.HLine)
        self.line.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_2.setWidget(3, QFormLayout.SpanningRole, self.line)

        self.rewind = QCheckBox(self.emulation)
        self.rewind.setObjectName(u"rewind")

        self.formLayout_2.setWidget(4, QFormLayout.FieldRole, self.rewind)

        self.label_8 = QLabel(self.emulation)
        self.label_8.setObjectName(u"label_8")

        self.formLayout_2.setWidget(5, QFormLayout.LabelRole, self.label_8)

        self.horizontalLayout_13 = QHBoxLayout()
        self.horizontalLayout_13.setObjectName(u"horizontalLayout_13")
        self.rewindCapacity = QSpinBox(self.emulation)
        self.rewindCapacity.setObjectName(u"rewindCapacity")
        self.rewindCapacity.setMaximum(3600)

        self.horizontalLayout_13.addWidget(self.rewindCapacity)

        self.label_7 = QLabel(self.emulation)
        self.label_7.setObjectName(u"label_7")

        self.horizontalLayout_13.addWidget(self.label_7)


        self.formLayout_2.setLayout(5, QFormLayout.FieldRole, self.horizontalLayout_13)

        self.line_3 = QFrame(self.emulation)
        self.line_3.setObjectName(u"line_3")
        self.line_3.setFrameShape(QFrame.Shape.HLine)
        self.line_3.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_2.setWidget(6, QFormLayout.SpanningRole, self.line_3)

        self.label_15 = QLabel(self.emulation)
        self.label_15.setObjectName(u"label_15")

        self.formLayout_2.setWidget(7, QFormLayout.LabelRole, self.label_15)

        self.idleOptimization = QComboBox(self.emulation)
        self.idleOptimization.addItem("")
        self.idleOptimization.addItem("")
        self.idleOptimization.addItem("")
        self.idleOptimization.setObjectName(u"idleOptimization")

        self.formLayout_2.setWidget(7, QFormLayout.FieldRole, self.idleOptimization)

        self.preload = QCheckBox(self.emulation)
        self.preload.setObjectName(u"preload")

        self.formLayout_2.setWidget(8, QFormLayout.FieldRole, self.preload)

        self.forceGbp = QCheckBox(self.emulation)
        self.forceGbp.setObjectName(u"forceGbp")

        self.formLayout_2.setWidget(9, QFormLayout.FieldRole, self.forceGbp)

        self.vbaBugCompat = QCheckBox(self.emulation)
        self.vbaBugCompat.setObjectName(u"vbaBugCompat")
        self.vbaBugCompat.setChecked(True)

        self.formLayout_2.setWidget(10, QFormLayout.FieldRole, self.vbaBugCompat)

        self.stackedWidget.addWidget(self.emulation)
        self.enhancements = QWidget()
        self.enhancements.setObjectName(u"enhancements")
        self.formLayout_6 = QFormLayout(self.enhancements)
        self.formLayout_6.setObjectName(u"formLayout_6")
        self.label_36 = QLabel(self.enhancements)
        self.label_36.setObjectName(u"label_36")

        self.formLayout_6.setWidget(0, QFormLayout.LabelRole, self.label_36)

        self.hwaccelVideo = QComboBox(self.enhancements)
        self.hwaccelVideo.addItem("")
        self.hwaccelVideo.addItem("")
        self.hwaccelVideo.setObjectName(u"hwaccelVideo")

        self.formLayout_6.setWidget(0, QFormLayout.FieldRole, self.hwaccelVideo)

        self.audioHle = QCheckBox(self.enhancements)
        self.audioHle.setObjectName(u"audioHle")

        self.formLayout_6.setWidget(1, QFormLayout.FieldRole, self.audioHle)

        self.oglEnhance = QGroupBox(self.enhancements)
        self.oglEnhance.setObjectName(u"oglEnhance")
        self.formLayout_7 = QFormLayout(self.oglEnhance)
        self.formLayout_7.setObjectName(u"formLayout_7")
        self.label_37 = QLabel(self.oglEnhance)
        self.label_37.setObjectName(u"label_37")

        self.formLayout_7.setWidget(0, QFormLayout.LabelRole, self.label_37)

        self.horizontalLayout_18 = QHBoxLayout()
        self.horizontalLayout_18.setObjectName(u"horizontalLayout_18")
        self.videoScale = QSpinBox(self.oglEnhance)
        self.videoScale.setObjectName(u"videoScale")
        self.videoScale.setSuffix(u"\u00d7")
        self.videoScale.setMinimum(1)
        self.videoScale.setMaximum(16)

        self.horizontalLayout_18.addWidget(self.videoScale)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_18.addItem(self.horizontalSpacer)

        self.videoScaleSize = QLabel(self.oglEnhance)
        self.videoScaleSize.setObjectName(u"videoScaleSize")
        self.videoScaleSize.setEnabled(False)

        self.horizontalLayout_18.addWidget(self.videoScaleSize)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_18.addItem(self.horizontalSpacer_2)


        self.formLayout_7.setLayout(0, QFormLayout.FieldRole, self.horizontalLayout_18)


        self.formLayout_6.setWidget(2, QFormLayout.SpanningRole, self.oglEnhance)

        self.stackedWidget.addWidget(self.enhancements)
        self.bios = QWidget()
        self.bios.setObjectName(u"bios")
        self.formLayout_5 = QFormLayout(self.bios)
        self.formLayout_5.setObjectName(u"formLayout_5")
        self.label = QLabel(self.bios)
        self.label.setObjectName(u"label")

        self.formLayout_5.setWidget(0, QFormLayout.LabelRole, self.label)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.gbBios = QLineEdit(self.bios)
        self.gbBios.setObjectName(u"gbBios")
        sizePolicy2.setHeightForWidth(self.gbBios.sizePolicy().hasHeightForWidth())
        self.gbBios.setSizePolicy(sizePolicy2)

        self.horizontalLayout.addWidget(self.gbBios)

        self.gbBiosBrowse = QPushButton(self.bios)
        self.gbBiosBrowse.setObjectName(u"gbBiosBrowse")

        self.horizontalLayout.addWidget(self.gbBiosBrowse)


        self.formLayout_5.setLayout(0, QFormLayout.FieldRole, self.horizontalLayout)

        self.label_30 = QLabel(self.bios)
        self.label_30.setObjectName(u"label_30")

        self.formLayout_5.setWidget(1, QFormLayout.LabelRole, self.label_30)

        self.horizontalLayout_12 = QHBoxLayout()
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.sgbBios = QLineEdit(self.bios)
        self.sgbBios.setObjectName(u"sgbBios")
        sizePolicy2.setHeightForWidth(self.sgbBios.sizePolicy().hasHeightForWidth())
        self.sgbBios.setSizePolicy(sizePolicy2)

        self.horizontalLayout_12.addWidget(self.sgbBios)

        self.sgbBiosBrowse = QPushButton(self.bios)
        self.sgbBiosBrowse.setObjectName(u"sgbBiosBrowse")

        self.horizontalLayout_12.addWidget(self.sgbBiosBrowse)


        self.formLayout_5.setLayout(1, QFormLayout.FieldRole, self.horizontalLayout_12)

        self.label_5 = QLabel(self.bios)
        self.label_5.setObjectName(u"label_5")

        self.formLayout_5.setWidget(2, QFormLayout.LabelRole, self.label_5)

        self.horizontalLayout_30 = QHBoxLayout()
        self.horizontalLayout_30.setObjectName(u"horizontalLayout_30")
        self.gbcBios = QLineEdit(self.bios)
        self.gbcBios.setObjectName(u"gbcBios")
        sizePolicy2.setHeightForWidth(self.gbcBios.sizePolicy().hasHeightForWidth())
        self.gbcBios.setSizePolicy(sizePolicy2)

        self.horizontalLayout_30.addWidget(self.gbcBios)

        self.gbcBiosBrowse = QPushButton(self.bios)
        self.gbcBiosBrowse.setObjectName(u"gbcBiosBrowse")

        self.horizontalLayout_30.addWidget(self.gbcBiosBrowse)


        self.formLayout_5.setLayout(2, QFormLayout.FieldRole, self.horizontalLayout_30)

        self.label_4 = QLabel(self.bios)
        self.label_4.setObjectName(u"label_4")

        self.formLayout_5.setWidget(3, QFormLayout.LabelRole, self.label_4)

        self.horizontalLayout_8 = QHBoxLayout()
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.gbaBios = QLineEdit(self.bios)
        self.gbaBios.setObjectName(u"gbaBios")
        sizePolicy2.setHeightForWidth(self.gbaBios.sizePolicy().hasHeightForWidth())
        self.gbaBios.setSizePolicy(sizePolicy2)

        self.horizontalLayout_8.addWidget(self.gbaBios)

        self.gbaBiosBrowse = QPushButton(self.bios)
        self.gbaBiosBrowse.setObjectName(u"gbaBiosBrowse")

        self.horizontalLayout_8.addWidget(self.gbaBiosBrowse)


        self.formLayout_5.setLayout(3, QFormLayout.FieldRole, self.horizontalLayout_8)

        self.useBios = QCheckBox(self.bios)
        self.useBios.setObjectName(u"useBios")
        self.useBios.setChecked(True)

        self.formLayout_5.setWidget(4, QFormLayout.FieldRole, self.useBios)

        self.skipBios = QCheckBox(self.bios)
        self.skipBios.setObjectName(u"skipBios")

        self.formLayout_5.setWidget(5, QFormLayout.FieldRole, self.skipBios)

        self.stackedWidget.addWidget(self.bios)
        self.paths = QWidget()
        self.paths.setObjectName(u"paths")
        self.formLayout_3 = QFormLayout(self.paths)
        self.formLayout_3.setObjectName(u"formLayout_3")
        self.formLayout_3.setFieldGrowthPolicy(QFormLayout.FieldsStayAtSizeHint)
        self.label_21 = QLabel(self.paths)
        self.label_21.setObjectName(u"label_21")

        self.formLayout_3.setWidget(1, QFormLayout.LabelRole, self.label_21)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.savegamePath = QLineEdit(self.paths)
        self.savegamePath.setObjectName(u"savegamePath")
        sizePolicy2.setHeightForWidth(self.savegamePath.sizePolicy().hasHeightForWidth())
        self.savegamePath.setSizePolicy(sizePolicy2)
        self.savegamePath.setMinimumSize(QSize(170, 0))

        self.horizontalLayout_3.addWidget(self.savegamePath)

        self.savegameBrowse = QPushButton(self.paths)
        self.savegameBrowse.setObjectName(u"savegameBrowse")

        self.horizontalLayout_3.addWidget(self.savegameBrowse)


        self.formLayout_3.setLayout(1, QFormLayout.FieldRole, self.horizontalLayout_3)

        self.savegameSameDir = QCheckBox(self.paths)
        self.savegameSameDir.setObjectName(u"savegameSameDir")

        self.formLayout_3.setWidget(2, QFormLayout.FieldRole, self.savegameSameDir)

        self.line_7 = QFrame(self.paths)
        self.line_7.setObjectName(u"line_7")
        self.line_7.setFrameShape(QFrame.Shape.HLine)
        self.line_7.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_3.setWidget(3, QFormLayout.SpanningRole, self.line_7)

        self.label_22 = QLabel(self.paths)
        self.label_22.setObjectName(u"label_22")

        self.formLayout_3.setWidget(4, QFormLayout.LabelRole, self.label_22)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.savestatePath = QLineEdit(self.paths)
        self.savestatePath.setObjectName(u"savestatePath")
        sizePolicy2.setHeightForWidth(self.savestatePath.sizePolicy().hasHeightForWidth())
        self.savestatePath.setSizePolicy(sizePolicy2)
        self.savestatePath.setMinimumSize(QSize(170, 0))

        self.horizontalLayout_4.addWidget(self.savestatePath)

        self.savestateBrowse = QPushButton(self.paths)
        self.savestateBrowse.setObjectName(u"savestateBrowse")

        self.horizontalLayout_4.addWidget(self.savestateBrowse)


        self.formLayout_3.setLayout(4, QFormLayout.FieldRole, self.horizontalLayout_4)

        self.savestateSameDir = QCheckBox(self.paths)
        self.savestateSameDir.setObjectName(u"savestateSameDir")

        self.formLayout_3.setWidget(5, QFormLayout.FieldRole, self.savestateSameDir)

        self.line_6 = QFrame(self.paths)
        self.line_6.setObjectName(u"line_6")
        self.line_6.setFrameShape(QFrame.Shape.HLine)
        self.line_6.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_3.setWidget(6, QFormLayout.SpanningRole, self.line_6)

        self.label_23 = QLabel(self.paths)
        self.label_23.setObjectName(u"label_23")

        self.formLayout_3.setWidget(7, QFormLayout.LabelRole, self.label_23)

        self.horizontalLayout_7 = QHBoxLayout()
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.screenshotPath = QLineEdit(self.paths)
        self.screenshotPath.setObjectName(u"screenshotPath")
        sizePolicy2.setHeightForWidth(self.screenshotPath.sizePolicy().hasHeightForWidth())
        self.screenshotPath.setSizePolicy(sizePolicy2)
        self.screenshotPath.setMinimumSize(QSize(170, 0))

        self.horizontalLayout_7.addWidget(self.screenshotPath)

        self.screenshotBrowse = QPushButton(self.paths)
        self.screenshotBrowse.setObjectName(u"screenshotBrowse")

        self.horizontalLayout_7.addWidget(self.screenshotBrowse)


        self.formLayout_3.setLayout(7, QFormLayout.FieldRole, self.horizontalLayout_7)

        self.screenshotSameDir = QCheckBox(self.paths)
        self.screenshotSameDir.setObjectName(u"screenshotSameDir")

        self.formLayout_3.setWidget(8, QFormLayout.FieldRole, self.screenshotSameDir)

        self.line_15 = QFrame(self.paths)
        self.line_15.setObjectName(u"line_15")
        self.line_15.setFrameShape(QFrame.Shape.HLine)
        self.line_15.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_3.setWidget(9, QFormLayout.SpanningRole, self.line_15)

        self.label_47 = QLabel(self.paths)
        self.label_47.setObjectName(u"label_47")

        self.formLayout_3.setWidget(10, QFormLayout.LabelRole, self.label_47)

        self.horizontalLayout_26 = QHBoxLayout()
        self.horizontalLayout_26.setObjectName(u"horizontalLayout_26")
        self.patchPath = QLineEdit(self.paths)
        self.patchPath.setObjectName(u"patchPath")
        sizePolicy2.setHeightForWidth(self.patchPath.sizePolicy().hasHeightForWidth())
        self.patchPath.setSizePolicy(sizePolicy2)
        self.patchPath.setMinimumSize(QSize(170, 0))

        self.horizontalLayout_26.addWidget(self.patchPath)

        self.patchBrowse = QPushButton(self.paths)
        self.patchBrowse.setObjectName(u"patchBrowse")

        self.horizontalLayout_26.addWidget(self.patchBrowse)


        self.formLayout_3.setLayout(10, QFormLayout.FieldRole, self.horizontalLayout_26)

        self.patchSameDir = QCheckBox(self.paths)
        self.patchSameDir.setObjectName(u"patchSameDir")

        self.formLayout_3.setWidget(11, QFormLayout.FieldRole, self.patchSameDir)

        self.line_14 = QFrame(self.paths)
        self.line_14.setObjectName(u"line_14")
        self.line_14.setFrameShape(QFrame.Shape.HLine)
        self.line_14.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_3.setWidget(12, QFormLayout.SpanningRole, self.line_14)

        self.label_48 = QLabel(self.paths)
        self.label_48.setObjectName(u"label_48")

        self.formLayout_3.setWidget(13, QFormLayout.LabelRole, self.label_48)

        self.horizontalLayout_27 = QHBoxLayout()
        self.horizontalLayout_27.setObjectName(u"horizontalLayout_27")
        self.cheatsPath = QLineEdit(self.paths)
        self.cheatsPath.setObjectName(u"cheatsPath")
        sizePolicy2.setHeightForWidth(self.cheatsPath.sizePolicy().hasHeightForWidth())
        self.cheatsPath.setSizePolicy(sizePolicy2)
        self.cheatsPath.setMinimumSize(QSize(170, 0))

        self.horizontalLayout_27.addWidget(self.cheatsPath)

        self.cheatsBrowse = QPushButton(self.paths)
        self.cheatsBrowse.setObjectName(u"cheatsBrowse")

        self.horizontalLayout_27.addWidget(self.cheatsBrowse)


        self.formLayout_3.setLayout(13, QFormLayout.FieldRole, self.horizontalLayout_27)

        self.cheatsSameDir = QCheckBox(self.paths)
        self.cheatsSameDir.setObjectName(u"cheatsSameDir")

        self.formLayout_3.setWidget(14, QFormLayout.FieldRole, self.cheatsSameDir)

        self.stackedWidget.addWidget(self.paths)
        self.logging = QWidget()
        self.logging.setObjectName(u"logging")
        self.verticalLayout = QVBoxLayout(self.logging)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.loggingView = QTableView(self.logging)
        self.loggingView.setObjectName(u"loggingView")
        self.loggingView.horizontalHeader().setMinimumSectionSize(0)
        self.loggingView.horizontalHeader().setDefaultSectionSize(77)

        self.verticalLayout.addWidget(self.loggingView)

        self.horizontalLayout_19 = QHBoxLayout()
        self.horizontalLayout_19.setObjectName(u"horizontalLayout_19")
        self.logToFile = QCheckBox(self.logging)
        self.logToFile.setObjectName(u"logToFile")

        self.horizontalLayout_19.addWidget(self.logToFile)

        self.logToStdout = QCheckBox(self.logging)
        self.logToStdout.setObjectName(u"logToStdout")

        self.horizontalLayout_19.addWidget(self.logToStdout)


        self.verticalLayout.addLayout(self.horizontalLayout_19)

        self.horizontalLayout_20 = QHBoxLayout()
        self.horizontalLayout_20.setObjectName(u"horizontalLayout_20")
        self.logFile = QLineEdit(self.logging)
        self.logFile.setObjectName(u"logFile")

        self.horizontalLayout_20.addWidget(self.logFile)

        self.logFileBrowse = QPushButton(self.logging)
        self.logFileBrowse.setObjectName(u"logFileBrowse")

        self.horizontalLayout_20.addWidget(self.logFileBrowse)


        self.verticalLayout.addLayout(self.horizontalLayout_20)

        self.stackedWidget.addWidget(self.logging)
        self.gb = QWidget()
        self.gb.setObjectName(u"gb")
        self.verticalLayout_2 = QVBoxLayout(self.gb)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.groupBox_2 = QGroupBox(self.gb)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.formLayout_9 = QFormLayout(self.groupBox_2)
        self.formLayout_9.setObjectName(u"formLayout_9")
        self.label_29 = QLabel(self.groupBox_2)
        self.label_29.setObjectName(u"label_29")

        self.formLayout_9.setWidget(0, QFormLayout.LabelRole, self.label_29)

        self.gbModel = QComboBox(self.groupBox_2)
        self.gbModel.setObjectName(u"gbModel")

        self.formLayout_9.setWidget(0, QFormLayout.FieldRole, self.gbModel)

        self.label_32 = QLabel(self.groupBox_2)
        self.label_32.setObjectName(u"label_32")

        self.formLayout_9.setWidget(1, QFormLayout.LabelRole, self.label_32)

        self.sgbModel = QComboBox(self.groupBox_2)
        self.sgbModel.setObjectName(u"sgbModel")

        self.formLayout_9.setWidget(1, QFormLayout.FieldRole, self.sgbModel)

        self.label_33 = QLabel(self.groupBox_2)
        self.label_33.setObjectName(u"label_33")

        self.formLayout_9.setWidget(2, QFormLayout.LabelRole, self.label_33)

        self.cgbModel = QComboBox(self.groupBox_2)
        self.cgbModel.setObjectName(u"cgbModel")

        self.formLayout_9.setWidget(2, QFormLayout.FieldRole, self.cgbModel)

        self.label_38 = QLabel(self.groupBox_2)
        self.label_38.setObjectName(u"label_38")

        self.formLayout_9.setWidget(3, QFormLayout.LabelRole, self.label_38)

        self.cgbHybridModel = QComboBox(self.groupBox_2)
        self.cgbHybridModel.setObjectName(u"cgbHybridModel")

        self.formLayout_9.setWidget(3, QFormLayout.FieldRole, self.cgbHybridModel)

        self.label_39 = QLabel(self.groupBox_2)
        self.label_39.setObjectName(u"label_39")

        self.formLayout_9.setWidget(4, QFormLayout.LabelRole, self.label_39)

        self.cgbSgbModel = QComboBox(self.groupBox_2)
        self.cgbSgbModel.setObjectName(u"cgbSgbModel")

        self.formLayout_9.setWidget(4, QFormLayout.FieldRole, self.cgbSgbModel)

        self.sgbBorders = QCheckBox(self.groupBox_2)
        self.sgbBorders.setObjectName(u"sgbBorders")

        self.formLayout_9.setWidget(5, QFormLayout.FieldRole, self.sgbBorders)


        self.verticalLayout_2.addWidget(self.groupBox_2)

        self.groupBox = QGroupBox(self.gb)
        self.groupBox.setObjectName(u"groupBox")
        self.formLayout_8 = QFormLayout(self.groupBox)
        self.formLayout_8.setObjectName(u"formLayout_8")
        self.label_40 = QLabel(self.groupBox)
        self.label_40.setObjectName(u"label_40")

        self.formLayout_8.setWidget(0, QFormLayout.LabelRole, self.label_40)

        self.colorPreset = QComboBox(self.groupBox)
        self.colorPreset.setObjectName(u"colorPreset")

        self.formLayout_8.setWidget(0, QFormLayout.FieldRole, self.colorPreset)

        self.label_28 = QLabel(self.groupBox)
        self.label_28.setObjectName(u"label_28")

        self.formLayout_8.setWidget(1, QFormLayout.LabelRole, self.label_28)

        self.horizontalLayout_9 = QHBoxLayout()
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.color0 = QFrame(self.groupBox)
        self.color0.setObjectName(u"color0")
        self.color0.setMinimumSize(QSize(24, 24))
        self.color0.setAutoFillBackground(True)
        self.color0.setFrameShape(QFrame.StyledPanel)
        self.color0.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_9.addWidget(self.color0)

        self.color1 = QFrame(self.groupBox)
        self.color1.setObjectName(u"color1")
        self.color1.setMinimumSize(QSize(24, 24))
        self.color1.setAutoFillBackground(True)
        self.color1.setFrameShape(QFrame.StyledPanel)
        self.color1.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_9.addWidget(self.color1)

        self.color2 = QFrame(self.groupBox)
        self.color2.setObjectName(u"color2")
        self.color2.setMinimumSize(QSize(24, 24))
        self.color2.setAutoFillBackground(True)
        self.color2.setFrameShape(QFrame.StyledPanel)
        self.color2.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_9.addWidget(self.color2)

        self.color3 = QFrame(self.groupBox)
        self.color3.setObjectName(u"color3")
        self.color3.setMinimumSize(QSize(24, 24))
        self.color3.setAutoFillBackground(True)
        self.color3.setFrameShape(QFrame.StyledPanel)
        self.color3.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_9.addWidget(self.color3)


        self.formLayout_8.setLayout(1, QFormLayout.FieldRole, self.horizontalLayout_9)

        self.label_69 = QLabel(self.groupBox)
        self.label_69.setObjectName(u"label_69")

        self.formLayout_8.setWidget(2, QFormLayout.LabelRole, self.label_69)

        self.horizontalLayout_15 = QHBoxLayout()
        self.horizontalLayout_15.setObjectName(u"horizontalLayout_15")
        self.color4 = QFrame(self.groupBox)
        self.color4.setObjectName(u"color4")
        self.color4.setMinimumSize(QSize(24, 24))
        self.color4.setAutoFillBackground(True)
        self.color4.setFrameShape(QFrame.StyledPanel)
        self.color4.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_15.addWidget(self.color4)

        self.color5 = QFrame(self.groupBox)
        self.color5.setObjectName(u"color5")
        self.color5.setMinimumSize(QSize(24, 24))
        self.color5.setAutoFillBackground(True)
        self.color5.setFrameShape(QFrame.StyledPanel)
        self.color5.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_15.addWidget(self.color5)

        self.color6 = QFrame(self.groupBox)
        self.color6.setObjectName(u"color6")
        self.color6.setMinimumSize(QSize(24, 24))
        self.color6.setAutoFillBackground(True)
        self.color6.setFrameShape(QFrame.StyledPanel)
        self.color6.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_15.addWidget(self.color6)

        self.color7 = QFrame(self.groupBox)
        self.color7.setObjectName(u"color7")
        self.color7.setMinimumSize(QSize(24, 24))
        self.color7.setAutoFillBackground(True)
        self.color7.setFrameShape(QFrame.StyledPanel)
        self.color7.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_15.addWidget(self.color7)


        self.formLayout_8.setLayout(2, QFormLayout.FieldRole, self.horizontalLayout_15)

        self.label_70 = QLabel(self.groupBox)
        self.label_70.setObjectName(u"label_70")

        self.formLayout_8.setWidget(3, QFormLayout.LabelRole, self.label_70)

        self.horizontalLayout_37 = QHBoxLayout()
        self.horizontalLayout_37.setObjectName(u"horizontalLayout_37")
        self.color8 = QFrame(self.groupBox)
        self.color8.setObjectName(u"color8")
        self.color8.setMinimumSize(QSize(24, 24))
        self.color8.setAutoFillBackground(True)
        self.color8.setFrameShape(QFrame.StyledPanel)
        self.color8.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_37.addWidget(self.color8)

        self.color9 = QFrame(self.groupBox)
        self.color9.setObjectName(u"color9")
        self.color9.setMinimumSize(QSize(24, 24))
        self.color9.setAutoFillBackground(True)
        self.color9.setFrameShape(QFrame.StyledPanel)
        self.color9.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_37.addWidget(self.color9)

        self.color10 = QFrame(self.groupBox)
        self.color10.setObjectName(u"color10")
        self.color10.setMinimumSize(QSize(24, 24))
        self.color10.setAutoFillBackground(True)
        self.color10.setFrameShape(QFrame.StyledPanel)
        self.color10.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_37.addWidget(self.color10)

        self.color11 = QFrame(self.groupBox)
        self.color11.setObjectName(u"color11")
        self.color11.setMinimumSize(QSize(24, 24))
        self.color11.setAutoFillBackground(True)
        self.color11.setFrameShape(QFrame.StyledPanel)
        self.color11.setFrameShadow(QFrame.Raised)

        self.horizontalLayout_37.addWidget(self.color11)


        self.formLayout_8.setLayout(3, QFormLayout.FieldRole, self.horizontalLayout_37)

        self.line_19 = QFrame(self.groupBox)
        self.line_19.setObjectName(u"line_19")
        self.line_19.setFrameShape(QFrame.Shape.HLine)
        self.line_19.setFrameShadow(QFrame.Shadow.Sunken)

        self.formLayout_8.setWidget(4, QFormLayout.SpanningRole, self.line_19)

        self.gridLayout_2 = QGridLayout()
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.sgbColor = QRadioButton(self.groupBox)
        self.sgbColor.setObjectName(u"sgbColor")

        self.gridLayout_2.addWidget(self.sgbColor, 0, 1, 1, 1)

        self.gbColor = QRadioButton(self.groupBox)
        self.gbColor.setObjectName(u"gbColor")

        self.gridLayout_2.addWidget(self.gbColor, 0, 0, 1, 1)

        self.cgbColor = QRadioButton(self.groupBox)
        self.cgbColor.setObjectName(u"cgbColor")

        self.gridLayout_2.addWidget(self.cgbColor, 1, 0, 1, 1)

        self.scgbColor = QRadioButton(self.groupBox)
        self.scgbColor.setObjectName(u"scgbColor")

        self.gridLayout_2.addWidget(self.scgbColor, 1, 1, 1, 1)


        self.formLayout_8.setLayout(5, QFormLayout.SpanningRole, self.gridLayout_2)


        self.verticalLayout_2.addWidget(self.groupBox)

        self.groupBox_3 = QGroupBox(self.gb)
        self.groupBox_3.setObjectName(u"groupBox_3")
        self.formLayout_10 = QFormLayout(self.groupBox_3)
        self.formLayout_10.setObjectName(u"formLayout_10")
        self.label_27 = QLabel(self.groupBox_3)
        self.label_27.setObjectName(u"label_27")

        self.formLayout_10.setWidget(0, QFormLayout.LabelRole, self.label_27)

        self.cameraDriver = QComboBox(self.groupBox_3)
        self.cameraDriver.setObjectName(u"cameraDriver")
        sizePolicy2.setHeightForWidth(self.cameraDriver.sizePolicy().hasHeightForWidth())
        self.cameraDriver.setSizePolicy(sizePolicy2)

        self.formLayout_10.setWidget(0, QFormLayout.FieldRole, self.cameraDriver)

        self.label_35 = QLabel(self.groupBox_3)
        self.label_35.setObjectName(u"label_35")

        self.formLayout_10.setWidget(1, QFormLayout.LabelRole, self.label_35)

        self.camera = QComboBox(self.groupBox_3)
        self.camera.setObjectName(u"camera")
        self.camera.setEnabled(False)
        sizePolicy2.setHeightForWidth(self.camera.sizePolicy().hasHeightForWidth())
        self.camera.setSizePolicy(sizePolicy2)

        self.formLayout_10.setWidget(1, QFormLayout.FieldRole, self.camera)


        self.verticalLayout_2.addWidget(self.groupBox_3)

        self.stackedWidget.addWidget(self.gb)

        self.gridLayout.addWidget(self.stackedWidget, 1, 1, 1, 1)

        self.buttonBox = QDialogButtonBox(QGBA__SettingsView)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setStandardButtons(QDialogButtonBox.Apply|QDialogButtonBox.Cancel|QDialogButtonBox.Ok)

        self.gridLayout.addWidget(self.buttonBox, 2, 0, 1, 2)


        self.retranslateUi(QGBA__SettingsView)
        self.buttonBox.accepted.connect(QGBA__SettingsView.close)
        self.buttonBox.rejected.connect(QGBA__SettingsView.close)
        self.tabs.currentRowChanged.connect(self.stackedWidget.setCurrentIndex)
        self.savegameSameDir.toggled.connect(self.savegamePath.setDisabled)
        self.savestateSameDir.toggled.connect(self.savestatePath.setDisabled)
        self.screenshotSameDir.toggled.connect(self.screenshotPath.setDisabled)
        self.patchSameDir.toggled.connect(self.patchPath.setDisabled)
        self.cheatsSameDir.toggled.connect(self.cheatsPath.setDisabled)
        self.fastForwardUnbounded.toggled.connect(self.fastForwardRatio.setDisabled)
        self.fastForwardHeldUnbounded.toggled.connect(self.fastForwardHeldRatio.setDisabled)
        self.dynamicTitle.toggled.connect(self.showFps.setEnabled)
        self.dynamicTitle.toggled.connect(self.showFilename.setEnabled)
        self.showOSD.toggled.connect(self.showFrameCounter.setEnabled)
        self.showOSD.toggled.connect(self.showResetInfo.setEnabled)

        self.tabs.setCurrentRow(-1)
        self.stackedWidget.setCurrentIndex(0)
        self.audioBufferSize.setCurrentIndex(3)
        self.sampleRate.setCurrentIndex(2)


        QMetaObject.connectSlotsByName(QGBA__SettingsView)
    # setupUi

    def retranslateUi(self, QGBA__SettingsView):
        QGBA__SettingsView.setWindowTitle(QCoreApplication.translate("QGBA::SettingsView", u"Settings", None))

        __sortingEnabled = self.tabs.isSortingEnabled()
        self.tabs.setSortingEnabled(False)
        ___qlistwidgetitem = self.tabs.item(0)
        ___qlistwidgetitem.setText(QCoreApplication.translate("QGBA::SettingsView", u"Audio/Video", None));
        ___qlistwidgetitem1 = self.tabs.item(1)
        ___qlistwidgetitem1.setText(QCoreApplication.translate("QGBA::SettingsView", u"Gameplay", None));
        ___qlistwidgetitem2 = self.tabs.item(2)
        ___qlistwidgetitem2.setText(QCoreApplication.translate("QGBA::SettingsView", u"Interface", None));
        ___qlistwidgetitem3 = self.tabs.item(3)
        ___qlistwidgetitem3.setText(QCoreApplication.translate("QGBA::SettingsView", u"Update", None));
        ___qlistwidgetitem4 = self.tabs.item(4)
        ___qlistwidgetitem4.setText(QCoreApplication.translate("QGBA::SettingsView", u"Emulation", None));
        ___qlistwidgetitem5 = self.tabs.item(5)
        ___qlistwidgetitem5.setText(QCoreApplication.translate("QGBA::SettingsView", u"Enhancements", None));
        ___qlistwidgetitem6 = self.tabs.item(6)
        ___qlistwidgetitem6.setText(QCoreApplication.translate("QGBA::SettingsView", u"BIOS", None));
        ___qlistwidgetitem7 = self.tabs.item(7)
        ___qlistwidgetitem7.setText(QCoreApplication.translate("QGBA::SettingsView", u"Paths", None));
        ___qlistwidgetitem8 = self.tabs.item(8)
        ___qlistwidgetitem8.setText(QCoreApplication.translate("QGBA::SettingsView", u"Logging", None));
        ___qlistwidgetitem9 = self.tabs.item(9)
        ___qlistwidgetitem9.setText(QCoreApplication.translate("QGBA::SettingsView", u"Game Boy", None));
        self.tabs.setSortingEnabled(__sortingEnabled)

        self.groupBox_4.setTitle(QCoreApplication.translate("QGBA::SettingsView", u"Audio", None))
        self.label_14.setText(QCoreApplication.translate("QGBA::SettingsView", u"Audio driver:", None))
        self.audioBufferSizeLabel.setText(QCoreApplication.translate("QGBA::SettingsView", u"Audio buffer:", None))
        self.audioBufferSize.setItemText(0, QCoreApplication.translate("QGBA::SettingsView", u"512", None))
        self.audioBufferSize.setItemText(1, QCoreApplication.translate("QGBA::SettingsView", u"768", None))
        self.audioBufferSize.setItemText(2, QCoreApplication.translate("QGBA::SettingsView", u"1024", None))
        self.audioBufferSize.setItemText(3, QCoreApplication.translate("QGBA::SettingsView", u"1536", None))
        self.audioBufferSize.setItemText(4, QCoreApplication.translate("QGBA::SettingsView", u"2048", None))
        self.audioBufferSize.setItemText(5, QCoreApplication.translate("QGBA::SettingsView", u"3072", None))
        self.audioBufferSize.setItemText(6, QCoreApplication.translate("QGBA::SettingsView", u"4096", None))

        self.audioBufferSize.setCurrentText(QCoreApplication.translate("QGBA::SettingsView", u"1536", None))
        self.label_16.setText(QCoreApplication.translate("QGBA::SettingsView", u"samples", None))
        self.label_19.setText(QCoreApplication.translate("QGBA::SettingsView", u"Sample rate:", None))
        self.sampleRate.setItemText(0, QCoreApplication.translate("QGBA::SettingsView", u"22050", None))
        self.sampleRate.setItemText(1, QCoreApplication.translate("QGBA::SettingsView", u"32000", None))
        self.sampleRate.setItemText(2, QCoreApplication.translate("QGBA::SettingsView", u"44100", None))
        self.sampleRate.setItemText(3, QCoreApplication.translate("QGBA::SettingsView", u"48000", None))

        self.sampleRate.setCurrentText(QCoreApplication.translate("QGBA::SettingsView", u"44100", None))
        self.label_20.setText(QCoreApplication.translate("QGBA::SettingsView", u"Hz", None))
        self.label_17.setText(QCoreApplication.translate("QGBA::SettingsView", u"Volume:", None))
        self.mute.setText(QCoreApplication.translate("QGBA::SettingsView", u"Mute", None))
        self.label_34.setText(QCoreApplication.translate("QGBA::SettingsView", u"Fast forward volume:", None))
        self.muteFf.setText(QCoreApplication.translate("QGBA::SettingsView", u"Mute", None))
        self.label_43.setText(QCoreApplication.translate("QGBA::SettingsView", u"Audio in multiplayer:", None))
        self.multiplayerAudioAll.setText(QCoreApplication.translate("QGBA::SettingsView", u"All windows", None))
        self.multiplayerAudio1.setText(QCoreApplication.translate("QGBA::SettingsView", u"Player 1 window only", None))
        self.multiplayerAudioActive.setText(QCoreApplication.translate("QGBA::SettingsView", u"Currently active player window", None))
        self.groupBox_5.setTitle(QCoreApplication.translate("QGBA::SettingsView", u"Video", None))
        self.label_10.setText(QCoreApplication.translate("QGBA::SettingsView", u"Display driver:", None))
        self.label_9.setText(QCoreApplication.translate("QGBA::SettingsView", u"Frameskip:", None))
        self.label_12.setText(QCoreApplication.translate("QGBA::SettingsView", u"Skip every", None))
        self.label_13.setText(QCoreApplication.translate("QGBA::SettingsView", u"frames", None))
        self.lockAspectRatio.setText(QCoreApplication.translate("QGBA::SettingsView", u"Lock aspect ratio", None))
        self.lockIntegerScaling.setText(QCoreApplication.translate("QGBA::SettingsView", u"Force integer scaling", None))
        self.interframeBlending.setText(QCoreApplication.translate("QGBA::SettingsView", u"Interframe blending", None))
        self.resampleVideo.setText(QCoreApplication.translate("QGBA::SettingsView", u"Bilinear filtering", None))
        self.label_3.setText(QCoreApplication.translate("QGBA::SettingsView", u"FPS target:", None))
        self.label_11.setText(QCoreApplication.translate("QGBA::SettingsView", u"frames per second", None))
        self.nativeGB.setText(QCoreApplication.translate("QGBA::SettingsView", u"Native (59.7275)", None))
        self.label_2.setText(QCoreApplication.translate("QGBA::SettingsView", u"Sync:", None))
        self.videoSync.setText(QCoreApplication.translate("QGBA::SettingsView", u"Video", None))
        self.audioSync.setText(QCoreApplication.translate("QGBA::SettingsView", u"Audio", None))
        self.label_24.setText(QCoreApplication.translate("QGBA::SettingsView", u"On loading a game:", None))
        self.autoload.setText(QCoreApplication.translate("QGBA::SettingsView", u"Load last state", None))
        self.cheatAutoload.setText(QCoreApplication.translate("QGBA::SettingsView", u"Load cheats", None))
        self.autosave.setText(QCoreApplication.translate("QGBA::SettingsView", u"Periodically autosave state", None))
        self.cheatAutosave.setText(QCoreApplication.translate("QGBA::SettingsView", u"Save entered cheats", None))
        self.label_51.setText(QCoreApplication.translate("QGBA::SettingsView", u"Save state extra data:", None))
        self.saveStateScreenshot.setText(QCoreApplication.translate("QGBA::SettingsView", u"Screenshot", None))
        self.saveStateSave.setText(QCoreApplication.translate("QGBA::SettingsView", u"Save game", None))
        self.saveStateCheats.setText(QCoreApplication.translate("QGBA::SettingsView", u"Cheat codes", None))
        self.label_52.setText(QCoreApplication.translate("QGBA::SettingsView", u"Load state extra data:", None))
        self.loadStateScreenshot.setText(QCoreApplication.translate("QGBA::SettingsView", u"Screenshot", None))
        self.loadStateSave.setText(QCoreApplication.translate("QGBA::SettingsView", u"Save game", None))
        self.loadStateCheats.setText(QCoreApplication.translate("QGBA::SettingsView", u"Cheat codes", None))
        self.useDiscordPresence.setText(QCoreApplication.translate("QGBA::SettingsView", u"Enable Discord Rich Presence", None))
        self.label_26.setText(QCoreApplication.translate("QGBA::SettingsView", u"Language", None))
        self.label_6.setText(QCoreApplication.translate("QGBA::SettingsView", u"Library:", None))
        self.libraryStyle.setItemText(0, QCoreApplication.translate("QGBA::SettingsView", u"List view", None))
        self.libraryStyle.setItemText(1, QCoreApplication.translate("QGBA::SettingsView", u"Tree view", None))

        self.showLibrary.setText(QCoreApplication.translate("QGBA::SettingsView", u"Show when no game open", None))
        self.showFilenameInLibrary.setText(QCoreApplication.translate("QGBA::SettingsView", u"Show filename instead of ROM name in library view", None))
        self.clearCache.setText(QCoreApplication.translate("QGBA::SettingsView", u"Clear cache", None))
        self.allowOpposingDirections.setText(QCoreApplication.translate("QGBA::SettingsView", u"Allow opposing input directions", None))
        self.suspendScreensaver.setText(QCoreApplication.translate("QGBA::SettingsView", u"Suspend screensaver", None))
        self.label_41.setText(QCoreApplication.translate("QGBA::SettingsView", u"When inactive:", None))
        self.pauseOnFocusLost.setText(QCoreApplication.translate("QGBA::SettingsView", u"Pause", None))
        self.muteOnFocusLost.setText(QCoreApplication.translate("QGBA::SettingsView", u"Mute", None))
        self.label_42.setText(QCoreApplication.translate("QGBA::SettingsView", u"When minimized:", None))
        self.pauseOnMinimize.setText(QCoreApplication.translate("QGBA::SettingsView", u"Pause", None))
        self.muteOnMinimize.setText(QCoreApplication.translate("QGBA::SettingsView", u"Mute", None))
        self.dynamicTitle.setText(QCoreApplication.translate("QGBA::SettingsView", u"Dynamically update window title", None))
        self.showFps.setText(QCoreApplication.translate("QGBA::SettingsView", u"Show FPS in title bar", None))
        self.showFilename.setText(QCoreApplication.translate("QGBA::SettingsView", u"Show filename instead of ROM name in title bar", None))
        self.showOSD.setText(QCoreApplication.translate("QGBA::SettingsView", u"Show OSD messages", None))
        self.showFrameCounter.setText(QCoreApplication.translate("QGBA::SettingsView", u"Show frame count in OSD", None))
        self.showResetInfo.setText(QCoreApplication.translate("QGBA::SettingsView", u"Show emulation info on reset", None))
        self.label_46.setText(QCoreApplication.translate("QGBA::SettingsView", u"Current channel:", None))
        self.label_50.setText(QCoreApplication.translate("QGBA::SettingsView", u"Current version:", None))
        self.label_45.setText(QCoreApplication.translate("QGBA::SettingsView", u"Update channel:", None))
        self.label_44.setText(QCoreApplication.translate("QGBA::SettingsView", u"Available version:", None))
        self.availVersion.setText(QCoreApplication.translate("QGBA::SettingsView", u"(Unknown)", None))
        self.label_49.setText(QCoreApplication.translate("QGBA::SettingsView", u"Last checked:", None))
        self.updateAutoCheck.setText(QCoreApplication.translate("QGBA::SettingsView", u"Automatically check on start", None))
        self.checkUpdate.setText(QCoreApplication.translate("QGBA::SettingsView", u"Check now", None))
        self.label_18.setText(QCoreApplication.translate("QGBA::SettingsView", u"Fast forward speed:", None))
        self.fastForwardUnbounded.setText(QCoreApplication.translate("QGBA::SettingsView", u"Unbounded", None))
        self.label_181.setText(QCoreApplication.translate("QGBA::SettingsView", u"Fast forward (held) speed:", None))
        self.fastForwardHeldUnbounded.setText(QCoreApplication.translate("QGBA::SettingsView", u"Unbounded", None))
        self.label_31.setText(QCoreApplication.translate("QGBA::SettingsView", u"Autofire interval:", None))
        self.rewind.setText(QCoreApplication.translate("QGBA::SettingsView", u"Enable rewind", None))
        self.label_8.setText(QCoreApplication.translate("QGBA::SettingsView", u"Rewind history:", None))
        self.label_7.setText(QCoreApplication.translate("QGBA::SettingsView", u"frames", None))
        self.label_15.setText(QCoreApplication.translate("QGBA::SettingsView", u"Idle loops:", None))
        self.idleOptimization.setItemText(0, QCoreApplication.translate("QGBA::SettingsView", u"Run all", None))
        self.idleOptimization.setItemText(1, QCoreApplication.translate("QGBA::SettingsView", u"Remove known", None))
        self.idleOptimization.setItemText(2, QCoreApplication.translate("QGBA::SettingsView", u"Detect and remove", None))

        self.preload.setText(QCoreApplication.translate("QGBA::SettingsView", u"Preload entire ROM into memory", None))
        self.forceGbp.setText(QCoreApplication.translate("QGBA::SettingsView", u"Enable Game Boy Player features by default", None))
        self.vbaBugCompat.setText(QCoreApplication.translate("QGBA::SettingsView", u"Enable VBA bug compatibility in ROM hacks", None))
        self.label_36.setText(QCoreApplication.translate("QGBA::SettingsView", u"Video renderer:", None))
        self.hwaccelVideo.setItemText(0, QCoreApplication.translate("QGBA::SettingsView", u"Software", None))
        self.hwaccelVideo.setItemText(1, QCoreApplication.translate("QGBA::SettingsView", u"OpenGL", None))

        self.audioHle.setText(QCoreApplication.translate("QGBA::SettingsView", u"XQ GBA audio (experimental)", None))
        self.oglEnhance.setTitle(QCoreApplication.translate("QGBA::SettingsView", u"OpenGL enhancements", None))
        self.label_37.setText(QCoreApplication.translate("QGBA::SettingsView", u"High-resolution scale:", None))
        self.videoScaleSize.setText(QCoreApplication.translate("QGBA::SettingsView", u"(240\u00d7160)", None))
        self.label.setText(QCoreApplication.translate("QGBA::SettingsView", u"GB BIOS file:", None))
        self.gbBiosBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.label_30.setText(QCoreApplication.translate("QGBA::SettingsView", u"SGB BIOS file:", None))
        self.sgbBiosBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.label_5.setText(QCoreApplication.translate("QGBA::SettingsView", u"GBC BIOS file:", None))
        self.gbcBiosBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.label_4.setText(QCoreApplication.translate("QGBA::SettingsView", u"GBA BIOS file:", None))
        self.gbaBiosBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.useBios.setText(QCoreApplication.translate("QGBA::SettingsView", u"Use BIOS file if found", None))
        self.skipBios.setText(QCoreApplication.translate("QGBA::SettingsView", u"Skip BIOS intro", None))
        self.label_21.setText(QCoreApplication.translate("QGBA::SettingsView", u"Save games", None))
        self.savegameBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.savegameSameDir.setText(QCoreApplication.translate("QGBA::SettingsView", u"Same directory as the ROM", None))
        self.label_22.setText(QCoreApplication.translate("QGBA::SettingsView", u"Save states", None))
        self.savestateBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.savestateSameDir.setText(QCoreApplication.translate("QGBA::SettingsView", u"Same directory as the ROM", None))
        self.label_23.setText(QCoreApplication.translate("QGBA::SettingsView", u"Screenshots", None))
        self.screenshotBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.screenshotSameDir.setText(QCoreApplication.translate("QGBA::SettingsView", u"Same directory as the ROM", None))
        self.label_47.setText(QCoreApplication.translate("QGBA::SettingsView", u"Patches", None))
        self.patchBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.patchSameDir.setText(QCoreApplication.translate("QGBA::SettingsView", u"Same directory as the ROM", None))
        self.label_48.setText(QCoreApplication.translate("QGBA::SettingsView", u"Cheats", None))
        self.cheatsBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Browse", None))
        self.cheatsSameDir.setText(QCoreApplication.translate("QGBA::SettingsView", u"Same directory as the ROM", None))
        self.logToFile.setText(QCoreApplication.translate("QGBA::SettingsView", u"Log to file", None))
        self.logToStdout.setText(QCoreApplication.translate("QGBA::SettingsView", u"Log to console", None))
        self.logFileBrowse.setText(QCoreApplication.translate("QGBA::SettingsView", u"Select Log File", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("QGBA::SettingsView", u"Models", None))
        self.label_29.setText(QCoreApplication.translate("QGBA::SettingsView", u"GB only:", None))
        self.label_32.setText(QCoreApplication.translate("QGBA::SettingsView", u"SGB compatible:", None))
        self.label_33.setText(QCoreApplication.translate("QGBA::SettingsView", u"GBC only:", None))
        self.label_38.setText(QCoreApplication.translate("QGBA::SettingsView", u"GBC compatible:", None))
        self.label_39.setText(QCoreApplication.translate("QGBA::SettingsView", u"SGB and GBC compatible:", None))
        self.sgbBorders.setText(QCoreApplication.translate("QGBA::SettingsView", u"Super Game Boy borders", None))
        self.groupBox.setTitle(QCoreApplication.translate("QGBA::SettingsView", u"Game Boy palette", None))
        self.label_40.setText(QCoreApplication.translate("QGBA::SettingsView", u"Preset:", None))
        self.label_28.setText(QCoreApplication.translate("QGBA::SettingsView", u"Default BG colors:", None))
        self.label_69.setText(QCoreApplication.translate("QGBA::SettingsView", u"Default sprite colors 1:", None))
        self.label_70.setText(QCoreApplication.translate("QGBA::SettingsView", u"Default sprite colors 2:", None))
        self.sgbColor.setText(QCoreApplication.translate("QGBA::SettingsView", u"SGB color palette if available", None))
        self.gbColor.setText(QCoreApplication.translate("QGBA::SettingsView", u"Default color palette only", None))
        self.cgbColor.setText(QCoreApplication.translate("QGBA::SettingsView", u"GBC color palette if available", None))
        self.scgbColor.setText(QCoreApplication.translate("QGBA::SettingsView", u"SGB (preferred) or GBC color palette if available", None))
        self.groupBox_3.setTitle(QCoreApplication.translate("QGBA::SettingsView", u"Game Boy Camera", None))
        self.label_27.setText(QCoreApplication.translate("QGBA::SettingsView", u"Driver:", None))
        self.label_35.setText(QCoreApplication.translate("QGBA::SettingsView", u"Source:", None))
    # retranslateUi

