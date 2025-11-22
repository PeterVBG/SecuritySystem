#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <numeric>
#include <bits/stdc++.h>
#include "seccardsystutils.h"
#include <regex>
#include <ctime>


enum ClLvlEnum {
    INTERNAL,
    RESTRICTED,
    SECRET
};

// Safely convert string to int with exception handling. Returns true if argument is an integer
bool tryConvertToInt(const std::string str) 
{
    int outValue;
    try 
    {
        outValue = std::stoi(str);
        return true;
    } 
    catch (const std::invalid_argument&) 
    {
        //std::cout << "Error: Invalid argument" << std::endl;
        return false;
    } 
    catch (const std::out_of_range&)
    {
        //std::cout << "Error: Number out of range for int" << std::endl;
        return false;
    }
}

//Returns true if input is integer 1, otherwise false
bool user1InputOk(std::string inpStr)
{
    bool test = tryConvertToInt(inpStr);   
    if (test)
    {
        //Integer
        int inp = std::stoi(inpStr);
        if (inp == 1) {return true;}
        else {return false;}
    } 
    else
    {
        //Input was not an integer
        return false;
    }
}

//Returns true if input is integer 1 or 2, otherwise false
bool user12InputOk(std::string inpStr)
{
    bool test = tryConvertToInt(inpStr);   
    if (test)
    {
        //Integer
        int inp = std::stoi(inpStr);
        if (inp == 1 || inp == 2) {return true;}
        else {return false;}
    } 
    else
    {
        //Input was not an integer
        return false;
    }
}

//Returns true if input is integer 1, 2 or 3, otherwise false
bool user123InputOk(std::string inpStr)
{
    bool test = tryConvertToInt(inpStr);   
    if (test)
    {
        //Integer
        int inp = std::stoi(inpStr);
        if (inp == 1 || inp == 2 || inp == 3) {return true;}
        else {return false;}
    } 
    else
    {
        //Input was not an integer
        return false;
    }
}

//Returns true if input is integer 0, 1 or 2, otherwise false
bool user012InputOk(std::string inpStr)
{
    bool test = tryConvertToInt(inpStr);   
    if (test)
    {
        //Integer
        int inp = std::stoi(inpStr);
        if (inp == 1 || inp == 2 || inp == 0) {return true;}
        else {return false;}
    } 
    else
    {
        //Input was not an integer
        return false;
    }
}

//Returns true if input is integer 1, 2, 3 or 0, otherwise false
bool user0123InputOk(std::string inpStr)
{
    bool test = tryConvertToInt(inpStr);   
    if (test)
    {
        //Integer
        int inp = std::stoi(inpStr);
        if (inp == 1 || inp == 2 || inp == 3 || inp == 0) {return true;}
        else {return false;}
    } 
    else
    {
        //Input was not an integer
        return false;
    }
}

//Returns true if input is integer 1, 2, 3 or 4, otherwise false
bool user1234InputOk(std::string inpStr) 
{
    bool test = tryConvertToInt(inpStr);   
    if (test)
    {
        //Integer
        int inp = std::stoi(inpStr);
        if (inp == 1 || inp == 2 || inp == 3 || inp == 4) {return true;}
        else {return false;}
    } 
    else
    {
        //Input was not an integer
        return false;
    }
}

