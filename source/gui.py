from ctypes import *

lib = ".\\build\\libSecOCLib.dll"

mylib = WinDLL(lib)

# Initializing SecOC
mylib.GUIInterface_init();


# Create an array of bytes in Python
bytes_array = [9, 9]
num_bytes = len(bytes_array)

# Convert the Python list to a ctypes array of c_uint8 values
c_bytes_array = (c_uint8 * num_bytes)(*bytes_array)

mylib.GUIInterface_authenticate(0, c_bytes_array, num_bytes);

securedlen = c_int8()
secpdu = POINTER(c_uint8)()

secpdu = mylib.GUIInterface_getSecuredPDU(0, byref(securedlen));


secpdu = bytearray(cast(secpdu, POINTER(c_uint8 * securedlen.value)).contents)

for i in range(securedlen.value):
    print(secpdu[i], end = " ")
print() 
#print(secpdu_bytes)


# for i in range(securedlen.value):
#     print(secpdu)
# Get a reference to the function
#my_function = getattr(mylib, 'SecOC_test')
mylib.SecOC_test.restype = c_void_p

# Call the function
result = mylib.SecOC_test(2, 13)

result = c_char_p(result).value.decode('utf-8')


print(result)

print('We still in python')

#getattr(my_functions, 'SecOC_test')()

