#include<iostream>
using namespace std;
class bank{
private:
    string name;
    string code;
    string address;
public:
    bank(){}
    bank(string n,string c,string a): name(n),code(c),address(a){}
    void display_bank_info(){
        cout<<"name: "<<name<<"\ncode: "<<code<<"\naddress: "<<address<<endl;
    }  
    string get_name() const { return name; }
    string get_code() const { return code; }
    string get_address() const { return address; }    
};
class branch:public bank{
private:
    string branch_name;
    string location;
public:
    branch(){}
    branch(string n,string c,string a,string bname, string loc): bank(n,c,a), branch_name(bname),location(loc){}
    void display_branch_info(){
        display_bank_info();
        cout<<"branch name: "<<branch_name<<"\nlocation: "<<location<<endl;
    }
}; 
class transaction: public bank{
private: 
    string id;
    string date;
    float amount;
public: 
    transaction(){}
    transaction(string n,string c,string a, string i, string d, float amt): bank(n,c,a), id(i), date(d), amount(amt){}
    void display_transaction_info(){
        display_bank_info();
        cout<<"transaction id: "<<id<<"\ndate: "<<date<<"\namount: "<<amount<<endl;
    }
};
class branchemployee: public branch{
private: 
    string emp_id;
    string emp_name;
    string position;
public:
    branchemployee(){}
    branchemployee(string n,string c,string a,string bname, string loc, string eid, string ename, string pos): 
    branch(n,c,a,bname,loc), emp_id(eid), emp_name(ename),position(pos){}
    void display_employee_info(){
        display_branch_info();
        cout<<"employee id: "<<emp_id<<"\nemployee name: "<<emp_name<<"\nposition: "<<position<<endl;
    } 
};
class customer: public branch{
private:
    string name;
    string number;
    float balance;
public:
    customer(){}
    customer(string n,string c,string a,string bname, string loc, string cname, string cnum, float bal):
    branch(n,c,a,bname,loc), name(cname), number(cnum), balance(bal){}
    float deposit(float amount){
        balance+=amount;
        return balance;
    }
    float withdraw(float amount){
        if(amount<=balance){
            balance-=amount;
            return balance;
        }
        else{
            cout<<"insufficient balance!"<<endl;
            return balance;
        }
    }
    void transfer(float amount, customer& target){
        if(amount<=balance){
            balance-=amount;
            target.balance+=amount;
            cout<<"transfer successful! new balance: "<<balance<<endl;
        }
        else{
            cout<<"insufficient balance!"<<endl;
        }
    }
    void display_customer_info(){
        display_branch_info();
        cout<<"customer name: "<<name<<"\ncontact number: "<<number<<"\nbalance: "<<balance<<endl;
    }
};
int main(){
    string bank_name, bank_code, bank_address;
    cout << "Enter Bank Details:\n";
    cout << "Bank Name: "; getline(cin, bank_name);
    cout << "Bank Code: "; getline(cin, bank_code);
    cout << "Bank Address: "; getline(cin, bank_address);
    bank myBank(bank_name, bank_code, bank_address);
    int n=3;
    customer* customers=new customer[n];
    for (int i=0;i<n;i++){
        string branch_name, branch_location;
        string customer_name, customer_number;
        float initial_balance;
        cout<<"Enter details for customer "<<i+1<<":\n";
        cout<<"Branch Name: "; getline(cin, branch_name);
        cout<<"Branch Location: "; getline(cin, branch_location);
        cout<<"Customer Name: "; getline(cin, customer_name);
        cout<<"Customer Contact Number: "; getline(cin, customer_number);
        cout<<"Initial Balance: "; cin>>initial_balance; 
        cin.ignore(); 
        customers[i] = customer(myBank.get_name(), myBank.get_code(), myBank.get_address(), 
        branch_name, branch_location, customer_name, customer_number, initial_balance);
    }
    int b=2;
    branchemployee* employees=new branchemployee[b];
    for(int i=0;i<b;i++){
        string branch_name, branch_location;
        string emp_id, emp_name, position;
        cout<<"Enter details for employee "<<i+1<<":\n";
        cout<<"Branch Name: "; getline(cin, branch_name);
        cout<<"Branch Location: "; getline(cin, branch_location);
        cout<<"Employee ID: "; getline(cin, emp_id);
        cout<<"Employee Name: "; getline(cin, emp_name);
        cout<<"Position: "; getline(cin, position);
        employees[i] = branchemployee(myBank.get_name(), myBank.get_code(), myBank.get_address(), branch_name, branch_location,
        emp_id, emp_name, position);
    }
    cout<<"------------ performing transactions ------------\n";
    cout<<"which customer do you want to perform transaction for? (0 to "<<n-1<<"): ";
    int cust_index;
    cin>>cust_index;
    if(cust_index < 0 || cust_index >= n) {
        cout<<"Invalid customer index!"<<endl;
        return 1;
    }
    customer& cust = customers[cust_index];
    cout<<"1. Deposit\n2. Withdraw\n3. Transfer\nChoose an option: ";
    int option;
    cin>>option;
    switch(option) {
        case 1: {
            float deposit_amount;
            cout<<"Enter amount to deposit: ";
            cin>>deposit_amount;
            float new_balance = cust.deposit(deposit_amount);
            cout<<"New balance after deposit: "<<new_balance<<endl;
            break;
        }
        case 2: {
            float withdraw_amount;
            cout<<"Enter amount to withdraw: ";
            cin>>withdraw_amount;
            float new_balance = cust.withdraw(withdraw_amount);
            cout<<"New balance after withdrawal: "<<new_balance<<endl;
            break;
        }
        case 3: {
            int target_index;
            cout<<"Enter target customer index for transfer (0 to "<<n-1<<"): ";
            cin>>target_index;
            if(target_index < 0 || target_index >= n || target_index == cust_index) {
                cout<<"Invalid target customer index!"<<endl;
                break;
            }
            customer& target_cust = customers[target_index];
            float transfer_amount;
            cout<<"Enter amount to transfer: ";
            cin>>transfer_amount;
            cust.transfer(transfer_amount, target_cust);
            break;
        }
        default:
            cout<<"Invalid option!"<<endl;
    }
    cout << "\n=== Adding New Employee ===\n";
    branchemployee* newemployee = new branchemployee(
        "Global Bank", "GB123", "123 Main St", "Downtown", "City Center", 
        "E1003", "David Wilson", "Loan Officer");
    newemployee->display_employee_info();
    cout<<"---------- bank system information------------\n";
    cout<<"displaying bank information: \n";
    myBank.display_bank_info();
    cout<<"displaying customer information: \n";
    for(int i=0;i<n;i++){
        customers[i].display_customer_info();
    }
    cout<<"displaying employee information: \n";
    for(int i=0;i<b;i++){
        employees[i].display_employee_info();
    }
    delete[] customers;
    delete[] employees;
    delete newemployee;
    cout<<"---------- end of bank system information------------\n";
    system("pause");
    return 0;
}