//This function prints out information about the logged in user. Return value equals next state ( 0 = END, 1 = DISPLAYNORMALUSEROPTIONS)
int showLoginPersInfo(int _emplId)
{
    std::string line, iDStr, userName, userEmail, userPhNbr, userCardNbrStr, UserClLvl, showNormUserSelStr, cardNbrInFileStr;
    std::ifstream file("User.csv"); 
    bool found = false;   
    int commaLoc, iD, showNormUserSel, userCardNbr, cardNbrInFile;
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file, line); //First line contains headings
    while (found == false && std::getline(file, line))
    {
        //std::cout << line << std::endl;
        //std::getline(file, line); //Read next line from stream file and save in string line
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        line = line.substr(commaLoc + 1, line.length()); //removes ID from string line
        iD = stoi(iDStr); //Convert string --> int since _emplIdU is an int
        if (iD == _emplId)
        {
            commaLoc = line.find(',');
            userName = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userEmail = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userPhNbr = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userCardNbrStr = line.substr(0, commaLoc);

            found = true;
        }
    }
    file.close();

    //Read clearance level from Card.csv
    bool found1 = false;
    std::ifstream file1("Card.csv");
    if (!file1) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    userCardNbr = stoi(userCardNbrStr);
    std::getline(file1, line); //First line contains headings 
    while (!found1 && std::getline(file1, line))
    {
        //std::getline(file1, line);
        commaLoc = line.find(',');
        cardNbrInFileStr = line.substr(0, commaLoc);
        line = line.substr(commaLoc + 1, line.length());
        cardNbrInFile = stoi(cardNbrInFileStr);
        if (cardNbrInFile == userCardNbr)
        {
            commaLoc = line.find(',');
            UserClLvl = line.substr(commaLoc + 1, line.length());
            found1 = true;
        }
    }
    file1.close();

    std::cout << "User name: " << userName << std::endl;
    std::cout << "User email: " << userEmail << std::endl;
    std::cout << "User phone number: " << userPhNbr << std::endl;
    std::cout << "User card number: " << userCardNbr << std::endl;
    std::cout << "User clearance level: " << UserClLvl << std::endl;
    std::cout << std::endl;

    //Now personal info has been shown. Now ask the user if they like to go back

    std::cout << "Press 1 to go back" << std::endl;
    std::getline(std::cin, showNormUserSelStr);
    bool userInpOk = user1InputOk(showNormUserSelStr);
    if (!userInpOk) 
    {
        std::cout << "Incorrect input - Program terminated" << std::endl;
        return 0;
    }
    else
    {
        return 1;        
    }

}

//This function allows the user to change information about the logged in user. Returns 1 if input email and phone are valid (this makes the system go back to DISPLAYNORMALUSEROPTIONS. Otherwise it goes to state END)
int ChangePersInfo(int _emplId)
{
    std::string line, iDStr, userName, userEmail, userPhNbr, userCardNbr, UserClLvl, userId, newName, newEmail, newPhoneNbr;  
    int commaLoc, iD;
    std::cout << "Enter new first name" << std::endl;
    std::getline(std::cin, newName); 
    std::cout << "Enter new email adress in a valid format (name@mail.com)" << std::endl;
    std::getline(std::cin, newEmail); 
    bool eMailAns = EmailValid(newEmail);
    std::cout << "Enter new phone number in format +46712345678 or 0712345678: " << std::endl;
    std::getline(std::cin, newPhoneNbr);
    bool phoneAns = PhoneValid(newPhoneNbr);
    if (!eMailAns || !phoneAns || (newName == ""))
    {
        std::cout << "Not correct name / mail / phone - program terminates" << std::endl;
        return 0;
    }
    std::ifstream file("User.csv"); //Original data
    std::ofstream tempFile("Temp.csv"); //write data to this temporay file that in the end shall replace User.csv
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    if (!tempFile) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }

    std::getline(file, line); //First line contains headings
    tempFile << line << std::endl;

    while (std::getline(file, line))
    {
        //std::getline(file, line); //Detta görs inne i while-satsen
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        iD = stoi(iDStr); //Convert string --> int since _emplIdU is an int
        if (iD == _emplId)
        {
            //line = line.substr(commaLoc + 1, line.length()); //removes ID from string line

            commaLoc = line.find(',');
            userId = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userName = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userEmail = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userPhNbr = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userCardNbr = line.substr(0, commaLoc);

            line = userId + "," + newName + "," + newEmail + "," + newPhoneNbr + "," + userCardNbr; 
            tempFile << line << std::endl;
        }
        else
        {
            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    std::remove("User.csv");
    std::rename("Temp.csv", "User.csv");

    return 1;

}

//Function finds ID (int) related to name (string)
int IdName(std::string inpStr)
{
    std::string line, iDStr, name;
    std::ifstream file("User.csv"); 
    bool found = false;   
    int commaLoc, iD;
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file, line); //First line contains headings

    while (found == false && std::getline(file, line))
    {
        //std::getline(file, line); //Read next line from stream file and save in string line
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        line = line.substr(commaLoc + 1, line.length()); //removes ID from string line
        commaLoc = line.find(','); //Find location of second comma
        name = line.substr(0, commaLoc); //Extract name
        if (name == inpStr)
        {
            //std::cout << iDStr << std::endl;
            //Correct line found
            iD = stoi(iDStr); //Convert string --> int since _emplIdU is an int
            found = true;
        }
    }

    return iD;
}

