#include "LoadBalancer.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    cout << "\n=== Matriz de Adyacencia ===\n";
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            if (val == INF) {
                cout << setw(4) << "INF" << " ";
            } else {
                cout << setw(4) << val << " ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() {
    cout << "\n=== Menu del Balanceador de Carga ===\n";
    cout << "1. Ver cargas de los servidores\n";
    cout << "2. Agregar nueva solicitud\n";
    cout << "3. Completar solicitud\n";
    cout << "4. Ver estados de los servidores\n";
    cout << "5. Ver matriz de adyacencia\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    srand(time(0));

    int numServers;
    cout << "Ingrese el numero de servidores: ";
    cin >> numServers;

    int maxRequests;
    cout << "Ingrese el numero maximo de solicitudes por servidor: ";
    cin >> maxRequests;

    vector<vector<int>> matrix(numServers, vector<int>(numServers, INF));
    for (int i = 0; i < numServers; ++i) {
        for (int j = i; j < numServers; ++j) {
            if (i == j) {
                matrix[i][j] = 0; 
            } else {
                if (rand() % 100 < 5) {  
                    matrix[i][j] = INF;  
                    matrix[j][i] = INF;
                } else {
                    int cost = rand() % 50 + 1;  
                    matrix[i][j] = cost;
                    matrix[j][i] = cost;
                }
            }
        }
    }

    LoadBalancer lb(numServers, matrix, maxRequests);
    int option;
    int nextRequestId = 0;

    do {
        printMenu();
        cin >> option;
        clearInput();

        switch(option) {
            case 1:
                lb.displayServerLoads();
                break;
            case 2: {
                cout << "Agregando solicitud con ID: " << nextRequestId << "\n";
                lb.distributeRequest(nextRequestId++);
                break;
            }
            case 3: {
                int requestId;
                cout << "Ingrese el ID de la solicitud a completar: ";
                cin >> requestId;
                clearInput();
                lb.completeRequest(requestId);
                break;
            }
            case 4:
                lb.displayRequestStatistics();
                break;
            case 5:
                printMatrix(matrix);
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Por favor intente de nuevo.\n";
        }
    } while (option != 6);

    return 0;
}