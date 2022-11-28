# **Code style**
This file contains the followed code style throughout the project according to BSWGeneral SWS documentation

Table of contents
=================

<!--ts-->
* [Configuration containers](#Configuration)
* [Enumeration literals and pre-processor directives](#Enumeration-literals-and-pre-processor-directives)
* [Enumeration](#Enumeration)
* [Error values](#Error-values)
* [Global data](#Global-data)
* [Type definitions](#Type-definitions)
* [Callout APIS](#Callout-APIs)
* [Summary](#Summary)

<!--te-->
<br/>

# Configuration

<br/>

## Configuration parameter
<br/>

-  `[SWS_BSW_00126]` Naming conventions for Configuration parameters names Camel case: `<Ma><Pn>`
- `<Pn>` is the specific parameter name in camel case
- The term `<Pn>` may consist of several words which may or may not be
separated by underscore.`(SRS_BSW_00408, SRS_BSW_00347)`
## Example for configuration parameter 
```C
SecOCSecuredTxPduLength
```
> Note: It's written exactly as the documentation

<br/>

## Configuration container
<br/>

- `[SWS_BSW_00146]` ConfigType shall be labelled according to the following convention:
`<Ma>_<Tn>Type`

Where `<Ma>` is the Module abbreviation ([SWS_BSW_00101]) and `<Tn>` is the Type
name, which shall be written in camel case `(SRS_BSW_00305)`

## Example for configuration container
```C
typedef struct
{
   uint16                  SecOCMessageLinkLen;
   uint16                  SecOCMessageLinkPos;
} SecOC_UseMessageLinkType;
```

<br/>

# Enumeration literals and pre-processor directives 

`[SWS_BSW_00124]`

All enumeration literals, status values and pre-processor
directives (#define) shall be labeled in the following way:
`<MIP>_<SN>`
- `<MIP>` is the Capitalized module implementation prefix of this BSW Module `[SWS_BSW_00102]` and `<SN>` is is the specific name.
- If `<SN>` consists of several words, they shall be separated by underscore.

## Example for pre-processor directives

```C
#define SECOC_AUTH_PDUHEADER_LENGTH         ((uint8)0)
```
## Example for enumeration literals

> Note: Enumeration literals means the parameters inside the enumeration
```C
typedef enum
{
    SECOC_IFPDU,    /* SECOC_IFPDU Interface communication API */ 
    SECOC_TPPDU,    /* SECOC_TPPDU Transport Protocol communication API */ 
} SecOC_PduType_Type;
```
<br/>

# Enumeration
<br/>


- Enumeration shall be labelled according to the following convention:
`<Ma>_<Tn>_Type` <br/>
Where `<Ma>` is the Module abbreviation ([SWS_BSW_00101]) and `<Tn>` is the Type
name, which shall be written in camel case `(SRS_BSW_00305)`
> No enoughe evidence on this one. Depended on enumeratione example in Pg.38, file: SWS_BSWGeneral
## Example for enumeration 
```C
typedef enum
{
    SECOC_IFPDU,    /* SECOC_IFPDU Interface communication API */ 
    SECOC_TPPDU,    /* SECOC_TPPDU Transport Protocol communication API */ 
} SecOC_PduType_Type;
```
<br/>



# Error values
<br/>

- Error values shall be named in the following way: `<MIP_E_<EN>` <br/>
Where here `<MIP>` is the Capitalized module implementation prefix of this BSW Module `[SWS_BSW_00102]`, `<EN>` is the error name. Only capital letters shall be used. If `<EN>` consists of several words, they shall be separated by underscore.c `(SRS_BSW_-00327)`
## Example for error values 
```C
#define SECOC_BUFREQ_E_NOT_OK // Data was not copied because an error occurred.
```
<br/>



# Global data
<br/>

- If the BSW Module defines d global variables, then their definition shall take place in the Implementation source file `(SRS_BSW_00308)`
- All global variables defined by the BSW Module shall be labeled according to the following: `<Mip>_<Vn>` <br/>
Where `<Mip>` is the Module implementation prefix of the BSW Module
`[SWS_BSW_00102]` and `<Vn>` is the Variable name, which shall be written in camel case `(SRS_BSW_00307)`

## Example for global variable 
```C
SecOC_MessageBuffer[SECOC_BUFFER_LENGTH]
```
- Definition of **constant global** variables dIf the BSW Module defines global variables with read-only purpose, this shall be formalized by assigning the **const** qualifier to their definitions and declarations `(SRS_BSW_00309)`

<br/>



# Type definitions
<br/>

- `[SWS_BSW_00146]` All data types defined by the BSW Module, **except ConfigType**, shall be labelled according to the following convention: `<Ma>_<Tn>Type`<br/>
 Where `<Ma>` is the Module abbreviation `[SWS_BSW_00101]` and `<Tn>` is the Type name, which shall be written in camel case `(SRS_BSW_00305)`

## Example for Typedefs
```C
typedef uint16 SecOC_VerificationStatusType
```
<br/>



# Callout APIS
<br/>

- `[SWS_BSW_00135]` The following convention shall be used for declaration of Callout functions prototypes:<br/>
```C
 /* --- Start section definition: --- */

#define <MIP>_START_SEC_<CN>_CODE

/* --- Function prototype definition: --- */

FUNC(void, <MIP>_<CN>_CODE) <Cn> (void);

/* --- Stop section definition: --- */

#define <MIP>_STOP_SEC_<CN>_CODE
```

## Example for Callout
```C
 /* --- Start section definition: --- */

#define SECOC_START_SEC_GETRXFRESHNESS_CODE

/* --- Function prototype definition: --- */

FUNC(void, SECOC_GETRXFRESHNESS_CODE) GetRxFreshness (void);

/* --- Stop section definition: --- */

#define SECOC_STOP_SEC_GETRXFRESHNESS_CODE
```
<br/>



# Summary 

<br/>

## Example for configuration type and its parameters
```C
typedef struct
{
   uint16                  SecOCMessageLinkLen;
   uint16                  SecOCMessageLinkPos;
} SecOC_UseMessageLinkType;
```


## Example for pre-processor directives
```C
#define SECOC_AUTH_PDUHEADER_LENGTH         ((uint8)0)
```


## Example for enumeration and enumeration literals
```C
typedef enum
{
    SECOC_IFPDU,    /* SECOC_IFPDU Interface communication API */ 
    SECOC_TPPDU,    /* SECOC_TPPDU Transport Protocol communication API */ 
} SecOC_PduType_Type;
```


## Example for error values 
```C
#define SECOC_BUFREQ_E_NOT_OK // Data was not copied because an error occurred.
```


## Example for global variable 
```C
SecOC_MessageBuffer[SECOC_BUFFER_LENGTH]
```
> If the global variable is read-only, add the const qualifer 


## Example for Typedefs
```C
typedef uint16 SecOC_VerificationStatusType
```

## Example for Callout
```C
 /* --- Start section definition: --- */

#define SECOC_START_SEC_GETRXFRESHNESS_CODE

/* --- Function prototype definition: --- */

FUNC(void, SECOC_GETRXFRESHNESS_CODE) GetRxFreshness (void);

/* --- Stop section definition: --- */

#define SECOC_STOP_SEC_GETRXFRESHNESS_CODE
```
