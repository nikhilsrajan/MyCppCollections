# IO_File

A flexible data storage class based on Entity-Component-System.

## How to use

An object of the ```IO_File``` class has the following public member functions:

#### Node related functions
- ```CreateIONode```
- ```DestroyIONode```
- ```GetTopLevelNodes```

#### Hierarchy related functions
- ```SetAsParentChild```
- ```RemoveAsParentChild```
- ```HasChildren```
- ```HasParent```
- ```GetChildren```
- ```GetParents```

#### Attribute related functions
- ```AttributeExists```
- ```CreateAttribute```
- ```DestroyAttribute```
- ```SetDefaultValueForAttribute```
- ```GetAttributeList```
- ```GetAttributeType```

#### Attribute-Node related functions
- ```HasAttribute```
- ```SetAttribute```
- ```GetAttribute```
- ```RemoveAttribute```

---

### Example
There are 5 people.

4 people's names are Alex, Anne, Mindy, and Marx.

Alex has "Employee Id" of 1 and "Salary" of 1000.0.

We can use IO_File to store the above information as follows:

#### Create IO_File object
```
IO_File file;
```

#### Create nodes
```
IO_Node n0 = file.CreateIONode();
IO_Node n1 = file.CreateIONode();
IO_Node n2 = file.CreateIONode();
IO_Node n3 = file.CreateIONode();
IO_Node n4 = file.CreateIONode();
```

Each node represents a person.

#### Create attributes
```
file.CreateAttribute<std::string>("Name", "[noname]");
file.CreateAttribute<int>("Id", -1);
file.CreateAttribute<double>("Salary", 0.0);
```

```[noname]```, ``` -1```, ```` 0.0```` values we have predecided to return if a node doesn't have that attribute.

This is an optional parameter.

#### Add attributes for the nodes
```
file.SetAttribute<std::string>("Name", n0, "Alex");
file.SetAttribute<int>("Employee Id", n0, 1);
file.SetAttribute<double>("Salary", n0, 1000.0);
file.SetAttribute<std::string>("Name", n1, "Anne");
file.SetAttribute<std::string>("Name", n2, "Mindy");
file.SetAttribute<std::string>("Name", n3, "Marx");
```

#### Verification

To check whether the information is stored as expected I have created a ```Print(IO_File&)``` function as follows:
```
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
    }
}
```

We get the following output when ```Print(file)``` is executed.

```
node[0]:
└─ Name: Alex
└─ Employee Id: 1
└─ Salary: 1000
node[1]:
└─ Name: Anne
node[2]:
└─ Name: Mindy
node[3]:
└─ Name: Marx
node[4]:
└─ Name: [noname]
```

### Continuing ...

Anne has a Bank account.

She has deposited 1000.0 into it.


#### Create a Bank class
```
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
```

#### Add the corresponding attribute to IO_File
```
file.CreateAttribute<Bank>("Bank");
```
Here we haven't added the default value. In such situation ```IO_File``` returns the object created using the default constructor of the class.

#### Create a Bank object and use it
```
Bank b1;
b1.Deposit(1000.0);
```

#### Add the attribute to the corresponding node
```
file.SetAttribute<Bank>("Bank", n1, b1);
```

#### Verification
We add the following lines into the ```Print(IO_File&)``` function to print the ```Bank``` object.
```
if(file.GetAttribute("Bank", node, bank)) {
    std::cout << "└─ Bank Balance: " << bank.Balance() << std::endl;
}
```

Calling ```Print(file)``` gives:
```
node[0]:
└─ Name: Alex
└─ Employee Id: 1
└─ Salary: 1000
node[1]:
└─ Name: Anne
└─ Bank Balance: 1000
node[2]:
└─ Name: Mindy
node[3]:
└─ Name: Marx
node[4]:
└─ Name: [noname]
```

### Continuing ...

Anne withdraws 500 from her bank account.

#### Get the Bank attribute
```
Bank getter;
file.GetAttribute<Bank>("Bank", n1, getter);
```

#### Withdraw the amount
```
getter.Withdraw(500.0);
```

#### Set the attribute back
```
file.SetAttribute<Bank>("Bank", n1, getter);
```

#### Verification
```
node[0]:
└─ Name: Alex
└─ Employee Id: 1
└─ Salary: 1000
node[1]:
└─ Name: Anne
└─ Bank Balance: 500
node[2]:
└─ Name: Mindy
node[3]:
└─ Name: Marx
node[4]:
└─ Name: [noname]
```

### Continuing...
Mindy and Marx are children of Alex and Anne

#### Set the corresponding nodes as parent and child
```
file.SetAsParentChild(n0, n2);
file.SetAsParentChild(n0, n3);
file.SetAsParentChild(n1, n2);
file.SetAsParentChild(n1, n3);
```

#### Verification
We add the following lines to ```Print(IO_File&)``` to display children.

```
if(file.HasChildren(node)) {
    std::cout << "└─ Children: " << std::flush;
    std::vector<IO_Node> children = file.GetChildren(node);
    for(auto v_it = children.begin(); v_it != children.end(); ++v_it) {
        file.GetAttribute("Name", *v_it, name);
        std::cout << (v_it == children.begin() ? "" : ", ") << name << std::flush;
    }
    std::cout << std::endl;
}
```

Calling ```Print(file)``` gives:
```
node[0]:
└─ Name: Alex
└─ Employee Id: 1
└─ Salary: 1000
└─ Children: Mindy, Marx
node[1]:
└─ Name: Anne
└─ Bank Balance: 500
└─ Children: Mindy, Marx
node[2]:
└─ Name: Mindy
node[3]:
└─ Name: Marx
node[4]:
└─ Name: [noname]
```

### Continuing...

We don't wish to store Marx information anymore anywhere.

#### Destroy the corresponding node
```
file.DestroyIONode(n3);
```

#### Verification
```
node[0]:
└─ Name: Alex
└─ Employee Id: 1
└─ Salary: 1000
└─ Children: Mindy
node[1]:
└─ Name: Anne
└─ Bank Balance: 500
└─ Children: Mindy
node[2]:
└─ Name: Mindy
node[4]:
└─ Name: [noname]
```

### Continuing...

We don't wish to store "Name" or "Bank" infomations anymore anywhere.

#### Destory the attributes
```
file.DestroyAttribute("Name");
file.DestroyAttribute("Bank");
```

#### Verification
```
node[0]:
└─ Name: 
└─ Employee Id: 1
└─ Salary: 1000
└─ Children: 
node[1]:
└─ Name: 
└─ Children: 
node[2]:
└─ Name: 
node[4]:
└─ Name:
```