//Show available floors for a specific user. Assumes ID as input (not name)
//1. Find users clearance level
//2. Find clearance level for each floor and compare with users clearance level
//3. Print out available floors
//Return value 1 = goto DISPLAYNORMALUSEROPTIONS. Return value 0 = goto END.
int ShowAvailFloors(int _emplId)
{
    std::string line, iDStr, userName, userEmail, userPhNbr, userCardNbrStr, clLvlUser, clLvlFloor, floorName, cardNbrInFileStr, UserSelStr;
    std::ifstream file("User.csv"); 
    bool found = false;   
    int commaLoc, iD, userCardNbr, cardNbrInFile, userSel;
    enum ClLvlEnum clLvlU, clLvlF;
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file, line); //First line contains headings
    while (found == false && std::getline(file, line))
    {
        //std::getline(file, line); //Read next line from stream file and save in string line
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        line = line.substr(commaLoc + 1, line.length()); //removes ID from string line
        iD = stoi(iDStr); //Convert string --> int since _emplIdU is an int
        if (iD == _emplId)
        {
            commaLoc = line.find(',');
            userName = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userEmail = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userPhNbr = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userCardNbrStr = line.substr(0, commaLoc);
            //line = line.substr(commaLoc + 1, line.length());
            //commaLoc = line.find(',');
            //clLvlUser = line.substr(0, commaLoc);
            //change to enum for easier comparison
            //if (clLvlUser == "SECRET"){clLvlU = SECRET;}
            //else if (clLvlUser == "RESTRICTED"){clLvlU = RESTRICTED;}
            //else {clLvlU = INTERNAL;} //lowest level in else statement, security
            found = true;
        }
    }
    file.close();

    //Vi vet nu användarens kortnummer (userCardNbrStr). Nu vill vi öppna Card.csv. Leta upp raden med userCardNbrStr, sen extrahera clearancelevel. Detta blir clLvlUser
    
    //userCardNbr = stoi(userCardNbrStr);
    bool found1 = false;
    std::ifstream file1("Card.csv");
    if (!file1) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file1, line); //First line contains headings 
    //std::cout << line << std::endl;
    //std::getline(file1, line); //Why do I need this line?
    //std::cout << line << std::endl;
    while (!found1 && std::getline(file1, line))
    {
        //std::cout << line << std::endl;
        //std::getline(file1, line);
        commaLoc = line.find(',');
        cardNbrInFileStr = line.substr(0, commaLoc);
        //std::cout << cardNbrInFileStr << std::endl;
        //std::cout << userCardNbrStr << std::endl;
        line = line.substr(commaLoc + 1, line.length());
        //cardNbrInFile = stoi(cardNbrInFileStr);
        if (cardNbrInFileStr == userCardNbrStr)
        {
            commaLoc = line.find(',');
            clLvlUser = line.substr(commaLoc + 1, line.length());
            found1 = true;
        }
    }
    file1.close();

    if (clLvlUser == "SECRET"){clLvlU = SECRET;}
    else if (clLvlUser == "RESTRICTED"){clLvlU = RESTRICTED;}
    else {clLvlU = INTERNAL;}
    //Now Clearance level for the user (clLvlUser) is found: clLvlU is INTERNAL, RESTRICTED or SECRET

    std::ifstream file2("Floor.csv");
    if (!file2) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file2, line); //First line contains headings

    //3 floors building. Hard coded.
    int availFloor[3] = {0, 0, 0};
    for (int i = 1; i < 4; i++)
    {
        std::getline(file2, line);
        commaLoc = line.find(','); //Find location of first comma
        line = line.substr(commaLoc + 1, line.length()); //removes Floor from string line   
        commaLoc = line.find(','); //Find location of first comma
        floorName = line.substr(0, commaLoc); //save floor name
        line = line.substr(commaLoc + 1, line.length()); //removes Name from string line  
        commaLoc = line.find(','); //Find location of first comma  
        clLvlFloor = line.substr(0, commaLoc);

        if (clLvlFloor == "SECRET"){clLvlF = SECRET;}
        else if (clLvlFloor == "RESTRICTED"){clLvlF = RESTRICTED;}
        else {clLvlF = INTERNAL;}

        if (clLvlU >= clLvlF)
        {
        std::cout << floorName << " is avaiblable" << std::endl;
        availFloor[i] = 1;
        } 
 
    }
    file2.close();

    //Här är egentligen hela funktionen "ShowAvailableFloors" klar. Användaren får nu valet att gå tillbaka till menyn NormalUserOptions eller att accessa en våning.

    //Available floors has been shown. Now ask the user for the next step
    //NEW 20251104 array availFloor[3] tex (0 0 1) visar vilka våningar som är tillgängliga
    //Ingen säkerhet utan litar på att användaren gör rätt. Antingen har hen access till en eller flera våningar eller inte till någon

    int n = sizeof(availFloor) / sizeof(availFloor[0]);
    int sum = std::accumulate(availFloor, availFloor + n, 0); // Using accumulate to find the sum

    //No floors are available
    if (sum == 0)
    {
        std::cout << "You don't have access to any floors, press 1 to go back" << std::endl;  
        std::getline(std::cin, UserSelStr); 
        bool inputOk = user1InputOk(UserSelStr);
        if (!inputOk)
        {
            std::cout << "Incorrect input - program terminated" << std::endl;
            return 0; //This equals goto state END            
        }
        else
        {
            return 1; //This equals goto state DISPLAYNORMALUSEROPTIONS 
        }
    }
    //Floors are available to access
    else
    {
        std::cout << "**************************" << std::endl;
        std::cout << "Press 1 to go back or 2 to enter a floor" << std::endl;
        std::getline(std::cin, UserSelStr);
        bool inputOk = user12InputOk(UserSelStr);
        //User input is not 1 or 2
        if (!inputOk) 
        {
            std::cout << "Incorrect input - program terminated" << std::endl;
            return 0; //This equals goto state END
            //currentState = END;
        }
        //User input ok, 1 or 2
        else
        {
            userSel = std::stoi(UserSelStr);
            //User wants to go back
            if (userSel == 1)
            {
                return 1;
            }
            //User wants to access a floor
            else if (userSel == 2)
            {
                std::ofstream file3("FloorAccessHistory.csv", std::ios::app);
                std::string inp, inpX;
                int inpInt;
                std::cout << "Type the number (1, 2 or 3) on the floor you like to enter or 0 to exit" << std::endl;
                //SÄKERTHET - INGEN CHECK PÅ ATT MAN BARA KAN GÅ IN I VÅNINGAR MAN HAR ACCESS TILL
                if (!file3) 
                {
                    std::cout << "Error opening file - program terminated" << std::endl;
                    exit(0); // Ends the program immediately
                }
                std::getline(std::cin, inp);
                bool inputOk = user0123InputOk(inp); //Input was 0, 1, 2 or 3
                if (inputOk)
                {
                    inpInt = stoi(inp);
                    //time_t timestamp;
                    time_t timestamp = time(NULL);
                    if (inpInt == 1)
                    {
                        //Access floor 1
                        line = userName + ",,," + ctime(&timestamp);
                        file3 << line << std::endl; 
                        std::cout << "You entered floor 1. Press any key to go back" << std::endl;
                        std::getline(std::cin, inpX);
                        return 1;
                    }
                    else if (inpInt == 2)
                    {
                        //Access floor 2
                        line = "," + userName + ",," + ctime(&timestamp);
                        file3 << line << std::endl;
                        std::cout << "You entered floor 2. Press any key to go back" << std::endl;
                        std::getline(std::cin, inpX);
                        return 1;
                    }
                    else if (inpInt == 3)
                    {
                        //Access floor 3
                        line = ",," + userName + "," + ctime(&timestamp);
                        file3 << line << std::endl; 
                        std::cout << "You entered floor 3. Press any key to go back" << std::endl;
                        std::getline(std::cin, inpX);
                        return 1;
                    }
                    //User wants to go back
                    else if (inpInt == 0)
                    {
                        return 1;
                    }
                }
                //input was incorrect
                else
                {
                    return 0;
                }
                
                file3.close();
            }
        }   
    }
  
}

