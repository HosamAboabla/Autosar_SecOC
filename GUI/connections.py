try:
    from mydialog import MyDialog
except ImportError:
    pass

from ctypes import *
import sys
from pathlib import Path
import threading
import datetime
import struct

class MyConnections:
    def __init__(self, dialog):
        self.dialog : MyDialog = dialog


        if sys.platform == 'win32':
            libname = 'libSecOCLibShared.dll'
        elif sys.platform == 'linux':
            libname = 'libSecOCLibShared.so'
        else:
            raise Exception("Not supported OS")


        lib = Path('build') / libname 

        self.mylib = CDLL(str(lib))


        # Initializing SecOC
        self.mylib.GUIInterface_init()

        # Reciving thread
        self.current_rx_id = -1


        receiver_thread = threading.Thread(target=self.receiver)
        receiver_thread.start()
        # Transmitter tab connections
        self.dialog.configSelect.currentIndexChanged.connect(self.OnConfigChanged)

        self.dialog.accelButton.clicked.connect(self.OnAccelButtonClicked)
        self.dialog.decelButton.clicked.connect(self.OnDecelButtonClicked)
        self.dialog.showTimeButton.clicked.connect(self.OnShowTimeButtonClicked)
        self.dialog.showDateButton.clicked.connect(self.OnShowDateButtonClicked)

        self.dialog.alterFreshButton.clicked.connect(self.OnAlterFreshButtonClicked)
        self.dialog.alterAuthButton.clicked.connect(self.OnAlterAuthButtonClicked)

        self.dialog.transmitButton.clicked.connect(self.OnTransmitButtonClicked)
        self.dialog.tlogClearButton.clicked.connect(self.OnTlogClearButtonClicked)

        # Receiver tab connections
        self.dialog.verifyButton.clicked.connect(self.OnVerifyButtonClicked)
        self.dialog.rlogClearButton.clicked.connect(self.OnRlogClearButtonClicked)


        
    def UpdateTransmitterSecPayload(self):
        # preparing argument and return type for getsecuredPDU
        securedLen = c_int8()

        currentIndex = self.dialog.configSelect.currentIndex()
        secPdu = self.mylib.GUIInterface_getSecuredPDU(currentIndex, byref(securedLen))

        # convert the char* to a Python string
        my_bytes = string_at(secPdu, securedLen.value)
        my_string = my_bytes.decode('utf-8')

        # Update the Secured Payload in transmitter tab
        self.dialog.transmitPayload.setText(my_string)
    
    def UpdateReceiverSecPayload(self):
        # preparing argument and return type for getsecuredPDU
        securedLenString = c_int8()
        securedLen = c_int8()


        secPdu = self.mylib.GUIInterface_getSecuredRxPDU(self.current_rx_id , byref(securedLenString), byref(securedLen))

        # convert the char* to a Python string
        my_bytes = string_at(secPdu, securedLenString.value)
        my_string = my_bytes.decode('utf-8')

        # Update the Secured Payload in transmitter tab
        self.dialog.receivePayload.setText(my_string)

   
    def OnConfigChanged(self, index):
        # if CanIf is used
        if(index not in [0,3,5]):
            self.dialog.showDateButton.setEnabled(True)
            self.dialog.showTimeButton.setEnabled(True)
        else:
            self.dialog.showDateButton.setEnabled(False)
            self.dialog.showTimeButton.setEnabled(False)

        if(index in [3]):
            self.dialog.alterFreshButton.setEnabled(False)
        else:
            self.dialog.alterFreshButton.setEnabled(True)
        self.UpdateTransmitterSecPayload()                    

  
    def OnAccelButtonClicked(self):
        self.dialog.tlog.debug("Accelerate  ⬆")

        currentIndex = self.dialog.configSelect.currentIndex()
        # Create an array of bytes in Python
        # if header is 0
        if currentIndex in [3]:
            data = (c_ubyte * 4)(1,0,0,0)
        elif currentIndex in [4]:
            data = (c_ubyte * 19)(1,0,0,0)
        else:
            data = (c_ubyte * 1)(1)

        dataLen = len(data)

        # Generate Frame
        self.mylib.GUIInterface_authenticate(currentIndex, data, dataLen);

        self.UpdateTransmitterSecPayload()

    
    def OnDecelButtonClicked(self):
        self.dialog.tlog.debug("Decelerate  ⬇")
        currentIndex = self.dialog.configSelect.currentIndex()

        # Create an array of bytes in Python
        # if header is 0
        if currentIndex in [3]:
            data = (c_ubyte * 4)(2,0,0,0)
        elif currentIndex in [4]:
            data = (c_ubyte * 19)(2,0,0,0)
        else:
            data = (c_ubyte * 1)(2)

        dataLen = len(data)

        # Generate Frame
        self.mylib.GUIInterface_authenticate(currentIndex, data, dataLen);

        self.UpdateTransmitterSecPayload()

    def OnShowTimeButtonClicked(self):
        self.dialog.tlog.debug("Show Time 🕗")
        # Get the current time as a string in the format "03:12 AM"
        current_time_str =  '3' + datetime.datetime.now().strftime("%I:%M %p") + + 10 * "$"

        # Convert the string to a c_ubyte array
        data = struct.pack("{}s".format(len(current_time_str)), current_time_str.encode())
        dataLen = len(data)

        # Generate Frame
        currentIndex = self.dialog.configSelect.currentIndex()
        self.mylib.GUIInterface_authenticate(currentIndex, data, dataLen);

        self.UpdateTransmitterSecPayload() 


    def OnShowDateButtonClicked(self):
        self.dialog.tlog.debug("Show Date 📅")
        # Get the current date as a string in the format "3/10/2000"
        current_date_str = '4' + datetime.datetime.now().strftime("%-Y/%-m/%d") + 9 * "$"
        # Convert the string to a c_ubyte array
        data = struct.pack("{}s".format(len(current_date_str)), current_date_str.encode())
        dataLen = len(data)

        # Generate Frame
        currentIndex = self.dialog.configSelect.currentIndex()
        self.mylib.GUIInterface_authenticate(currentIndex, data, dataLen);

        self.UpdateTransmitterSecPayload()


    def OnAlterFreshButtonClicked(self):
        self.dialog.tlog.debug("Altered Freshness")

        currentIndex = self.dialog.configSelect.currentIndex()
        self.mylib.GUIInterface_alterFreshness(currentIndex)

        self.UpdateTransmitterSecPayload()

    
    def OnAlterAuthButtonClicked(self):
        self.dialog.tlog.debug("Altered Authenticator")

        currentIndex = self.dialog.configSelect.currentIndex()
        self.mylib.GUIInterface_alterAuthenticator(currentIndex)

        self.UpdateTransmitterSecPayload()
  

    def OnTransmitButtonClicked(self):
        securedLen = c_int8()
        currentIndex = self.dialog.configSelect.currentIndex()
        secPdu = self.mylib.GUIInterface_getSecuredPDU(currentIndex, byref(securedLen))

        if(securedLen.value == 0):
            self.dialog.tlog.error("PDU is empty")
            return

        self.mylib.GUIInterface_transmit(self.dialog.configSelect.currentIndex())
        self.dialog.tlog.info("Transmitted PDU 📡")

   


    def OnTlogClearButtonClicked(self):
        self.dialog.tlogger.clear()                                             


