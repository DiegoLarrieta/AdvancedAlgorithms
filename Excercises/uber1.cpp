#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solution(vector<int>& serversPowers, vector<string>& events) {
    // Initialize some variables
    int totalServers = serversPowers.size();
    vector<int> currentCapacities = serversPowers; // track current server capacities
    vector<bool> failedServers(totalServers, false); // track failed servers
    int currentServer = 0; // start with the first server
    int handledRequests = 0;

    // Loop through each event
    for (string event : events) {
        if (event == "REQUEST") {
            // Try to route the request to a functioning server
            bool requestHandled = false;
            while (!requestHandled) {
                // Find a server that isn't failed
                if (!failedServers[currentServer] && currentCapacities[currentServer] > 0) {
                    // Server can handle the request
                    currentCapacities[currentServer]--;
                    handledRequests++;
                    requestHandled = true;
                } 
                // Move to the next server (cyclically)
                currentServer = (currentServer + 1) % totalServers;
            }
        } else if (event.find("FAIL") == 0) {
            // Extract the server index to fail
            int spacePos = event.find(" ");
            int failedServerIndex = stoi(event.substr(spacePos + 1));
            failedServers[failedServerIndex] = true; // Mark server as failed
        }

        // After each event, reset capacities if a new cycle starts
        if (event == "REQUEST" && currentServer == 0) {
            for (int i = 0; i < totalServers; i++) {
                if (!failedServers[i]) {
                    currentCapacities[i] = serversPowers[i]; // Reset non-failed server capacities
                }
            }
        }
    }

    return handledRequests;
}

int main() {
    vector<int> serversPowers = {1, 2, 1, 2, 1};
    vector<string> events = {
        "REQUEST", 
        "REQUEST", 
        "FAIL 2", 
        "REQUEST", 
        "FAIL 3", 
        "REQUEST", 
        "REQUEST"
    };

    cout << "Total handled requests: " << solution(serversPowers, events) << endl;

    return 0;
}