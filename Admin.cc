
// TO HOLD THE ELECTION AND THE VOTES FROM THE PUBLIC

#include <iostream>
#include <fstream> // Include this header for file I/O
#include <vector>
#include <string>
#include <limits> // Include this header for numeric_limits

using namespace std;

// Struct to represent a party
class Party {
    int codeNumber;
    string name;
    string candidate;
    int votes;

public:
    Party(int codeNumber, const string& name, const string& candidate) : codeNumber(codeNumber), name(name), candidate(candidate), votes(0) {}

    int getCodeNumber() const {
        return codeNumber;
    }

    int getVotes() const {
        return votes;
    }

    void incrementVotes() {
        votes++;
    }

    string getName() const {
        return name;
    }

    string getCandidate() const {
        return candidate;
    }
};

// Function prototypes
void display(const string& fileName);
void vote(int no_of_voters, vector<Party>& parties);
Party findMaxVotedParty(const vector<Party>& parties);
bool validateCodeNumber(int codeNumber, const vector<Party>& parties);
void displayResult(const vector<Party> parties);

int main() {
    const string fileName = "data.txt";
    vector<Party> parties;

    cout << "Enter the number of voters: ";
    int no_of_Voters;
    cin >> no_of_Voters;

    display(fileName);

    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return 1;
    }

    int codeNumber;
    string partyName;
    string candiName;

    while (inputFile >> codeNumber >> partyName >> candiName) {
        Party party(codeNumber, partyName, candiName);
        parties.push_back(party);
    }

    inputFile.close();

    vote(no_of_Voters, parties);

    displayResult(parties);

    return 0;
}

void display(const string& fileName) {
    // Output a header indicating the start of the list of political parties
    cout << "\t\t\tThe list of political parties is:\n";

    // Open the input file with the given file name
    ifstream inputFile(fileName);

    // Check if the file is open, and display an error message if it is not
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file " << fileName << endl;
        return;
    }

    // Declare variables to store the code number, party name, and candidate name
    int codeNumber;
    string partyName;
    string candiName;

    // Read data from the input file into the variables, and display the data
    while (inputFile >> codeNumber >> partyName >> candiName) {
        // Output the code number for the party
        cout << "\t\tCodeNumber Number for the party: " << codeNumber << endl;

        // Output the name of the party
        cout << "\t\tParty Name: " << partyName << endl;

        // Output the name of the candidate
        cout << "\t\tCandidate Name: " << candiName << endl << endl;
    }

    // Close the input file
    inputFile.close();
}

void displayResult(vector<Party> parties){
    // Find the party with the maximum number of votes
    Party maxVotedParty = findMaxVotedParty(parties);

    // Output the winner of the election if there are any votes
    if (maxVotedParty.getCodeNumber() != -1) {
        cout << "\n\n\t\tWinner of the Election is :"<<endl;
        cout << "\t\tCodeNumber Number: " << maxVotedParty.getCodeNumber() << " ";
        cout << "\t\tParty Name: " << maxVotedParty.getName() << " ";
        cout << "\t\tCandidate Name: " << maxVotedParty.getCandidate() << " "<<endl;
    } else {
        cout << "No votes cast yet.\n";
    }

    return;
}

void vote(int no_of_voters, vector<Party>& parties) {
    cout << "Voting Process:\n";
    for (int i = 0; i < no_of_voters; ++i) {
        int codeNumber;
        bool voted = false;

        cout << "\t\tVoter " << i + 1 << ": Enter the codeNumber number of the party you want to vote for: ";

        while (!voted) {
            if (cin >> codeNumber) {
                if (validateCodeNumber(codeNumber, parties)) {
                    for (auto& party : parties) {
                        if (party.getCodeNumber() == codeNumber) {
                            party.incrementVotes();
                            voted = true;
                            break;
                        }
                    }
                } else {
                    cout << "\t\tInvalid codeNumber number. Please enter a valid codeNumber number: ";
                }
            } else {
                cout << "\t\tInvalid input. Please enter an integer codeNumber number: ";
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        }
    }
}

bool validateCodeNumber(int codeNumber, const vector<Party>& parties) {
    // Check if codeNumber is valid by comparing with existing party code numbers
    for (const auto& party : parties) {
        if (party.getCodeNumber() == codeNumber) {
            return true;
        }
    }
    return false;
}

// This function returns the Party object with the maximum number of votes from the given vector of Party objects.
// If there are no votes cast yet, it returns a Party object with codeNumber -1 and empty name and candidate.
Party findMaxVotedParty(const vector<Party>& parties) {
    Party maxParty(-1, "", ""); // Initialize maxParty with codeNumber -1 and empty name and candidate

    // Iterate through the given vector of Party objects
    for (const auto& party : parties) {
        // If the current Party object has more votes than maxParty, update maxParty
        if (party.getVotes() > maxParty.getVotes()) {
            maxParty = party;
        }
    }

    // Return the Party object with the maximum number of votes
    return maxParty;
}

