#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class State {
  public:
  int current;
  char letter;
  int next;
};

class DFA {
  public:
  vector<int> Q;
  vector<string> Sigma;
  int q0;
  vector<int> T;
  vector<State*> Delta;
};

int main(int argc, char **argv)
{
  if (argc != 2) {
    cout << "usage: ./hw5 filename\n";
    exit(-1);
  }

  // create dfa and assign args accordingly
  DFA* dfa = new DFA();
  string line;
  string buffer = "";

  ifstream myfile(argv[1]);
  int idx = 0;
  if (myfile) { // is the file good?
    while (getline( myfile, line )) {
      //cout << line << '\n';
      if (idx == 0) {
        line = line + ' '; // add space to end of line for parsing
        for (int i = 0; i < line.size(); i++) {
          if (line[i] == ' ') {
            dfa->Q.push_back(atoi(buffer.c_str())); // push back the possible states
            buffer = "";
          }
          else {
            buffer += line[i];
          }
        }
      }
      if (idx == 1) {
        buffer = "";
        line = line + ' '; // add space to end of line for parsing
        for (int i = 0; i < line.size(); i++) {
          if (line[i] == ' ') {
            dfa->Sigma.push_back(buffer);
            buffer = "";
          }
          else {
            buffer += line[i];
          }
        }
      }
      if (idx == 2) {
        dfa->q0 = atoi(line.c_str());
      }
      if (idx == 3) {
        buffer = "";
        line = line + ' '; // add space to end of line for parsing
        for (int i = 0; i < line.size(); i++) {
          if (line[i] == ' ') {
            dfa->T.push_back(atoi(buffer.c_str()));
            buffer = "";
          }
          else {
            buffer += line[i];
          }
        }
      }
      if (idx > 3) { // idx > 3
        //cout << line << '\n';
        int counter = 0;
        buffer = "";
        int current1, next1;
        char letter1;

        line += '\n';
        State* newState = new State();
        for (int i = 0; i < line.size(); i++) { // for each char in the line
          //cout << line[i] ;
          if (line[i] == ' ' && counter == 0) { // put the buffer into a state's->current
            current1 = stoi(buffer);
            buffer = "";
            counter++;
            newState->current = current1;
          }
          else if (line[i] == ' ' && counter == 1) { // put the buffer into a state's->letter
            letter1 = buffer[1]; // buffer contains a space and a letter
            buffer = "";
            counter++;
            newState->letter = letter1;
          }
          else if (line[i] == '\n' && counter == 2) { // put the buffer into a state's->next
            next1 = stoi(buffer);
            buffer = "";
            counter = 0;
            newState->next = next1;
            dfa->Delta.push_back(newState);
          }
          buffer += line[i];
        }
      }
      idx++;
    }
  }

  /* check that all data in dfa is correct
  for (int i = 0; i < dfa->Delta.size(); i++) {
    State* newState = new State();
    newState = dfa->Delta[i];
    cout << newState->current << ' ';
    cout << newState->letter << ' ';
    cout << newState->next << '\n';

  }
  for (int i = 0; i < dfa->Q.size(); i++) {
    cout << dfa->Q[i] << ' ';
  }
  cout << '\n';
  for (int i = 0; i < dfa->Sigma.size(); i++) {
    cout << dfa->Sigma[i] << ' ';
  }
  cout << '\n';

  for (int i = 0; i < dfa->T.size(); i++) {
    cout << dfa->T[i] << ' ';
  }
  cout << '\n';*/

  // check if q0 is an accepting state
  bool q0Accepting = false;
  for (int i = 0; i < dfa->T.size(); i++) {
    if (dfa->q0 == dfa->T[i])
      q0Accepting = true;
  }
  // add the * if its accepting
  if (q0Accepting)
    cout << "q0 = " << dfa->q0 << '*' << '\n';
  else
    cout << "q0 = " << dfa->q0 << '\n';

  // for each delta
  for (int i = 0; i < dfa->Delta.size(); i++) {
    State* newState = new State();
    newState = dfa->Delta[i];
    bool finalState = false;
    for (int j = 0; j < dfa->T.size(); j++) {
      if (newState->next == dfa->T[j])
        finalState = true; // if its a finish state assing finalState to true
    }
    if (finalState) // it its a finish state add the *
      cout << newState->current << ',' << newState->letter << " -> " << newState->next << "*\n";
    else
      cout << newState->current << ',' << newState->letter << " -> " << newState->next << "\n";
  }

  vector<int> StatesRunThrough; // this will keep track of states for printing
  string userInput = "";
  cout << "Enter a string to check\n";

  while(getline(cin,userInput)) { // get one line at a time

    int currentState = dfa->q0; // start in state (q0)

    for (int i = 0; i < userInput.size(); i++) { // for each character in our string
        for (int j = 0; j < dfa->Delta.size(); j++) { // for each state
          State* state = new State();
          state = dfa->Delta[j];
          if (currentState == state->current && userInput[i] == state->letter) { // if same state and same letter
            currentState = state->next; // move to the next state
            j = dfa->Delta.size();// we may need to break out of the state loop
          }
        }
        StatesRunThrough.push_back(currentState);
    }

    // check the if the finalState is and accepting state or not
    bool finalState = false;
    for (int i = 0; i < dfa->T.size(); i++) {
      if (currentState == dfa->T[i])
        finalState = true;
    }
    if (finalState) {
      cout << "accepted\n";
    }
    else
      cout << "rejected\n";

    string output = to_string(dfa->q0);
    //check if q0 is a valid state
    if (q0Accepting && StatesRunThrough.size() == 0) // if the size is 0 we are checking lambda
      output += "*";
    else if (q0Accepting)
      output += "* -> ";
    else if (!q0Accepting && StatesRunThrough.size() == 0) // when lambda itn't accepted
      output = output;
    else
      output += " -> ";

    for (int i = 0; i < StatesRunThrough.size(); i++) { // for each state we ran through
      output += to_string(StatesRunThrough[i]); // add to our output
      bool validEndState = false;

      for (int j = 0; j < dfa->T.size(); j++) { // for each state check if we need to add a *
        if (StatesRunThrough[i] == dfa->T[j])
          finalState = true;
        else
          finalState = false;
        if (finalState)
          output += '*';
      }
      if (i != StatesRunThrough.size() -1) // don't add -> if its the last state
        output += " -> ";
    }
    cout << output << '\n';
    StatesRunThrough.clear(); // clear our vector for future strings to check

    cout << "==================\n";
    cout << "Enter a string: \n";
  }
}
