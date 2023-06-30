# Concept Brainstorming for Bushido Freeze Project
**Created:**&nbsp;&nbsp; June 29<sup>th</sup>, 2023  
**Updated:**&nbsp; 06-29-23 @ 10:46 PM
---

&nbsp;
## 1 &nbsp;&nbsp; Main Idea

A CLI (terminal) tool for accessing, managing, and storing GitHub personal authorization tokens securely.


&nbsp;
## 2 &nbsp;&nbsp; Main Concepts

* allow users to add any number of personal access tokens to be stored and managed by the system
	* allow users to add/edit metadata like a title, a description, start date, and end date for each token added
	* allow users to remove tokens they've added
* allow users to view a summary of all their tokens and token metadata
* allow users to easily access their tokens "on demand"
* allow users to configure pre-expiry notifications for their tokens
	* system will always notify users when they access expired tokens
* allow users to configure security features (like encryption) for their locally stored token data
	* security features will be appropriately minimal by default
* allow users to export their tokens to file for backing up and/or remote storage
	* allow users to configure security features for export files (like encryption)
	* by default the export file should be human-readable (no security)
* allow users to designate a particular token as their default for access operations
	* other tokens that aren't the default can be referenced specifically, when needed
* allow users to set an alias for a given token for referencing during export operations


&nbsp;
## 3 &nbsp;&nbsp; Initial Analysis

##### Expected Token (Meta)Data

* title
...

##### Sample System Flowchart

...

##### Identified Use Cases

1. Add a personal access token
2. Edit a token (metadata)
3. View summary of token metadata
4. Get expiry status of token
5. Export token metadata to a file
6. Configure pre-expiry notifications for token
7. Configure storage security for token metadata
8. Set default token to access
