# Extracting MFI Using CLM
Extracting `MFI (Maximum Frequent Itemset)` is one of the problem in computer science. It is famously known as `Market Basket Analysis`. In this project I am using a Data Structure known as `CLM (Completely Linked Matrix)` to find MFI more efficiently than ever requiring less time and space. The current project works for extracting `3-FI (FI with 3 itemset length)` and the MFI from them. Further work is being done to enhance the scope to finding FI of greater itemset length.

## Getting Started
To be able to have this project work on your local machine, all you need is a C++ compiler such as [MinGW](https://www.mingw-w64.org/downloads/) which you can also download through [MSYS2](https://www.msys2.org/). After installing a compiler you can download a Code Editor like [VSC](https://code.visualstudio.com/download) or an IDE like [Clion](https://www.jetbrains.com/clion/download/#section=windows) for viewing the code and editing it.

### Installing 
You can simply add this project to your system using Git Clone or just downloading this project as a zip file and then extracting it.

## Running
Following are the few arguments to be provided when the program is run:
- `Transactions` : The transactions using which MFI are found
- `MinSup` : The minimum support of the transactions for finding MFI

### Example Run 
A simple example of a run having:
- `Transactions` : BCDE ABDE BCDE ABCDE DE C
- `MinSup` : 2

Input:
```
clm-miner -transactions "BCDE ABDE BCDE ABCDE DE C" -MinSup 2
```
Output:
```
Graph:

Node : Weight
A : 2
B : 4
C : 4
D : 5
E : 5

From : To : Additional information : weight
A : B : D E  : 1
A : D : E  : 2
A : E :  : 2
A : B : C D E  : 1
A : C : D E  : 1
B : C : D E  : 3
B : D : E  : 4
B : E :  : 4
C : D : E  : 3
C : E :  : 3
D : E :  : 5

CLM:

  A A B C D E B A B C D E C A B C D E D A B C D E E A B C D E
A 2 0 0 0 0 0 2 0 0 1 2 2 1 0 0 0 1 1 2 0 0 0 0 2 2 0 0 0 0 0
B 0 0 0 0 0 0 4 0 0 0 0 0 3 0 0 0 3 3 4 0 0 0 0 4 4 0 0 0 0 0
C 0 0 0 0 0 0 0 0 0 0 0 0 4 0 0 0 0 0 3 0 0 0 0 3 3 0 0 0 0 0
D 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 0 5 0 0 0 0 0
E 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 0


FIs : (minSup : 2)
A AB ABD ABE AD ADE AE B BC BCD BCE BD BDE BE C CD CDE CE D DE E

MFI : ABD ABE ADE BCD BCE BDE CDE
```

## Built With
- [MinGW](https://www.mingw-w64.org/) - The compiler used
- [CLion](https://www.jetbrains.com/clion/) - The IDE used
- [Qt 6](https://www.qt.io/product/qt6) - The GUI software

## Contributors
```
- Ubaid Ur Rehman (Graph, CLM, CLM-Miner, UI)
- Abdur Rahman Goraya (Alpha Tester)
- Course Instructor: Dr. Zahid Halim 
- Course Lab Instructor: Sir Usama Arshad
```

## Based On 
This project was based on the following paper:
> On the Efficient Representation of Datasets as Graphs to Mine Maximal Frequent Itemsets

by
- Zahid Halim, Senior Member, IEEE
- Omer Ali
- Muhammad Ghufran Khan