//Check if an integer is an ID in User.csv. 
bool IDIsInFile(int id)
{
    //return true if id is an ID in User.csv
    std::string line, iDStr;
    std::ifstream file("User.csv"); 
    bool found = false;   
    int commaLoc, iDFile;
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file, line); //First line contains headings
    while (found == false && std::getline(file, line))
    {
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        iDFile = stoi(iDStr);
        if (id == iDFile)
        {
            found = true;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

//Check if an integer is a card number in Card.csv. Returns true if cardNbr exists in Card.csv
bool CardNbrIsInFile(int _cardNbr)
{
    std::string line, cardNbrStr;
    std::ifstream file("Card.csv"); 
    bool found = false;   
    int commaLoc, cardNbr;
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file, line); //First line contains headings
    while (found == false && std::getline(file, line))
    {
        commaLoc = line.find(','); //Find location of first comma
        cardNbrStr = line.substr(0, commaLoc); //cardNbrStr is string
        cardNbr = stoi(cardNbrStr);
        if (_cardNbr == cardNbr)
        {
            found = true;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

//Check if a string is a name in User.csv.
bool nameIsInFile(std::string inpName)
{
    //return true if name is a name in User.csv
    std::string line, iDStr, name;
    std::ifstream file("User.csv"); 
    bool found = false;   
    int commaLoc;
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file, line); //First line contains headings

    while (found == false && std::getline(file, line))
    {
        //std::getline(file, line); //Read next line from stream file and save in string line
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        line = line.substr(commaLoc + 1, line.length()); //removes ID from string line
        commaLoc = line.find(','); //Find location of second comma
        name = line.substr(0, commaLoc); //Extract name
        if (name == inpName)
        {
            //std::cout << "Your ID is: " << iDStr << std::endl;
            //Correct line found
            //iD = stoi(iDStr); //Convert string --> int since _emplIdU is an int
            found = true;
        }
    }
    return found;
}

//Display access history for a floor on the screen
int ShowAccHistFloor(int floor)
{
    std::string line, name, time;
    int commaLoc;
    std::ifstream file("FloorAccessHistory.csv");
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    std::getline(file, line); //Heading
    std::cout << "Access history for floor " << floor << " is:" << std::endl;
    if (floor == 1)
    {
        while (std::getline(file, line))
        {
            commaLoc = line.find(','); //Find location of first comma
            name = line.substr(0, commaLoc); //name is string
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(','); //Find location of second comma
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(','); //Find location of third comma
            time = line.substr(commaLoc + 1, line.length());
            if (name != "")
            {
                std::cout << name << std::endl;
                std::cout << time << std::endl;
            }
        }
    }
    else if (floor == 2)
    {
        while (std::getline(file, line))
        {
            commaLoc = line.find(','); //Find location of first comma
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(','); //Find location of second comma
            name = line.substr(0, commaLoc); //name is string
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(','); //Find location of third comma
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(','); //Find location of third comma
            time = line.substr(0, commaLoc); //
            if (name != "")
            {
                std::cout << name << std::endl;
                std::cout << time << std::endl;
            }
        }    
    }
    else if (floor == 3)
    {
        while (std::getline(file, line))
        {
            commaLoc = line.find(','); //Find location of first comma
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(','); //Find location of first comma
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(','); //Find location of second comma
            name = line.substr(0, commaLoc); //name is string
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(','); //Find location of third comma
            time = line.substr(commaLoc + 1, line.length());
            if (name != "")
            {
                std::cout << name << std::endl;
                std::cout << time << std::endl;
            }
        }    
    }        

    file.close();

    //std::cout << "Press any key to go back" << std::endl;
    return 1; //going back to display admin options

}

//Change floor data: name or clearance level. Returns 1 if operation succeded, 0 otherwise
int ChngFloorData(int floor)
{
    int chngSel, state, commaLoc;
    std::string chngSelStr, newName, floorName, clLvl, line, lineX, newclLvl, name;
    std::fstream file("Floor.csv"); //Original data
    std::ofstream tempFile("Temp1.csv"); //write data to this temporay file that in the end shall replace Floor.csv
    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    if (!tempFile) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }    

    std::getline(file, line); //First line contains headings
    tempFile << line << std::endl;

    std::cout << "Press 1 to change name and 2 to change clearance level" << std::endl;
    std::getline(std::cin, chngSelStr);
    bool inpOk = user12InputOk(chngSelStr);
    if (inpOk)
    {
        chngSel = std::stoi(chngSelStr); //String to integer
        if (chngSel == 1) //change name
        {   
            std::cout << "Type new floor name" << std::endl;
            //control of input, cannot be blank
            std::getline(std::cin, newName);
            if (newName == "")
            {
                //Input not correct
                return 0;
            }
            else
            {
                if (floor == 1)
                {
                    std::getline(file, line); //Floor1
                    commaLoc = line.find(','); //Find location of first comma
                    line = line.substr(commaLoc + 1, line.length());
                    commaLoc = line.find(','); //Find location of second comma
                    line = line.substr(commaLoc + 1, line.length());
                    commaLoc = line.find(','); //Find location of third comma
                    clLvl = line.substr(0, commaLoc); //clLvl is string
                    lineX = "1," + newName + "," + clLvl;
                    tempFile << lineX << std::endl;
                    std::getline(file, line); //Floor2
                    tempFile << line << std::endl;
                    std::getline(file, line); //Floor3
                    tempFile << line << std::endl;
                }
                else if (floor == 2)
                {
                    std::getline(file, line); //Floor1
                    tempFile << line << std::endl;
                    std::getline(file, line); //Floor 2
                    commaLoc = line.find(','); //Find location of first comma
                    line = line.substr(commaLoc + 1, line.length());
                    commaLoc = line.find(','); //Find location of second comma
                    line = line.substr(commaLoc + 1, line.length());
                    commaLoc = line.find(','); //Find location of third comma
                    clLvl = line.substr(0, commaLoc); //clLvl is string
                    lineX = "2," + newName + "," + clLvl;
                    tempFile << lineX << std::endl;
                    std::getline(file, line);
                    tempFile << line << std::endl;
                }
                else if (floor == 3)
                {
                    std::getline(file, line); //Floor1
                    tempFile << line << std::endl;
                    std::getline(file, line); //Floor2
                    tempFile << line << std::endl;
                    std::getline(file, line); //Floor 3
                    commaLoc = line.find(','); //Find location of first comma
                    line = line.substr(commaLoc + 1, line.length());
                    commaLoc = line.find(','); //Find location of second comma
                    line = line.substr(commaLoc + 1, line.length());
                    commaLoc = line.find(','); //Find location of third comma
                    clLvl = line.substr(0, commaLoc); //clLvl is string
                    lineX = "3," + newName + "," + clLvl;
                    tempFile << lineX << std::endl;
                }
            }           
        }
        else if (chngSel == 2) //Change clearance level
        {
            std::cout << "Type new clearance level INTERNAL, RESTRICTED or SECRET" << std::endl;
            //control of input
            std::getline(std::cin, newclLvl);
            if (!(newclLvl == "SECRET" || newclLvl == "RESTRICTED" || newclLvl == "INTERNAL"))
            {
                //Input not correct
                return 0;
            }
            else
            {
            if (floor == 1)
            {
                std::getline(file, line); //Floor1
                commaLoc = line.find(','); //Find location of first comma
                line = line.substr(commaLoc + 1, line.length());
                commaLoc = line.find(','); //Find location of second comma
                name = line.substr(0, commaLoc); 
                lineX = "1," + name + "," + newclLvl;
                tempFile << lineX << std::endl;
                std::getline(file, line); //Floor2
                tempFile << line << std::endl;
                std::getline(file, line); //Floor3
                tempFile << line << std::endl;            
            }
            else if (floor == 2)
            {
                std::getline(file, line); //Floor1
                tempFile << line << std::endl;
                std::getline(file, line); //Floor 2
                commaLoc = line.find(','); //Find location of first comma
                line = line.substr(commaLoc + 1, line.length());
                commaLoc = line.find(','); //Find location of second comma
                name = line.substr(0, commaLoc);  
                lineX = "2," + name + "," + newclLvl;
                tempFile << lineX << std::endl;
                std::getline(file, line);
                tempFile << line << std::endl;
            }
            else if (floor == 3)
            {
                std::getline(file, line); //Floor1
                tempFile << line << std::endl;
                std::getline(file, line); //Floor2
                tempFile << line << std::endl;
                std::getline(file, line); //Floor 3
                commaLoc = line.find(','); //Find location of first comma
                line = line.substr(commaLoc + 1, line.length());
                commaLoc = line.find(','); //Find location of second comma
                name = line.substr(0, commaLoc); 
                lineX = "3," + name + "," + newclLvl;
                tempFile << lineX << std::endl;
            }
            }
        }

        file.close();
        tempFile.close();

        std::remove("Floor.csv");
        std::rename("Temp1.csv", "Floor.csv");

    }
    //Input not correct
    else
    {
        return 0;
    }

    return 1;

}

//Delete user and corresponding card
void DeleteUserAndCard(int user)
{
    std::string line, iDStr, userName, userEmail, userPhNbr, userCardNbrStr, cardNbrInFileStr;
    std::ifstream file("User.csv"); 
    std::ifstream file1("Card.csv");
    std::ofstream tempFile("Temp2.csv"); //write data to this temporay file that in the end shall replace User.csv
    bool found = false;   
    int commaLoc, iD;

    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    if (!file1) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    if (!tempFile) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }

    std::getline(file, line); //First line contains headings
    while (found == false && std::getline(file, line))
    {
        //std::getline(file, line); //Read next line from stream file and save in string line
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        line = line.substr(commaLoc + 1, line.length()); //removes ID from string line
        iD = stoi(iDStr); //Convert string --> int 
        if (iD == user)
        {
            commaLoc = line.find(',');
            userName = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userEmail = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userPhNbr = line.substr(0, commaLoc);
            line = line.substr(commaLoc + 1, line.length());

            commaLoc = line.find(',');
            userCardNbrStr = line.substr(0, commaLoc); //Now we know user card number

            found = true;
        }
    }
    file.close();

    //Read clearance level from Card.csv
    while (std::getline(file1, line))
    {
        commaLoc = line.find(',');
        cardNbrInFileStr = line.substr(0, commaLoc);
        if (cardNbrInFileStr == userCardNbrStr)
        {
            //ska inte med
        }
        else
        {
            //kopieras
            tempFile << line << std::endl;
        }
    }

    file1.close();
    tempFile.close();

    std::remove("Card.csv");
    std::rename("Temp2.csv", "Card.csv");

    //Now Card.csv is updated
    
    std::ifstream file3("User.csv");
    std::ofstream tempFile3("Temp3.csv");
    std::string ID;

    if (!file3) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }
    if (!tempFile3) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }

    tempFile3 << "Id,Name,Email,Phone number,Card number" << std::endl; //write heading
    std::getline(file3, line); //heading
    while (std::getline(file3, line))
    {
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        iD = stoi(iDStr); //Convert string --> int since _emplIdU is an int        
        if (iD == user)
        {
            //ska inte med
        }
        else
        {
            //kopieras
            tempFile3 << line << std::endl;
        }
    }

    file3.close();
    tempFile3.close();

    std::remove("User.csv");
    std::rename("Temp3.csv", "User.csv");

}

