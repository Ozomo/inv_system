#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <filesystem>
using namespace std;

void file_exists_check(string filename) { //ready
    ifstream file(filename+".txt");
    if (!file) {
        ofstream create_file(filename+".txt");
        create_file.close();
    }
    file.close();
}

void sort(vector <vector<int>>& inventory, vector <string>& item_names) { //ready
    for (int i = 0; i < inventory.size(); i++) {
        for (int j = 0; j < inventory.size() - i - 1; j++) {
            if (inventory[j][0] > inventory[j + 1][0]) {
                swap(inventory[j], inventory[j + 1]);
                swap(item_names[j], item_names[j + 1]);
            }
        }
    }
}

void clearing_vector_int(vector <vector<int>>& vec) { //ready
    while(vec.size() > 0){
        vec.pop_back();
    }
}

void clearing_vector_string(vector <string>& vec) { //ready
    while(vec.size() >0){
        vec.pop_back();
    }
}

bool is_there_already(vector <vector<int>>& inventory, int item) { //ready
    for(int i = 0; i< inventory.size(); i++){
        if(item == inventory[i][0]){
            return true;
        }
    }
    return false;
}

void add_item(vector <vector<int>>& inventory, vector <string>& item_names, int item) { //ready
    if(is_there_already(inventory, item)){
        for(int i = 0; i < inventory.size(); i++){
            if(inventory[i][0] == item){
                inventory[i][1]++;
                break;
            }
        }
    } else {
        item_names.push_back("Unnamed Item");
        inventory.push_back({item, 1});
    }
}

void add_name(vector <vector<int>>& inventory, vector <string>& item_names, int item, string name) { //ready
    if(!is_there_already(inventory, item)){ //check if item exists
        cout<<"Item does not exist in inventory."<<endl;
        return;
    }

    for(int i = 0; i < inventory.size(); i++){
        if(inventory[i][0] == item){
            if(i < item_names.size()){
                item_names[i] = name;
            } else {
                item_names.push_back(name);
            }
            cout<<"Name ["<<name<<"] assigned to item ["<<item<<"]."<<endl;
            return;
        }
    }

}

void remove_quantity(vector <vector<int>>& inventory, int item) { //ready
    for(int i = 0; i < inventory.size(); i++){
        if(inventory[i][0] == item && inventory[i][1] > 0){
            inventory[i][1]--;
            cout<<"Quantity of item ["<<item<<"] decreased by one."<<endl;
            return;
        } else if (inventory[i][0] == item && inventory[i][1] == 0){
            cout<<"Can't decrease quantity further."<<endl;
            return;
        }
    }
    cout<<"There is no such item in inventory."<<endl;
    return;
}

void remove_item(vector <vector<int>>& inventory, vector <string>& item_names ,int item) { //ready
    if(!is_there_already(inventory, item)){
        cout<<"There is no such item in inventory."<<endl;
        return;
    }

    vector <vector<int>> var_inv = {};
    vector <string> var_names = {};
    for(int i = inventory.size() - 1; i >= 0; i--){
        if(inventory[i][0] == item){
            inventory.pop_back();
            item_names.pop_back();
            while(var_inv.size() > 0){
                inventory.push_back(var_inv[var_inv.size() - 1]);
                item_names.push_back(var_names[var_names.size() - 1]);
                var_inv.pop_back();  
                var_names.pop_back();
            }
            cout<<"Whole item ["<<item<<"] removed successfully."<<endl;
            return;
        } else {
            var_inv.push_back(inventory[inventory.size() - 1]);
            var_names.push_back(item_names[item_names.size() - 1]);
            inventory.pop_back();
            item_names.pop_back();
        }   
    }
}

void show_items(vector <vector<int>>& inventory, vector <string>& item_names) { //ready
    sort(inventory, item_names);
    cout << "Items in inventory:" << endl;
    for(int i = 0; i < inventory.size(); i++){
        cout << "Item: " << inventory[i][0] << " | Name: " << item_names[i] <<" | Quantity: " << inventory[i][1] << endl;
    }
}

void reading(vector <vector<int>>& inventory, vector <string>& item_names){ //ready
    fstream file;
    file.open("inventory.txt", ios::in);

    if(file.fail()){
        return;
    }

    clearing_vector_int(inventory);
    clearing_vector_string(item_names);

    string line;
    int item;
    int qty;
    while(true){
        file>>line;
        if(line == ""){
            file.close();
            return;
        }   
        item = stoi(line);
        file>>line;
        item_names.push_back(line);
        file>>line;
        qty = stoi(line);
        inventory.push_back({item, qty});
        line = "";
    }
}

