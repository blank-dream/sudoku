#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
using namespace std;

const int GRID_SIZE = 9;
const int SUBGRID_SIZE = 3;
const int MIN_HOLES = 20;
const int MAX_HOLES = 55;


int number1 = 0;
int number = 0;
ofstream outfile;

bool isValid(int row, int col, int val, vector<vector<int>>& board) noexcept {
    for (int i = 0; i < 9; i++)
        if (board[row][i] == val)
            return false;
    for (int j = 0; j < 9; j++)
        if (board[j][col] == val)
            return false;
    for (int i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++)
        for (int j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
            if (board[i][j] == val)
                return false;
    return true;
}

bool sudoku(vector<vector<int>>& board) {

    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[0].size(); j++) {
            if (board[i][j] != 0)
                continue;
            for (int k = 9; k >= 1; k--) {
                if (isValid(i, j, k, board)) {
                    board[i][j] = k;
                    if (sudoku(board)) {
                        for (int i = 0; i < 9; i++) {
                            for (int j = 0; j < 9; j++) {
                                outfile << board[i][j] << " ";
                            }
                            outfile << endl;
                        }
                        outfile << "______________________" << endl;

                    }

                    board[i][j] = 0;
                }
            }
            return false;
        }
    }
    return true;
}

// 打印数独盘面
void printSudoku(const vector<vector<int>>& board) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == 0) {
                cout << "$ ";
            }
            else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// 检查数字num是否在行中重复
bool isNumInRow(const vector<vector<int>>& board, int row, int num) {
    for (int col = 0; col < GRID_SIZE; col++) {
        if (board[row][col] == num) {
            return true;
        }
    }
    return false;
}

// 检查数字num是否在列中重复
bool isNumInCol(const vector<vector<int>>& board, int col, int num) {
    for (int row = 0; row < GRID_SIZE; row++) {
        if (board[row][col] == num) {
            return true;
        }
    }
    return false;
}

// 检查数字num是否在3x3子网格中重复
bool isNumInSubgrid(const vector<vector<int>>& board, int startRow, int startCol, int num) {
    for (int row = 0; row < SUBGRID_SIZE; row++) {
        for (int col = 0; col < SUBGRID_SIZE; col++) {
            if (board[row + startRow][col + startCol] == num) {
                return true;
            }
        }
    }
    return false;
}

// 检查数字num是否可以放置在指定的位置
bool isNumValid(const vector<vector<int>>& board, int row, int col, int num) {
    return !isNumInRow(board, row, num) &&
        !isNumInCol(board, col, num) &&
        !isNumInSubgrid(board, row - row % SUBGRID_SIZE, col - col % SUBGRID_SIZE, num);
}

// 查找空白格的位置
bool findEmptyCell(const vector<vector<int>>& board, int& row, int& col) {
    for (row = 0; row < GRID_SIZE; row++) {
        for (col = 0; col < GRID_SIZE; col++) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// 求解数独问题
bool solveSudoku(vector<vector<int>>& board) {
    int row, col;
    //cout<<"回溯中..."<<endl;
    if (!findEmptyCell(board, row, col)) {
        return true;  // 找到解决方案
    }

    for (int num = 1; num <= GRID_SIZE; num++) {
        if (isNumValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board)) {

                return true;  // 找到解决方案
            }
            board[row][col] = 0;  // 回溯
        }
    }
    return false;  // 没有找到解决方案
}

// 生成数独终局
void generateSudoku(vector<vector<int>>& board) {

    // 清空数独盘面
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    random_device rd;//随机生成第一个数
    auto currentTime = chrono::system_clock::now();
    auto timestamp = chrono::duration_cast<chrono::milliseconds>(currentTime.time_since_epoch()).count();
    mt19937 rng(static_cast<unsigned int>(timestamp));
    uniform_int_distribution<int> dist(0, 8);
    int row = dist(rng);
    int col = dist(rng);
    uniform_int_distribution<int> num_dist(1, 9);
    int num = num_dist(rng);
    board[row][col] = num;

    solveSudoku(board);  // 解决数独问题来生成终盘
}

// 随机生成挖空的数独游戏
void generateSudokuGame(vector<vector<int>>& board, int numHoles) {
    random_device rd;
    auto currentTime = chrono::system_clock::now();
    auto timestamp = chrono::duration_cast<chrono::milliseconds>(currentTime.time_since_epoch()).count();

    mt19937 rng(static_cast<unsigned int>(timestamp));
    uniform_int_distribution<int> dist(0, 8);

    generateSudoku(board);

    int holes = 0;
    while (holes < numHoles) {
        int row = dist(rng);
        int col = dist(rng);

        if (board[row][col] != 0) {
            board[row][col] = 0;
            holes++;
        }
    }
}

