#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

int vertices, edges;
vector<vector<int>> weightInt;
vector<vector<string>> weight;

void initGraph(string filePath) {
    ifstream infile(filePath);
    if (!infile) {
        cout << "Cannot open input file" << endl;
        return;
    }

    string line;
    getline(infile, line);
    if (!line.empty()) {
        stringstream ss(line);
        ss >> vertices >> edges;
        weightInt.assign(vertices, vector<int>(vertices, 0));
        weight.assign(vertices, vector<string>(vertices, "oo"));
        for (int i = 0; i < vertices; ++i) {
            weight[i][i] = "0";
        }
    }
    else {
        cout << "Empty input file" << endl;
        return;
    }

    while (getline(infile, line)) {
        stringstream ss(line);
        int from, to, lineWeight;
        ss >> from >> to >> lineWeight;
        weight[from][to] = to_string(lineWeight);
        weight[to][from] = to_string(lineWeight);
        weightInt[from][to] = lineWeight;
        weightInt[to][from] = lineWeight;
    }
}

string weightMatrixToString() {
    ostringstream result;
    result << "| v\\v |";
    for (int i = 0; i < vertices; ++i) {
        result << " v" << setw(2) << i << "|";
    }
    result << endl;
    for (int i = 0; i < vertices; ++i) {
        result << "| v" << setw(2) << i << " |";
        for (int j = 0; j < vertices; ++j) {
            result << " " << setw(2) << weight[i][j] << " |";
        }
        result << endl;
    }
    return result.str();
}

void printMatrix(string matrix) {
    cout << matrix << endl;
}

void saveMatrixToFile(string matrix, string filePath) {
    ofstream outfile(filePath);
    if (!outfile) {
        cout << "Cannot open output file" << endl;
        return;
    }
    outfile << matrix;
}

void menu() {
    string filePath;
    cout << "Input path to file(or name): ";
    getline(cin, filePath);
    try {
        initGraph(filePath);
    }
    catch (const exception& e) {
        cout << "Incorrect input file" << endl;
        throw runtime_error(e.what());
    }
    string fileToSave;
    int menu;
    do {
        cout << "Choose operation:" << endl;
        cout << "1: Print weight matrix into console" << endl;
        cout << "2: Save weight matrix into file" << endl;
        cout << "0: Shutdown" << endl;
        cout << "Input: ";
        cin >> menu;
        switch (menu) {
        case 1:
            printMatrix(weightMatrixToString());
            break;
        case 2:
            cout << "Input file to save(without .txt): ";
            cin.ignore();
            getline(cin, fileToSave);
            fileToSave += ".txt";
            saveMatrixToFile(weightMatrixToString(), fileToSave);
            break;
        default:
            break;
        }
    } while (menu != 0);
}

int main() {
    menu();
    return 0;
}
