from PySide2 import QtWidgets
from PySide2.QtGui import QPalette, QColor, Qt
import sys

from mydialog import MyDialog


        




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
print(dlg.gauge.connect)
# for debugging messages
#dlg.assingloggers(tlog, rlog)

dlg.tlog.error("Authentication failed")
dlg.tlog.info("Info message")

dlg.tlog.warning("Authentication stopped")
dlg.tlog.debug("Debug message")
dlg.rlog.error("Verification failed")

dlg.show()
dlg.raise_()
sys.exit(app.exec_())