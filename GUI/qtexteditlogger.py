from PySide2 import QtWidgets
import logging
import threading







class QTextEditLogger(QtWidgets.QPlainTextEdit, logging.Handler):
    def __init__(self, parent):
        super().__init__()

        self.setReadOnly(True)
        self.setLevel(logging.DEBUG)
        self.setFormatter(logging.Formatter('%(levelname)8s %(message)s'))
        self.filters = []
        self.lock = threading.RLock()


    def emit(self, record):
        msg = self.format(record)
        if record.levelname == 'WARNING':
            emoji = u'\u26A0\ufe0f' # Unicode for the warning emoji
            text = f'{emoji} {msg}'
        elif record.levelname == 'INFO':
            emoji = u'\U00002705' # Unicode for the check mark emoji
            text = f'{emoji} {msg}'
        elif record.levelname == 'DEBUG':
            emoji = u'\U0001f41e' # Unicode for the spider emoji
            text = f'{emoji} {msg}'
        elif record.levelname == 'ERROR':
            emoji = u'\u274c' # Unicode for the red circle emoji
            text = f'{emoji} {msg}'
        else:
            text = msg


        self.appendPlainText(text)