############ Receiver tab buttons #########################


    def OnVerifyButtonClicked(self):
        if self.current_rx_id == -1:
            self.dialog.rlog.error("PDU is empty")      
            return 
        if self.current_rx_id in [6,7]:
            self.current_rx_id = 5
        status = self.mylib.GUIInterface_verify(self.current_rx_id)
        self.dialog.rlog.debug("Verification Completed")      

        # convert the char* to a Python string
        my_bytes = string_at(status) # , status.value
        my_string = my_bytes.decode('utf-8')
        print(my_string)


        if my_string == "E_OK":
            authData , authLen = self.get_auth_data(self.current_rx_id)

            if authData[0] == 1:
                self.dialog.gauge.updateValue(self.dialog.gauge.value + 10)
            elif authData[0] == 2:
                self.dialog.gauge.updateValue(self.dialog.gauge.value - 10)
            elif chr(authData[0]) == '3' or chr(authData[0]) == '4':
                # convert the char* to a Python string
                my_bytes = string_at(authData, authLen.value)
                my_string = my_bytes.decode('utf-8').replace("$" , "")
                self.dialog.LCD.setText(my_string[1:])

            self.dialog.receivePayload.setText("")
            self.dialog.rlog.info('PDU is Authentic')
        else:
            self.dialog.rlog.error(my_string)

        self.current_rx_id = -1
        self.UpdateReceiverSecPayload()

            


    def OnRlogClearButtonClicked(self):
        self.dialog.rlogger.clear()                                             
    

    def get_auth_data(self , idx):
        # # preparing argument and return type for getsecuredPDU
        authLen = c_int8()
        
        authPdu = self.mylib.GUIInterface_getAuthPdu(idx, byref(authLen))

        authPdu = cast(authPdu, POINTER(c_uint8))

        # # Create a a byte array with the returned address
        authPdu = (c_uint8 * authLen.value).from_address(addressof(authPdu.contents))

        # print("GUI: Print secured PDU")
        # for i in range(authLen.value):
        #     print(authPdu[i], end = " ")
        # print() 
        return authPdu , authLen

    def receiver(self):

        while(True):
            rxId = c_int8()
            rxLenString = c_int8()
            finalRxLen = c_int8()
            securedLen = c_int8()

            self.mylib.GUIInterface_receive(byref(rxId) , byref(finalRxLen))
            self.current_rx_id = rxId.value
            securedPdu = self.mylib.GUIInterface_getSecuredRxPDU(self.current_rx_id , byref(rxLenString) , byref(securedLen))

            securedPdu = cast(securedPdu, POINTER(c_uint8))

            # # Create a a byte array with the returned address
            securedPdu = (c_uint8 * securedLen.value).from_address(addressof(securedPdu.contents))
            if securedLen.value >= finalRxLen.value:
                # Update the Secured Payload in transmitter tab
                self.UpdateReceiverSecPayload()
                self.dialog.rlog.info("Received PDU 📩")
