#include <iostream>
#include <vector>
using namespace std;

// Question is saying we have n positions of rooms in hotel for players and we have 
// to allocate the rooms for players in such a way than the minimum distance between 
// two players is maximum. We have to return the distance which is maximum and players
// can be arranged in that way.

// Approach 1: Brute Force Approach
// Time Complexity: O(N * Max)
// Space Complexity: O(1)

bool isPossible(vector<int> &positions, int numRooms, int players, int minDist) {
    // function for checking is current minimum Distance between two players can be 
    // possible for generate a solution.

	int lastRoomPos = positions[0]; 
    // currently first room is occupies and start from one ahead

	int count = 1; // initially only one player occupied 

	for (int i=1; i<numRooms; i++) {
		if (minDist <= positions[i] - lastRoomPos) { 
            // if distance between current room and last room is bigger or equal to
            // minimum distance given, increase count of players and update last room 
            // position.

			count++;
			lastRoomPos = positions[i];
		}

        if (count == players) {
            break;
        }
	}
    
    // if the count is small than players, means the answer is not possible
	if (count < players) {
		return false;
	}

	return true; // if count is equal to player answer is possible
}
 
int chessTournament(vector<int> positions, int numRooms, int players){
	// step 1: sort the positions

	sort(positions.begin(), positions.end());

	int maxDist = positions[numRooms - 1];

	int ans = 0;

    // step 2: maximum distance can be last till last element - 1.

    for (int i = 1; i < positions[numRooms-1]; i++) {
		bool minAns = isPossible(positions, numRooms, players, i);
        // check is answer for current distance value is possible or not

		if (minAns == false) { 
        // if answer is not possible so for next i elements answer also not possible 
        // due to sorting of array. Hence, return the current value of ans.

			return ans;
		}

		ans = i; // else store the current i as answer and go for next itertation.
	}

	return ans;
}

// Approach 2: Binary Search
// Time Complexity: O(N * Log N);
// Space Complexity: O(1)

int chessTournament(vector<int> positions, int numRooms, int players){
	
	sort(positions.begin(), positions.end());

	int minDist = 1;

	int maxDist = positions[numRooms - 1];

	int ans = 0;

    // similar to above we cna try binary search instead of Linear Search.
	while (minDist <= maxDist) { 
		int mid = minDist + (maxDist - minDist)/2;

		bool minAns = isPossible(positions, numRooms, players, mid);

        // if answer is possible try to find for next element for maximization
		if (minAns == true) { 
			ans = mid;
			minDist = mid + 1;
		}
        // if not possible try for one before element
		else {
			maxDist = mid - 1;
		}
    }

	return ans;
}