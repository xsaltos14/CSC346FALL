//
//  main.cpp
//  LLab
//
//  Created by xavier saltos on 9/9/25.
//
#include <iostream>
#include <string>     
#include <cstdlib>
#include <ctime>
using namespace std;

struct Commit {
    int hash;          // Simulated unique commit ID
    string message;    // Commit message
    Commit* next;      // Pointer to the next commit in the list

    // Constructor to initialize a commit node
    Commit(int h, const string& msg) : hash(h), message(msg), next(nullptr) {}
};



class CommitHistory {
private:
    Commit* head;  // Points to the first commit in the list

public:
    // Constructor initializes an empty history
    CommitHistory() : head(nullptr) {}

    // Methods to simulate Git behavior
    void commit(const string& message);   // Add new commit (append at end)
    void log() const;                     // Display all commits
    void reset();                         // Delete the last commit
    static CommitHistory merge(const CommitHistory& branch1, const CommitHistory& branch2); // Merge two branches

    Commit* findByHash(int hash) const;   // Find commit by hash value
    CommitHistory branch() const;         // Duplicate branch (copy list)

    // Destructor to free memory
    ~CommitHistory();
};

// Simulates "git commit"
void CommitHistory::commit(const string& message) {
    int hash = rand() % 10000; // Generate a random number as the commit hash
    Commit* newCommit = new Commit(hash, message); // Create new commit node

    if (!head) {  // If list is empty, new commit becomes the first node
        head = newCommit;
    } else {      // Otherwise, traverse to the end of the list
        Commit* temp = head;
        while (temp->next) temp = temp->next; // Move to the last commit
        temp->next = newCommit; // Attach new commit at the end
    }

    cout << "Commit added: [" << hash << "] " << message << endl;
}

// Simulates "git log"
void CommitHistory::log() const {
    if (!head) {  // If there are no commits
        cout << "No commits yet." << endl;
        return;
    }

    Commit* temp = head;
    while (temp) {
        // Display commit hash and message
        cout << "[" << temp->hash << "] " << temp->message;
        if (temp->next) cout << " <- "; // Show arrow between commits
        temp = temp->next; // Move to next commit
    }
    cout << endl;
}

// Simulates "git reset --hard HEAD~1"
void CommitHistory::reset() {
    if (!head) {  // If list is empty
        cout << "No commits to reset." << endl;
        return;
    }

    // If there’s only one commit, delete it and clear the head
    if (!head->next) {
        cout << "Last commit removed (reset): [" << head->hash << "]" << endl;
        delete head;
        head = nullptr;
        return;
    }

    // Otherwise, find the second-to-last commit
    Commit* temp = head;
    while (temp->next && temp->next->next)
        temp = temp->next;

    // Delete the last commit
    cout << "Last commit removed (reset): [" << temp->next->hash << "]" << endl;
    delete temp->next;
    temp->next = nullptr; // End the list
}

// Simulates "git merge branch1 branch2"
CommitHistory CommitHistory::merge(const CommitHistory& branch1, const CommitHistory& branch2) {
    CommitHistory merged; // New merged history

    // Copy commits from branch 1
    Commit* temp = branch1.head;
    while (temp) {
        merged.commit(temp->message);
        temp = temp->next;
    }

    // Copy commits from branch 2
    temp = branch2.head;
    while (temp) {
        merged.commit(temp->message);
        temp = temp->next;
    }

    cout << "Branches merged." << endl;
    return merged; // Return new merged list
}

// Simulates "git show <hash>"
Commit* CommitHistory::findByHash(int hash) const {
    Commit* temp = head;
    while (temp) {
        if (temp->hash == hash) return temp; // matching commit
        temp = temp->next;
    }
    return nullptr; // Not found
}

// Simulates "git branch"
CommitHistory CommitHistory::branch() const {
    CommitHistory newBranch;
    Commit* temp = head;

    // Copy all commits into a new branch
    while (temp) {
        newBranch.commit(temp->message);
        temp = temp->next;
    }

    cout << "Branch created (duplicate)." << endl;
    return newBranch;
}

// Destructor – free all dynamically allocated commits
CommitHistory::~CommitHistory() {
    Commit* temp = head;
    while (temp) {
        Commit* toDelete = temp;
        temp = temp->next;
        delete toDelete; // Free memory for each commit
    }
}

int main() {
    srand(time(0)); // Seed random number generator (for unique hashes)

    // Create master branch and add commits
    CommitHistory master;
    master.commit("Initial commit");
    master.commit("Add README");
    master.commit("Implement login system");

    // Create a separate feature branch
    CommitHistory featureBranch;
    featureBranch.commit("Start feature X");
    featureBranch.commit("Fix bug in feature X");

    // Show master branch history
    cout << "\n== Master Branch ==" << endl;
    master.log();

    // Show feature branch history
    cout << "\n== Feature Branch ==" << endl;
    featureBranch.log();

    // Reset (delete) last commit from master branch
    cout << "\n== Reset last commit on master ==" << endl;
    master.reset();
    master.log();

    // Merge master and feature branches into a new merged branch
    cout << "\n== Merged History ==" << endl;
    CommitHistory merged = CommitHistory::merge(master, featureBranch);
    merged.log();

    // Demonstrate branching (duplicate master branch)
    cout << "\n== Branching Example ==" << endl;
    CommitHistory newBranch = master.branch();
    newBranch.commit("Experiment with feature Y");
    newBranch.log();

    
    return 0;
}