void writing(vector <vector<int>>& inventory, vector <string> item_names){ //ready
    fstream file;
    file.open("inventory.txt", ios::out | ios::trunc);

    for(int i = 0; i < inventory.size(); i++){
        file<<inventory[i][0]<<endl;
        file<<item_names[i]<<endl;
        file<<inventory[i][1]<<endl;
    }
    file.close();
}

void update_names(vector <vector<int>>& inventory, vector <string>& item_names){ //ready

    fstream file;
    file.open("config\\id_name_data.txt", ios::in);
    if(file.fail()){
            cout<<"No names data file found. Skipping name update."<<endl;
    }

    string line;
    int item;

    while(true){
        file>>line;
        if(line == ""){
            file.close();
            return;
        }
        item = stoi(line);
        for(int i = 0; i < inventory.size(); i++){
            if(inventory[i][0] == item){
                file>>line;
                item_names[i] = line;
                line = "";
                break;
            }
            if(i == inventory.size() - 1){
                file>>line;
                line = "";
            }
        }
    }
}

void menu(){ //ready
    cout<<"Inventory System"<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<"1. Fast Add Item"<<endl;
    cout<<"2. Add Item"<<endl;
    cout<<"3. Name Item"<<endl;
    cout<<"4. Remove Quantity"<<endl;
    cout<<"5. Remove Item"<<endl;
    cout<<"6. Show Items"<<endl;
    cout<<"7. Exit"<<endl;
    cout<<"-----------------------------"<<endl;
}

int main(){
    vector <vector<int>> inventory = {};
    vector <string> item_names = {};

    menu();
    
    system("mkdir config 2> nul"); //create config folder
    
    file_exists_check("config\\id_name_data"); //create config file if not exists
    file_exists_check("inventory"); //create inventory file if not exists
    
    reading(inventory, item_names); //read existing inventory from file

    update_names(inventory, item_names); //update names from config file

    again:
    cout<<"Enter your choice: ";

    int choice;
    cin>>choice;

    switch(choice){
        case 1:{
            system("cls");
            menu();
            int item_to_add;
            cout<<"Enter item ID to add (type 0 for repeating, then 0 to stop): ";
            cin>>item_to_add;
            if(item_to_add == 0){
                item_to_add = -1;
                while(item_to_add != 0){
                cin>>item_to_add;
                add_item(inventory, item_names, item_to_add);
                }
                break;
            } 
            else if (item_to_add != 0){
                add_item(inventory, item_names,item_to_add);
            }
            system("cls");
            menu();
            cout<<"Item ["<<item_to_add<<"] added successfully."<<endl;
            writing(inventory, item_names);
            break;
        }
        case 2:{
            system("cls");
            menu();
            int item_to_add;
            int qty;
            cout<<"Enter item ID to add: ";
            cin>>item_to_add;
            cout<<"Enter quantity to add: ";
            cin>>qty;
            for(int i = 0; i < qty; i++){
                add_item(inventory, item_names, item_to_add);
            }
            system("cls");
            menu();
            cout<<"Item ["<<item_to_add<<"] added "<<qty<<" times successfully."<<endl;
            writing(inventory, item_names);
            break;
        }
        case 3:{
            system("cls");
            menu();
            cout<<"Enter item ID to name it: ";
            int item;
            cin>>item;
            cout<<"Enter name for the item: ";
            string name;
            cin.ignore();
            cin>>name;
            system("cls");
            menu();
            add_name(inventory, item_names, item, name);
            writing(inventory, item_names);
            break;
        }
        case 4:{
            system("cls");
            menu();
            int item_to_remove_qty;
            cout<<"Enter item ID to remove one quantity: ";
            cin>>item_to_remove_qty;
            system("cls");
            menu();
            remove_quantity(inventory, item_to_remove_qty);
            writing(inventory, item_names);
            break;
        }
        case 5:{
            system("cls");
            menu();
            int item_to_remove;
            cout<<"Enter item ID to remove whole item: ";
            cin>>item_to_remove;
            system("cls");
            menu();
            remove_item(inventory, item_names ,item_to_remove);
            writing(inventory, item_names);
            break;
        }
        case 6:{
            system("cls");
            menu();
            show_items(inventory, item_names);
            break;
        }
        case 7:{
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