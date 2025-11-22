**Information**

Here is my implementation of the scecurity card system. It is coded in a traditional way , a state machine where the states are represented by enumerations. The state machine is called from an etertal loop inside the main function. The idea is that "we" are in a state and checking wheather we shall transit to another state.
In each state there are specific functionality and it is implemented as funtions.

There is a big room for improvement of the code but it does what it should.
Future improvements:
- Use more references and/or pointers
- Make the functions more modular (combine functions, create more but smaller functions etc)
- Reduce the code in the state machine, put it as functions instead
- Make fault handing better, now the program is terminated if input isn't correct or if files are not possible to open etc. 

**Requirements**

1. Program submitted via Github

2. Req 1.1 Role based: implemented. 
Checks that input is only 0, 1 or 2

3. Req 1.2 User login: implemented. 
Login by name or ID.
Users specified in User.csv

4. Req 1.3 User operations: implemented.
List all floors - Access floor (see FloorAccessHistory.csv)
Show personal info  
Change personal info
Log out

5. Req 1.4 Admin login: implemented
Login with ID and password. Checks on password and match ID/Password
Admins are specified in Admin.csv

6. Req 1.5 Admin operations: implemented.
List all floors - see access history & change floor info
List all users - change & delete user
Create new user
Log out

7. Req 1.6 User: implemented. User info in User.csv. Card number in User.csv and Card.csv
ID and card are unique.

8. Req 1.7 Admin: implemented. 
ID and card are unique. 

9. Req 1.8 Floor: implemented. 
This buildning contains 3 fllors (fixed).

10. Req 1.9 Card: implemented.
Card number unique. Card number in both User.csv and Card.csv 

11. Req 2.1 Persistence:implemented.
Data saved in csv files

12. Req 2.2 Validation: implemented.
Password, email and phone number validated. 

13. Req 2.3 Exceptions: partly implemented.

14 Req 2.4 Logging: implemented.
Logging data saved in FloorAccessHistory.csv

**General information about the assignment**

- checks that the user inputs only valid characters. If not, the program is usually terminated.

- Implementation done in a very traditional way with functions

- Code could of cause be improved and reduced 

**csv files**

User.scv: user info, ID (unique), name (only first name), email, phone number and card number (unique). Card number also in Card.csv
Admin.csv: similar to User.csv but contains password as well. Each admin has unique ID/Password
Card.csv: card number and clearance level. Clearance level tied to a specific user via card number
Floor.csv: floor, name and clearance level
FloorAccesHistory.csv: User access history, name and when they entered the floor
Temp1.csv: only used during program execution


**Assignment descriptiom**

You are tasked with implementing the business logic for a card access system for a government building in C++. The system will allow users and administrators to interact with the system through a console-based interface and handle access based on the floors and employees clearance levels.

Deliverable
The complete program must be submitted via a private GitHub repository and shared with the examiner (@lafftale1999).

The student must also perform a live demonstration in a small group, where the program is run and key features are shown.

During the demo, the student must be able to explain key design and implementation decisions, as well as answer questions regarding the codebase.

Grading
2.1. Pass (G)
All functional and non-functional requirements marked as G are correctly implemented and working as intended.
The system runs without crashes and fulfills the specified user and admin operations.
The student can clearly explain how the program works.
 
2.2. Pass with distinction (VG)
All requirements for Grade G are met in full.
All VG-level requirements are fully implemented and functional.
The student demonstrates:
Consistent naming conventions
Good folder structure
Efficient and non-repetitive code following DRY principles
Good use of STL
The student can articulate and justify their design and implementation decisions, showing an understanding of advanced C++ concepts and system design principles.

SecureCardSystem Requirement Specification.pdf (see files in Git)
