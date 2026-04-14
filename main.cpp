// P=NP Maze Challenge - Two Truths & a Lie
// Team members: Guild 1
// Description: a two truths and a lie maze game with a main menu, leaderboard,
// a lava rising mechanic, and a scoring system

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Constants for the game
const int ROWS = 19; //vertical
const int COLS = 21; //horizontal
const int TOTAL_CHECKPOINTS = 9;
const int MAX_MOVES = 300; //the player only gets this many moves before the lava gets them
const int MAX_LEADERBOARD = 5; //we only keep the top 5 scores

/*
This is the maze setup
all of the #'s are walls
a "." means an open floor space
S marks the spot of the starting point
to edit the checkpoints, edit them below this code
The exit is hardcoded at row 17, col 19
*/
char maze[ROWS][COLS] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','S','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','#','#','#','.','#','.','#','#','#','#','#','.','#','#','#','.','#'},
    {'#','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','.','#','.','#','.','#','.','#','.','#','#','#','.','#','.','#','.','#'},
    {'#','.','.','.',  '#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','#','.','#','#','#','.','#','.','#','.','#','#','#','#','#','.','#'},
    {'#','.','#','.','.','.','.','#','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','.','#','#','#','.','#','#','#','.','#','#','#','#','#','#','#','.','#'},
    {'#','.','.','.',  '#','.','.','.','.','.','.','.','.','.','.','.','.','#','.','.','#'},
    {'#','.','#','#','#','.','#','#','#','#','#','#','#','#','#','.','#','.','#','#','#'},
    {'#','.','#','.','.','.','.','#','.','.','.','.','.','.','.','.','.','.','.','.',  '#'},
    {'#','.','#','.','#','#','#','.','#','#','#','#','#','#','#','#','#','.','#','.','#'},
    {'#','.','#','.','.','.','.','.',  '#','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','#','#','#','.','#','.','#','.','#','#','#','#','#','#','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',  '#'},
    {'#','.','#','#','#','#','#','#','#','#','#','.','#','#','#','#','#','#','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','.','.','.','.','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};


// Checkpoint positions (index 1 through 9)
int cpRow[10] = {0,  1,  5,  3,  7, 11, 13,  9, 13, 17};
int cpCol[10] = {0, 10,  5,  3,  3,  3,  3, 11, 14, 19};


// ALL QUESTION DATA!!!!
// Each array has 10 slots; index 0 is unused (checkpoints are 1-9)

//Question Header
string questionHeader[10] = {
    "",
    "Two Truths & a Lie -- which one is the LIE?(Ahmed Edition)",
    "Two Truths & a Lie -- which one is the LIE?(Mohamed Edition)",
    "Two Truths & a Lie -- which one is the LIE?(Hassan Edition)",
    "Two Truths & a Lie -- which one is the LIE?(Abdullah Edition)",
    "Two Truths & a Lie -- which one is the LIE?(Lucas Edition)",
    "Two Truths & a Lie -- which one is the LIE?(Chuck)",
    "Two Truths & a Lie -- which one is the LIE?(Aiden)",
    "Two Truths & a Lie -- which one is the LIE?(Luis)",
    "FINAL CHECKPOINT -- Two Truths & a Lie. Which is the LIE?(Mostafa)"
};

//Answer A options
string optionA[10] = {
    "",
    "  A) Ahmed was a med student for 2 years",
    "  A) Mohamed has been pulled over by military police",
    "  A) Hassan is HVAC certified",
    "  A) Abdullah's favorite sport is soccer",
    "  A) Lucas has squated 405 pounds",
    "  A) Chuck is a prince in a different country",
    "  A) Aiden plays basketball",
    "  A) Luis playe soccer",
    "  A) Mostafa knows rubix cube algorithms"
};

//Answer B  options
string optionB[10] = {
    "",
    "  B) Ahmed got pulled over for reckless driving",
    "  B) Mohamed is banned from Little Caesars Arena",
    "  B) Hassan lost 150 pounds of weight",
    "  B) Abdullah's favorite food is steak",
    "  B) Lucas has won a high school golf tournament",
    "  B) Chuck can bench 405",
    "  B) Aiden is passionate about real-estate",
    "  B) Luis has ran a sub 5 minute mile",
    "  B) Mostafa is a middle child"
};

//Answer c options
string optionC[10] = {
    "",
    "  C) Ahmed won all-county at QB in 11th grade High School Football",
    "  C) Mohamed is a former Roblox YouTuber",
    "  C) Hassan got stopped by Airport police for carrying cannabis",
    "  C) Abdullah owns and drives an Audi RS7",
    "  C) Lucas played 1 year of D3 football before quitting",
    "  C) Chuck can squat 600 pounds",
    "  C) Aiden used to live in Colorado",
    "  C) Luis is allergic to peanut butter",
    "  C) Mostafa can speak two languages fluently"
};

// The letter of the lie for each checkpoint
char correctAnswer[10] = {' ', 'c', 'b', 'c', 'c', 'c', 'b', 'c', 'c', 'a'};

//random fun facts.
string funFact[10] = {
    "",
    "Ahemed actually got pulled over for reckless driving and was a med student for 2 years!",
    "Mohamed got pulled over by military police and he's grappler and hyper-extended his neck.",
    "Hassan has his HVAC liscense and he used to weigh a lot more than he does now!",
    "Abdullah doesn't drive a RS7 although he wishes he did!",
    "Lucas had college offers but never wanted to play college football",
    "Chuck is an insanely strong former football player",
    "Aiden is actually obsessed with real estate",
    "Luis actually loves peanut butter!",
    "Mostafa is truly bilingual!"
};


// Game state variables

//player positions
int playerRow = 1;
int playerCol = 1;

int checkpointsFound = 0; //for the checkpoint counter
bool cpCollected[10] = {false, false, false, false, false, false, false, false, false, false}; //which checkpoint is found
bool exitUnlocked = false; //after all checkpoints are grabbed this will be true
bool gameWon = false;
bool gameLost = false; //this turns true when the player runs out of moves (lava gets them)
int totalMoves = 0;
int score = 0; //the player's running score during the game
string statusMessage = "Find all 9 checkpoints to unlock the exit!";


// Leaderboard data
//we use parallel arrays to store names and scores (same idea as cpRow and cpCol)
string lbNames[5]; //the name for each leaderboard slot
int lbScores[5]; //the score for each leaderboard slot
int lbCount = 0; //how many entries are in the leaderboard right now


// Clears the console after each turn
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


// Loads the leaderboard from the file
//the file stores: count on the first line, then alternating name and score lines
void loadLeaderboard() {
    ifstream inFile("leaderboard.txt");

    //if the file doesnt exist yet thats fine, just set count to 0
    if (!inFile.is_open()) {
        lbCount = 0;
        return;
    }

    inFile >> lbCount;
    for (int i = 0; i < lbCount; i++) {
        inFile >> lbNames[i];
        inFile >> lbScores[i];
    }
    inFile.close();
}


// Saves the leaderboard to the file
void saveLeaderboard() {
    ofstream outFile("leaderboard.txt");
    outFile << lbCount << endl;
    for (int i = 0; i < lbCount; i++) {
        outFile << lbNames[i] << endl;
        outFile << lbScores[i] << endl;
    }
    outFile.close();
}


// Adds a new score to the leaderboard and sorts it highest to lowest
void addScore(string name, int playerScore) {

    //if the leaderboard isnt full yet just add the new entry at the end
    if (lbCount < MAX_LEADERBOARD) {
        lbNames[lbCount] = name;
        lbScores[lbCount] = playerScore;
        lbCount++;
    } else {
        //leaderboard is full so find the lowest score and replace it
        int lowest = 0;
        for (int i = 1; i < lbCount; i++) {
            if (lbScores[i] < lbScores[lowest]) {
                lowest = i;
            }
        }
        //only replace if the new score is actually higher
        if (playerScore > lbScores[lowest]) {
            lbNames[lowest] = name;
            lbScores[lowest] = playerScore;
        }
    }

    //simple bubble sort to put the highest scores on top
    for (int i = 0; i < lbCount - 1; i++) {
        for (int j = 0; j < lbCount - i - 1; j++) {
            if (lbScores[j] < lbScores[j + 1]) {
                //swap the scores
                int tempScore = lbScores[j];
                lbScores[j] = lbScores[j + 1];
                lbScores[j + 1] = tempScore;
                //swap the names too so they stay matched up
                string tempName = lbNames[j];
                lbNames[j] = lbNames[j + 1];
                lbNames[j + 1] = tempName;
            }
        }
    }

    saveLeaderboard();
}


// Shows the leaderboard screen
void showLeaderboard() {
    clearScreen();

    cout << "\n";
    cout << "  +====================================+\n";
    cout << "  |        LEADERBOARD  (TOP 5)        |\n";
    cout << "  +====================================+\n";
    cout << "\n";

    if (lbCount == 0) {
        cout << "  No scores yet! Be the first to play!\n";
    } else {
        cout << "  Rank   Name               Score\n";
        cout << "  ----   ----               -----\n";
        for (int i = 0; i < lbCount; i++) {
            cout << "  #" << (i + 1) << "     " << lbNames[i];

            //pad the name with spaces so the scores line up nicely
            for (int s = lbNames[i].length(); s < 18; s++) {
                cout << " ";
            }
            cout << lbScores[i] << "\n";
        }
    }

    cout << "\n  Press Enter to go back to the menu...";
    cin.ignore();
    cin.get();
}


// Shows the main menu and returns whatever the player picked
int showMenu() {
    clearScreen();

    cout << "\n";
    cout << "  +====================================+\n";
    cout << "  |                                    |\n";
    cout << "  |            P = NP ?                |\n";
    cout << "  |    Two Truths & a Lie Maze Game    |\n";
    cout << "  |                                    |\n";
    cout << "  +====================================+\n";
    cout << "\n";
    cout << "  1) Play Game\n";
    cout << "  2) Leaderboard\n";
    cout << "  3) Quit\n";
    cout << "\n";
    cout << "  Enter your choice: ";

    char choice;
    cin >> choice;
    return choice - '0'; //converts the char to a number
}


// Prints the lava danger bar and the rising lava waves
//this shows the player how close they are to running out of moves
void printLavaBar() {
    int movesLeft = MAX_MOVES - totalMoves;
    int dangerLevel = (totalMoves * 20) / MAX_MOVES; //goes from 0 to 20

    //draw the bar
    cout << "\n  LAVA: [";
    for (int i = 0; i < 20; i++) {
        if (i < dangerLevel)
            cout << "=";
        else
            cout << " ";
    }
    cout << "] ";

    //pick a warning label based on how full the bar is
    if (dangerLevel < 5)
        cout << "Low";
    else if (dangerLevel < 10)
        cout << "Rising...";
    else if (dangerLevel < 15)
        cout << "DANGER!";
    else
        cout << "!!! CRITICAL !!!";

    cout << "  (" << movesLeft << " moves left)\n";

    //draw lava wave lines that rise up as danger gets worse
    //the pattern shifts every move so it looks like the lava is actually moving
    int waveCount = 0;
    if (dangerLevel > 14) waveCount = 3;
    else if (dangerLevel > 10) waveCount = 2;
    else if (dangerLevel > 6) waveCount = 1;

    for (int w = 0; w < waveCount; w++) {
        cout << "  ";
        for (int i = 0; i < 50; i++) {
            //this makes the ^ characters shift position each turn
            if ((i + totalMoves + w) % 4 == 0)
                cout << "^";
            else
                cout << "~";
        }
        cout << "\n";
    }
}


// Prints the maze for the start of every new turn
void printMaze() {
    for (int r = 0; r < ROWS; r++) {
        cout << "  ";
        for (int c = 0; c < COLS; c++) {

            // places the player in the proper spot
            if (r == playerRow && c == playerCol) {
                cout << " @ ";
                continue;
            }

            // Exit tile (always at row 17, col 19)
            if (r == 17 && c == 19) {
                if (exitUnlocked)
                    cout << "[E]";
                else
                    cout << "[X]";
                continue;
            }

            // Checks and draws the checkpoints
            bool drawnAsCP = false;
            for (int i = 1; i <= TOTAL_CHECKPOINTS; i++) {
                if (r == cpRow[i] && c == cpCol[i]) {
                    if (cpCollected[i])
                        cout << " * ";
                    else
                        cout << "[" << i << "]";
                    drawnAsCP = true;
                    break;
                }
            }
            if (drawnAsCP) continue;

            // Regular maze tiles
            if (maze[r][c] == '#') {
                cout << "###";
            } else if (maze[r][c] == 'S') {
                cout << " S ";
            } else {
                cout << "   ";
            }
        }
        cout << "\n";
    }
}


// Prints the fun info beneath the maze
void printHUD() {
    cout << "\n";

    //show the players score
    cout << "  Score: " << score << "\n";

    //show which checkpoints have been collected
    cout << "  Checkpoints: [ ";
    for (int i = 1; i <= TOTAL_CHECKPOINTS; i++) {
        if (cpCollected[i])
            cout << i << " ";
        else
            cout << "- ";
    }
    cout << "]  " << checkpointsFound << " / " << TOTAL_CHECKPOINTS;

    if (exitUnlocked)
        cout << "   *** EXIT IS OPEN ***";
    else
        cout << "   [X] Exit is locked";

    cout << "\n";
    cout << "  Moves: " << totalMoves << " / " << MAX_MOVES;
    cout << "      Controls: W = up, S = down, A = left, D = right, Q = quit\n";

    if (statusMessage != "") {
        cout << "\n  >> " << statusMessage << "\n";
    }
}


// How the questions are asked
//same as before but now the player earns 100 points for each correct answer
bool askQuestion(int cpNumber) {
    clearScreen();

    cout << "\n";
    cout << "  +------------------------------------------+\n";
    cout << "  |  CHECKPOINT " << cpNumber << " of " << TOTAL_CHECKPOINTS;
    cout << "                           |\n";
    cout << "  +------------------------------------------+\n";
    cout << "\n";
    cout << "  " << questionHeader[cpNumber] << "\n\n";
    cout << optionA[cpNumber] << "\n";
    cout << optionB[cpNumber] << "\n";
    cout << optionC[cpNumber] << "\n";
    cout << "\n  Your answer (A, B, or C): ";

    string input;
    cin >> input;
    char answer = tolower(input[0]);

    // displays if right
    if (answer == correctAnswer[cpNumber]) {
        clearScreen();
        cout << "\n\n";
        cout << "  +--------------------------+\n";
        cout << "  |   CORRECT! Nice work!    |\n";
        cout << "  +--------------------------+\n\n";

        //award points for the correct answer
        score += 100;
        cout << "  +100 points!\n\n";

        cout << "  Did you know: " << funFact[cpNumber] << "\n\n";
        cout << "  Press Enter to keep going...";
        cin.ignore();
        cin.get();
        return true;

    } else {
        clearScreen();
        cout << "\n\n";
        cout << "  +-------------------------------+\n";
        cout << "  |   Nope! That's not the lie.   |\n";
        cout << "  +-------------------------------+\n\n";
        cout << "  The correct answer was " << (char)toupper(correctAnswer[cpNumber]) << ".\n";
        cout << "  " << funFact[cpNumber] << "\n\n";
        cout << "  You've been sent back to where you came from.\n";
        cout << "  Walk back to this checkpoint to try again!\n\n";
        cout << "  Press Enter to continue...";
        cin.ignore();
        cin.get();
        return false;
    }
}


// How to move
//there are exceptions for walls, the exit, and now the move limit
void tryMove(int newRow, int newCol) {

    // Bounds check
    if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS) {
        statusMessage = "You can't go outside the maze!";
        return;
    }

    // Locked exit acts like a wall
    if (newRow == 17 && newCol == 19 && !exitUnlocked) {
        statusMessage = "The exit is locked! You need all " + to_string(TOTAL_CHECKPOINTS) + " checkpoints first.";
        return;
    }

    // Wall check
    if (maze[newRow][newCol] == '#') {
        statusMessage = "Ouch! That's a wall.";
        return;
    }

    // Check if there is an uncollected checkpoint at the destination
    int checkpointHere = 0;
    for (int i = 1; i <= TOTAL_CHECKPOINTS; i++) {
        if (newRow == cpRow[i] && newCol == cpCol[i] && !cpCollected[i]) {
            checkpointHere = i;
            break;
        }
    }

    // If there's a checkpoint, do the quiz before allowing movement
    if (checkpointHere != 0) {
        bool answeredCorrectly = askQuestion(checkpointHere);

        if (answeredCorrectly) {
            // Move the player to the checkpoint
            playerRow = newRow;
            playerCol = newCol;
            totalMoves++;

            //survival points for the move
            score += 10;

            // Mark it as collected
            cpCollected[checkpointHere] = true;
            checkpointsFound++;

            // Check if that was the last one
            if (checkpointsFound == TOTAL_CHECKPOINTS) {
                exitUnlocked = true;
                statusMessage = "ALL CHECKPOINTS FOUND! The exit [E] is now open -- go get out!";
                gameWon = true;   // checkpoint 9 is the exit tile, so game is won
            } else {
                statusMessage = "Checkpoint " + to_string(checkpointHere) + " collected! ("
                              + to_string(checkpointsFound) + " / " + to_string(TOTAL_CHECKPOINTS) + ")";
            }

        } else {
            // Wrong answer -- player stays put (don't update playerRow/playerCol)
            statusMessage = "Wrong answer. Find that checkpoint again to retry.";
        }

        return;
    }

    // Just a normal tile -- move there
    playerRow = newRow;
    playerCol = newCol;
    totalMoves++;

    //give survival points for each successful move (the longer you survive the more points you get)
    score += 10;

    statusMessage = "";

    // open exit at the end of the game
    if (newRow == 17 && newCol == 19 && exitUnlocked) {
        gameWon = true;
    }

    //check if the player used up all their moves
    if (totalMoves >= MAX_MOVES) {
        gameLost = true;
    }

    //show warning messages as the lava gets higher
    int dangerLevel = (totalMoves * 20) / MAX_MOVES;
    if (statusMessage == "") {
        if (dangerLevel >= 18) {
            statusMessage = "!!! THE LAVA IS ALMOST HERE! HURRY !!!";
        } else if (dangerLevel >= 14) {
            statusMessage = "DANGER! The lava is rising fast!";
        } else if (dangerLevel >= 10 && totalMoves % 10 == 0) {
            statusMessage = "The lava is getting closer...";
        }
    }
}


