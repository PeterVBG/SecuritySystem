#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <numeric>
#include "seccardsystutils.h"


//States in the state machine
enum SysSt {
  START,
  NORMALUSERLOGIN,
  ADMINLOGIN,
  DISPLAYNORMALUSEROPTIONS,
  DISPLAYADMINOPTIONS,
  LISTAVAILFLOORS,
  SHOWNORMALUSERINFO,
  CHANGENORMALUSERINFO,
  LISTALLFLOORS,
  LISTALLUSERS,
  CREATERNEWUSER,
  END
};

//State machine. Idea; we ARE in a state, checking if a transition to another state shall occure
SysSt CheckState(SysSt currentState)
{
    int userSel, emplId;
    bool userInpOk;
    std::string userSelStr, userInputStr, adminPasswd;

    /*Start of state meachine. A person can select to login as a normal user or an admin.
    Transitions to: NORMALUSERLOGIN, ADMINLOGIN or END*/
    if (currentState == START)
    {
        std::cout << "Press 1 for normal user, 2 for admin and 0 to exit" << std::endl;
        std::getline(std::cin, userSelStr); //Read a string
        bool inputOk = user012InputOk(userSelStr);
        //User input is not 0, 1 or 2
        if (!inputOk) 
        {
            std::cout << "Incorrect input - program terminated" << std::endl;
            currentState = END;
            return currentState; //Terminate program due to incorrect input
        }
        //User input ok
        else
        {
            userSel = std::stoi(userSelStr);
            if (userSel == 0)
            {
                currentState = END;
            }
            else if (userSel == 1)
            {
                currentState = NORMALUSERLOGIN;
            }
            else if (userSel == 2)
            {
                currentState = ADMINLOGIN;
            }
        }
    }

    /*Normal user login with ID or name. 
    Transitions to: DISPLAYNORMALUSEROPTIONS or END*/
    else if (currentState == NORMALUSERLOGIN)
    {
        bool idValid, nameValid;

        std::cout << "User login:" << std::endl;
        std::cout << "**************************" << std::endl;
        std::cout << "Enter your name or ID (as it's written in User.csv)" << std::endl;
        std::getline(std::cin, userInputStr);
        
        //Check if user input was an ID or a name
        if (tryConvertToInt(userInputStr)) //It was an integer
        {
            emplId = std::stoi(userInputStr); //String to int
            idValid = IDIsInFile(emplId); //Check that the user input integer is an ID in User.csv
            if (!idValid)
            {
                std::cout << "Input is not a valid ID. Program terminated" << std::endl;
                currentState = END;
                return currentState; //Terminate program due to incorrect input
            }
            else
            {
                currentState = DISPLAYNORMALUSEROPTIONS;    
            }
        } 
        else //It was a string 
        {
            nameValid = nameIsInFile(userInputStr); //Check that the user input string is a name in User.csv
            if (!nameValid)
            {
                std::cout << "Not an employee name. Program terminated" << std::endl;
                currentState = END;
                return currentState; //Terminate program due to incorrect input
            }
            else
            {
                emplId = IdName(userInputStr); //Get ID matching to name
                currentState = DISPLAYNORMALUSEROPTIONS;
            }
        }   
    }

    /*Admin login requires an ID and a password. Checks that password is correct and fulfills requirements.
    Transitions to: DISPLAYADMINOPTIONS or END*/
    else if (currentState == ADMINLOGIN)
    {
        std::string adminIdStr, adminPasswd;
        bool iDOk, passWdOk, match;

        std::cout << "Admin login:" << std::endl;
        std::cout << "**************************" << std::endl;
        std::cout << "Enter your admin ID" << std::endl;
        std::getline(std::cin, adminIdStr);
        std::cout << "Enter your password" << std::endl;
        std::getline(std::cin, adminPasswd);  

        iDOk = ValidateAdminID(adminIdStr);     
        passWdOk = ValidatePassWd(adminPasswd);
        match = CheckMatchPassWd(adminPasswd, adminIdStr);

        //If ID input doesn't exist, or password does not fulfill req or password is not the correct one 
        if (!match || !passWdOk || !iDOk) 
        {
            std::cout << "Not correct ID and / or password - program terminated" << std::endl;
            currentState = END; 
            return currentState; //Terminate program due to incorrect input
        } 
        else 
        {
            currentState = DISPLAYADMINOPTIONS;
        }

    }

    /*Normal users first level of choices after logging in with ID or name.
    1. List available floors
    2. Show personal information
    3. Change personal information
    4. Log out
    Transitions to: LISTAVAILFLOORS, SHOWNORMALUSERINFO, CHANGENORMALUSERINFO, START, END*/
    else if (currentState == DISPLAYNORMALUSEROPTIONS)
    {
        int dispNormUserSel;
        std::string dispNormUserSelStr; 

        std::cout << "User options. Select one of the following:" << std::endl;
        std::cout << "**************************" << std::endl;
        std::cout << "1 - List all available floors" << std::endl;
        std::cout << "2 - Show your personal information" << std::endl;
        std::cout << "3 - Change your personal information" << std::endl;
        std::cout << "4 - Log out" << std::endl;

        std::getline(std::cin, dispNormUserSelStr);
        bool inputOk = user1234InputOk(dispNormUserSelStr);
        //User input is not 1, 2, 3 or 4
        if (!inputOk) 
        {
            std::cout << "Incorrect input - program terminated" << std::endl;
            currentState = END;
            return currentState; //Terminate program due to incorrect input
        }
        //User input ok
        else
        {
            int dispNormUserSel = std::stoi(dispNormUserSelStr);
            if (dispNormUserSel == 1)
            {
                currentState = LISTAVAILFLOORS;   
            }
            else if (dispNormUserSel == 2)
            {
                currentState = SHOWNORMALUSERINFO;
            }
            else if (dispNormUserSel == 3)
            {
                currentState = CHANGENORMALUSERINFO;
            }
            else if (dispNormUserSel == 4)
            {
                currentState = START;
            }
        }  
    }

    /*Admins first level of choices after logging in with ID and password.
    1. List all floors
    2. List all users
    3. Create new user
    4. Log out
    Transitions to: LISTALLFLOORS, LISTALLUSERS, CREATERNEWUSER, START, END*/
    else if (currentState == DISPLAYADMINOPTIONS)
    {
        int dispAdminSel;
        std::string dispAdminSelStr; 

        std::cout << "Admin options. Select one of the following:" << std::endl;
        std::cout << "**************************" << std::endl;
        std::cout << "1 - List all floors" << std::endl;
        std::cout << "2 - List all users" << std::endl;
        std::cout << "3 - Create new user" << std::endl;
        std::cout << "4 - Log out" << std::endl;

        std::getline(std::cin, dispAdminSelStr);
        bool inpOk = user1234InputOk(dispAdminSelStr);
        if (inpOk)
        {
            dispAdminSel = std::stoi(dispAdminSelStr); //String to integer
            if (dispAdminSel == 1)
            {
                currentState = LISTALLFLOORS;   
            }
            else if (dispAdminSel == 2)
            {
                currentState = LISTALLUSERS;
            }
            else if (dispAdminSel == 3)
            {
                currentState = CREATERNEWUSER;
            }
            else if (dispAdminSel == 4)
            {
                currentState = START;
            }
        }
        else
        {
            std::cout << "Incorrect input. Program terminated" << std::endl;
            currentState = END;
            return currentState; //Terminate program due to incorrect input
        }

    }

    /*A normal user can show available floors (based on clearance lever user / floor)
    Transitions to: DISPLAYNORMALUSEROPTIONS*/
    else if (currentState == LISTAVAILFLOORS)
    {
        int goBack; 

        goBack = ShowAvailFloors(emplId); //Funktionen skriver ut tillgängliga våningar samt "Press 0 to go back"
        if (goBack == 1)
        {
            currentState = DISPLAYNORMALUSEROPTIONS; 
        }
        else
        {
            std::cout << "Incorrect input - program terminated" << std::endl; 
            currentState = END; //This will never take place...
            return currentState; //Terminate program due to incorrect input
        }

    }

    /*A normal user can show personal information
    Transitions to: DISPLAYNORMALUSEROPTIONS*/
    else if (currentState == SHOWNORMALUSERINFO)
    {
        int goBack;
        goBack = showLoginPersInfo(emplId);
        if (goBack == 1)
        {
            currentState = DISPLAYNORMALUSEROPTIONS; 
        }
        else
        {
            currentState = END;
            return currentState; //Terminate program due to incorrect input
        }
    }

    /*A normal user can change his personal information
    Transitions to: DISPLAYNORMALUSEROPTIONS*/
    else if (currentState == CHANGENORMALUSERINFO)
    {
        //emplId is known
        //Användaren ska kunna ändra Namn, mail och telefon för sig själv. När detta är gjort ska man automatiskt gå till DISPLAYNORMALUSEROPTIONS
        int ansChangePers = ChangePersInfo(emplId);
                if (ansChangePers == 0)
                {
                    std::cout << "Incorrect input - program terminated" << std::endl;
                    currentState = END;
                    return currentState; //Terminate program due to incorrect input
                }
                else
                {
                    currentState = DISPLAYNORMALUSEROPTIONS;
                }
    }

    /*Admin can list all floors. Possible to select a specific floor and modify floor information or show access history for the floor. 
    Transitions to: DISPLAYADMINOPTIONS*/
    else if (currentState == LISTALLFLOORS)
    {
        int floorSel, floorSel2, state, input;
        bool inpCorr;
        std::string floorSelStr, floorSelStr2;

        std::cout << "Press number to select floor 1, 2 or 3" << std::endl;
        std::getline(std::cin, floorSelStr);
        bool inpOk = user123InputOk(floorSelStr);
        if (inpOk)
        {
            floorSel = std::stoi(floorSelStr); //Selected floor
        }
        else
        {
            std::cout << "Incorrect input - program terminated" << std::endl;
            currentState = END;
            return currentState; //Terminate program due to incorrect input
        }

        std::cout << "Press 1 to show access history or 2 to change floor information" << std::endl;
        std::getline(std::cin, floorSelStr2);
        inpOk = user12InputOk(floorSelStr2);
        //Input was correct
        if (inpOk)
        {
            floorSel2 = std::stoi(floorSelStr2); //String to integer
            if (floorSel2 == 1) //Access history
            {   
                state = ShowAccHistFloor(floorSel);
                if (state == 1) 
                {
                    currentState = DISPLAYADMINOPTIONS;
                }
                //Will never occure
                else 
                {
                    currentState = END;
                    return currentState; //Terminate program due to incorrect input
                }
            }
            else if (floorSel2 == 2) //Change floor info
            {
                state = ChngFloorData(floorSel);
                if (state == 1) 
                {
                    currentState = DISPLAYADMINOPTIONS;
                }
                else 
                {
                    currentState = END;
                    return currentState; //Terminate program due to incorrect input
                }
            }
        }
        else
        {
            std::cout << "Incorrect input - program terminated" << std::endl;
            currentState = END;
            return currentState; //Terminate program due to incorrect input
        }
     
    }

    /*Admin can list all users. Possible to select a specific user and modify user information or delete the user
    Transitions to: DISPLAYNORMALUSEROPTIONS*/
    else if (currentState == LISTALLUSERS)
    {
        int userID, userSel;
        std::string line, userIdStr, userSelStr;
        std::ifstream file("User.csv");

        if (!file) 
        {
            std::cout << "Error opening file - program terminated" << std::endl;
            exit(0); // Ends the program immediately
        }

        while (std::getline(file, line))
        {
            std::cout << line << std::endl; //heading
        }

        file.close();

        //UserID cannot be zero.
        std::cout << "\n";
        std::cout << "Press 0 to go back or User ID to change/delete the user" << std::endl;
        std::getline(std::cin, userIdStr);
        bool inpOk = tryConvertToInt(userIdStr);
        if (!inpOk)
        {
            std::cout << "Incorrect input - program terminated" << std::endl;
            currentState = END;
            return currentState; //Terminate program due to incorrect input            
        }
        //User input is an integer
        else
        { 
            userID = std::stoi(userIdStr);
            //Här vill jag kolla att userID faktiskt är en användare. Annars avsluta programmet
            bool validUserId = IDIsInFile(userID);
            if (!validUserId)
            {
                std::cout << "Input is not a valid ID" << std::endl;
                currentState = DISPLAYADMINOPTIONS;
                return currentState;
            }
            else
            {
                std::cout << "Press 1 change user information or 2 to delete user" << std::endl;
                std::getline(std::cin, userSelStr);
                bool inp2Ok = user12InputOk(userSelStr);
                if (!inp2Ok)
                {
                    std::cout << "Incorrect input" << std::endl;
                    currentState = END;
                    return currentState; //Terminate program due to incorrect input                    
                }
                else
                {
                    userSel = std::stoi(userSelStr);
                    if (userSel == 1) //Change
                    {
                        int ansChangePers = ChangePersInfo(userID);
                        if (ansChangePers == 0)
                        {
                            currentState = END;
                            return currentState; //Terminate program due to incorrect input
                        }
                        else
                        {
                            currentState = DISPLAYADMINOPTIONS;
                        }
                    }      
                    else if (userSel == 2) //Delete - user + card
                    {
                        DeleteUserAndCard(userID);
                        currentState = DISPLAYADMINOPTIONS;
                    }
                }
            }
        }
    }

    /*Admin can create a new user (including a new card)
    Transitions to: DISPLAYNORMALUSEROPTIONS*/
    else if (currentState == CREATERNEWUSER)
    {
        int ansCreateNewUser = CreateNewUser(); 
        if (ansCreateNewUser == 0) //Not correct input when new user is created
        {
            std::cout << "Incorrect input - program terminated" << std::endl;
            currentState = END;
            return currentState; //Terminate program due to incorrect input
        }
        else
        {
            currentState = DISPLAYADMINOPTIONS;
        }
    }
    
    return currentState;

}

int main()
{
    SysSt currState = START; //Begin execution in state START
    while (currState != END)
    {
        currState = CheckState(currState);       
    }

  return 0;

}


