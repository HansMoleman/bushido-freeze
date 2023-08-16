# Use Case Document for Bushido Freeze Project
**Created:**&nbsp;&nbsp; June 30<sup>th</sup>, 2023  
**updated:**&nbsp; 08-16-2023 @ 6:13 PM
---

&nbsp;
### Index of Contents

1. [List of System Use Cases](#1-list-of-system-use-cases)
2. [Brief Use Case Descriptions](#2-brief-use-case-descriptions)
3. Detailed Use Case Descriptions

---


&nbsp;
## 1 &nbsp;&nbsp; List of System Use Cases

The following are all identified use cases of the system:

* Add new token for storage
* Edit (existing) token's metadata
* Remove token (including metadata) from storage
* Set target token as default token
* Access (target) token's value
* View target token's metadata
* View summary of all tokens/system
* Check (target) token's expiry status
* Export target token's data to file
* Export all tokens' data to file


&nbsp;
## 2 &nbsp;&nbsp; Brief Use Case Descriptions

The following are brief descriptions of all identified system use cases:

##### Add New Token for Storage

The user runs the system with argument denoting a new token should be added. The system then collects the token metadata from the user and uses it to create a token instance, which is then saved to file. The system gives the user confirmation the new token has been stored successfully, then exits.

##### Edit (Existing) Token's Metadata

The user runs the system with argument denoting a token's data should be modified, specifying the target token and the changes to be made. The system loads the target token's data from file, creating a temporary token instance to represent the token. The system modifies the token instance's data according to the changes submitted by the user, then saves the token instance to file (over-writing previous save data). The system gives user confirmation the changes have been saved successfully, then exits.

##### Remove Token (Completely & Permanently) From Storage

The user runs the system with argument denoting a token should be removed from storage, specifying the target token to remove. The system loads the contents of the save file, removes all data associated with target token, then saves the remaining data back to file (overwriting previous save data). The system gives user confirmation that target token has been removed successfully, then exits.

##### Access (Target) Token's Value

The user runs the system with argument denoting a token's value should be accessed, specifying the target token, or not specifying a token if the default token should be accessed. The system loads the data of the target (or default) token and outputs the token's value for the user, then exits.


&nbsp;
## 3 &nbsp;&nbsp; Detailed Use Case Descriptions

The following are detailed descriptions of all identified system use cases:
