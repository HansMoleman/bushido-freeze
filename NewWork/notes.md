# Notes for Bushido Freeze Project Concept
**Created:**&nbsp;&nbsp; March 28<sup>th</sup>, 2024  
**Updated:**&nbsp; 03-28-2024 @ 07:13 PM

---

&nbsp;
### Index of Contents

1. Use Cases
    1.1 List of Use Cases
    1.2 Brief Descriptions
        1.2.1 Update Token Value
        1.2.2 Get Token Value
        1.2.3 Export Token Value
        1.2.4 Import Token Value
    1.3 Detailed Descriptions

2. Misc.

---


&nbsp;
## 1 &nbsp;&nbsp; Use Cases

This section outlines all information related to the use cases associated with the concept system.

### 1.1 &nbsp;&nbsp; List of Use Cases

1. Update the Token's Value
2. Get the Token's Value
3. Export the Token's Value
4. Import the Token's Value


### 1.2 &nbsp;&nbsp; Brief Descriptions

The following are brief descriptions for each of the use cases listed in the previous section.

#### 1.2.1 &nbsp;&nbsp; Update Token Value

(description)

#### 1.2.2 &nbsp;&nbsp; Get Token Value

(description)

#### 1.2.3 &nbsp;&nbsp; Export Token Value

(description)

#### 1.2.4 &nbsp;&nbsp; Import Token Value

(description)


### 1.3 &nbsp;&nbsp; Detailed Descriptions

The following are more detailed descriptions for each of the use cases listed in section 1.1.


#### 1.3.1 &nbsp;&nbsp; Update Token Value

**Primary User:**&nbsp;&nbsp; Main User
**User's Goals:**&nbsp;&nbsp; Update stored token to a new value.


##### Pre-Conditions

No pre-conditions are associated with this use case.


##### Post-Conditions

* token data is stored to local storage.
* system is able to make token available to user via 'Get Token Value' use case.


##### Main Success Scenario

1. User prompts system to update the stored token value.
2. System requests new token value from the user.
3. User enters the new token value and submits it to the system. [Exc-1: submission is an unexpected length]
4. System loads key data stored in local storage.
5. System uses key data to encrypt the new token data.
6. System writes new encrypted token data to local storage, overwriting (any) previous token data.
7. System confirms operation has completed successfully and then exits.


##### Alternative Flows

No alternative flows associated with this use case.

##### Exceptions

<u>**Exc-1:**_Submission is of Unexpected Length_</u>  
1. User submits a new token value that's less/greater in length than the expected token length.
2. System notifies the user that the submission cannot be accepted and so operation is canceled.
3. System exits.


##### Special Requirements

No special requirements associated with this use case.


##### Open Issues

No issues currently open for this use case.



#### 1.3.2 &nbsp;&nbsp; Get Token Value

**Primary User:**&nbsp;&nbsp;
**User's Goals:**&nbsp;&nbsp;

##### Pre-Conditions

##### Post-Conditions

##### Main Success Scenario

##### Alternative Flows

##### Exceptions

##### Special Requirements

##### Open Issues


#### 1.3.3 &nbsp;&nbsp; Export Token Value

**Primary User:**&nbsp;&nbsp;
**User's Goals:**&nbsp;&nbsp;

##### Pre-Conditions

##### Post-Conditions

##### Main Success Scenario

##### Alternative Flows

##### Exceptions

##### Special Requirements

##### Open Issues


#### 1.3.4 &nbsp;&nbsp; Import Token Value

**Primary User:**&nbsp;&nbsp;
**User's Goals:**&nbsp;&nbsp;

##### Pre-Conditions

##### Post-Conditions

##### Main Success Scenario

##### Alternative Flows

##### Exceptions

##### Special Requirements

##### Open Issues



&nbsp;
## 2 &nbsp;&nbsp; Misc.

...



&nbsp;
&nbsp;

---

&nbsp;
&nbsp;
