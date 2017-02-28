#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
peg locations:

         1                1  3  6  10 15
       2   3              2  5  9  14
     4   5   6            4  8  13
   7   8   9   10         7  12
 11  12  13  14  15       11

*/

void printUsage() {
  cout << "usage: ./a.out emptyPegLocation printBoard\nwhere emptyPegLocation is between 1 and 15 (inclusive)\n" <<
  "and printBoard is either 'true' or 'false'\n         1\n       2   3\n     4   5   6\n   7   8   9   10\n" <<
  "11  12  13  14   15\n\n";
  exit(-1);
}

// returns a pre-filled board
void initBoard(vector<vector<int> > &board, int pegLoc) {
  int counter = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      board[i].push_back(j);
      board[i][j] = 1;
      counter++;
      if (counter==10||counter==14||counter==15||counter==18||counter==19||
      counter==20||counter==22||counter==23||counter==24||counter==25) {
        board[i].push_back(j);
        board[i][j] = -1;
      }
    }
  }
  // set the hole
  if (pegLoc==1) board[0][0]=0;
  if (pegLoc==2) board[1][0]=0; if (pegLoc==3) board[0][1]=0;
  if (pegLoc==4) board[2][0]=0; if (pegLoc==5) board[1][1]=0; if (pegLoc==6) board[0][2]=0;
  if (pegLoc==7) board[3][0]=0; if (pegLoc==8) board[2][1]=0; if (pegLoc==9) board[1][2]=0; if (pegLoc==10) board[0][3]=0;
  if (pegLoc==11) board[4][0]=0; if (pegLoc==12) board[3][1]=0; if (pegLoc==13) board[2][2]=0; if (pegLoc==14) board[1][3]=0;if (pegLoc==15) board[0][4]=0;
}

// printBoard prints a passed board
void printBoard(vector<vector<int> > board) {
  printf("%9d\n",board[0][0]);
  printf("%7d   %d\n",board[1][0],board[0][1]);
  printf("%5d   %d   %d\n",board[2][0],board[1][1],board[0][2]);
  printf("%3d   %d   %d   %d\n",board[3][0],board[2][1],board[1][2],board[0][3]);
  printf("%d   %d   %d   %d   %d\n",board[4][0],board[3][1],board[2][2],board[1][3],board[0][4]);
  printf("====================\n");
}

// remap locates hard coded peg location numbers
int remap(int i, int j) {
  if (i==0 && j==0) return 1;
  if (i==1 && j==0) return 2; if (i==0 && j==1) return 3;
  if (i==2 && j==0) return 4; if (i==1 && j==1) return 5; if (i==0 && j==2) return 6;
  if (i==3 && j==0) return 7; if (i==2 && j==1) return 8; if (i==1 && j==2) return 9; if (i==0 && j==3) return 10;
  if (i==4 && j==0) return 11; if (i==3 && j==1) return 12; if (i==2 && j==2) return 13; if (i==1 && j==3) return 14; if (i==0 && j==4) return 15;
  return -1;
}

// returns the number of pegs left on a given board
int findNumPegs(vector<vector<int> > board) {
  int numPegs = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (board[i][j] == 1)
        numPegs++;
    }
  }
  return numPegs;
}

