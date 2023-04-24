# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'GUIQkVzNF.ui'
##
## Created by: Qt User Interface Compiler version 6.4.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide2.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide2.QtWidgets import (QApplication, QComboBox, QDialog, QGridLayout,
    QGroupBox, QHBoxLayout, QLayout, QLineEdit,
    QPushButton, QSizePolicy, QSpacerItem, QTabWidget,
    QVBoxLayout, QWidget)

from Custom_Widgets.AnalogGaugeWidget import AnalogGaugeWidget
from qtexteditlogger import QTextEditLogger

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        if not Dialog.objectName():
            Dialog.setObjectName(u"Dialog")
        Dialog.resize(430, 653)
        sizePolicy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(Dialog.sizePolicy().hasHeightForWidth())
        Dialog.setSizePolicy(sizePolicy)
        self.verticalLayout_3 = QVBoxLayout(Dialog)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.ModeTabs = QTabWidget(Dialog)
        self.ModeTabs.setObjectName(u"ModeTabs")
        sizePolicy.setHeightForWidth(self.ModeTabs.sizePolicy().hasHeightForWidth())
        self.ModeTabs.setSizePolicy(sizePolicy)
        self.TransmitterTab = QWidget()
        self.TransmitterTab.setObjectName(u"TransmitterTab")
        self.verticalLayout_5 = QVBoxLayout(self.TransmitterTab)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.ConfigSelect = QComboBox(self.TransmitterTab)
        self.ConfigSelect.addItem("")
        self.ConfigSelect.addItem("")
        self.ConfigSelect.setObjectName(u"ConfigSelect")
        sizePolicy1 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Maximum)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.ConfigSelect.sizePolicy().hasHeightForWidth())
        self.ConfigSelect.setSizePolicy(sizePolicy1)

        self.verticalLayout_5.addWidget(self.ConfigSelect)

        self.ControlBox = QGroupBox(self.TransmitterTab)
        self.ControlBox.setObjectName(u"ControlBox")
        self.gridLayout = QGridLayout(self.ControlBox)
        self.gridLayout.setObjectName(u"gridLayout")
        self.pushButton_3 = QPushButton(self.ControlBox)
        self.pushButton_3.setObjectName(u"pushButton_3")
        self.pushButton_3.setEnabled(False)
        sizePolicy1.setHeightForWidth(self.pushButton_3.sizePolicy().hasHeightForWidth())
        self.pushButton_3.setSizePolicy(sizePolicy1)

        self.gridLayout.addWidget(self.pushButton_3, 2, 0, 1, 1)

        self.pushButton_9 = QPushButton(self.ControlBox)
        self.pushButton_9.setObjectName(u"pushButton_9")
        self.pushButton_9.setEnabled(False)
        sizePolicy1.setHeightForWidth(self.pushButton_9.sizePolicy().hasHeightForWidth())
        self.pushButton_9.setSizePolicy(sizePolicy1)
        self.pushButton_9.setCheckable(False)
        self.pushButton_9.setChecked(False)
        self.pushButton_9.setFlat(False)

        self.gridLayout.addWidget(self.pushButton_9, 2, 1, 1, 1)

        self.pushButton_2 = QPushButton(self.ControlBox)
        self.pushButton_2.setObjectName(u"pushButton_2")
        sizePolicy1.setHeightForWidth(self.pushButton_2.sizePolicy().hasHeightForWidth())
        self.pushButton_2.setSizePolicy(sizePolicy1)

        self.gridLayout.addWidget(self.pushButton_2, 0, 0, 1, 1)

        self.pushButton = QPushButton(self.ControlBox)
        self.pushButton.setObjectName(u"pushButton")
        sizePolicy1.setHeightForWidth(self.pushButton.sizePolicy().hasHeightForWidth())
        self.pushButton.setSizePolicy(sizePolicy1)

        self.gridLayout.addWidget(self.pushButton, 0, 1, 1, 1)


        self.verticalLayout_5.addWidget(self.ControlBox)

        self.groupBox_2 = QGroupBox(self.TransmitterTab)
        self.groupBox_2.setObjectName(u"groupBox_2")
        sizePolicy.setHeightForWidth(self.groupBox_2.sizePolicy().hasHeightForWidth())
        self.groupBox_2.setSizePolicy(sizePolicy)
        self.groupBox_2.setFlat(False)
        self.groupBox_2.setCheckable(False)
        self.verticalLayout = QVBoxLayout(self.groupBox_2)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.lineEdit = QLineEdit(self.groupBox_2)
        self.lineEdit.setObjectName(u"lineEdit")
        self.lineEdit.setAutoFillBackground(False)
        self.lineEdit.setDragEnabled(False)
        self.lineEdit.setReadOnly(True)

        self.verticalLayout.addWidget(self.lineEdit)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.pushButton_4 = QPushButton(self.groupBox_2)
        self.pushButton_4.setObjectName(u"pushButton_4")
        sizePolicy1.setHeightForWidth(self.pushButton_4.sizePolicy().hasHeightForWidth())
        self.pushButton_4.setSizePolicy(sizePolicy1)

        self.horizontalLayout.addWidget(self.pushButton_4)

        self.pushButton_10 = QPushButton(self.groupBox_2)
        self.pushButton_10.setObjectName(u"pushButton_10")
        sizePolicy1.setHeightForWidth(self.pushButton_10.sizePolicy().hasHeightForWidth())
        self.pushButton_10.setSizePolicy(sizePolicy1)

        self.horizontalLayout.addWidget(self.pushButton_10)


        self.verticalLayout.addLayout(self.horizontalLayout)


        self.verticalLayout_5.addWidget(self.groupBox_2)

        self.pushButton_11 = QPushButton(self.TransmitterTab)
        self.pushButton_11.setObjectName(u"pushButton_11")
        sizePolicy1.setHeightForWidth(self.pushButton_11.sizePolicy().hasHeightForWidth())
        self.pushButton_11.setSizePolicy(sizePolicy1)

        self.verticalLayout_5.addWidget(self.pushButton_11)

        self.groupBox = QGroupBox(self.TransmitterTab)
        self.groupBox.setObjectName(u"groupBox")
        sizePolicy.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy)
        self.groupBox.setMinimumSize(QSize(0, 0))
        self.groupBox.setMaximumSize(QSize(16777215, 158))
        self.verticalLayout_4 = QVBoxLayout(self.groupBox)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.tlogger = QTextEditLogger(self.groupBox)
        self.tlogger.setObjectName(u"tlogger")
        sizePolicy.setHeightForWidth(self.tlogger.sizePolicy().hasHeightForWidth())
        self.tlogger.setSizePolicy(sizePolicy)
        self.tlogger.setMaximumSize(QSize(16777215, 16777215))
        self.tlogger.setSizeIncrement(QSize(0, 0))
        self.tlogger.setBaseSize(QSize(0, 0))
        font = QFont()
        font.setFamilies([u"Noto Color Emoji"])
        self.tlogger.setFont(font)

        self.verticalLayout_4.addWidget(self.tlogger)

        self.pushButton_12 = QPushButton(self.groupBox)
        self.pushButton_12.setObjectName(u"pushButton_12")
        sizePolicy1.setHeightForWidth(self.pushButton_12.sizePolicy().hasHeightForWidth())
        self.pushButton_12.setSizePolicy(sizePolicy1)

        self.verticalLayout_4.addWidget(self.pushButton_12)


        self.verticalLayout_5.addWidget(self.groupBox)

        self.ModeTabs.addTab(self.TransmitterTab, "")
        self.ReceiverTab = QWidget()
        self.ReceiverTab.setObjectName(u"ReceiverTab")
        self.verticalLayout_10 = QVBoxLayout(self.ReceiverTab)
        self.verticalLayout_10.setObjectName(u"verticalLayout_10")
        self.DashBoard = QGroupBox(self.ReceiverTab)
        self.DashBoard.setObjectName(u"DashBoard")
        sizePolicy.setHeightForWidth(self.DashBoard.sizePolicy().hasHeightForWidth())
        self.DashBoard.setSizePolicy(sizePolicy)
        self.verticalLayout_11 = QVBoxLayout(self.DashBoard)
        self.verticalLayout_11.setObjectName(u"verticalLayout_11")
        self.gauge = AnalogGaugeWidget(self.DashBoard)
        self.gauge.setObjectName(u"gauge")
        sizePolicy2 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.gauge.sizePolicy().hasHeightForWidth())
        self.gauge.setSizePolicy(sizePolicy2)
        self.gauge.setMinimumSize(QSize(368, 265))
        self.gauge.setBaseSize(QSize(0, 0))
        self.verticalLayout_2 = QVBoxLayout(self.gauge)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")

        self.verticalLayout_11.addWidget(self.gauge)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalSpacer = QSpacerItem(70, 20, QSizePolicy.Fixed, QSizePolicy.Minimum)

        self.horizontalLayout_2.addItem(self.horizontalSpacer)

        self.LCD = QLineEdit(self.DashBoard)
        self.LCD.setObjectName(u"LCD")
        sizePolicy3 = QSizePolicy(QSizePolicy.Maximum, QSizePolicy.Maximum)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.LCD.sizePolicy().hasHeightForWidth())
        self.LCD.setSizePolicy(sizePolicy3)
        self.LCD.setMinimumSize(QSize(100, 0))
        self.LCD.setAlignment(Qt.AlignCenter)
        self.LCD.setReadOnly(True)
        self.LCD.setCursorMoveStyle(Qt.LogicalMoveStyle)

        self.horizontalLayout_2.addWidget(self.LCD)

        self.horizontalSpacer_2 = QSpacerItem(70, 20, QSizePolicy.Fixed, QSizePolicy.Minimum)

        self.horizontalLayout_2.addItem(self.horizontalSpacer_2)


        self.verticalLayout_11.addLayout(self.horizontalLayout_2)


        self.verticalLayout_10.addWidget(self.DashBoard)

        self.groupBox_3 = QGroupBox(self.ReceiverTab)
        self.groupBox_3.setObjectName(u"groupBox_3")
        sizePolicy.setHeightForWidth(self.groupBox_3.sizePolicy().hasHeightForWidth())
        self.groupBox_3.setSizePolicy(sizePolicy)
        self.groupBox_3.setFlat(False)
        self.groupBox_3.setCheckable(False)
        self.verticalLayout_8 = QVBoxLayout(self.groupBox_3)
        self.verticalLayout_8.setObjectName(u"verticalLayout_8")
        self.lineEdit_3 = QLineEdit(self.groupBox_3)
        self.lineEdit_3.setObjectName(u"lineEdit_3")
        sizePolicy1.setHeightForWidth(self.lineEdit_3.sizePolicy().hasHeightForWidth())
        self.lineEdit_3.setSizePolicy(sizePolicy1)
        self.lineEdit_3.setAutoFillBackground(False)
        self.lineEdit_3.setDragEnabled(False)
        self.lineEdit_3.setReadOnly(True)

        self.verticalLayout_8.addWidget(self.lineEdit_3)


        self.verticalLayout_10.addWidget(self.groupBox_3)

        self.pushButton_18 = QPushButton(self.ReceiverTab)
        self.pushButton_18.setObjectName(u"pushButton_18")
        sizePolicy1.setHeightForWidth(self.pushButton_18.sizePolicy().hasHeightForWidth())
        self.pushButton_18.setSizePolicy(sizePolicy1)

        self.verticalLayout_10.addWidget(self.pushButton_18)

        self.LogBox = QGroupBox(self.ReceiverTab)
        self.LogBox.setObjectName(u"LogBox")
        sizePolicy4 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.LogBox.sizePolicy().hasHeightForWidth())
        self.LogBox.setSizePolicy(sizePolicy4)
        self.LogBox.setMaximumSize(QSize(16777215, 158))
        self.verticalLayout_9 = QVBoxLayout(self.LogBox)
        self.verticalLayout_9.setObjectName(u"verticalLayout_9")
        self.verticalLayout_9.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.rlogger = QTextEditLogger(self.LogBox)
        self.rlogger.setObjectName(u"rlogger")
        sizePolicy.setHeightForWidth(self.rlogger.sizePolicy().hasHeightForWidth())
        self.rlogger.setSizePolicy(sizePolicy)
        self.rlogger.setFont(font)

        self.verticalLayout_9.addWidget(self.rlogger)

        self.pushButton_19 = QPushButton(self.LogBox)
        self.pushButton_19.setObjectName(u"pushButton_19")
        sizePolicy1.setHeightForWidth(self.pushButton_19.sizePolicy().hasHeightForWidth())
        self.pushButton_19.setSizePolicy(sizePolicy1)

        self.verticalLayout_9.addWidget(self.pushButton_19)


        self.verticalLayout_10.addWidget(self.LogBox)

        self.ModeTabs.addTab(self.ReceiverTab, "")

        self.verticalLayout_3.addWidget(self.ModeTabs)


        self.retranslateUi(Dialog)

        self.ModeTabs.setCurrentIndex(1)
        self.pushButton_9.setDefault(False)


        QMetaObject.connectSlotsByName(Dialog)
    # setupUi

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"SecOC", None))
        self.ConfigSelect.setItemText(0, QCoreApplication.translate("Dialog", u"CANIF", None))
        self.ConfigSelect.setItemText(1, QCoreApplication.translate("Dialog", u"CANTP", None))

        self.ControlBox.setTitle(QCoreApplication.translate("Dialog", u"Control Box", None))
        self.pushButton_3.setText(QCoreApplication.translate("Dialog", u"Show Time", None))
        self.pushButton_9.setText(QCoreApplication.translate("Dialog", u"Show Date", None))
        self.pushButton_2.setText(QCoreApplication.translate("Dialog", u"ACCEL", None))
        self.pushButton.setText(QCoreApplication.translate("Dialog", u"DECEL", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("Dialog", u"Secured Payload", None))
        self.lineEdit.setText(QCoreApplication.translate("Dialog", u"3 - 13412 - 34 - 192381209", None))
        self.pushButton_4.setText(QCoreApplication.translate("Dialog", u"Alter Freshness", None))
        self.pushButton_10.setText(QCoreApplication.translate("Dialog", u"Alter Authenticator", None))
        self.pushButton_11.setText(QCoreApplication.translate("Dialog", u"Transmit Secured PDU", None))
        self.groupBox.setTitle(QCoreApplication.translate("Dialog", u"Log", None))
        self.pushButton_12.setText(QCoreApplication.translate("Dialog", u"Clear", None))
        self.ModeTabs.setTabText(self.ModeTabs.indexOf(self.TransmitterTab), QCoreApplication.translate("Dialog", u"Transmitter", None))
        self.DashBoard.setTitle(QCoreApplication.translate("Dialog", u"DashBoard", None))
        self.LCD.setText(QCoreApplication.translate("Dialog", u"3:12 AM 3/10/2000", None))
        self.groupBox_3.setTitle(QCoreApplication.translate("Dialog", u"Secured Payload", None))
        self.lineEdit_3.setText(QCoreApplication.translate("Dialog", u"3 - 13412 - 34 - 192381209", None))
        self.pushButton_18.setText(QCoreApplication.translate("Dialog", u"Verify Secured PDU", None))
        self.LogBox.setTitle(QCoreApplication.translate("Dialog", u"Log", None))
        self.pushButton_19.setText(QCoreApplication.translate("Dialog", u"Clear", None))
        self.ModeTabs.setTabText(self.ModeTabs.indexOf(self.ReceiverTab), QCoreApplication.translate("Dialog", u"Receiver", None))
    # retranslateUi

