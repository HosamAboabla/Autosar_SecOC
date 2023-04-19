from PySide2 import QtWidgets
import logging
import threading







class QTextEditLogger(QtWidgets.QPlainTextEdit, logging.Handler):
    def __init__(self, parent):
        super().__init__()

        logging.getLogger().addHandler(self)

        self.setReadOnly(True)
        self.setLevel(logging.DEBUG)
        self.setFormatter(logging.Formatter('%(levelname)s\t- %(message)s'))
        self.filters = []
        self.lock = threading.RLock()


    def emit(self, record):
        msg = self.format(record)
        if record.levelname == 'WARNING':
            emoji = u'\U000026A0' # Unicode for the warning emoji
            text = f'{emoji} {msg}'
        elif record.levelname == 'INFO':
            emoji = u'\U00002705' # Unicode for the check mark emoji
            text = f'{emoji} {msg}'
        elif record.levelname == 'DEBUG':
            emoji = u'\U0001F41D' # Unicode for the spider emoji
            text = f'{emoji} {msg}'
        elif record.levelname == 'ERROR':
            emoji = u'\U0001F6A8' # Unicode for the red circle emoji
            text = f'{emoji} {msg}'
        else:
            text = msg


        self.appendPlainText(text)

logging.getLogger().setLevel(logging.DEBUG)  # Set root logger level to DEBUG