void solve(vector<vector<vector<int> > > &game, vector<vector<int> > board, bool &finished, vector<string>&output, bool printBoardb) {
  game.push_back(board); // store the currentBoard

  vector<vector<int> > currentBoard; // create a new Board

  if (!finished) {
    int numPegs = findNumPegs(board);
    if (numPegs == 1) {
      //printBoard(board);
      finished = true;

      for (int i = 0; i < game.size(); i++) {
        if (i > 0)
          cout << output[i];

        if (printBoardb)
          printBoard(game[i]);
      }
      return;
    }
    //printBoard(board);

    // loop through the holes
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (board[i][j] == 1) { // continue till a peg is found

          // Test the North
          if (i >= 2) {
            if (board[i-1][j] == 1) { // check if one peg north is 1
              if (board[i-2][j] == 0) { // check if two peg north is 0
                //cout << "north\n";
                currentBoard = board; // assign the new board to last one
                currentBoard[i][j] = 0;
                currentBoard[i-1][j] = 0;
                currentBoard[i-2][j] = 1;
                output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i-2,j)) + "\n");
                solve(game, currentBoard, finished, output, printBoardb);
              }
            }
          }

          // Test the East
          if (i == 2) {
            if (j == 0) {
              if (board[i][j+1] == 1) { // check if one peg east is 1
                if (board[i][j+2] == 0) { // check if two pegs east is 0
                  //cout << "east\n";
                  currentBoard = board; // assign the new board to last one
                  currentBoard[i][j] = 0;
                  currentBoard[i][j+1] = 0;
                  currentBoard[i][j+2] = 1;
                  output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i,j+2)) + "\n");
                  solve(game, currentBoard, finished, output, printBoardb);
                }
              }
            }
          }
          if (i == 1) {
            if (j <= 1) {
              if (board[i][j+1] == 1) { // check if one peg east is 1
                if (board[i][j+2] == 0) { // check if two pegs east is 0
                  //cout << "east\n";
                  currentBoard = board; // assign the new board to last one
                  currentBoard[i][j] = 0;
                  currentBoard[i][j+1] = 0;
                  currentBoard[i][j+2] = 1;
                  output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i,j+2)) + "\n");
                  solve(game, currentBoard, finished, output, printBoardb);
                }
              }
            }
          }
          if (i == 0) {
            if (j <= 2) {
              if (board[i][j+1] == 1) { // check if one peg east is 1
                if (board[i][j+2] == 0) { // check if two pegs east is 0
                  //cout << "east\n";
                  currentBoard = board; // assign the new board to last one
                  currentBoard[i][j] = 0;
                  currentBoard[i][j+1] = 0;
                  currentBoard[i][j+2] = 1;
                  output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i,j+2)) + "\n");
                  solve(game, currentBoard, finished, output, printBoardb);
                }
              }
            }
          }

          // Test the South
          if (i <= 2) {
            if (board[i+1][j] == 1) { // check if one peg south is 1
              if (board[i+2][j] == 0) { // check if two peg south is 0
                //cout << "south\n";
                currentBoard = board; // assign the new board to last one
                currentBoard[i][j] = 0;
                currentBoard[i+1][j] = 0;
                currentBoard[i+2][j] = 1;
                output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i+2,j)) + "\n");
                solve(game, currentBoard, finished, output, printBoardb);
              }
            }
          }

          // Test the West
          if (i == 0) {
            if (j >= 2) {
              if (board[i][j-1] == 1) { // check if one peg west is 1
                if (board[i][j-2] == 0) { // check if two pegs west is 0
                  //cout << "west\n";
                  currentBoard = board; // assign the new board to last one
                  currentBoard[i][j] = 0;
                  currentBoard[i][j-1] = 0;
                  currentBoard[i][j-2] = 1;
                  output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i,j-2)) + "\n");
                  solve(game, currentBoard, finished, output, printBoardb);
                }
              }
            }
          }
          if (i == 1) {
            if (j >= 2) {
              if (board[i][j-1] == 1) { // check if one peg west is 1
                if (board[i][j-2] == 0) { // check if two pegs west is 0
                  //cout << "west\n";
                  currentBoard = board; // assign the new board to last one
                  currentBoard[i][j] = 0;
                  currentBoard[i][j-1] = 0;
                  currentBoard[i][j-2] = 1;
                  output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i,j-2)) + "\n");
                  solve(game, currentBoard, finished, output, printBoardb);
                }
              }
            }
          }
          if (i == 2) {
            if (j >= 2) {
              if (board[i][j-1] == 1) { // check if one peg west is 1
                if (board[i][j-2] == 0) { // check if two pegs west is 0
                  //cout << "west\n";
                  currentBoard = board; // assign the new board to last one
                  currentBoard[i][j] = 0;
                  currentBoard[i][j-1] = 0;
                  currentBoard[i][j-2] = 1;
                  output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i,j-2)) + "\n");
                  solve(game, currentBoard, finished, output, printBoardb);
                }
              }
            }
          }

          // Test the North East (ex. 12->14)
          if (i >= 2) {
            if (j <= 2) {
              if (board[i-1][j+1] == 1) { // 1 peg NE is 1
                if (board[i-2][j+2] == 0) { // 2 pegs NE is 0
                  //cout << "ne\n";
                  currentBoard = board; // assign the new board to last one
                  currentBoard[i][j] = 0;
                  currentBoard[i-1][j+1] = 0;
                  currentBoard[i-2][j+2] = 1;
                  output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i-2,j+2)) + "\n");
                  solve(game, currentBoard, finished, output, printBoardb);
                }
              }
            }
          }

          // Test the South West (ex. 6->4)
          if (i <=2) {
            if (j >= 2) {
              if (board[i+1][j-1] == 1) { // 1 peg SW is 1
                if (board[i+2][j-2] == 0) { // 2 pegs SW is 0
                  //cout << "sw\n";
                  currentBoard = board; // assign the new board to last one
                  currentBoard[i][j] = 0;
                  currentBoard[i+1][j-1] = 0;
                  currentBoard[i+2][j-2] = 1;
                  output.push_back(to_string(remap(i,j)) + "  ->  " + to_string(remap(i+2,j-2)) + "\n");
                  solve(game, currentBoard, finished, output, printBoardb);
                }
              }
            }
          }
        }
      }
    }
  }
  output.pop_back();
  game.pop_back();
}

int main(int argc, char **argv)
{

  if (argc != 3) {
    printUsage();
  }

  int emptyPegLocation = 1;
  bool printBoardb = false;

  try {
  emptyPegLocation = atoi(argv[1]);
  }
  catch(int e) {
    printUsage();
  }
  string tmp = (argv[2]);
  if (tmp == "true")
    printBoardb = true;
  else if (tmp == "false")
    printBoardb = false;
  else {
    printUsage();
  }
  //cout << emptyPegLocation << "\n";//bool
  //cout << printBoardb << "\n";// num

  vector<vector<int> > board(5);
  initBoard(board, emptyPegLocation);
  cout << emptyPegLocation << "  ->  " << emptyPegLocation << "\n";
  vector<string> output;
  output.push_back(to_string(emptyPegLocation) + "  ->  " + to_string(emptyPegLocation));
  vector<vector<vector<int> > > game; // game holds the boards

  bool finished = false;
  solve(game, board, finished, output, printBoardb);
}
