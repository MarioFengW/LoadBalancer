#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <iostream>

using namespace std;

const int INF = INT_MAX;

class LoadBalancer {
private:
    int numServers;
    vector<vector<int>> adjacencyMatrix;  
    vector<vector<int>> serverLoads;    
    int maxRequestsPerServer;
    vector<int> totalRequestsPerServer;
    
    int totalRequests() const;

public:
    LoadBalancer(int n, const vector<vector<int>>& matrix, int maxRequests);
    void distributeRequest(int requestId);         
    void completeRequest(int serverId);
    void displayServerLoads();
    void displayRequestStatistics();
};

#endif