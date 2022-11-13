# **Code style**
This file contains the followed code style throughout the project

<br/>

## **Configuration**
---
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

## Cofiguration container
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





## **Naming convention for enumeration literals, status values and pre-processor directives `[SWS_BSW_00124]`**
---
<br/>

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

## **Enumeration**
---

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

