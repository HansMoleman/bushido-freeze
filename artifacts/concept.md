# Concept Brainstorming for Bushido Freeze Project
**Created:**&nbsp;&nbsp; June 29<sup>th</sup>, 2023  
**Updated:**&nbsp; 06-30-23 @ 3:14 AM
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

The following table outlines the data points expected to be associated with a given token:

| Data Name   | Description |
|-------------|-------------|
| title       | token name  |
| description | token desc. |
| value       | PAT value   |
| valid-from  | start date  |
| valid-to    | expiry date |
| date-added  | date added  |
| UID         | unique id   |
| alias       | token ref.  |
|-------------|-------------|


##### Sample System Flowchart

The following outlines the main usage flow for the system based on three scenarios: the user is referencing no token, the user is referencing a single token, and the user is referencing multiple tokens. The scenarios are ordered such that each use case appears with the state it can be first used, and certain use cases can be used in the states below them. For example, a user may view the list of all tokens & data registered with the system during any state, whereas a user may only export token data in the last two states (once there is one or more sets of token data to export), and a user may only access during the second state (since only one token can be accessed at once).

**Flowchart:**

0. User has no tokens registered with the system
	1. User may view a list of all tokens registered with the system and their associated metadata
	2. User may configure any available system settings

1. User registers a new token with the system
	1. User may edit any metadata associated with the token
	2. User may access the token's value
	3. User may view a summary of the token's metadata
	4. User may check the status of the token (data related to expiration)
	5. User may configure expiry notifications for the token
	6. User may configure security settings/features for the token
	7. User may export token data to file
	8. User may set token as the default token for accessing
	9. User may set an alias for referencing the token

2. User has registered more than one token with the system
	1. User may view a list of all tokens registered with the system and their associated metadata
	2. User may export all, or a selction of, the tokens registered with the system to file


##### Identified Use Cases

1. Add a personal access token
2. Edit a token (metadata)
3. View summary of token metadata
4. Get expiry status of token
5. Export token metadata to a file
6. Configure pre-expiry notifications for token
7. Configure storage security for token metadata
8. Set default token to access

