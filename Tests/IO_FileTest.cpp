#include "../IO_File/IO_File.hpp"
#include <iostream>

class Bank {
public:
    Bank()
        : balance(0.0) {}
    void Withdraw(const double& amount) {
        balance -= amount;
    }
    void Deposit(const double& amount) {
        balance += amount;
    }
    const double& Balance() {
        return balance;
    }
private:
    double balance;
};

void Print(IO_File& file) {
    std::string name;
    int id;
    double salary;
    Bank bank;
    for(auto it = file.begin(); it != file.end(); ++it) {
        auto node = IO_File::GetIONode(it);

        std::cout << "node[" << node.GetId() << "]:" << std::endl;

        file.GetAttribute("Name", node, name);
        std::cout << "└─ Name: " << name << std::endl;

        if(file.GetAttribute("Employee Id", node, id)) {
            std::cout << "└─ Employee Id: " << id << std::endl;
        }

        if(file.GetAttribute("Salary", node, salary)) {
            std::cout << "└─ Salary: " << salary << std::endl;
        }

        if(file.GetAttribute("Bank", node, bank)) {
            std::cout << "└─ Bank Balance: " << bank.Balance() << std::endl;
        }

        if(file.HasChildren(node)) {
            std::cout << "└─ Children: " << std::flush;
            std::vector<IO_Node> children = file.GetChildren(node);
            for(auto v_it = children.begin(); v_it != children.end(); ++v_it) {
                file.GetAttribute("Name", *v_it, name);
                std::cout << (v_it == children.begin() ? "" : ", ") << name << std::flush;
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    IO_File file;

    // Creating attributes
    file.CreateAttribute<std::string>("Name", "[noname]");
    file.CreateAttribute<int>("Id", -1);
    file.CreateAttribute<double>("Salary", 0.0);
    file.CreateAttribute<Bank>("Bank");

    // Getting the Attribute-Type list
    std::vector<std::pair<std::string, std::string>> attribute_list = file.GetAttributesList();
    
    // // Printing Attribute-Type list
    // for(auto it = attribute_list.begin(); it !=  attribute_list.end(); ++it) {
    //     auto attribute = it->first;
    //     auto type = it -> second;
    //     std::cout << "(" << attribute << ", " << type << ")" << std::endl;
    // }
    // std::cout << "--------------------" << std::endl;

    // Creating nodes
    IO_Node n0 = file.CreateIONode();
    IO_Node n1 = file.CreateIONode();
    IO_Node n2 = file.CreateIONode();
    IO_Node n3 = file.CreateIONode();
    IO_Node n4 = file.CreateIONode();

    // Adding attributes to nodes
    file.SetAttribute<std::string>("Name", n0, "Alex");
    file.SetAttribute<std::string>("Name", n1, "Anne");
    file.SetAttribute<std::string>("Name", n2, "Mindy");
    file.SetAttribute<std::string>("Name", n3, "Marx");

    Print(file);
    std::cout << "--------------------" << std::endl;

    file.SetAttribute<int>("Employee Id", n0, 1);
    file.SetAttribute<double>("Salary", n0, 1000.0);

    Print(file);
    std::cout << "--------------------" << std::endl;
    
    Bank b1;
    b1.Deposit(1000.0);
    file.SetAttribute<Bank>("Bank", n1, b1);

    Print(file);
    std::cout << "--------------------" << std::endl;

    Bank getter;
    file.GetAttribute<Bank>("Bank", n1, getter);
    getter.Withdraw(500.0);
    file.SetAttribute<Bank>("Bank", n1, getter);

    Print(file);
    std::cout << "--------------------" << std::endl;

    file.SetAsParentChild(n0, n2);
    file.SetAsParentChild(n0, n3);
    file.SetAsParentChild(n1, n2);
    file.SetAsParentChild(n1, n3);

    Print(file);
    std::cout << "--------------------" << std::endl;

    file.DestroyIONode(n3);

    Print(file);
    std::cout << "--------------------" << std::endl;

    file.DestroyAttribute("Name");
    file.DestroyAttribute("Bank");

    Print(file);
    std::cout << "--------------------" << std::endl;

    return 0;
}