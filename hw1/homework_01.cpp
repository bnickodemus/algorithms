#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int smaller;
int larger;
int smallestDistance = -1; // something bad happend if we end with -1

void bruteForce(vector<int> nums) 
{
	// asuming we have good user input (2+ sorted ints in vector) 

	for(int i = 0; i < nums.size(); i++) // for each point
	{
		if(i+1 != nums.size()) // if we are not at the end
		{
			if(smallestDistance == -1) // we initilize the smallestDistance to the first one we find
			{
				smallestDistance = nums[i+1] - nums[i];
				smaller = nums[i];
				larger = nums[i+1]; 
			}
			else 
			{
				if((nums[i+1] - nums[i]) < smallestDistance) // if the larger value - smaller value < smallestDist
				{
					smallestDistance = nums[i+1] - nums[i]; // assign the smallestDist to the new smallerDist
					smaller = nums[i];
					larger = nums[i+1]; 
				}
			}
		}
	}
	//cout << "(" << smaller << "," << larger << ")" << endl ;
}

int recursive(vector<int> nums, int start, int size)
{
	vector<int> left;
	//cout << "nums size:" << nums.size() << endl;
	//cout << "left" << endl;
	for(int i = 0; i < size/2; i++) // get the left half
	{
		left.push_back(nums[i]);
		//cout << nums[i] << endl;
	}

	vector<int> right;
	//cout << "right" << endl;
	for(int i = size/2; i < size; i++) // get the right half
	{
		right.push_back(nums[i]);
		//cout << nums[i] << endl;
	}

	size = size/2; // reduce size each time so we eventually finish
	
	if(size == 3 || size == 2) // base case
	{
		bruteForce(left); 
		bruteForce(right);
		
		return 0;
	}	

	recursive(left, start, size); // rinse and repeat
	recursive(right, start, size); 
}

int main(int argc, char *argv[])
{
	if(argc == 1) 
	{
		vector<int>nums;
		
		int myInt;
		while(cin >> myInt) // get user input
		{
			if(cin.good()) 
				nums.push_back(myInt);
			else
			{
				cin.clear();
				cin.ignore();
			}
		}
		if(nums.size() > 2) // we need atleast two numbers to compare
		{
			sort(nums.begin(), nums.end()); // sort the vector of nums			
			bruteForce(nums); 
			cout << "brute force closest pair: 		   (" << smaller << "," << larger << ")" << endl ;		
		 	
			smallestDistance == -1; // set smallestDistance back to -1

			recursive(nums, 0, nums.size());
			cout << "recursive divide and conquer closest pair: (" << smaller << "," << larger << ")" << endl; 
		}
	}
	else
	{
		cout << "usage:./hw1" << endl;	
		return -1;		
	}
}