//Create new user incl card. User must select valid ID and card number. Returns 0 if program shall terminate
int CreateNewUser()
{
    std::string newUserIdStr, newUserNameStr, newUserEmailStr, newUserPhNbrStr, newUserCardNbrStr, newUserClLvlStr, lineNewUser, lineNewCard;
    bool carNbrUnique, userIdNotUnique, userCardNbrNotUnique;

    std::cout << "Type new user ID: " << std::endl;
    std::getline(std::cin, newUserIdStr);
    std::cout << "Type new user name: " << std::endl;
    std::getline(std::cin, newUserNameStr);
    std::cout << "Type new user email: " << std::endl;
    std::getline(std::cin, newUserEmailStr);
    bool eMailAns = EmailValid(newUserEmailStr);
    std::cout << "Type new phone number in format: +46712345678 or 0712345678:" << std::endl;
    std::getline(std::cin, newUserPhNbrStr);
    bool phoneAns = PhoneValid(newUserPhNbrStr);
    std::cout << "Type new user card number: " << std::endl;
    std::getline(std::cin, newUserCardNbrStr);
    std::cout << "Type new user clearance level: " << std::endl;
    std::getline(std::cin, newUserClLvlStr);
    /*
    User ID must be unique
    Name != "". 
    Valid email and phone number
    Card number must be unique
    Clearance level must be "INTERNAL" || "RESTRICTED" || "SECRET"
    */

    //Checks if user entered ID exists in User.csv
    if (tryConvertToInt(newUserIdStr))
    {
        //Is an integer
        int userId = stoi(newUserIdStr);
        userIdNotUnique = IDIsInFile(userId); //userIdUnique is true if entered ID already exist, e.g false means "ok"
    }
    else
    {
        //Not an integer
        return 0;
    }

    //Checks if user entered card number exists in Card.csv
    if (tryConvertToInt(newUserCardNbrStr))
    {
        //Is an integer
        int userCardNbr = stoi(newUserCardNbrStr);
        userCardNbrNotUnique = CardNbrIsInFile(userCardNbr); //userCardNbrUnique is true if entered card number already exist
    }
    else
    {
        //Not an integer
        return 0;
    }

    if (!eMailAns || !phoneAns || newUserNameStr == "" || userIdNotUnique || userCardNbrNotUnique || !(newUserClLvlStr == "RESTRICTED" || newUserClLvlStr == "INTERNAL" || newUserClLvlStr == "SECRET")) 
    {
        std::cout << "Incorrect input - program terminates" << std::endl;
        return 0;
    }
    else
    {
        std::ofstream file("User.csv", std::ios::app);
        std::ofstream file1("Card.csv", std::ios::app);

        if (!file) 
        {
            std::cout << "Error opening file - program terminated" << std::endl;
            exit(0); // Ends the program immediately
        }
        if (!file1) 
        {
            std::cout << "Error opening file - program terminated" << std::endl;
            exit(0); // Ends the program immediately
        }

        lineNewUser = newUserIdStr + "," + newUserNameStr + "," + newUserEmailStr + "," + newUserPhNbrStr + "," + newUserCardNbrStr;
        file << lineNewUser << std::endl;
        lineNewCard = newUserCardNbrStr + "," + newUserClLvlStr;
        file1 << lineNewCard << std::endl;

        file.close();
        file1.close();

        return 1;
    }
}

