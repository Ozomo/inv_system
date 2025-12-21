#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
void clearing_vector(vector<int>& vec) { //ready
    while(vec.size() > 0){
        vec.pop_back();
    }
}

bool is_there_already(vector<int>& items, int item) { //test

    for(int i = 0; i< items.size(); i++){
        if(item == items[i]){
            return true;
        }
    }
    return false;
}

void add_item(vector<int>& items, vector<int>& quantity, int item) { //ready
    if(is_there_already(items, item)){
        for(int i = 0; i < items.size(); i++){
            if(items[i] == item){
                quantity[i]++;
                break;
            }
        }
    } else {
        items.push_back(item);
        quantity.push_back(1);
    }
}

void remove_quantity(vector<int>& items, vector<int>& quantity, int item) { //ready
    for(int i = 0; i < items.size(); i++){
        if(items[i] == item){
            if(quantity[i] > 0){
                quantity[i]--;
            }
            break;
        }
        else {
            cout<<"There is no such item in inventory."<<endl;
        }
    }
}

void remove_item(vector<int>& items, vector<int>& quantity, int item) { //ready

    if(!is_there_already(items, item)){
        cout<<"There is no such item in inventory."<<endl;
        return;
    }

    vector <int> var_items = {};
    vector <int> var_quantity = {};
    for(int i = items.size() - 1; i >= 0; i--){
        if(items[i] == item){
            items.pop_back();
            quantity.pop_back();
            while(var_items.size() > 0){
                items.push_back(var_items[var_items.size() - 1]);
                quantity.push_back(var_quantity[var_quantity.size() - 1]);
                var_items.pop_back();
                var_quantity.pop_back();   
            }
            return;
        }
        else{
            var_items.push_back(items[i]);
            items.pop_back();
            var_quantity.push_back(quantity[i]);
            quantity.pop_back();
        }   
    }
}

void show_items(vector<int>& items, vector<int>& quantity) { //ready
    cout << "Items in inventory:" << endl;
    for(int i = 0; i < items.size(); i++){
        cout << "Item: " << items[i] << " | Quantity: " << quantity[i] << endl;
    }
}

void reading(vector<int>& items, vector<int>& quantity){
    fstream file;
    file.open("inventory.txt", ios::in);

    if(file.fail()){
        cout<<"File could not be opened."<<endl;
        return;
    }

    clearing_vector(items);
    clearing_vector(quantity);

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
        qty = stoi(line);
        items.push_back(item);
        quantity.push_back(qty);
        line = "";
    }
}

void writing(vector<int>& items, vector<int>& quantity){
    fstream file;
    file.open("inventory.txt", ios::out | ios::trunc);
    for(int i = 0; i < items.size(); i++){
        file<<items[i]<<endl;
        file<<quantity[i]<<endl;
    }
}
void menu(){
    cout<<"Inventory System"<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<"1. Fast Add Item"<<endl;
    cout<<"2. Add Item"<<endl;
    cout<<"3. Remove Quantity"<<endl;
    cout<<"4. Remove Item"<<endl;
    cout<<"5. Show Items"<<endl;
    cout<<"6. Save Inventory to File"<<endl;
    cout<<"7. Load Inventory from File"<<endl;
    cout<<"8. Exit"<<endl;
    cout<<"-----------------------------"<<endl;
}
int main(){
    vector <int> items = {};
    vector <int> quantity = {};

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
            cout<<"Enter item ID to add: ";
            cin>>item_to_add;
            add_item(items, quantity, item_to_add);
            system("cls");
            menu();
            cout<<"Item ["<<item_to_add<<"] added successfully."<<endl;
            break;
        }
        case 2:{
            system("cls");
            menu();
            int item_to_add;
            int qty;
            cout<<"Enter item ID to add: ";
            cin>>item_to_add;
            cout<<"enter quantity to add: ";
            cin>>qty;
            for(int i = 0; i < qty; i++){
                add_item(items, quantity, item_to_add);
            }
            system("cls");
            menu();
            cout<<"Item ["<<item_to_add<<"] added "<<qty<<" times successfully."<<endl;
            break;
        }
        case 3:{
            system("cls");
            menu();
            int item_to_remove_qty;
            cout<<"Enter item ID to remove one quantity: ";
            cin>>item_to_remove_qty;
            remove_quantity(items, quantity, item_to_remove_qty);
            system("cls");
            menu();
            cout<<"Item ["<<item_to_remove_qty<<"] removed once successfully."<<endl;
            break;
        }
        case 4:{
            system("cls");
            menu();
            int item_to_remove;
            cout<<"Enter item ID to remove whole item: ";
            cin>>item_to_remove;
            remove_item(items, quantity, item_to_remove);
            system("cls");
            menu();
            cout<<"Whole item ["<<item_to_remove<<"] removed successfully."<<endl;
            break;
        }
        case 5:{
            system("cls");
            menu();
            show_items(items, quantity);
            break;
        }
        case 6:{
            system("cls");
            menu();
            writing(items, quantity);
            cout<<"Inventory saved to file."<<endl;
            break;
        }
        case 7:{
            system("cls");
            menu();
            reading(items, quantity);
            cout<<"Inventory loaded from file."<<endl;
            break;
        }
        case 8:{
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