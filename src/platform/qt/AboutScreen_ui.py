# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'AboutScreen.ui'
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
from PySide6.QtWidgets import (QApplication, QGridLayout, QLabel, QLayout,
    QSizePolicy, QSpacerItem, QVBoxLayout, QWidget)

class Ui_QGBA_AboutScreen(object):
    def setupUi(self, QGBA__AboutScreen):
        if not QGBA__AboutScreen.objectName():
            QGBA__AboutScreen.setObjectName(u"QGBA__AboutScreen")
        QGBA__AboutScreen.resize(617, 341)
        self.gridLayout_2 = QGridLayout(QGBA__AboutScreen)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout_2.setSizeConstraint(QLayout.SetFixedSize)
        self.extraLinks = QLabel(QGBA__AboutScreen)
        self.extraLinks.setObjectName(u"extraLinks")
        self.extraLinks.setAlignment(Qt.AlignCenter)
        self.extraLinks.setOpenExternalLinks(True)

        self.gridLayout_2.addWidget(self.extraLinks, 4, 1, 1, 1)

        self.gitInfo = QLabel(QGBA__AboutScreen)
        self.gitInfo.setObjectName(u"gitInfo")
        font = QFont()
        font.setPointSize(10)
        self.gitInfo.setFont(font)
        self.gitInfo.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.gridLayout_2.addWidget(self.gitInfo, 2, 1, 1, 1)

        self.projectName = QLabel(QGBA__AboutScreen)
        self.projectName.setObjectName(u"projectName")
        font1 = QFont()
        font1.setPointSize(36)
        font1.setBold(True)
        self.projectName.setFont(font1)
        self.projectName.setText(u"{projectName}")
        self.projectName.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout_2.addWidget(self.projectName, 0, 1, 1, 1)

        self.patronsHeader = QLabel(QGBA__AboutScreen)
        self.patronsHeader.setObjectName(u"patronsHeader")
        self.patronsHeader.setAlignment(Qt.AlignCenter)
        self.patronsHeader.setWordWrap(True)

        self.gridLayout_2.addWidget(self.patronsHeader, 6, 0, 1, 2)

        self.copyright = QLabel(QGBA__AboutScreen)
        self.copyright.setObjectName(u"copyright")
        self.copyright.setFont(font)
        self.copyright.setAlignment(Qt.AlignCenter)
        self.copyright.setWordWrap(True)

        self.gridLayout_2.addWidget(self.copyright, 8, 0, 1, 4)

        self.projectVersion = QLabel(QGBA__AboutScreen)
        self.projectVersion.setObjectName(u"projectVersion")
        font2 = QFont()
        font2.setBold(True)
        self.projectVersion.setFont(font2)
        self.projectVersion.setText(u"{projectVersion}")
        self.projectVersion.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)
        self.projectVersion.setTextInteractionFlags(Qt.LinksAccessibleByMouse|Qt.TextSelectableByKeyboard|Qt.TextSelectableByMouse)

        self.gridLayout_2.addWidget(self.projectVersion, 1, 1, 1, 1)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(8, -1, 16, 12)
        self.verticalSpacer_2 = QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer_2)

        self.logo = QLabel(QGBA__AboutScreen)
        self.logo.setObjectName(u"logo")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.logo.sizePolicy().hasHeightForWidth())
        self.logo.setSizePolicy(sizePolicy)
        self.logo.setMinimumSize(QSize(256, 192))
        self.logo.setText(u"{logo}")

        self.verticalLayout.addWidget(self.logo)

        self.verticalSpacer_3 = QSpacerItem(0, 0, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer_3)


        self.gridLayout_2.addLayout(self.verticalLayout, 0, 0, 6, 1)

        self.description = QLabel(QGBA__AboutScreen)
        self.description.setObjectName(u"description")
        self.description.setAlignment(Qt.AlignCenter)
        self.description.setWordWrap(True)

        self.gridLayout_2.addWidget(self.description, 3, 1, 1, 1)

        self.patrons = QLabel(QGBA__AboutScreen)
        self.patrons.setObjectName(u"patrons")
        self.patrons.setText(u"{patrons}")
        self.patrons.setAlignment(Qt.AlignCenter)
        self.patrons.setWordWrap(True)

        self.gridLayout_2.addWidget(self.patrons, 7, 0, 1, 2)


        self.retranslateUi(QGBA__AboutScreen)

        QMetaObject.connectSlotsByName(QGBA__AboutScreen)
    # setupUi

    def retranslateUi(self, QGBA__AboutScreen):
        QGBA__AboutScreen.setWindowTitle(QCoreApplication.translate("QGBA::AboutScreen", u"About", None))
        self.extraLinks.setText(QCoreApplication.translate("QGBA::AboutScreen", u"<a href=\"http://mgba.io/\">Website</a> \u2022 <a href=\"https://forums.mgba.io/\">Forums / Support</a> \u2022 <a href=\"https://patreon.com/mgba\">Donate</a> \u2022 <a href=\"https://github.com/mgba-emu/mgba/tree/{gitBranch}\">Source</a>", None))
        self.gitInfo.setText(QCoreApplication.translate("QGBA::AboutScreen", u"Branch: <tt>{gitBranch}</tt><br/>Revision: <tt>{gitCommit}</tt>", None))
        self.patronsHeader.setText(QCoreApplication.translate("QGBA::AboutScreen", u"{projectName} would like to thank the following patrons from Patreon:", None))
        self.copyright.setText(QCoreApplication.translate("QGBA::AboutScreen", u"\u00a9 2013 \u2013 {year} Jeffrey Pfau, licensed under the Mozilla Public License, version 2.0\n"
"Game Boy Advance is a registered trademark of Nintendo Co., Ltd.", None))
        self.description.setText(QCoreApplication.translate("QGBA::AboutScreen", u"{projectName} is an open-source Game Boy Advance emulator", None))
    # retranslateUi