// Shows the end screen with the final score
//this runs whether the player won or lost
void showEndScreen() {
    clearScreen();

    if (gameWon) {
        //give an escape bonus for actually making it out
        score += 500;

        cout << "\n\n";
        cout << "  +==========================================+\n";
        cout << "  |                                          |\n";
        cout << "  |       YOU ESCAPED THE MAZE!!!            |\n";
        cout << "  |                                          |\n";
        cout << "  |   All 9 questions answered correctly!   |\n";
        cout << "  |                                          |\n";
        cout << "  +==========================================+\n\n";
    } else {
        cout << "\n\n";
        cout << "  +==========================================+\n";
        cout << "  |                                          |\n";
        cout << "  |          THE LAVA GOT YOU!               |\n";
        cout << "  |                                          |\n";
        cout << "  |       You ran out of moves...            |\n";
        cout << "  |                                          |\n";
        cout << "  +==========================================+\n\n";
    }

    //show the final score
    cout << "  Total moves: " << totalMoves << "\n";
    cout << "  Checkpoints collected: " << checkpointsFound << " / " << TOTAL_CHECKPOINTS << "\n";
    cout << "\n";
    cout << "  FINAL SCORE: " << score << "\n";
    cout << "\n";

    //ask for name and save it to the leaderboard
    cout << "  Enter your name for the leaderboard: ";
    string playerName;
    cin >> playerName;

    addScore(playerName, score);
    cout << "\n  Score saved! Check the leaderboard from the main menu.\n";

    cout << "\n  Press Enter to return to menu...";
    cin.ignore();
    cin.get();
}


