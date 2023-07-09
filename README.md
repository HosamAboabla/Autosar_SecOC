# Implementation of AUTOSAR SecOC Module 



## Table of Contents

- [Introduction](#introduction)
- [Contributors](#contributors)
- [SecOC Operation](#secoc-operation)
- [Supported Modes](#supported-modes)
- [Tools](#tools)
- [Installation](#installation)
- [Testing](#testing)
- [Documentation](#documentation)
- [Conclusion](#conclusion)
- [Supported Features](#supported-features)
- [Future Work](#future-work)
- [License](#license)
- [Credits](#credits)
- [Contact](#contact)


___


## Introduction

This is a bachelor's graduation project that aims to implement the AUTOSAR software module concerned with providing effective information security on in-vehicle networks, addressing the rising concerns surrounding malicious attacks. By supplementing the existing AUTOSAR package, SecOC introduces a set of communication encryption and verification standards specifically designed for telematics buses.


## Contributors

SecOC team under the supervision of:
* Prof. Dr. Wael Mohammed AlAwadi.  
* Eng. Ahmed Elsaka.


Team members are six senior Computer and Automatic Controls Students :
* Abdallah Alaa Ali Salem.
* Galal Nasser Mohamed Elfeky.
* Hosam Sayed Ahmed Mohamed Aboabla. 
* Hussein AbdAlsalam Hassan Elsaka.
* Mohammed Abdelsattar Abdelsattar Aboelniel.
* Ziad Ashraf Kamel Gamalelden.


### What is SecOC?

SecOC (Secure On-Board Communication) is integrated as an information security component within the AUTOSAR architecture. It incorporates various functionalities, including encryption and decryption operations, key management, and fresh value management and distribution. At the PDU (Protocol Data Unit) level, SecOC offers a robust authentication mechanism for critical data. The authentication mechanism seamlessly integrates with the current AUTOSAR communication systems while minimizing resource consumption, ensuring backward compatibility with legacy systems.


### Why to use SecOC?

In modern vehicles, the number of on-board controllers has significantly
increased, accompanied by the advancement of automotive electronics and
the complexity of vehicle functions. These controllers rely on constant
communication, transmitting and receiving vast amounts of data to fulfill their
respective functions. Various communication protocols, such as Lin, CAN,
CANFD, Flex Ray, and vehicle Ethernet, are employed to facilitate this
communication. However, the majority of data transmission within in-vehicle
networks lacks adequate security measures. Even in cases where security
measures exist, they are often rudimentary, leaving the controllers to interact
with data in its raw form.

SecOC ensures the authenticity and integrity of received data in vehicle systems. It ensures that received data comes from the right ECU and has the correct value.

## SecOC Operation

Both the sending and receiving ECUs must implement a SecOC module to verify
the authenticity and freshness of Protocol Data Units (PDUs) exchanged within
the vehicle architecture. The SecOC modules on both sides integrate with the
upper and lower layer PduR APIs and interact with the PduR module. External
Freshness Managers provide message freshness to the SecOC modules for each
uniquely identifiable Secured I-PDU (Secured Inter-Process Data  Unit).

* Sender Side Operations:

On the sender side, the SecOC module creates a Secured I-PDU by adding authentication information to the outgoing Authentic I-PDU. This authentication information consists of an Authenticator (such as a Message Authentication Code) and optionally a Freshness Value. The Freshness Value, whether included or not in the Secure I-PDU payload, influences the generation of the Authenticator. When using a Freshness Counter, it should be incremented by the Freshness Manager before providing the authentication information to the receiver side.

* Receiver Side Operations

On the receiver side, the SecOC module verifies the freshness and authenticity of the received Authentic I-PDU by examining the appended authentication information added by the sender side SecOC module. The verification process entails comparing the received Secured I-PDU with the one provided by the sender side SecOC module. Additionally, the receiver side SecOC module requires knowledge of the Freshness Value used during the creation of the Authenticator.



## Supported Modes

1. Direct mode:

Direct mode in the SecOC module is a security mode that provides basic authentication and message integrity.
In direct mode, the SecOC module uses a shared secret key to authenticate the sender and verify the integrity of the message. The shared secret key is preshared between the sender and receiver.
When a message is sent in direct mode, the SecOC module calculates a
message authentication code (MAC) using the shared secret key. The MAC is then appended to the message.
The receiver of the message calculates the MAC using the same shared secret key. If the calculated MAC matches the MAC that was appended to the message, then the receiver can be confident that the message was sent by a legitimate sender and that the message has not been tampered with.

2. TP Mode:

- The TP mode in SecOC involves the use of a transport protocol for secure communication between sender and receiver entities.
- The transport protocol is responsible for establishing a reliable and secure communication channel between the SecOC modules on both sides.
- In the TP mode, large messages are segmented into smaller units at the sender side before transmission.
- The segments are individually secured and transmitd ovteer the communication channel.
- At the receiver side, the segments are reassembled to reconstruct the original message.



## Tools

1. CMake (version 3.25.2)

* CMake served as a vital tool for various aspects of our development process. We utilized CMake to compile the codebase, primarily focusing on the Windows platform for development and testing purposes.
However, our main target environment was the Linux-based Raspberry Pi.

* CMake played a crucial role in integrating Google Test (Gtest) into our project. By leveraging CMake's capabilities, we configured the build settings and dependencies required for incorporating Gtest. This facilitated the creation and execution of unit tests, ensuring the robustness and accuracy of our
codebase.

* CMake aided us in printing the paths of included files. This feature was particularly valuable for working with MISRA extension and ensuring compliance with its guidelines. By extracting and logging the paths of included files, we could cross-reference them with MISRA requirements, promoting code
quality and adherence to industry standards.

* CMake facilitated the creation of a static/shared library from our codebase. This library served as a modular component that could be easily integrated with both the GUI frontend and the Gtest framework. By organizing our code into a library, we enhanced code management, reusability, and the
overall project structure.


2. CppCheck

* we utilized the Cppcheck extension in our integrated development environment (IDE) to enforce MISRA compliance. Cppcheck is a static analysis tool for C and C++ code that helps identify potential issues and adherence to coding standards.

* By incorporating the Cppcheck extension into our IDE, we were able to run MISRA checks on our codebase. The extension provided us with valuable
feedback by indicating the number of rule violations detected in our code.

3. Github

* GitHub played a pivotal role in our project as a robust collaboration platform. We utilized GitHub for seamless teamwork, version control, and efficient
project management.

* Through GitHub's collaborative features, team members could work together effectively regardless of geographical locations. We leveraged its branching and merging capabilities to create separate branches for different features or bug fixes, enabling parallel development and minimizing conflicts. This streamlined
our workflow and allowed for efficient collaboration.


## Installation
``` bash
git clone https://github.com/HosamAboabla/Autosar_SecOC.git
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
```
## Testing

* Test Cases and Results

1. Test Case 1: Message Authentication

        o Description: Verify that the SecOC module properly authenticates outgoing messages.
        o Result: Pass

2. Test Case 2: Message Integrity Verification

        o Description: Ensure that the SecOC module correctly verifies the integrity of incoming messages.
        o Result: Pass
        
3. Test Case 3: Communication Security

        o Description: Validate the end-to-end communication security using the SecOC module using direct transmission with header.
        o Result: Pass


4. Test Case 4: Different configurations of PDUs using the GUI

        o Description: Ensures that the SecOC is working correctly with different configurations of PDUs like direct with header, direct
        without header, and transport protocol over CAN or Ethernet
        o Result: Pass

5. Test Case 5: Sending PDUs with altered MAC and Freshness and sending the same PDU twice:

        o Description: Ensures that the SecOC is responding successfully to different attacks like replay attack and man in the middle attack
        o Result: Pass



## Conclusion

the SecOC module represents an effective and essential information security solution for in-vehicle networks. Its implementation significantly enhances the security of automotive systems, safeguarding against unauthorized access, tampering, and data breaches. By adopting SecOC, automotive manufacturers demonstrate their commitment to customer safety
and contribute to building a more secure and resilient automotive ecosystem.

## Documentation

Software was developed following certain standards and specifications.

APIs, interfaces, confgurations, code and files structure follows the AUTOSAR SecureOnboardCommunication_SWS as per version R21-11 .


The code was developed using best practice techniques following and abiding by the MISRA rules as per MISRA C:2012 standard.

Here you can find our graduation book where you can find more details [Book](https://openai.com "Graduation Document").



## Supported Features
| Section |   |
|----|-----|
| Authentic I-PDU and Secured I-PDU | SWS_SecOC_00261 |
|  Freshness Values | SWS_SecOC_00261 SWS_SecOC_00094 SWS_SecOC_00220 SWS_SecOC_00221 SWS_SecOC_00222 SWS_SecOC_00225 SWS_SecOC_00226 SWS_SecOC_00227 SWS_SecOC_00228 SWS_SecOC_00230 SWS_SecOC_00231 SWS_SecOC_00232 SWS_SecOC_00234 SWS_SecOC_00236 SWS_SecOC_00237 SWS_SecOC_00238 SWS_SecOC_00239 SWS_SecOC_00256 SWS_SecOC_00241 SWS_SecOC_00242 SWS_SecOC_00247 SWS_SecOC_00250|
| Authentication of I-PDUs | SWS_SecOC_00031 SWS_SecOC_00033 SWS_SecOC_00034 SWS_SecOC_00035 SWS_SecOC_00036 SWS_SecOC_00037 |
| Verification of I-PDUs | SWS_SecOC_00040 SWS_SecOC_00203 SWS_SecOC_00211 SWS_SecOC_00042 SWS_SecOC_00046 SWS_SecOC_00047|
| Successful verification of I-PDUs | SWS_SecOC_00050 |
| Relationship to PduR | SWS_SecOC_00153 SWS_SecOC_00212 |
| Initialization | SWS_SecOC_00054 SWS_SecOC_00269 |
| Authentication of outgoing PDUs | SWS_SecOC_00252 SWS_SecOC_00201 SWS_SecOC_00202 SWS_SecOC_00209 SWS_SecOC_00210 SWS_SecOC_00270 SWS_SecOC_00057 SWS_SecOC_00146 SWS_SecOC_00110 SWS_SecOC_00262 |
| Authentication during direct transmission | SWS_SecOC_00058 SWS_SecOC_00060 SWS_SecOC_00061 SWS_SecOC_00062 SWS_SecOC_00063 SWS_SecOC_00064 |
| Authentication during transport protocol transmission | SWS_SecOC_00072 SWS_SecOC_00073 SWS_SecOC_00074 SWS_SecOC_00075 |
| Error handling and cancelation of transmission | SWS_SecOC_00076 SWS_SecOC_00151 SWS_SecOC_00108 |
| Verification of incoming PDUs | SWS_SecOC_00214 SWS_SecOC_00215 SWS_SecOC_00204 SWS_SecOC_00216 SWS_SecOC_00207 SWS_SecOC_00257 SWS_SecOC_00259 |
| Verification during bus interface reception | SWS_SecOC_00078 SWS_SecOC_00079 SWS_SecOC_00080 |
| Verification during transport protocol reception | SWS_SecOC_00082 SWS_SecOC_00083 SWS_SecOC_00084 SWS_SecOC_00085 SWS_SecOC_00086 SWS_SecOC_00087 SWS_SecOC_00255 |
| Skipping Authentication for Secured I-PDUs at SecOC | SWS_SecOC_00265 |
| Error handling and discarding of reception | SWS_SecOC_00089 SWS_SecOC_00121 SWS_SecOC_00208 SWS_SecOC_00109 SWS_SecOC_00263 SWS_SecOC_00264 |
| Multicore Distribution | SWS_SecOC_00276 |
| Imported types | SWS_SecOC_00103 |
| Type definitions | SWS_SecOC_00104 SWS_SecOC_00162 |
| Function definitions | SWS_SecOC_00106 SWS_SecOC_00161 SWS_SecOC_00157 SWS_SecOC_00112 SWS_SecOC_00113 |
| Call-back notifications | SWS_SecOC_00124 SWS_SecOC_00125 SWS_SecOC_00126 SWS_SecOC_00152 SWS_SecOC_00128 SWS_SecOC_00129 SWS_SecOC_00130 SWS_SecOC_00181 SWS_SecOC_00012 |
| Callout Definitions | SWS_SecOC_91007 SWS_SecOC_91004 SWS_SecOC_91003 |
| Scheduled functions | SWS_SecOC_00171 SWS_SecOC_00172 SWS_SecOC_00173 SWS_SecOC_00174 SWS_SecOC_00175 SWS_SecOC_00176 SWS_SecOC_00177 SWS_SecOC_00178 SWS_SecOC_00179 SWS_SecOC_00180 |
| Expected Interfaces | SWS_SecOC_00137 SWS_SecOC_00138 |
| Service Interfaces | SWS_SecOC_91002 SWS_SecOC_91012 |
---
## Future Work

While the SecOC module provides a robust security solution for in-vehicle communication, there may be certain SWS (Software Specifications) that are not currently implemented but can be considered for future enhancements. These potential areas for future work can further strengthen the overall security posture of automotive systems. The following SWS can be explored for
implementation:


| Section |   |
|----|-----|
| Authentic I-PDU and Secured IPDU | SWS_SecOC_00011 |
| Freshness Values | SWS_SecOC_00219 SWS_SecOC_00223 SWS_SecOC_00224 SWS_SecOC_00229 SWS_SecOC_00233 SWS_SecOC_00243 SWS_SecOC_00244 SWS_SecOC_00245 SWS_SecOC_00246 SWS_SecOC_00247 SWS_SecOC_00248 SWS_SecOC_00249 |
| Verification of I-PDUs |  SWS_SecOC_00048 SWS_SecOC_00271 SWS_SecOC_00272|
| Authentication during triggered transmission |  SWS_SecOC_00065 SWS_SecOC_00066 SWS_SecOC_00067 SWS_SecOC_00068 SWS_SecOC_00150 SWS_SecOC_00069 |
| Authentication during transport protocol transmission | SWS_SecOC_00253 SWS_SecOC_00254 SWS_SecOC_00070 SWS_SecOC_00071 |
| Error handling and cancelation of transmission |  SWS_SecOC_00077 SWS_SecOC_00155 SWS_SecOC_00217 SWS_SecOC_00218 SWS_SecOC_00260 SWS_SecOC_00266 |
|Verification of incoming PDUs|  SWS_SecOC_00205 SWS_SecOC_00206 SWS_SecOC_00258 |
| Verification during bus interface reception | SWS_SecOC_00268 SWS_SecOC_00081 |
| Verification during transport protocol reception | SWS_SecOC_00088 SWS_SecOC_00213 |
| Error handling and discarding of reception| SWS_SecOC_00267 |
|Security Events | SWS_SecOC_00273 SWS_SecOC_00274 SWS_SecOC_00115 SWS_SecOC_00275 |
| Error Classification| SWS_SecOC_00101 SWS_SecOC_00114|
| Security Profiles| SWS_SecOC_00311 SWS_SecOC_00312 SWS_SecOC_00313 SWS_SecOC_00314 SWS_SecOC_00190 SWS_SecOC_00191 SWS_SecOC_00192 SWS_SecOC_00193 SWS_SecOC_00194 |
| Function definitions | SWS_SecOC_00107 SWS_SecOC_91008 SWS_SecOC_91009 SWS_SecOC_91010 SWS_SecOC_00122 SWS_SecOC_91013 |
| Call-back notifications | SWS_SecOC_00127 |
| Callout Definitions | SWS_SecOC_91006 SWS_SecOC_91005 |
| Expected Interfaces | SWS_SecOC_00119 SWS_SecOC_91014 |
| Service Interfaces | SWS_SecOC_00141 SWS_SecOC_00148 SWS_SecOC_00142 SWS_SecOC_00002 SWS_SecOC_91016 SWS_SecOC_91001 SWS_SecOC_91020 SWS_SecOC_91021 SWS_SecOC_91022 SWS_SecOC_91015 SWS_SecOC_00149 SWS_SecOC_00160 SWS_SecOC_00991 |
---



## Credits

The Team would like to sincerely thank Assoc. Prof. Dr. Wael Mohammed AlAwadi for his invaluable guidance and support throughout the graduation project. His expertise and mentorship have been instrumental in shaping the outcome of the research.

The Team is also grateful to the technical support team of the company Appraid LLC, especially Eng. Ahmed Elsaka, for their assistance and expertise. Their contributions have greatly enhanced the quality of the work.

The Team would like to express their appreciation to their families and friends for their endless support throughout this endeavor. Their encouragement and belief in the authors' abilities have always been a constant source of motivation.

To every individual who contributed to this project, regardless of their role or level of involvement, thank you for your invaluable contributions. It has been
an honor for the authors to work with such exceptional individuals.



## Contact

If you have any questions, feedback, or suggestions, feel free to reach out:

- [abdallahalaasalem7@gmail.com](mailto:abdallahalaasalem7@gmail.com)
- [galalnasser5@gmail.com](mailto:galalnasser5@gmail.com)
- [hosamaboabla@yahoo.com](mailto:hosamaboabla@yahoo.com)
- [ehussein366@gmail.com](mailto:ehussein366@gmail.com)
- [mohamedaboelnile68@gmail.com](mailto:mohamedaboelnile68@gmail.com)
- [ziad.gamalelden@gmail.com](mailto:ziad.gamalelden@gmail.com)


We would love to hear from you!



## License

This project is licensed under the [MIT License](LICENSE).



### Copyrights

>Copyright (c) 2022-2023 Faculty of Engineering Tanta University 