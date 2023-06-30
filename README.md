# sudoku
一个简单的生成数独和求解数独的C++控制台程序。
运行环境为64-bit windows10。
使用以下命令执行程序：
\n
\n生成指定数量的数独终局到指定文件中，不同数独用分割符分隔，数量范围为1-1000000：.\sudoku.exe -c <终局数量> -o <输出文件路径> 
\n示例：
\n.\sudoku.exe -c 20 -o final.txt
\n
\n按照指定挖空范围生成数独游戏，空格范围为20-55，需要同时指定范围最小值和最大值，用'\~'连接：.\sudoku.exe -n <游戏数量> -r <挖空数量范围> -o <输出文件路径> 
\n示例：
\n.\sudoku.exe -n 20 -r 24~30 -o hole_game.txt
\n
\n按照指定难度生成数独游戏，难度范围为1-3，其实是按挖的空格数来判断难度的，没有实现更复杂的难度判定方法：.\sudoku.exe -n <游戏数量> -m <难度范围> -o <输出文件路径> 
\n示例：
\n.\sudoku.exe -n 10 -m 2 -o diff_game.txt
\n
\n生成只有唯一解的数独游戏，每次挖空时对数独求解，有重复解则放弃该空另挖：sudoku -n <游戏数量> -u -o <输出文件路径> 
\n示例：
\n.\sudoku.exe -n 50 -u  -o unique_game.txt
\n
\n解决数独游戏：.\sudoku.exe -s <输入文件路径> -o <输出文件路径>
\n示例：
\n.\sudoku.exe -s game.txt -o result.txt