// Runs one full game from start to finish
void playGame() {

    // Reset everything for a new game
    playerRow = 1;
    playerCol = 1;
    checkpointsFound = 0;
    exitUnlocked = false;
    gameWon = false;
    gameLost = false;
    totalMoves = 0;
    score = 0;
    statusMessage = "Find all 9 checkpoints to unlock the exit!";

    for (int i = 0; i < 10; i++) {
        cpCollected[i] = false;
    }

    // Main game loop -- keeps going until the player wins or the lava gets them
    while (!gameWon && !gameLost) {
        clearScreen();
        printMaze();
        printLavaBar();
        printHUD();

        cout << "\n  Enter move (W/A/S/D) or Q to quit: ";

        char input;
        cin >> input;
        input = tolower(input); //so that case doesn't matter

        if (input == 'q') {
            cout << "\n  Thanks for playing!\n\n";
            return; //goes back to the menu without showing the end screen
        } else if (input == 'w') {
            tryMove(playerRow - 1, playerCol);
        } else if (input == 's') {
            tryMove(playerRow + 1, playerCol);
        } else if (input == 'a') {
            tryMove(playerRow, playerCol - 1);
        } else if (input == 'd') {
            tryMove(playerRow, playerCol + 1);
        } else {
            statusMessage = "Not a valid key. Use W, A, S, or D.";
        }
    }

    // game ended so show the score screen
    showEndScreen();
}


// Main
int main() {

    //load the leaderboard from the file when the program first starts
    loadLeaderboard();

    bool running = true;

    //this loop keeps the menu going until the player picks quit
    while (running) {
        int choice = showMenu();

        if (choice == 1) {
            playGame();
        } else if (choice == 2) {
            showLeaderboard();
        } else if (choice == 3) {
            cout << "\n  Thanks for playing!\n\n";
            running = false;
        }
        //if they type something weird it just shows the menu again
    }

    return 0;
}
