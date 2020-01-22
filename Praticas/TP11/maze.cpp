#include "maze.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>

using namespace std;

DisjointSets Maze::getSets() const {
    return maze;
}

void Maze::printMaze() const
{
    cout << setw(3) << " ";
    for (int j=0; j<ncols; j++) {
        cout << setw(6) << "______";
    }
    for (int i=0; i<nrows; i++) {
        cout << endl;
        cout << setw(3) << "|";
        for (int j=0; j<ncols-1; j++) {
            int val = i*nrows+j;
            cout << setw(3) << val<<setw(3);
            if (noWalls.empty() || find(noWalls.begin(),noWalls.end(),pair<int,int>(val,val+1)) == noWalls.end())
                cout << "|";
            else
                cout <<" ";
        }
        int val = i*nrows+ncols-1;
        cout << setw(3) << val<<setw(3) << "|";
        cout <<endl;
        cout << setw(3) << " ";
        for (int j=0; j<ncols; j++) {
            int val = i*nrows+j;
            if (i<nrows-1) {
                if ( noWalls.empty() || find(noWalls.begin(), noWalls.end(), pair<int, int>(val, val + ncols)) == noWalls.end())
                    cout << setw(6) << "______";
                else
                    cout << setw(6) << " ";
            } else
                cout << setw(6) << "______";
        }

    }
    cout <<endl << endl;
}



// a implementar

Maze::Maze(int rows, int cols) : maze(rows*cols){
    this->ncols = cols;
    this->nrows = rows;
    this->noWalls.clear();
}

vector<int> Maze::getNeighbours(int x) const {
    vector<int> res;

    if (x % ncols == 0) {
        res.push_back(x + 1);
    }
    else if (x % ncols == ncols - 1) {
        res.push_back(x - 1);
    }
    else {
        res.push_back(x - 1);
        res.push_back(x + 1);
    }

    if (x < ncols) {
        res.push_back(x + ncols);
    }
    else if (x > (nrows * (ncols - 1) - 1)) {
        res.push_back(x - ncols);
    }
    else {
        res.push_back(x - ncols);
        res.push_back(x + ncols);
    }

    return res;
}

void Maze::buildRandomMaze() {
    noWalls.clear();
    int pos, new_pos, find1, find2;
    vector<int> neighbours;
    srand(time(NULL));

    while(this->maze.getNumberOfSets() != 1) {
        pos = rand() % (nrows * ncols);
        neighbours = getNeighbours(pos);
        new_pos = neighbours[rand() % neighbours.size()];
        find1 = maze.find(pos);
        find2 = maze.find(new_pos);
        if (find1 != find2) {
            maze.unionSets(find2, find1);
            noWalls.push_back(pair<int,int> (min(pos,new_pos),max(pos,new_pos)));
        }
    }

}

