#include <iostream>
#include <random>
#include <string>
#include <iomanip>
#include "Node.h"
#include "Sort.h"
#include "stock_names.h"
using namespace std;

void prompt();

class InvalidInputException : public exception {
    public:
        const char* what() const noexcept override {
            return "Invalid input.";
    }
 };

class binaryStock 
{
    private:
    Node* head;

    public:
    binaryStock () {
        head = NULL;
    }

    void generateStocks(string name, int stock) {
        Node* newNode = new Node(name,  stock);

        if(head == NULL){
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void resetStocks() {
        Node* temp;
        while(head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
        head = NULL;
    }

    void display() {
        bool recordExists = false;
        int i = 1;
        Node *p = head;
            
            //check if there are records
            if(p!=NULL){
                recordExists = true;
            } else {
                cout << "No stock prices currently exists...\n";
                cout << "Returning to main...\n";
                prompt();
                return;
            }
    
        cout << "=========================================================\n";
        cout << setw(18) << "STOCK NAME" << setw(10) << " || " 
        << setw(20) << "STOCK PRICES"  << endl;
        cout << "=========================================================\n";
        p = head;
            
        while (p != NULL) {
            cout << left << "#" << setw(10) << i  
            << "|" << setw(25) << p->name  
            << setw(38) << p->stock  
            << endl;  
            p = p->next;
            i++;
        }
        prompt();
    }

    int randomNumb(int min, int max) {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<int> distribution(min, max);
        
        return distribution(gen);
    }

    void sortStockMerge() {
        if (head!=NULL) {
            cout << "===================================\n";
            cout << "            MERGE SORT             \n";
            cout << "===================================\n";
        }
        head = Sort::mergeSort(head);
    }

    void findStockBinary(int target) {
        if (head!=NULL) {
            cout << "===================================\n";
            cout << "          BINARY SEARCH            \n";
            cout << "===================================\n";
        }
        Sort::binarySearch(head, target);
    }

   

};


class GUI {
    public:

    void dSpace(){
        for (int i = 0; i < 57; i++){
            cout << "=";
        }
        cout << endl;
    }

    void cls() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void showGUI(){
        binaryStock bin;

        while(1) {
            char choice;

            cls();
            dSpace();
            cout << setw(40) << "HADJI STOCK SYSTEM\n";
		    dSpace();
		    cout <<"A. GENERATE STOCKS\n";
		    cout <<"B. SEARCH STOCK PRICE \n";
		    cout <<"C. VIEW ALL STOCKS PRICES\n";
            cout <<"D. SORT STOCK PRICES\n";
            cout <<"E. EXIT\n";
		    dSpace();
		    cout <<"Your Choice: ";

            while (true) {
                try {
                    cin >> choice;
    
                    if (cin.fail() || cin.peek() != '\n' || !isalpha(choice)) {
                        throw InvalidInputException();
                    }
                    break;
                } catch (const InvalidInputException &e) {
                    cout << e.what() << endl;
                    cin.ignore(10000, '\n');
                }
                cout << "Try again: ";
            }

            choice = toupper(choice);
            switch(choice) {
                case 'A': {
                    bin.resetStocks();
                    string input;
                    bool flag = true;
                    int a = 100, b = 200, N = 0;

                    cout << "Enter N Number of Generated Stock Prices: ";
                    while(flag) {
                        cin >> input;
                        N = checkValid(input);
                        if(N == -1){
                            cout << "Try again: ";
                            cin.clear();
                            cin.ignore(1000, '\n');
                        } else {
                            flag = false;
                        }
                    }

                    generateStockNames(N);
                    for (int i = 0; i < N; i++){
                        bin.generateStocks(stockNames[i], bin.randomNumb(a,b));
                    }

                    cout << "Stock prices generated\n";
                    cleanupStockNames();
                    x:
                    y:
                    prompt();
                    break;
                }
                case 'B': {
                    string input;
                    int target; //change to string for error  handling
                    cout << "ENTER TARGET STOCK PRICE: ";
                    cin >> input;

                    target = checkValid(input);
                    if(target == -1){
                        prompt();
                        goto z;
                    }

                    bin.sortStockMerge();
                    bin.findStockBinary(target);
                    prompt();
                    z:
                    break;
                }
                case 'C': {
                    bin.display();
                    break;
                }
                case 'D': {
                    bin.sortStockMerge();
                    prompt();
                    break;
                }
                case 'E': {
                    cout <<"Thank you! Exiting...\n";
                    return;
                    break;
                }
                default: {
                    cout << "Please Enter letters A-E\n";
                    prompt();
                }
            }
        }

    }

    int checkValid(const string& input) { //input validity checking
        bool checkValid = false;
        try { 
        for(char c : input) {
            if(!isdigit(c)) {
                throw InvalidInputException();
            }
        }
            return stoi(input);
        } catch (const exception& e) {
            cout << e.what() << endl;
            return -1;
        }
    }
};

int main()
{
    GUI prog;

    prog.showGUI();
    return 0;
}


void prompt() {
    cout <<"\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    cout << resetiosflags(ios::adjustfield | ios::basefield | ios::floatfield); //reset setw
}
