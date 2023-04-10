from ctypes import *

lib = ".\\build\\libSecOCLib.dll"

mylib = WinDLL(lib)

# gui for windows

# Get a reference to the function
#my_function = getattr(mylib, 'SecOC_test')


# Call the function
mylib.SecOC_test(2, 13)

print('We still in python')

#getattr(my_functions, 'SecOC_test')()

