# Dijkstra
Implementation of the Dijkstra algorithm to traverse the graph and return the cost of the path between two given points and the number of points visited.
This algorithm uses adjacency list.

# Problem

## Entry
The first line will contain a number T (1 ≤ T ≤ 100), indicating the number of cases of
test. For each test case, the first line will contain an integer N (1 ≤ N ≤ 20,000),
indicating the number of points that can be visited, considering the point of origin, and M (1 ≤ M ≤ 100,000), indicating the total number of edges. Then there are M lines, each with three integers, C1, C2 and C3, separated
by spaces, with 1 ≤ C1, C2 ≤ 20,000 and 1 ≤ C3 ≤ 1,000, indicating the cost of C3 to go from point C1 to point C2. The next line will contain two integers S and K, indicating the origin point and the destination point, respectively.

## Return
For each test case, print two integers on a line: the total cost of the journey from the origin point to the destination point and the maximum number of points visited

## Input model
2 <br>
4 5 <br>
1 2 1<br>
1 3 3<br>
1 4 2<br>
2 3 2<br>
3 4 2<br>
1 3<br>
5 7<br>
1 2 1<br>
1 4 4<br>
1 5 3<br>
2 3 2<br>
2 4 4<br>
3 4 3<br>
4 5 2<br>
1 1

## Output model
3 2<br>
0 0

# How to run

In terminal, do

**To compile your code, use**:
* gcc -o <name_of_output> dijkstra.c

**To execute, use**:
* ./<name_of_output> < entrada

> Change te sentence '<name_of_output>' to another name
