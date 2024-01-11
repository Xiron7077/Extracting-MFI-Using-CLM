#include <iostream>
#include <vector>
#include "../include/node.h"
#include "../include/edge.h"
#include "../include/combination.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

using namespace std;

//Graph for storing transactions and items
class Graph {
private:
    //Vector to store all the get_nodes
    vector<Node*> node_vector;

public:
    //Default constructor
    Graph() = default;

    //Returns the number of nodes
    int get_size(){
        return node_vector.size();
    }

    //Returns the node vector
    vector<Node*> get_nodes(){
        return node_vector;
    }

    //Check if node is present in graph
    bool is_present(const char& data) {
        for(Node* node : node_vector) {
            if(node->data == data) {
                return true;
            }
        }
        return false;
    }

    void sort_graph(){
        int size = node_vector.size();

        for(int i = 0; i < size - 1; i++){
            for(int j = 0; j < size - i - 1; j++){
                if(node_vector.at(j)->data > node_vector.at(j+1)->data){
                    Node* node = node_vector.at(j);
                    node_vector.at(j) = node_vector.at(j+1);
                    node_vector.at(j+1) = node;
                }
            }
        }
    }


    //Add node to graph
    Node* add_node(const char& data, int weight = 0) {
        //Check if node is already created
        if(is_present(data)){
            cout<<"\nNode is already created."<<endl;
            return new Node;
        }
        //Create new node
        Node* new_node = new Node;

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
    static void add_edge(Node* first_node, Node* second_node, vector<Node*>neighbours){
        //Check if no edges for first node are present
        if(first_node->edges.empty()){
            //Creates a new edge and adds to first node
            Edge* new_edge = new Edge;
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
                        if(equal) {
                            //Adds weight if it's the same edge
                            edge->weight ++;
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
            Edge* new_edge = new Edge;
            new_edge->to = second_node;
            new_edge->weight = 1;
            new_edge->neighbours = neighbours;
            first_node->edges.push_back(new_edge);
        }
    }

    //Add transaction to the graph
    void add_transaction(const string& transaction){
        //Check if transaction consists of only one node
        if(transaction.size() == 1){
            if(is_present(transaction[0])){
                for(Node* node : node_vector){
                    if(transaction[0] == node->data){
                        node->weight ++;
                        return;
                    }
                }
            } else {
                add_node(transaction[0]);
                return;
            }
        }

        //Transaction vector to store all the get_nodes to create
        vector<Node*> transaction_vector;

        //Go through all node and create those not present and add them to vector
        for(char c : transaction){
            //Check if the node is already present
            if(!is_present(c)){
                //Create a new node and add it
                transaction_vector.push_back(add_node(c, 1));
            } else {
                //Find the node and add to the vector
                for(Node* node : node_vector){
                    if(node->data == c){
                        node->weight ++;
                        transaction_vector.push_back(node);
                        break;
                    }
                }
            }
        }

        //Nested for loop to iterate through the transaction and add all the edges
        for(int i  = 0; i < transaction_vector.size() - 1; i++){
            for(int j = i+1; j < transaction_vector.size(); j++){
                //Create a neighbour vector
                vector<Node*> neighbours;

                //Adds all the remaining get_nodes to neighbour vector
                for(int k = j+1; k < transaction_vector.size(); k++){
                    neighbours.push_back(transaction_vector.at(k));
                }

                //Adds the edge between the get_nodes
                add_edge(transaction_vector.at(i), transaction_vector.at(j), neighbours);
            }
        }

        findAllCombinations(transaction);
    }

    string graph_node(){
        string node_info;
        node_info += "Graph\n";

        node_info += "\nNode : Weight";
        for(Node* node : node_vector){
            node_info += "\n";
            node_info += node->data;
            node_info += " : ";
            node_info += to_string(node->weight);
        }

        return node_info;
    }

    string displayGraph(){
        string graph;
        graph += "From : To : Additional information : weight";
        for(Node* node : node_vector){
            for(Edge* edge : node->edges){
                graph += "\n";
                graph += node->data;
                graph += " : ";
                graph += edge->to->data;
                graph += " : ";
                for(Node* neighbour : edge->neighbours){
                    graph += neighbour->data;
                    graph += " ";
                }
                graph += " : ";
                graph += to_string(edge->weight);
            }
        }

        return graph;
    }
};

// Completely linked Matrix
class CLM{
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
    explicit CLM(int size){
        row = size;
        column = (size + 1) * size;

        // Initializes all cells with 0
        for(int i = 0; i < row; i++){
            clm_array.emplace_back();
            for(int j = 0; j < column; j++){
                clm_array.at(i).emplace_back(0);
            }
        }
    }

    // Inputs the values of get_nodes and edge support count
    void input_graph(Graph& graph){
        vector<Node*> node_vector = graph.get_nodes();

        // Nested for loop for input of all values
        for(Node* node : node_vector){
            // Finds position of column of 1-itemsets and adds Sup
            int node_position = node->data - 'A';
            clm_array[node_position][(node_position * 6)] = node->weight;
            for(Edge* edge : node->edges){
                // Finds position of column of 2-itemsets and adds Sup
                int to_position = edge->to->data - 'A';
                if(clm_array[node_position][(to_position * 6)] != 0){
                    clm_array[node_position][(to_position * 6)] ++;
                } else {
                    clm_array[node_position][(to_position * 6)] = edge->weight;
                }

                // Creates combinations possible
                string combination;
                combination += node->data;
                combination += edge->to->data;

                // Counter for the loop
                int counter = graph.get_size() - (edge->to->data - 'A') - 1;

                // Adds the Sup for 3-itemsets
                for(pair<string, int>* pairs : combinations){
                    if(pairs->first.size() == 3){
                        for(int i = 0; i < counter ; i++){
                            string itemset = combination;
                            int third_position = (edge->to->data + i + 1) - 'A' + 1;
                            itemset += edge->to->data + i + 1;
                            if(pairs->first == itemset){
                                clm_array[node_position][(to_position * 6) + third_position] = pairs->second;
                            }
                        }
                    }
                }
            }
        }
    }

    vector<string> find_FI(int minSup){
        vector<string> FIs;
        string fi;
        // Loop to check all the sup
        for(int i = 0; i < row; i++){
            char first = 'A' + i;
            fi += first;
            for(int j = 0; j < column; j++){
                if(clm_array[i][j] >= minSup){
                    char second = 'A' + (j/6);
                    if(first == second){
                        // Stores 1-FI
                        FIs.push_back(fi);
                        continue;
                    }
                    fi += second;
                    if((j % 6) == 0){
                        // Stores 2-FI
                        FIs.push_back(fi);
                        fi = first;
                    } else {
                        // Stores 3-FI
                        char third = 'A' + (j % 6) - 1;
                        fi += third;
                        FIs.push_back(fi);
                        fi = first;
                    }
                }
            }
            fi.clear();
        }
        return FIs;
    }

    string show_fi(const vector<string>& FIs, int minSup){

        // Prints all the FIs
        string fi_string;
        fi_string += "FIs : (minSup : ";
        fi_string += to_string(minSup);
        fi_string += ")\n";
        for(const string& FI : FIs){
            fi_string += FI;
            fi_string += " ";
        }
        fi_string += "\n\n";

        // Checks the largest of all the FIs
        int largest = 0;
        for(const string& FI : FIs){
            if(largest == 0){
                largest = FI.size();
            } else {
                if(FI.size() > largest){
                    largest = FI.size();
                }
            }
        }

        // Prints all the MFI
        fi_string += "MFI : ";
        for(const string& FI : FIs){
            if(FI.size() == largest){
                fi_string += FI;
                fi_string += " ";
            }
        }

        return fi_string;
    }

    string print(vector<Node*> nodes){
        string clm;
        clm += "CLM:\n\n  ";
        for(Node* node1 : nodes) {
            clm += node1->data;
            clm += " ";
            for (Node *node2: nodes) {
                clm += node2->data;
                clm += " ";
            }
        }

        clm += "\n";
        for (int i = 0; i < row; i++) {
            clm += nodes.at(i)->data;
            clm += " ";
            for (int j = 0; j < column; j++) {
                clm += to_string(clm_array[i][j]);
                clm += " ";
            }
            clm += "\n";
        }

        return clm;
    }
};

int main(int argc, char *argv[]) {
    Graph graph;

    CLM clm(graph.get_size());
    clm.input_graph(graph);

    vector<string> fi = clm.find_FI(3);

    QApplication app(argc, argv);

    QWidget window;

    QWidget clm_window;

    QWidget graph_window;

    QWidget transaction;
    QWidget graph_widget;

    QVBoxLayout* layout = new QVBoxLayout();

    QVBoxLayout* layout1 = new QVBoxLayout();
    QHBoxLayout* layout2 = new QHBoxLayout();
    QVBoxLayout* layout3 = new QVBoxLayout();
    QHBoxLayout* layout4 = new QHBoxLayout();

    QLabel* label1 = new QLabel("Add Transactions:", &transaction);
    QLabel* label2 = new QLabel(QString().fromStdString(graph.graph_node()), &graph_widget);
    QLabel* label3 = new QLabel(QString().fromStdString(graph.displayGraph()), &graph_widget);
    QLabel* label4 = new QLabel(QString().fromStdString(clm.print(graph.get_nodes())), &clm_window);
    QLabel* label5 = new QLabel(QString().fromStdString(clm.show_fi(fi, 3)), &clm_window);

    QLineEdit* lineEdit1 = new QLineEdit(&transaction);

    QPushButton* pushButton1 = new QPushButton("Add", &transaction);

    layout1->addWidget(label1);
    layout1->addWidget(lineEdit1);
    layout1->addWidget(pushButton1);

    layout2->addWidget(label2);
    layout2->addWidget(label3);

    layout3->addWidget(label4);
    layout3->addWidget(label5);

    layout4->addWidget(&transaction);
    layout4->addWidget(&graph_widget);

    transaction.setLayout(layout1);
    graph_widget.setLayout(layout2);
    graph_window.setLayout(layout4);

    clm_window.setLayout(layout3);

    layout->addWidget(&graph_window);
    layout->addWidget(&clm_window);

    QObject::connect(pushButton1, &QPushButton::clicked, [&]() {
        graph.add_transaction(lineEdit1->text().toStdString());
        label2->setText(QString().fromStdString(graph.graph_node()));
        label3->setText(QString().fromStdString(graph.displayGraph()));
        label4->setText(QString().fromStdString(clm.print(graph.get_nodes())));
        label5->setText(QString().fromStdString(clm.show_fi(fi, 3)));
    });

    window.setLayout(layout);

    window.show();

    return app.exec();
}
