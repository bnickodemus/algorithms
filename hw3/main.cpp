#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  if(argc != 1)
  {
    cout << "error: usage ./main" << endl;
    exit(-1);
  }
    string input = "";
    map<string, vector<string> > map1;
    map<string, int> map2;

    while(getline (cin, input)) // get user input
    {
      //cout << input << "\n";
      bool secondHalf = false;
      string node1 = ""; // node1 represets a node
      string node2 = ""; // node2 represents the node that node1 is pointing to

      // put the first node into node1 string and second node into node2 string
      for (int i = 0; i < input.size(); i++) {
        if (input[i] == ' ') // if we hit a space begin adding chars to second node
          secondHalf = true;
        else if (secondHalf) {
          node2 += input[i];
        }
        else {
          node1 += input[i];
        }
      }
      //cout << "c1: " << node1 << " c2: " << node2 << "\n";

      // parse the color from node1 and store it in color1 string
      string color1 = "";
      for (int i = 0; i < node1.length(); i++) {
        if (node1[i] == '-')
          break;
        else
          color1 += node1[i];
      }
      // parse the color from node2 and store it in color2 string
      string color2 = "";
      for (int i = 0; i < node2.length(); i++) {
        if (node2[i] == '-') {
          break;
        }
        else {
          color2 += node2[i];
        }
      }
      //cout << "color1: " << color1 << " color2: " << color2 << "\n";

      // if the key doesn't exist create it w/ value of 1, else inc the value of that key
      map2[color1 + " -> " + color2]++;
      //cout << "is this value correct: " << map2[color1 + " -> " + color2] << "\n";

      vector<string> v; // holds a temp vector

      if (map1.count(node1) > 0) { // the key exists
        v = map1.at(node1); // temp vector is now has correct data
        v.push_back(node2);
        map1[node1] = v; // add our new node to our key's value(vector)
        map1[node2]; // add node2 to the map if the it doesnt exist
      }
      else { // the key does not exist
        v.push_back(node2); // add node2
        map1[node1] = v;
        map1[node2]; // add node2 to the map if the it doesnt exist
      }
    }

    cout << "======== GRAPH ========\n";

    for(map<string,vector<string> >::iterator iter = map1.begin(); iter != map1.end(); iter++)
    {
      cout << iter->first << "\n"; // key
      vector<string> tmp = iter->second; // value
      for (int i = 0; i < tmp.size(); i++) {
        cout << "   => " << tmp[i] << "\n"; // for each node our current node is pointing to
      }
    }

    cout << "====== END GRAPH ======\n\n";
    cout << "==== COLOR COMBINATIONS ====\n";
    for(map<string,int>::iterator iter = map2.begin(); iter != map2.end(); iter++)
    {
      // print the key: [color1 + " -> " + color2] and the value: integer of times ocurred
      cout << iter->first << ": " << iter->second << "\n";
    }
    cout << "\n";
}
