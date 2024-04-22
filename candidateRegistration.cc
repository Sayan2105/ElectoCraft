
// TO REGISTER ALL THE PARTIES PARTICIPATING IN THE ELECTION

#include <iostream>
#include <fstream> // Include this header for file I/O
#include <string>
#include <vector>

using namespace std;

class DataVector {
private:
    int codeNumber;
    string partyName;
    string candiName;
public:
    // Constructor
    DataVector(int codeNumber, const string& partyName, const string& candidateName){
        this->codeNumber = codeNumber;
        this->partyName  = partyName;
        this->candiName  = candidateName;
    }

    // Getter for codeNumber
    int getCodeNumber() const {
        return codeNumber;
    }

    // Getter and Setter for partyName
    const string& getPartyName() const {
        return partyName;
    }
    void setPartyName(const string& party) {
        partyName = party;
    }

    // Getter and Setter for candiName
    const string& getCandiName() const {
        return candiName;
    }
    void setCandiName(const string& candidate) {
        candiName = candidate;
    }

};

// Function prototypes
void display(const vector<DataVector>& allCandidates);
void candidateRegister(vector<DataVector>& newCandidate);
void writeData(const vector<DataVector>& list_of_Parties, const string& fileName);
bool validateCandidateInput(const string& partyName, const string& candiName);

int main(){
    // Declare a vector of DataVector
    vector<DataVector> Candidates;

    // Call the candidateRegister function to register candidates
    candidateRegister(Candidates);

    // Call the writeData function to write the data to the file
    writeData(Candidates, "data.txt");

    // Output a message indicating that the candidate entries have been completed successfully
    cout<<"All the candidates' entries have been done successfully."<<endl;

    // Ask the user if they want to see the data of all the candidates
    cout<<"Do you want to see the data of all the candidates? (y/n) : ";
    char choice;
    cin>>choice;
    if(choice == 'y' || choice == 'Y') display(Candidates);

    return 0;
}

void display(const vector<DataVector>& allCandidates){
    for(int i = 0; i < allCandidates.size(); i++){
        cout<<"\t\t Code number: "<<allCandidates[i].getCodeNumber()<<endl;
        cout<<"\t\t Candidate name: "<<allCandidates[i].getCandiName()<<endl;
        cout<<"\t\t Party name: "<<allCandidates[i].getPartyName()<<endl<<endl;
    }

    // Send the user to the Admin File
    cout<<"Now you can go to the Admin.cc to conduct the votes.";
}

void candidateRegister(vector<DataVector>& newCandidate) {
    int numberOfCandidates;
    cout << "\t\t\tEnter the number of Candidates participating. : ";
    cin >> numberOfCandidates;
    cout<<endl;
    cin.ignore(); // To consume the newline character left by cin

    for(int i = 0; i < numberOfCandidates; i++){
        int code = 1001 + i;

        // Enter the name of the party.
        cout << "\t\tEnter the name of the party : ";
        string partyName;
        getline(cin, partyName);

        // Enter the name of the candidate
        cout << "\t\tEnter the name of the candidate : ";
        string candiName;
        getline(cin, candiName);

        // Validate candidate input
        if (validateCandidateInput(partyName, candiName)) {
            // Add the new candidate to the vector
            DataVector temp(code, partyName, candiName);
            newCandidate.push_back(temp);
        } else {
            cout << "\t\tInvalid input! Please enter valid party and candidate names.\n";
            i--; // Decrement i to re-enter data for this candidate
        }
        
        cout<<endl;
    }
}

bool validateCandidateInput(const string& partyName, const string& candiName) {
    // Simple validation: Ensure party name and candidate name are not empty
    return !partyName.empty() && !candiName.empty();
}

void writeData(const vector<DataVector>& list_of_Parties, const string& fileName){ 
    // open file for writing
    ofstream outFile(fileName);

    // check if file is open
    if(!outFile.is_open()){
        cout<<"There was an error while opening the file "<< fileName<<". Try Again :("<<endl;
        return;
    }

    // write data to file
    for(int i = 0; i < list_of_Parties.size(); i++){
        outFile<<list_of_Parties[i].getCodeNumber()<<" "<<list_of_Parties[i].getPartyName()<<" "<<list_of_Parties[i].getCandiName()<<endl;
    }

    outFile.close();
}

