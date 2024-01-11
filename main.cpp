#include <iostream>
#include <vector>
#include "include/node.h"
#include "include/edge.h"
#include "include/combination.h"

using namespace std;

//Graph for storing transactions and items
class Graph {
private:
    //Vector to store all the get_nodes
    vector<Node *> node_vector;

public:
    //Default constructor
    Graph() = default;

    //Returns the number of nodes
    int get_size() {
        return node_vector.size();
    }

    //Returns the node vector
    vector<Node *> get_nodes() {
        return node_vector;
    }

    //Check if node is present in graph
    bool is_present(const char &data) {
        for (Node *node: node_vector) {
            if (node->data == data) {
                return true;
            }
        }
        return false;
    }

    void sort_graph() {
        int size = node_vector.size();

        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (node_vector.at(j)->data > node_vector.at(j + 1)->data) {
                    Node *node = node_vector.at(j);
                    node_vector.at(j) = node_vector.at(j + 1);
                    node_vector.at(j + 1) = node;
                }
            }
        }
    }

    //Add node to graph
    Node *add_node(const char &data, int weight = 0) {
        //Check if node is already created
        if (is_present(data)) {
            cout << "\nNode is already created." << endl;
            return new Node;
        }
        //Create new node
        Node *new_node = new Node;

        //Assigning values
        new_node->data = data;
        new_node->weight = weight;

        //Add new node to node array
        node_vector.push_back(new_node);

        //Sort graph in ascending order
        sort_graph();

        //Returns the node created
        return new_node;
    }

    //Add an edge between 2 get_nodes
    static void add_edge(Node *first_node, Node *second_node, vector<Node *> neighbours) {
        //Check if no edges for first node are present
        if (first_node->edges.empty()) {
            //Creates a new edge and adds to first node
            Edge *new_edge = new Edge;
            new_edge->to = second_node;
            new_edge->weight = 1;
            new_edge->neighbours = neighbours;
            first_node->edges.push_back(new_edge);
            //Ends the function
            return;
        } else {
            //Check through all edges to find if edge already exists
            for (Edge *edge: first_node->edges) {
                if (edge->to->data == second_node->data) {
                    //Check if edge additional information is same
                    if (edge->neighbours.size() == neighbours.size()) {
                        bool equal = true;
                        for (int i = 0; i < neighbours.size(); i++) {
                            if (neighbours.at(i)->data != edge->neighbours.at(i)->data) {
                                equal = false;
                                break;
                            }
                        }
                        if (equal) {
                            //Adds weight if it's the same edge
                            edge->weight++;
                            return;
                        } else {
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }

            //Add a new edge to the first node
            Edge *new_edge = new Edge;
            new_edge->to = second_node;
            new_edge->weight = 1;
            new_edge->neighbours = neighbours;
            first_node->edges.push_back(new_edge);
        }
    }

    //Add transaction to the graph
    void add_transaction(const string &transaction) {
        //Check if transaction consists of only one node
        if (transaction.size() == 1) {
            if (is_present(transaction[0])) {
                for (Node *node: node_vector) {
                    if (transaction[0] == node->data) {
                        node->weight++;
                        return;
                    }
                }
            } else {
                add_node(transaction[0]);
                return;
            }
        }

        //Transaction vector to store all the get_nodes to create
        vector<Node *> transaction_vector;

        //Go through all node and create those not present and add them to vector
        for (char c: transaction) {
            //Check if the node is already present
            if (!is_present(c)) {
                //Create a new node and add it
                transaction_vector.push_back(add_node(c, 1));
            } else {
                //Find the node and add to the vector
                for (Node *node: node_vector) {
                    if (node->data == c) {
                        node->weight++;
                        transaction_vector.push_back(node);
                        break;
                    }
                }
            }
        }

        //Nested for loop to iterate through the transaction and add all the edges
        for (int i = 0; i < transaction_vector.size() - 1; i++) {
            for (int j = i + 1; j < transaction_vector.size(); j++) {
                //Create a neighbour vector
                vector<Node *> neighbours;

                //Adds all the remaining get_nodes to neighbour vector
                for (int k = j + 1; k < transaction_vector.size(); k++) {
                    neighbours.push_back(transaction_vector.at(k));
                }

                //Adds the edge between the get_nodes
                add_edge(transaction_vector.at(i), transaction_vector.at(j), neighbours);
            }
        }

        findAllCombinations(transaction);
    }

    void displayGraph() {
        cout << "\t\tGraph\n";

        //Prints the get_nodes in graph
        cout << "\nNode : Weight";
        for (Node *node: node_vector) {
            cout << "\n" << node->data << " : " << node->weight;
        }

        //Prints the edges in graph
        cout << "\n\nFrom : To : Additional information : weight";
        for (Node *node: node_vector) {
            for (Edge *edge: node->edges) {
                cout << "\n" << node->data << " : " << edge->to->data << " : ";
                for (Node *neighbour: edge->neighbours) {
                    cout << neighbour->data << " ";
                }
                cout << " : " << edge->weight;
            }
        }
    }
};

// Completely linked Matrix
class CLM {
private:
    // Row and column of matrix
    int row{};
    int column{};

    // CLM matrix
    vector<vector<int>> clm_array;

public:
    // Default constructor
    CLM() = default;

    // Constructor to initialize with a given size
    explicit CLM(int size) {
        row = size;
        column = (size + 1) * size;

        // Initializes all cells with 0
        for (int i = 0; i < row; i++) {
            clm_array.emplace_back();
            for (int j = 0; j < column; j++) {
                clm_array.at(i).emplace_back(0);
            }
        }
    }

    // Inputs the values of get_nodes and edge support count
    void input_graph(Graph &graph) {
        vector<Node *> node_vector = graph.get_nodes();
        int matrix = graph.get_size() + 1;

        // Nested for loop for input of all values
        for (Node *node: node_vector) {
            // Finds position of column of 1-itemsets and adds Sup
            int node_position = node->data - 'A';
            clm_array[node_position][(node_position * matrix)] = node->weight;
            for (Edge *edge: node->edges) {
                // Finds position of column of 2-itemsets and adds Sup
                int to_position = edge->to->data - 'A';
                if (clm_array[node_position][(to_position * matrix)] != 0) {
                    clm_array[node_position][(to_position * matrix)]++;
                } else {
                    clm_array[node_position][(to_position * matrix)] = edge->weight;
                }

                // Creates combinations possible
                string combination;
                combination += node->data;
                combination += edge->to->data;

                // Counter for the loop
                int counter = graph.get_size() - (edge->to->data - 'A') - 1;

                // Adds the Sup for 3-itemsets
                for (pair<string, int> *pairs: combinations) {
                    if (pairs->first.size() == 3) {
                        for (int i = 0; i < counter; i++) {
                            string itemset = combination;
                            int third_position = (edge->to->data + i + 1) - 'A' + 1;
                            itemset += edge->to->data + i + 1;
                            if (pairs->first == itemset) {
                                clm_array[node_position][(to_position * matrix) + third_position] = pairs->second;
                            }
                        }
                    }
                }
            }
        }
    }

    void find_FI(int minSup, int matrix) {
        vector<string> FIs;
        string fi;
        // Loop to check all the sup
        for (int i = 0; i < row; i++) {
            char first = 'A' + i;
            fi += first;
            for (int j = 0; j < column; j++) {
                if (clm_array[i][j] >= minSup) {
                    char second = 'A' + (j / matrix);
                    if (first == second) {
                        // Stores 1-FI
                        FIs.push_back(fi);
                        continue;
                    }
                    fi += second;
                    if ((j % matrix) == 0) {
                        // Stores 2-FI
                        FIs.push_back(fi);
                        fi = first;
                    } else {
                        // Stores 3-FI
                        char third = 'A' + (j % matrix) - 1;
                        fi += third;
                        FIs.push_back(fi);
                        fi = first;
                    }
                }
            }
            fi.clear();
        }

        // Prints all the FIs
        cout << "\n\nFIs : (minSup : " << minSup << ")" << endl;
        for (const string &FI: FIs) {
            cout << FI << " ";
        }
        cout << endl << endl;

        // Checks the largest of all the FIs
        int largest = 0;
        cout << "MFI : ";
        for (const string &FI: FIs) {
            if (largest == 0) {
                largest = FI.size();
            } else {
                if (FI.size() > largest) {
                    largest = FI.size();
                }
            }
        }

        // Prints all the MFI
        for (const string &FI: FIs) {
            if (FI.size() == largest) {
                cout << FI << " ";
            }
        }
        cout << endl;
    }

    void print(vector<Node *> nodes) {
        cout << "\n\nCLM:\n\n";
        cout << "  ";
        for (Node *node1: nodes) {
            cout << node1->data << " ";
            for (Node *node2: nodes) {
                cout << node2->data << " ";
            }
        }

        cout << endl;
        for (int i = 0; i < row; i++) {
            cout << nodes.at(i)->data << " ";
            for (int j = 0; j < column; j++) {
                cout << clm_array[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph;

    graph.add_transaction("BCDE");
    graph.add_transaction("ABDE");
    graph.add_transaction("BCDE");
    graph.add_transaction("ABCDE");
    graph.add_transaction("DE");
    graph.add_transaction("C");

    graph.displayGraph();

    CLM clm(graph.get_size());

    clm.input_graph(graph);

    clm.print(graph.get_nodes());

    clm.find_FI(1, graph.get_size() + 1);

    cout << endl;
    system("pause");
    return 0;
}