// 随机生成挖空的数独游戏
void onlyone_generateSudokuGame(vector<vector<int>>& board, int numHoles) {
    random_device rd;
    auto currentTime = chrono::system_clock::now();
    auto timestamp = chrono::duration_cast<chrono::milliseconds>(currentTime.time_since_epoch()).count();

    mt19937 rng(static_cast<unsigned int>(timestamp));
    uniform_int_distribution<int> dist(0, 8);

    generateSudoku(board);

    int holes = 0;
    while (holes < numHoles) {
        int row = dist(rng);
        int col = dist(rng);

        if (board[row][col] != 0) {
            int temp = board[row][col];
            board[row][col] = 0;
            // 检查解的唯一性
            std::vector<std::vector<int>> tempBoard = board;
            int solutions = 0;
            for(int i=0;i<5;i++){
                solveSudoku(tempBoard);
                if(tempBoard[row][col]!=temp){//存在不唯一解，直接退出，恢复原挖空
                    board[row][col]=temp;
                    break ;
                }
            }
            if(board[row][col]==temp)//原挖空得到恢复
            {
                holes--;
                continue;
            }
            holes++;
        }
    }
}

// 保存数独盘面到文件
void saveSudokuToFile(const vector<vector<int>>& board, const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "无法打开文件：" << filename << endl;
        return;
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == 0) {
                file << "$ ";
            }
            else {
                file << board[i][j] << " ";
            }
        }
        file << endl;
    }
    file << "----apart----" << endl;  // 使用分隔符分隔不同数独

    file.close();
}

// 从文件中读取数独盘面
void readSudokuFromFile(vector<vector<vector<int>>>& boards, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "无法打开文件：" << filename << endl;
        return;
    }
    string line;
    int count = 0;
    //holenums[count]=0;
    vector<vector<int>> board;  // 用于存储当前数独盘面
    while (getline(file, line)) {
        if (line == "----apart----") {
            if (!board.empty()) {
                boards.push_back(board);  // 将当前数独盘面添加到总体存储中
                board.clear();  // 清空当前数独盘面
                count++;
                //holenums[count]=0;// 当前空格置零
            }

        }
        else {
            vector<int> row;
            istringstream iss(line); // 使用istringstream处理每一行数据
            char num;
            while (iss >> num) {
                if (num == '$') {
                    // 将空格字符转换为特定的数值表示（例如：-1）
                    row.push_back(0);
                    //holenums[count]++;
                }
                else {
                    row.push_back(num - '0');
                }
            }
            board.push_back(row);  // 将当前行添加到当前数独盘面
        }
    }

    if (!board.empty()) {
        boards.push_back(board);  // 添加最后一个数独盘面
    }
    file.close();

    // 打印读取到的数独盘面
    for (int i = 0; i < boards.size(); i++) {
        cout << "数独盘面 " << i + 1 << ":" << endl;
        printSudoku(boards[i]);
        cout << endl;
    }
}




