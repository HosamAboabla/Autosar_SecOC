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

        self.dialog.alterFreshButton.clicked.connect(self.OnAccelButtonClicked)
        self.dialog.alterAuthButton.clicked.connect(self.OnAccelButtonClicked)

        self.dialog.transmitButton.clicked.connect(self.OnAccelButtonClicked)
        self.dialog.tlogClearButton.clicked.connect(self.OnAccelButtonClicked)

        # Receiver tab connections
        self.dialog.verifyButton.clicked.connect(self.OnAccelButtonClicked)
        self.dialog.rlogClearButton.clicked.connect(self.OnAccelButtonClicked)


    def OnAccelButtonClicked(self):
        self.dialog.tlog.debug("Button Clicked")
    
    def OnDecelButtonClicked(self):
        self.dialog.tlog.debug("Button Clicked")
   
    def OnShowTimeButtonClicked(self):
        self.dialog.tlog.debug("Button Clicked")
  
    def OnShowDateButtonClicked(self):
        self.dialog.tlog.debug("Button Clicked")


    def OnAccelButtonClicked(self):
        self.dialog.tlog.debug("Button Clicked")
    
    def OnAccelButtonClicked(self):
        self.dialog.tlog.debug("Button Clicked")

  
    def OnAccelButtonClicked(self):
        self.dialog.tlog.debug("Button Clicked")
   
    def OnAccelButtonClicked(self):
        self.dialog.tlog.debug("Button Clicked")                                                
