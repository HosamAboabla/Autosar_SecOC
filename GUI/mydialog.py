from PySide2 import QtWidgets, QtGui
from pathlib import Path
import logging

from ui import Ui_Dialog
from Custom_Widgets.AnalogGaugeWidget import AnalogGaugeWidget


class MyDialog(QtWidgets.QDialog, Ui_Dialog):

    tlog = logging.getLogger('Logger 1')
    rlog = logging.getLogger('Logger 2')

    def __init__(self, parent=None):
        super().__init__(parent)

        QtGui.QFontDatabase.addApplicationFont(str(Path('GUI')/'DS-DIGIB.TTF'))

        self.setupUi(self)
        self.stylegauge()
        self.styleLCD()
        self.gauge.updateValue(50)

        self.assingloggers(self.tlog, self.rlog)

    def assingloggers(self, tlog, rlog):

        # Set the log levels
        tlog.setLevel(logging.DEBUG)
        rlog.setLevel(logging.DEBUG)

        # Create the handlers
        thandler = self.tlogger
        rhandler = self.rlogger

        # Add the handlers to the loggers
        tlog.addHandler(thandler)
        rlog.addHandler(rhandler)
  

    def stylegauge(self):
        self.gauge: AnalogGaugeWidget # type hint for self.gauge 

        self.gauge.setMouseTracking(False)
        self.pushButton_10 : QtWidgets.QPushButton

        self.gauge.units = "Km/h"
        self.gauge.minValue = 0
        self.gauge.maxValue = 260
        self.gauge.scalaCount = 13
        self.gauge.setEnableBarGraph(False)
        self.gauge.setEnableValueText(True)

        self.gauge.setEnableScalePolygon(False)
        self.gauge.setBigScaleColor("white")
        self.gauge.setFineScaleColor("white")

        # Colors
        self.gauge.setNeedleColor(R=255, G=0, B=0)
        self.gauge.setScaleValueColor(R=255, G=255, B=255)
        self.gauge.setDisplayValueColor(R=255, G=255, B=255)
        self.gauge.setCustomGaugeTheme(
            color1= '#413A41', #outer
            color2= "#F7F6F6",
            color3= "#48444B"  #inner
        )


        # Font
        self.gauge.setValueFontFamily('DS-Digital')
        self.gauge.setScaleFontFamily('DS-Digital')
        
    def styleLCD(self):
        self.LCD : QtWidgets.QLineEdit
        self.LCD.setFont(QtGui.QFont('DS-Digital', 16))