//Checks that the entered ID exists in Admin.csv. Very similar to IDIsInFile(). Should be 1 common function!
bool ValidateAdminID(std::string adminIdStr)
{
    //return true if id is an ID in Admin.csv
    std::string line, iDStr, name;
    std::ifstream file("Admin.csv"); 
    bool found = false;   
    int commaLoc, iDFile, id;

    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }

    std::getline(file, line); //First line contains headings
    while (found == false && std::getline(file, line))
    {
        //std::getline(file, line); //Read next line from stream file and save in string line
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        //iDFile = stoi(iDStr);

        //id = stoi(adminIdStr); //

        if (iDStr == adminIdStr)
        {
            found = true;
        }
    }
    return found;
}

//Checks if the entered password fulfills all requirements
bool ValidatePassWd(std::string adminPasswd)
{
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    if (adminPasswd.length() < 8)
    {
        return false;
    } 

    //This is a foreach-loop, for each character in the "array" adminPasswd
    for (char cha : adminPasswd)
    {
        if (isupper(cha))
        {
            hasUpper = true;
        }
        else if (islower(cha))
        {
            hasLower = true;
        }
        else if (isdigit(cha))
        {
            hasDigit = true;
        }
        else if (!isalnum(cha))
        {
            hasSpecial = true;
        }
        if (hasUpper && hasLower && hasDigit && hasSpecial) //ok before looing through the array
        {
            break;
        }
    }

    return (hasUpper && hasLower && hasDigit && hasSpecial);

}

