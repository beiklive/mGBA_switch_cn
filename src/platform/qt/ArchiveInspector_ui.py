# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'ArchiveInspector.ui'
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
from PySide6.QtWidgets import (QAbstractButton, QApplication, QDialog, QDialogButtonBox,
    QGridLayout, QLabel, QSizePolicy, QWidget)

class Ui_QGBA_ArchiveInspector(object):
    def setupUi(self, QGBA__ArchiveInspector):
        if not QGBA__ArchiveInspector.objectName():
            QGBA__ArchiveInspector.setObjectName(u"QGBA__ArchiveInspector")
        QGBA__ArchiveInspector.resize(600, 400)
        self.gridLayout = QGridLayout(QGBA__ArchiveInspector)
        self.gridLayout.setObjectName(u"gridLayout")
        self.loading = QLabel(QGBA__ArchiveInspector)
        self.loading.setObjectName(u"loading")

        self.gridLayout.addWidget(self.loading, 1, 0, 1, 1)

        self.buttonBox = QDialogButtonBox(QGBA__ArchiveInspector)
        self.buttonBox.setObjectName(u"buttonBox")
        self.buttonBox.setStandardButtons(QDialogButtonBox.Cancel|QDialogButtonBox.Open)

        self.gridLayout.addWidget(self.buttonBox, 1, 1, 1, 1)

        self.archiveView = QGBA_LibraryController(QGBA__ArchiveInspector)
        self.archiveView.setObjectName(u"archiveView")

        self.gridLayout.addWidget(self.archiveView, 0, 0, 1, 2)


        self.retranslateUi(QGBA__ArchiveInspector)
        self.buttonBox.rejected.connect(QGBA__ArchiveInspector.reject)
        self.buttonBox.accepted.connect(QGBA__ArchiveInspector.accept)

        QMetaObject.connectSlotsByName(QGBA__ArchiveInspector)
    # setupUi

    def retranslateUi(self, QGBA__ArchiveInspector):
        QGBA__ArchiveInspector.setWindowTitle(QCoreApplication.translate("QGBA::ArchiveInspector", u"Open in archive...", None))
        self.loading.setText(QCoreApplication.translate("QGBA::ArchiveInspector", u"Loading...", None))
    # retranslateUi

