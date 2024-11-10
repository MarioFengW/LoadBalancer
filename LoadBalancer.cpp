#include <algorithm>

#include "LoadBalancer.h"
#include <iomanip>

using namespace std;    

LoadBalancer::LoadBalancer(int n, const vector<vector<int>>& matrix, int maxRequests)
    : numServers(n),
      adjacencyMatrix(matrix),
      serverLoads(n),  
      maxRequestsPerServer(maxRequests),
      totalRequestsPerServer(n, 0) {}

void LoadBalancer::distributeRequest(int requestId) {
    static int lastUsedServer = 0;
    int selectedServer = -1;
    int minCost = INF;
    int minLoad = INF;

    
    for (int i = 0; i < numServers; ++i) {

        if (serverLoads[i].size() >= maxRequestsPerServer || 
            adjacencyMatrix[lastUsedServer][i] == 0) {
            continue;
        }

        int currentLoad = serverLoads[i].size();
        int currentCost = adjacencyMatrix[lastUsedServer][i];

        if (selectedServer == -1 || 
            currentCost < minCost || 
            (currentCost == minCost && currentLoad < minLoad)) {
            selectedServer = i;
            minCost = currentCost;
            minLoad = currentLoad;
        }
    }

    if (selectedServer != -1) {
        serverLoads[selectedServer].push_back(requestId);
        totalRequestsPerServer[selectedServer]++;
        cout << "Solicitud " << requestId << " asignada al servidor " 
                  << selectedServer << " (Costo desde servidor " << lastUsedServer 
                  << ": " << minCost << ")\n";
        lastUsedServer = selectedServer;  
    } else {
        cout << "No hay servidores disponibles para la solicitud " 
                  << requestId << "\n";
    }
}

void LoadBalancer::completeRequest(int requestId) {
    for (int i = 0; i < numServers; ++i) {
        auto& requests = serverLoads[i];
        auto it = find(requests.begin(), requests.end(), requestId);
        if (it != requests.end()) {
            requests.erase(it);
            cout << "Solicitud " << requestId << " completada en servidor " << i << "\n";
            return;
        }
    }
    cout << "Error: Solicitud " << requestId << " no encontrada\n";
}

void LoadBalancer::displayServerLoads() {
    cout << "\n=== Cargas Actuales ===\n";
    for (int i = 0; i < numServers; ++i) {
        cout << "Servidor " << i << ": " 
                 << serverLoads[i].size() << " solicitudes activas\n";
    }
}

void LoadBalancer::displayRequestStatistics() {
    cout << "\n=== Estadisticas de Solicitudes ===\n";
    int total = totalRequests();
    
    for (int i = 0; i < numServers; ++i) {
        int currentLoad = serverLoads[i].size();
        double loadPercentage = (currentLoad * 100.0) / maxRequestsPerServer;
        
        cout << "Servidor " << i << ":\n"
                 << "  Solicitudes activas: " << currentLoad << "/" 
                 << maxRequestsPerServer << "\n"
                 << "  Total historico: " << totalRequestsPerServer[i] << "\n"
                 << "  % de capacidad: " << fixed << setprecision(2) 
                 << loadPercentage << "%\n";
    }
    cout << "Total solicitudes del sistema: " << total << "\n";
}

int LoadBalancer::totalRequests() const {
    int total = 0;
    for (int requests : totalRequestsPerServer) {
        total += requests;
    }
    return total;
}