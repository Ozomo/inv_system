#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void clearing_vector_int(vector <int>& vec) { //ready
    while(vec.size() > 0){
        vec.pop_back();
    }
}

void clearing_vector_string(vector <string>& vec) { //ready
    while(vec.size() >0){
        vec.pop_back();
    }
}

void sort(vector <int>& inventory, vector <string>& item_names) { //ready
    for (int i = 0; i < inventory.size(); i++) {
        for (int j = 0; j < inventory.size() - i - 1; j++) {
            if (inventory[j] > inventory[j + 1]) {
                swap(inventory[j], inventory[j + 1]);
                swap(item_names[j], item_names[j + 1]);
            }
        }
    }
}

void add_item(vector <int>& inventory, vector <string>& item_names, int item, string name) {
    for(int i = 0; i < inventory.size(); i++){
        if(inventory[i] == item){
            item_names[i] = name;
            return;
        }
    }
    inventory.push_back(item);
    item_names.push_back(name);
}

void show_items(vector <int>& inventory, vector <string>& item_names) { //ready
    sort(inventory, item_names);
    cout << "Items in data file:" << endl;
    for(int i = 0; i < inventory.size(); i++){
        cout << "Item: " << inventory[i] << " | Name: " << item_names[i] << endl;
    }
}

void reading(vector <int>& inventory, vector <string>& item_names){
    fstream file;
    file.open("config\\id_name_data.txt", ios::in);

    if(file.fail()){
        return;
    }

    clearing_vector_int(inventory);
    clearing_vector_string(item_names);

    string line;
    int item;
    while(true){
        file>>line;
        if(line == ""){
            file.close();
            return;
        }   
        item = stoi(line);
        file>>line;
        item_names.push_back(line);
        inventory.push_back(item);
        line = "";
    }
}

void writing(vector <int>& inventory, vector <string> item_names){ //ready
    fstream file;
    file.open("config\\id_name_data.txt", ios::out | ios::trunc);

    if(file.fail()){
        return;
    }

    for(int i = 0; i < inventory.size(); i++){
        file<<inventory[i]<<endl;
        file<<item_names[i]<<endl;
    }
    file.close();
}

void menu(){
    cout<<"Inventory System - id_name_update"<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<"1. Add / change name"<<endl;
    cout<<"2. Show list"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"-----------------------------"<<endl;
}
int main(){
    vector <string> item_names = {};
    vector <int> inventory = {};

    reading(inventory, item_names);

    menu();
    again:
    cout<<"Enter your choice: ";

    int choice;
    cin>>choice;

    switch(choice){
        case 1:{
            system("cls");
            menu();
            int item_to_add;
            string name;
            cout<<"Enter item ID to add / change: ";
            cin>>item_to_add;
            cout<<"Enter name for the item: ";
            cin>>name;
            add_item(inventory, item_names, item_to_add, name);
            
            system("cls");
            menu();
            cout<<"Item ["<<item_to_add<<"] added successfully."<<endl;
            writing(inventory, item_names);
            break;
        }
        case 2:{
            system("cls");
            menu();
            show_items(inventory, item_names);
            break;
        }
        case 3:{
            return 0;
            break;
        }
        default:{
            system("cls");
            menu();
            cout<<"Invalid choice."<<endl;
            break;
        }
    }
    cout<<"-----------------------------"<<endl;
    goto again;
    return 0;
}