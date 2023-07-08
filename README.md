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
- [Future Work](#future-work)
- [License](#license)
- [Credits](#credits)
- [Contact](#contact)


___


## Introduction

This is a bachelor's graduation project that aims to implement the AUTOSAR software module concerned with providing effective information security on in-vehicle networks, addressing the rising concerns surrounding malicious attacks. By supplementing the existing AUTOSAR package, SecOC introduces a set of communication encryption and verification standards specifically designed for telematics buses.


## Contributors

SecOC team under the supervision of:
* Eng. Ahmed Elsaka.
* Prof. Dr. Wael Mohammed AlAwadi.  


Team members are six senior Computer and Automatic Controls Students :
* Abdallah Alaa Ali Salem.
  (Email: @gmail.com)
* Galal Nasser Mohamed Elfeky.
  (Email: @gmail.com)
* Hosam Sayed Ahmed Mohamed Aboabla. 
 (Email: hosamaboabla@yahoo.com)
* Hussein AbdAlsalam Hassan Elsaka.
  (Email: @gmail.com)
* Mohammed Abdelsattar Abdelsattar Aboelniel.
  (Email: @gmail.com)
* Ziad Ashraf Kamel Gamalelden.
  (Email: @gmail.com)
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

* Test Cases

1. Test Case 1: Message Authentication

Verify that the SecOC module properly authenticates outgoing messages.

2. Test Case 2: Message Integrity Verification

Ensure that the SecOC module correctly verifies the integrity of incoming messages.

3. Test Case 3: Communication Security

Validate the end-to-end communication security using the SecOC module using direct transmission with header.

4. Test Case 4: Different configurations of PDUs using the GUI

Ensures that the SecOC is working correctly with different configurations of PDUs like direct with header, direct
without header, and transport protocol over CAN or Ethernet

5. Test Case 5: Sending PDUs with altered MAC and Freshness and sending the same PDU twice:

Ensures that the SecOC is responding successfully to different attacks like replay attack and man in the middle attack


* Test Results

1. Test Case 1: Message Authentication
 
* result: Pass
* Description: The SecOC module successfully authenticated outgoing messages. The encrypted messages matched the
expected encryption algorithm.


2. Test Case 2: Message Integrity Verification 

o Result: Pass 

o Description: The SecOC module correctly verified the integrity of incoming messages. Valid messages were detected as intact, and
invalid messages were detected as modified.


3. Test Case 3: Communication Security 
o Result: Pass 
o Description: The end-to-end communication security was successfully established using the SecOC module. Messages exchanged between the Raspberry Pis were properly encrypted,
transmitted, decrypted, and verified for integrity.


4. Test Case 4: Different configurations of PDUs using the GUI: 
o Result: Pass 
o Description: the PDUs are authenticated, transmitted, and verified successfully for all the following configurations 1. Direct Transmission (CanIf) 2. Transport protocol transmission (CanTp) 3. Transport protocol transmission (Ethernet) 4. Direct Transmission without Trunc-FV and header (CanIf) 5. Transport transmission without header (CanTp)
6. Secured PDU collection (CanIf)


5. Test Case 5: Sending PDUs with altered MAC and Freshness and sending the same PDU twice:
o Result: Pass 
o Description: The SecOC successfully detects the integrity violation
of repeated PDUs and altered PDUs in MAC or freshness value.

Overall Test Results: o Test Coverage: The defined test cases covered all the specified functionalities and scenarios.
o Defects: No critical defects were identified during the testing phase.
o Test Objectives: The test objectives were achieved, and the SecOC module implementation met the expected functionality, security,
and performance requirements.



## Conclusion

the SecOC module represents an effective and essential information security solution for in-vehicle networks. Its implementation significantly enhances the security of automotive systems, safeguarding against unauthorized access, tampering, and data breaches. By adopting SecOC, automotive manufacturers demonstrate their commitment to customer safety
and contribute to building a more secure and resilient automotive ecosystem.

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

