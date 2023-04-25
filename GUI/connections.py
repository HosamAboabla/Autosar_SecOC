try:
    from mydialog import MyDialog
except ImportError:
    pass


class MyConnections:
    def __init__(self, dialog):
        self.dialog : MyDialog = dialog

        # Transmitter tab connections
        self.dialog.accelButton.clicked.connect(self.OnAccelButtonClicked)
        self.dialog.decelButton.clicked.connect(self.OnDecelButtonClicked)
        self.dialog.showTimeButton.clicked.connect(self.OnShowTimeButtonClicked)
        self.dialog.showDateButton.clicked.connect(self.OnAccelButtonClicked)

        self.dialog.alterFreshButton.clicked.connect(self.OnAlterFreshButtonClicked)
        self.dialog.alterAuthButton.clicked.connect(self.OnAlterAuthButtonClicked)

        self.dialog.transmitButton.clicked.connect(self.OnTransmitButtonClicked)
        self.dialog.tlogClearButton.clicked.connect(self.OnTlogClearButtonClicked)

        # Receiver tab connections
        self.dialog.verifyButton.clicked.connect(self.OnVerifyButtonClicked)
        self.dialog.rlogClearButton.clicked.connect(self.OnRlogClearButtonClicked)


    def OnAccelButtonClicked(self):
        self.dialog.tlog.debug("OnAccelButtonClicked")
    
    def OnDecelButtonClicked(self):
        self.dialog.tlog.debug("OnDecelButtonClicked")
   
    def OnShowTimeButtonClicked(self):
        self.dialog.tlog.debug("OnShowTimeButtonClicked")
  
    def OnShowDateButtonClicked(self):
        self.dialog.tlog.debug("OnShowDateButtonClicked")


    def OnAlterFreshButtonClicked(self):
        self.dialog.tlog.debug("OnAlterFreshButtonClicked")
    
    def OnAlterAuthButtonClicked(self):
        self.dialog.tlog.debug("OnAlterAuthButtonClicked")

  
    def OnTransmitButtonClicked(self):
        self.dialog.tlog.debug("OnTransmitButtonClicked")
   
    def OnTlogClearButtonClicked(self):
        self.dialog.tlog.debug("OnTlogClearButtonClicked")                                                

    def OnVerifyButtonClicked(self):
        self.dialog.tlog.debug("OnVerifyButtonClicked")       

    def OnRlogClearButtonClicked(self):
        self.dialog.tlog.debug("OnRlogClearButtonClicked")               