//Checks that input password matches password (belonging to Admin-ID) in Admin.csv
bool CheckMatchPassWd(std::string adminPasswd, std::string adminIdStr)
{
    std::string line, iDStr, name, passWdinFile;
    bool found = false; 
    bool match = false;  
    int commaLoc, iD;

    std::ifstream file("Admin.csv"); //Original data

    if (!file) 
    {
        std::cout << "Error opening file - program terminated" << std::endl;
        exit(0); // Ends the program immediately
    }

    //Leta upp ID i filen
    std::getline(file, line); //First line contains headings
    while (found == false && std::getline(file, line))
    {
        //std::getline(file, line); //Read next line from stream file and save in string line
        commaLoc = line.find(','); //Find location of first comma
        iDStr = line.substr(0, commaLoc); //iDStr is string
        if (iDStr == adminIdStr)
        {
            line = line.substr(commaLoc + 1, line.length());
            commaLoc = line.find(',');
            passWdinFile = line.substr(0, commaLoc);
            if (passWdinFile == adminPasswd)
            {
                match = true;
            }
            found = true;
        }
    }
    
    return match;

}

//Validates if an email adress is correct. Checks for an @ before the dot, text after @ and before dot, dot and text afterwards 
bool EmailValid(std::string email)
{
    //Loop through string to find position of . and @
    int aT = -1; 
    int dot = -1;
    for (int i = 0; i < email.length(); i++) 
    {
        if (email[i] == '@') 
        {
            aT = i;
        }
        else if (email[i] == '.') 
        {
            dot = i;
        }
    }

    //@ or dot not present, or dot before @
    if ((aT == -1 || dot == -1) || (aT > dot))
    {
        return 0;
    }

    //dot is the last sign - not correct 
    return !(dot >= (email.length() - 1));    
}

//Validates if phone number is correct
bool PhoneValid(std::string phone)
{
    // Regex for format: +countrycode-area-local
    //std::regex pattern(R"(^\+\d{2}\d{9}$)"); //+46123456789
    std::regex pattern(R"(^\+467\d{8}$)"); //+46722079281
    std::regex pattern2(R"(^07\d{8}$)"); //0722079281
    if (std::regex_match(phone, pattern) || std::regex_match(phone, pattern2)) 
    {
        return true;
    } 
    else 
    {
        return false;
    }
}
