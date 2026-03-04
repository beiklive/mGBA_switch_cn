# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ReportView.ui'
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
from PySide6.QtWidgets import (QAbstractItemView, QAbstractScrollArea, QApplication, QCheckBox,
    QDialog, QGridLayout, QHBoxLayout, QLabel,
    QListWidget, QListWidgetItem, QPlainTextEdit, QPushButton,
    QSizePolicy, QVBoxLayout, QWidget)

class Ui_QGBA_ReportView(object):
    def setupUi(self, QGBA__ReportView):
        if not QGBA__ReportView.objectName():
            QGBA__ReportView.setObjectName(u"QGBA__ReportView")
        QGBA__ReportView.resize(914, 533)
        self.gridLayout = QGridLayout(QGBA__ReportView)
        self.gridLayout.setObjectName(u"gridLayout")
        self.fileList = QListWidget(QGBA__ReportView)
        self.fileList.setObjectName(u"fileList")
        self.fileList.setEnabled(False)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.fileList.sizePolicy().hasHeightForWidth())
        self.fileList.setSizePolicy(sizePolicy)
        self.fileList.setSizeAdjustPolicy(QAbstractScrollArea.AdjustToContents)
        self.fileList.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.fileList.setProperty(u"showDropIndicator", False)
        self.fileList.setHorizontalScrollMode(QAbstractItemView.ScrollPerPixel)

        self.gridLayout.addWidget(self.fileList, 1, 1, 3, 1)

        self.fileView = QPlainTextEdit(QGBA__ReportView)
        self.fileView.setObjectName(u"fileView")
        self.fileView.setEnabled(False)
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.MinimumExpanding, QSizePolicy.Policy.Expanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.fileView.sizePolicy().hasHeightForWidth())
        self.fileView.setSizePolicy(sizePolicy1)
        self.fileView.setTextInteractionFlags(Qt.TextEditorInteraction)

        self.gridLayout.addWidget(self.fileView, 1, 2, 3, 1)

        self.description = QLabel(QGBA__ReportView)
        self.description.setObjectName(u"description")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.MinimumExpanding)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.description.sizePolicy().hasHeightForWidth())
        self.description.setSizePolicy(sizePolicy2)
        self.description.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)
        self.description.setWordWrap(True)
        self.description.setOpenExternalLinks(True)

        self.gridLayout.addWidget(self.description, 1, 0, 1, 1)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.generate = QPushButton(QGBA__ReportView)
        self.generate.setObjectName(u"generate")
        icon = QIcon()
        iconThemeName = u"view-refresh"
        if QIcon.hasThemeIcon(iconThemeName):
            icon = QIcon.fromTheme(iconThemeName)
        else:
            icon.addFile(u"../../../../../../", QSize(), QIcon.Mode.Normal, QIcon.State.Off)

        self.generate.setIcon(icon)

        self.horizontalLayout_2.addWidget(self.generate)

        self.save = QPushButton(QGBA__ReportView)
        self.save.setObjectName(u"save")
        self.save.setEnabled(False)
        icon1 = QIcon()
        iconThemeName = u"document-save"
        if QIcon.hasThemeIcon(iconThemeName):
            icon1 = QIcon.fromTheme(iconThemeName)
        else:
            icon1.addFile(u"../../../../../../", QSize(), QIcon.Mode.Normal, QIcon.State.Off)

        self.save.setIcon(icon1)

        self.horizontalLayout_2.addWidget(self.save)

        self.openList = QPushButton(QGBA__ReportView)
        self.openList.setObjectName(u"openList")
        self.openList.setEnabled(False)
        icon2 = QIcon()
        iconThemeName = u"document-send"
        if QIcon.hasThemeIcon(iconThemeName):
            icon2 = QIcon.fromTheme(iconThemeName)
        else:
            icon2.addFile(u"../../../../../../", QSize(), QIcon.Mode.Normal, QIcon.State.Off)

        self.openList.setIcon(icon2)

        self.horizontalLayout_2.addWidget(self.openList)


        self.gridLayout.addLayout(self.horizontalLayout_2, 4, 1, 2, 2)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.includeSave = QCheckBox(QGBA__ReportView)
        self.includeSave.setObjectName(u"includeSave")
        sizePolicy3 = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Fixed)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.includeSave.sizePolicy().hasHeightForWidth())
        self.includeSave.setSizePolicy(sizePolicy3)
        self.includeSave.setChecked(True)

        self.verticalLayout.addWidget(self.includeSave)

        self.includeState = QCheckBox(QGBA__ReportView)
        self.includeState.setObjectName(u"includeState")
        sizePolicy3.setHeightForWidth(self.includeState.sizePolicy().hasHeightForWidth())
        self.includeState.setSizePolicy(sizePolicy3)
        self.includeState.setChecked(True)

        self.verticalLayout.addWidget(self.includeState)


        self.gridLayout.addLayout(self.verticalLayout, 2, 0, 4, 1)

        self.gridLayout.setColumnStretch(0, 3)
        self.gridLayout.setColumnStretch(1, 2)
        self.gridLayout.setColumnStretch(2, 7)

        self.retranslateUi(QGBA__ReportView)
        self.openList.clicked.connect(QGBA__ReportView.openBugReportPage)
        self.generate.clicked.connect(QGBA__ReportView.generateReport)
        self.save.clicked.connect(QGBA__ReportView.save)

        QMetaObject.connectSlotsByName(QGBA__ReportView)
    # setupUi

    def retranslateUi(self, QGBA__ReportView):
        QGBA__ReportView.setWindowTitle(QCoreApplication.translate("QGBA::ReportView", u"Generate Bug Report", None))
        self.description.setText(QCoreApplication.translate("QGBA::ReportView", u"<html><head/><body><p>To file a bug report, please first generate a report file to attach to the bug report you're about to file. It is recommended that you include the save files, as these often help with debugging issues. This will collect some information about the version of {projectName} you're running, your configuration, your computer, and the game you currently have open (if any). Once this collection is completed you can review all of the information gathered below and save it to a zip file. The collection will automatically attempt to redact any personal information, such as your username if it's in any of the paths gathered, but just in case you can edit it afterwards. After you have generated and saved it, please click the button below or go to <a href=\"https://mgba.io/i/\"><span style=\" text-decoration: underline; color:#2980b9;\">mgba.io/i</span></a> to file the bug report on GitHub. Make sure to attach the report you generated!</p></body></html>", None))
        self.generate.setText(QCoreApplication.translate("QGBA::ReportView", u"Generate report", None))
        self.save.setText(QCoreApplication.translate("QGBA::ReportView", u"Save", None))
        self.openList.setText(QCoreApplication.translate("QGBA::ReportView", u"Open issue list in browser", None))
        self.includeSave.setText(QCoreApplication.translate("QGBA::ReportView", u"Include save file", None))
        self.includeState.setText(QCoreApplication.translate("QGBA::ReportView", u"Create and include savestate", None))
    # retranslateUi

