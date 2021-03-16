#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class Labyrinth
{

private:
    int width;
    int height;
    std::string fileName;
    int longPathSize;

    vector<vector<char>> env;
    map<pair<int,int>, bool> visited;
    vector<vector<pair<int,int>>> paths;
    vector<pair<int,int>> path;

public:
    Labyrinth(){
        width = 7;
        height = 5;
        longPathSize = 0;
    };
    
    void startSolution(){

        while(true) {
        string userChoice;
        cout << "Which labyrinth test to solve? (press e to exit):" << endl;
        cin >> userChoice;
        if (userChoice == "e") {
            break;
        } else {
            env.clear();
            visited.clear();
            paths.clear();

            fileName = "../tests/" + userChoice + ".txt";
            ifstream file(fileName);
            string tempstr;

            if(!file) {
                cerr << "Test case unavialable.\n";
            } else {
                while (getline(file, tempstr)) {
                    vector<char> temp;
                    for(auto i: tempstr) {
                        temp.push_back(i);
                    }
                    env.push_back(temp);
                }
                cout << "Input: " << endl;
                printEnv();
                solveEnv();
            }


        }
    }

    };

    void printEnv(){

        for (auto row : env) {
        for (auto i : row) {
            cout << i;
        }
        cout << "\n";
    }

    };

    void solveEnv(){

        int x, y;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(env[i][j] == '.' && !visited[make_pair(i,j)]) {
                x = i;
                y = j;
                visited[make_pair(x,y)] = 1;
                vector<pair<int, int>> tempPath;
                tempPath.push_back(make_pair(x, y));
                while(true) {
                    if( y-1>0 && env[x][y-1] == '.' && !visited[make_pair(x,y-1)]) {
                        visited[make_pair(x,y-1)] = 1;
                        tempPath.push_back(make_pair(x, y-1));
                        y = y-1;
                    } else if(y+1<width && env[x][y+1] == '.' && !visited[make_pair(x,y+1)]) {
                        visited[make_pair(x,y+1)] = 1;
                        tempPath.push_back(make_pair(x, y+1));
                        y = y+1;
                    } else if(x-1>0 && env[x-1][y] == '.' && !visited[make_pair(x-1,y)]) {
                        visited[make_pair(x-1,y)] = 1;
                        tempPath.push_back(make_pair(x-1, y));
                        x = x-1;
                    } else if(x+1<height && env[x+1][y] == '.' && !visited[make_pair(x+1,y)]){
                        visited[make_pair(x+1,y)] = 1;
                        tempPath.push_back(make_pair(x+1, y));
                        x = x+1;
                    } else {
                        break;
                    }
                }
                if(tempPath.size() > longPathSize) {
                    longPathSize = tempPath.size();
                    path = tempPath;
                }
                paths.push_back(tempPath);
            }
        }
    }

    cout << "Solution: Longest Path Size is: " << longPathSize << endl;
     for (int i = 0; i < longPathSize; i++) {
            env[path[i].first][path[i].second] = '0' + i;
    }

    printEnv();

    };

};

int main (int argc, char *argv[]) {

    Labyrinth labyrinth;

    labyrinth.startSolution();

    return 0;
}