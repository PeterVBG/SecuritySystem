// If SECCARDSYSTUTILS_H is not defined, define it (start of header guard)
#ifndef SECCARDSYSTUTILS_H

// Define SECCARDSYSTUTILS_H to prevent multiple inclusions
#define SECCARDSYSTUTILS_H

#include <string>


//Function declarations

//Safely convert string to int with exception handling
bool tryConvertToInt(const std::string str); 

//Returns true if input is integer 1, otherwise false
bool user1InputOk(std::string inpStr);

//Returns true if input is integer 1 or 2, otherwise false
bool user12InputOk(std::string inpStr);

//Returns true if input is integer 1, 2 or 3, otherwise false
bool user123InputOk(std::string inpStr);

//Returns true if input is integer 0, 1 or 2, otherwise false
bool user012InputOk(std::string inpStr);

//Returns true if input is integer 1, 2, 3 or 0, otherwise false
bool user0123InputOk(std::string inpStr);

//Returns true if input is integer 1, 2, 3 or 4, otherwise false
bool user1234InputOk(std::string inpStr); 

//Prints out information about logged in user. Return value equals next state
int showLoginPersInfo(int _emplId);

//Allows user to change information about the logged in user. Returns 0 if any input is invalid
int ChangePersInfo(int _emplId);

//Checks if a string is an integer
bool isInteger(const std::string& input);

//Check if a string is a valid integer
bool isNumber(const std::string& str);

//Finds ID related to name 
int IdName(std::string inpStr);

//Show available floors
int ShowAvailFloors(int _emplId);

//Checks if ID exists in User.csv. 
bool IDIsInFile(int id);

//Checks if ID exists in Admin.csv.
bool ValidateAdminID(std::string adminIdStr);

//Check if a string is a name in User.csv.
bool nameIsInFile(std::string inpName);

//Display access history for a floor
int ShowAccHistFloor(int floor);

//Change name or clearance level for a floor
int ChngFloorData(int floor);

//Delete user and corresponding card
void DeleteUserAndCard(int user);

//Create new user incl card. User must select valid ID and card number. Returns 0 if any input is invalid
int CreateNewUser();

//Check if password fulfills requirements
bool ValidatePassWd(std::string adminPasswd);

//Check that input password matches password (belonging to Admin-ID) in Admin.csv
bool CheckMatchPassWd(std::string adminPasswd, std::string adminIdStr);

//Validates if an email adress is correct
bool EmailValid(std::string email);

//Validates if phone number is correct
bool PhoneValid(std::string phone);

#endif