int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 7) {
        cout << "使用方法：" << endl;
        cout << "生成数独终局：sudoku -c <终局数量> -o <输出文件路径>" << endl;
        cout << "生成数独游戏：sudoku -n <游戏数量> -r <挖空数量范围> -o <输出文件路径>" << endl;
        cout << "生成数独游戏：sudoku -n <游戏数量> -m <难度范围> -o <输出文件路径>" << endl;
        cout << "生成数独游戏：sudoku -n <游戏数量> -u -o <输出文件路径>" << endl;
        cout << "解决数独游戏：sudoku -s <输入文件路径> -o <输出文件路径>" << endl;
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        // 生成数独终局
        int puzzleCount = atoi(argv[2]);
        string outputFilename = argv[4];

        if (puzzleCount < 1 || puzzleCount > 1000000) {
            cout << "终局数量超出范围！请输入1-1000000之间的数。" << endl;
            return 1;
        }

        ofstream outputFile(outputFilename);
        if (!outputFile) {
            cout << "无法打开文件：" << outputFilename << endl;
            return 1;
        }

        for (int i = 0; i < puzzleCount; i++) {
            vector<vector<int>> board(GRID_SIZE, vector<int>(GRID_SIZE));
            generateSudoku(board);
            saveSudokuToFile(board, outputFilename);
        }

        outputFile.close();
        cout << "已生成数独终局，保存到文件：" << outputFilename << endl;
    }
    else if (strcmp(argv[1], "-n") == 0 && strcmp(argv[3], "-r") == 0 && argc <= 7) {
        // 生成数独游戏
        int gameCount = atoi(argv[2]);
        int minHoles = atoi(strtok(argv[4], "~"));
        int maxHoles = atoi(strtok(nullptr, "~"));

        string outputFilename = argv[6];

        if (gameCount < 1 || gameCount > 10000) {
            cout << "游戏数量超出范围！请输入1-10000之间的数。" << endl;
            return 1;
        }

        if (minHoles < MIN_HOLES || maxHoles > MAX_HOLES || minHoles > maxHoles) {
            cout << "挖空数量范围超出范围！请输入20-55之间的数，并确保最小值不大于最大值。" << endl;
            return 1;
        }

        ofstream outputFile(outputFilename);
        if (!outputFile) {
            cout << "无法打开文件：" << outputFilename << endl;
            return 1;
        }

        for (int i = 0; i < gameCount; i++) {
            vector<vector<int>> board(GRID_SIZE, vector<int>(GRID_SIZE));
            int numHoles = rand() % (maxHoles - minHoles + 1) + minHoles;
            generateSudokuGame(board, numHoles);
            saveSudokuToFile(board, outputFilename);
        }

        outputFile.close();
        cout << "已生成数独游戏，保存到文件：" << outputFilename << endl;
    }
    else if (strcmp(argv[1], "-n") == 0 && strcmp(argv[3], "-m") == 0 && argc <= 7) {
        int gameCount = atoi(argv[2]);
        int diff_m = atoi(argv[4]);

        string outputFilename = argv[6];
        if (gameCount < 1 || gameCount > 10000) {
            cout << "游戏数量超出范围！请输入1-10000之间的数。" << endl;
            return 1;
        }
        ofstream outputFile(outputFilename);
        if (!outputFile) {
            cout << "无法打开文件：" << outputFilename << endl;
            return 1;
        }
        int minHoles;
        int maxHoles;
        switch (diff_m)
        {
        case 1:
            minHoles = MIN_HOLES;
            maxHoles = 31;
            break;
        case 2:
            minHoles = 31;
            maxHoles = 43;
            break;
        case 3:
            minHoles = 43;
            maxHoles = MAX_HOLES;
            break;
        default:
            cout << "难度选择范围超出范围！请输入1-3之间的数。" << endl;
            return 1;
        }

        for (int i = 0; i < gameCount; i++) {
            vector<vector<int>> board(GRID_SIZE, vector<int>(GRID_SIZE));
            int numHoles = rand() % (maxHoles - minHoles + 1) + minHoles;
            generateSudokuGame(board, numHoles);
            vector<vector<int>> temp(GRID_SIZE, vector<int>(GRID_SIZE));
            temp = board;
            solveSudoku(temp);
            saveSudokuToFile(board, outputFilename);

        }
        outputFile.close();
        cout << "已生成数独游戏，保存到文件：" << outputFilename << endl;
    }
    else if (strcmp(argv[1], "-n") == 0 && strcmp(argv[3], "-u") == 0 ) {
        int gameCount = atoi(argv[2]);
        int minHoles = MIN_HOLES;
        int maxHoles = MAX_HOLES;

        string outputFilename = argv[5];

        if (gameCount < 1 || gameCount > 10000) {
            cout << "游戏数量超出范围！请输入1-10000之间的数。" << endl;
            return 1;
        }

        ofstream outputFile(outputFilename);
        if (!outputFile) {
            cout << "无法打开文件：" << outputFilename << endl;
            return 1;
        }

        for (int i = 0; i < gameCount; i++) {
            vector<vector<int>> board(GRID_SIZE, vector<int>(GRID_SIZE));
            int numHoles = rand() % (maxHoles - minHoles + 1) + minHoles;
            onlyone_generateSudokuGame(board, numHoles);
            saveSudokuToFile(board, outputFilename);
        }

        outputFile.close();
        cout << "已生成数独游戏，保存到文件：" << outputFilename << endl;
    }
    else if (strcmp(argv[1], "-s") == 0) {
        // 解决数独游戏
        string inputFilename = argv[2];
        string outputFilename = argv[4];

        vector<vector<vector<int>>> boards;
        cout << inputFilename;
        cout << "读取中..." << endl;
        //vector<int> holenums;
        readSudokuFromFile(boards, inputFilename);

        if (boards.empty()) {
            cout << "数据为空，读取数独盘面失败！" << endl;
            return 1;
        }
        cout << "解决中..." << endl;
        number = boards.size();
        outfile.open(outputFilename);

        for (int i = 0; i < number; i++) {
            outfile << i+1 << endl;
            sudoku(boards[i]);
        }
        cout << "已解决数独游戏，保存到文件：" << outputFilename << endl;
        outfile.close();
    }
    else {
        cout << "无效的命令参数！" << endl;
        return 1;
    }

    return 0;
}
