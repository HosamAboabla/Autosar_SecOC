from ctypes import *

lib = ".\\build\\libSecOCLib.dll"

mylib = WinDLL(lib)

print("GUI: started");

# Initializing SecOC
mylib.GUIInterface_init();


# Create an array of bytes in Python
data = (c_ubyte * 2)(9, 9)
dataLen = len(data)

print(f"GUI: Our data is: {data[0]} {data[1]}");

# Generate Frame
mylib.GUIInterface_authenticate(0, data, dataLen);

# preparing argument and return type for getsecuredPDU
securedLen = c_int8()
secPdu = mylib.GUIInterface_getSecuredPDU(0, byref(securedLen));

secPdu = cast(secPdu, POINTER(c_uint8))

# Create a a byte array with the returned address
secPdu = (c_uint8 * securedLen.value).from_address(addressof(secPdu.contents))

print("GUI: Print secured PDU")
for i in range(securedLen.value):
    print(secPdu[i], end = " ")
print() 

mylib.GUIInterface_alterFreshness(0)

print("GUI: Print secured PDU with altered freshness");
for i in range(securedLen.value):
    print(secPdu[i], end = " ")
print() 


mylib.GUIInterface_alterAuthenticator(0)

print("GUI: Print secured PDU with altered authenticator")
for i in range(securedLen.value):
    print(secPdu[i], end = " ")
print()

print("Python Program ran successfully");

