

from PySide2 import QtWidgets, QtGui, QtQuick
from pathlib import Path
import sys
import logging

from PySide2.QtCore import Qt

from ui import Ui_Dialog
from Custom_Widgets.AnalogGaugeWidget import AnalogGaugeWidget

# Uncomment below for terminal log messages
# logging.basicConfig(level=logging.DEBUG, format=' %(asctime)s - %(name)s - %(levelname)s - %(message)s')




class MyDialog(QtWidgets.QDialog, Ui_Dialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.setupUi(self)
        self.gauge: AnalogGaugeWidget # type hint for self.gauge        
        self.gauge.setMouseTracking(False)
        self.gauge.units = "Km/h"
        self.setAcceptDrops(False)
        self.gauge.minValue = 0
        self.gauge.maxValue = 260
        self.gauge.scalaCount = 13
        self.gauge.setEnableBarGraph(False)
        self.gauge.setEnableValueText(True)
        self.gauge.setNeedleColor(R=255, G=0, B=0)

        self.gauge.setEnableScalePolygon(False)
        self.gauge.setBigScaleColor("white")
        self.gauge.setFineScaleColor("white")



        self.gauge.setScaleValueColor(R=255, G=255, B=255)
        self.gauge.setDisplayValueColor(R=255, G=255, B=255)
        self.gauge.setCustomGaugeTheme(
            color1= '#413A41', #outer
            color2= "#F7F6F6",
            color3= "#48444B"  #inner
        )

        self.gauge.setScalePolygonColor(
            color1= '#ff1302', #end
            color2= "#2F393A",
            color3= "#2F393A",

        )

        QtGui.QFontDatabase.addApplicationFont(str(Path('GUI')/'DS-DIGIB.TTF'))
        self.gauge.setValueFontFamily('DS-Digital')
        self.gauge.setScaleFontFamily('DS-Digital')
        def  mouseMoveEvent(self, event):
            pass
        #self.gauge.setFont(QtGui.QFont('DS-Digital', 50))
        

        self.LCD : QtWidgets.QLineEdit
        self.LCD.setFont(QtGui.QFont('DS-Digital', 16))
        
        #self.gauge.set_scale_polygon_colors(["red"])









app = QtWidgets.QApplication(sys.argv)
app.setStyleSheet((Path('GUI')/'stylesheet.qss').read_text())



dlg = MyDialog()
dlg.show()
dlg.raise_()
sys.exit(app.exec_())