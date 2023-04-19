

from PySide2 import QtWidgets, QtGui
from PySide2.QtGui import QPalette, QColor, Qt
from pathlib import Path
from ui import Ui_Dialog

import sys
import logging

from Custom_Widgets.AnalogGaugeWidget import AnalogGaugeWidget




class MyDialog(QtWidgets.QDialog, Ui_Dialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        QtGui.QFontDatabase.addApplicationFont(str(Path('GUI')/'DS-DIGIB.TTF'))

        self.setupUi(self)
        self.stylegauge()
        self.styleLCD()
        self.gauge.updateValue(50)

    def stylegauge(self):
        self.gauge: AnalogGaugeWidget # type hint for self.gauge 

        self.gauge.setMouseTracking(False)

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
        









app = QtWidgets.QApplication(sys.argv)

# Dark Fusion Style
app.setStyle("Fusion")

dark_palette = QPalette()
dark_palette.setColor(QPalette.Window, QColor(53, 53, 53))
dark_palette.setColor(QPalette.WindowText, Qt.white)
dark_palette.setColor(QPalette.Base, QColor(25, 25, 25))
dark_palette.setColor(QPalette.AlternateBase, QColor(53, 53, 53))
dark_palette.setColor(QPalette.ToolTipBase, Qt.white)
dark_palette.setColor(QPalette.ToolTipText, Qt.white)
dark_palette.setColor(QPalette.Text, Qt.white)
dark_palette.setColor(QPalette.Button, QColor(53, 53, 53))
dark_palette.setColor(QPalette.ButtonText, Qt.white)
dark_palette.setColor(QPalette.BrightText, Qt.red)
dark_palette.setColor(QPalette.Link, QColor(42, 130, 218))
dark_palette.setColor(QPalette.Highlight, QColor(42, 130, 218))
dark_palette.setColor(QPalette.HighlightedText, Qt.black)
dark_palette.setColor(QPalette.Disabled, QPalette.Text, Qt.darkGray)
dark_palette.setColor(QPalette.Disabled, QPalette.ButtonText, Qt.darkGray)

app.setPalette(dark_palette)
app.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }")



dlg = MyDialog()



logging.debug('damn, a bug')
logging.info('something to remember')
logging.warning('that\'s not right')
logging.error('foobar')
logging.debug('damn, a bug')
dlg.show()
dlg.raise_()
sys.exit(app.exec_())