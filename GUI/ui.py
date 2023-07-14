# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'GUICfvJem.ui'
##
## Created by: Qt User Interface Compiler version 5.15.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtWidgets import *

from Custom_Widgets.AnalogGaugeWidget import AnalogGaugeWidget
from qtexteditlogger import QTextEditLogger


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        if not Dialog.objectName():
            Dialog.setObjectName(u"Dialog")
        Dialog.resize(442, 842)
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
        self.configSelect = QComboBox(self.TransmitterTab)
        self.configSelect.addItem("")
        self.configSelect.addItem("")
        self.configSelect.addItem("")
        self.configSelect.addItem("")
        self.configSelect.addItem("")
        self.configSelect.addItem("")
        self.configSelect.setObjectName(u"configSelect")
        sizePolicy1 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Maximum)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.configSelect.sizePolicy().hasHeightForWidth())
        self.configSelect.setSizePolicy(sizePolicy1)

        self.verticalLayout_5.addWidget(self.configSelect)

        self.ControlBox = QGroupBox(self.TransmitterTab)
        self.ControlBox.setObjectName(u"ControlBox")
        self.gridLayout = QGridLayout(self.ControlBox)
        self.gridLayout.setObjectName(u"gridLayout")
        self.showTimeButton = QPushButton(self.ControlBox)
        self.showTimeButton.setObjectName(u"showTimeButton")
        self.showTimeButton.setEnabled(False)
        sizePolicy1.setHeightForWidth(self.showTimeButton.sizePolicy().hasHeightForWidth())
        self.showTimeButton.setSizePolicy(sizePolicy1)

        self.gridLayout.addWidget(self.showTimeButton, 2, 0, 1, 1)

        self.showDateButton = QPushButton(self.ControlBox)
        self.showDateButton.setObjectName(u"showDateButton")
        self.showDateButton.setEnabled(False)
        sizePolicy1.setHeightForWidth(self.showDateButton.sizePolicy().hasHeightForWidth())
        self.showDateButton.setSizePolicy(sizePolicy1)
        self.showDateButton.setCheckable(False)
        self.showDateButton.setChecked(False)
        self.showDateButton.setFlat(False)

        self.gridLayout.addWidget(self.showDateButton, 2, 1, 1, 1)

        self.accelButton = QPushButton(self.ControlBox)
        self.accelButton.setObjectName(u"accelButton")
        sizePolicy1.setHeightForWidth(self.accelButton.sizePolicy().hasHeightForWidth())
        self.accelButton.setSizePolicy(sizePolicy1)

        self.gridLayout.addWidget(self.accelButton, 0, 0, 1, 1)

        self.decelButton = QPushButton(self.ControlBox)
        self.decelButton.setObjectName(u"decelButton")
        sizePolicy1.setHeightForWidth(self.decelButton.sizePolicy().hasHeightForWidth())
        self.decelButton.setSizePolicy(sizePolicy1)

        self.gridLayout.addWidget(self.decelButton, 0, 1, 1, 1)


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
        self.transmitPayload = QLineEdit(self.groupBox_2)
        self.transmitPayload.setObjectName(u"transmitPayload")
        self.transmitPayload.setAutoFillBackground(False)
        self.transmitPayload.setDragEnabled(False)
        self.transmitPayload.setReadOnly(True)

        self.verticalLayout.addWidget(self.transmitPayload)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.alterFreshButton = QPushButton(self.groupBox_2)
        self.alterFreshButton.setObjectName(u"alterFreshButton")
        sizePolicy1.setHeightForWidth(self.alterFreshButton.sizePolicy().hasHeightForWidth())
        self.alterFreshButton.setSizePolicy(sizePolicy1)

        self.horizontalLayout.addWidget(self.alterFreshButton)

        self.alterAuthButton = QPushButton(self.groupBox_2)
        self.alterAuthButton.setObjectName(u"alterAuthButton")
        sizePolicy1.setHeightForWidth(self.alterAuthButton.sizePolicy().hasHeightForWidth())
        self.alterAuthButton.setSizePolicy(sizePolicy1)

        self.horizontalLayout.addWidget(self.alterAuthButton)


        self.verticalLayout.addLayout(self.horizontalLayout)


        self.verticalLayout_5.addWidget(self.groupBox_2)

        self.transmitButton = QPushButton(self.TransmitterTab)
        self.transmitButton.setObjectName(u"transmitButton")
        sizePolicy1.setHeightForWidth(self.transmitButton.sizePolicy().hasHeightForWidth())
        self.transmitButton.setSizePolicy(sizePolicy1)

        self.verticalLayout_5.addWidget(self.transmitButton)

        self.groupBox = QGroupBox(self.TransmitterTab)
        self.groupBox.setObjectName(u"groupBox")
        sizePolicy.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy)
        self.groupBox.setMinimumSize(QSize(0, 0))
        self.groupBox.setMaximumSize(QSize(16777215, 250))
        self.verticalLayout_4 = QVBoxLayout(self.groupBox)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.tlogger = QTextEditLogger(self.groupBox)
        self.tlogger.setObjectName(u"tlogger")
        sizePolicy.setHeightForWidth(self.tlogger.sizePolicy().hasHeightForWidth())
        self.tlogger.setSizePolicy(sizePolicy)
        self.tlogger.setMaximumSize(QSize(16777215, 250))
        self.tlogger.setSizeIncrement(QSize(0, 0))
        self.tlogger.setBaseSize(QSize(0, 0))
        font = QFont()
        font.setFamily(u"Noto Color Emoji")
        font.setPointSize(14)
        font.setBold(False)
        font.setWeight(50)
        self.tlogger.setFont(font)

        self.verticalLayout_4.addWidget(self.tlogger)

        self.tlogClearButton = QPushButton(self.groupBox)
        self.tlogClearButton.setObjectName(u"tlogClearButton")
        sizePolicy1.setHeightForWidth(self.tlogClearButton.sizePolicy().hasHeightForWidth())
        self.tlogClearButton.setSizePolicy(sizePolicy1)

        self.verticalLayout_4.addWidget(self.tlogClearButton)


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
        self.LCD.setMinimumSize(QSize(150, 0))
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
        self.receivePayload = QLineEdit(self.groupBox_3)
        self.receivePayload.setObjectName(u"receivePayload")
        sizePolicy1.setHeightForWidth(self.receivePayload.sizePolicy().hasHeightForWidth())
        self.receivePayload.setSizePolicy(sizePolicy1)
        self.receivePayload.setAutoFillBackground(False)
        self.receivePayload.setDragEnabled(False)
        self.receivePayload.setReadOnly(True)

        self.verticalLayout_8.addWidget(self.receivePayload)


        self.verticalLayout_10.addWidget(self.groupBox_3)

        self.verifyButton = QPushButton(self.ReceiverTab)
        self.verifyButton.setObjectName(u"verifyButton")
        sizePolicy1.setHeightForWidth(self.verifyButton.sizePolicy().hasHeightForWidth())
        self.verifyButton.setSizePolicy(sizePolicy1)

        self.verticalLayout_10.addWidget(self.verifyButton)

        self.LogBox = QGroupBox(self.ReceiverTab)
        self.LogBox.setObjectName(u"LogBox")
        sizePolicy4 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.LogBox.sizePolicy().hasHeightForWidth())
        self.LogBox.setSizePolicy(sizePolicy4)
        self.LogBox.setMaximumSize(QSize(16777215, 250))
        self.verticalLayout_9 = QVBoxLayout(self.LogBox)
        self.verticalLayout_9.setObjectName(u"verticalLayout_9")
        self.verticalLayout_9.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.rlogger = QTextEditLogger(self.LogBox)
        self.rlogger.setObjectName(u"rlogger")
        sizePolicy.setHeightForWidth(self.rlogger.sizePolicy().hasHeightForWidth())
        self.rlogger.setSizePolicy(sizePolicy)
        font1 = QFont()
        font1.setFamily(u"Noto Color Emoji")
        font1.setPointSize(14)
        self.rlogger.setFont(font1)

        self.verticalLayout_9.addWidget(self.rlogger)

        self.rlogClearButton = QPushButton(self.LogBox)
        self.rlogClearButton.setObjectName(u"rlogClearButton")
        sizePolicy1.setHeightForWidth(self.rlogClearButton.sizePolicy().hasHeightForWidth())
        self.rlogClearButton.setSizePolicy(sizePolicy1)

        self.verticalLayout_9.addWidget(self.rlogClearButton)


        self.verticalLayout_10.addWidget(self.LogBox)

        self.ModeTabs.addTab(self.ReceiverTab, "")

        self.verticalLayout_3.addWidget(self.ModeTabs)


        self.retranslateUi(Dialog)

        self.ModeTabs.setCurrentIndex(0)
        self.showDateButton.setDefault(False)


        QMetaObject.connectSlotsByName(Dialog)
    # setupUi

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QCoreApplication.translate("Dialog", u"SecOC", None))
        self.configSelect.setItemText(0, QCoreApplication.translate("Dialog", u"Direct transmission (CanIf)", None))
        self.configSelect.setItemText(1, QCoreApplication.translate("Dialog", u"Transport protocol transmission (CanTp)", None))
        self.configSelect.setItemText(2, QCoreApplication.translate("Dialog", u"Transport protocol transmission (Ethernet)", None))
        self.configSelect.setItemText(3, QCoreApplication.translate("Dialog", u"Direct transmission without Trunc-FV and header (CanIf)", None))
        self.configSelect.setItemText(4, QCoreApplication.translate("Dialog", u"Transport protocol transmission without header(CanTp)", None))
        self.configSelect.setItemText(5, QCoreApplication.translate("Dialog", u"Secured Pdu Collection (CanIf)", None))

        self.ControlBox.setTitle(QCoreApplication.translate("Dialog", u"Control Box", None))
        self.showTimeButton.setText(QCoreApplication.translate("Dialog", u"Show Time", None))
        self.showDateButton.setText(QCoreApplication.translate("Dialog", u"Show Date", None))
        self.accelButton.setText(QCoreApplication.translate("Dialog", u"ACCEL", None))
        self.decelButton.setText(QCoreApplication.translate("Dialog", u"DECEL", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("Dialog", u"Secured Payload", None))
        self.transmitPayload.setText("")
        self.alterFreshButton.setText(QCoreApplication.translate("Dialog", u"Alter Freshness", None))
        self.alterAuthButton.setText(QCoreApplication.translate("Dialog", u"Alter Authenticator", None))
        self.transmitButton.setText(QCoreApplication.translate("Dialog", u"Transmit Secured PDU", None))
        self.groupBox.setTitle(QCoreApplication.translate("Dialog", u"Log", None))
        self.tlogClearButton.setText(QCoreApplication.translate("Dialog", u"Clear", None))
        self.ModeTabs.setTabText(self.ModeTabs.indexOf(self.TransmitterTab), QCoreApplication.translate("Dialog", u"Transmitter", None))
        self.DashBoard.setTitle(QCoreApplication.translate("Dialog", u"DashBoard", None))
        self.LCD.setText("")
        self.groupBox_3.setTitle(QCoreApplication.translate("Dialog", u"Secured Payload", None))
        self.receivePayload.setText("")
        self.verifyButton.setText(QCoreApplication.translate("Dialog", u"Verify Secured PDU", None))
        self.LogBox.setTitle(QCoreApplication.translate("Dialog", u"Log", None))
        self.rlogger.setPlainText("")
        self.rlogClearButton.setText(QCoreApplication.translate("Dialog", u"Clear", None))
        self.ModeTabs.setTabText(self.ModeTabs.indexOf(self.ReceiverTab), QCoreApplication.translate("Dialog", u"Receiver", None))
    # retranslateUi

