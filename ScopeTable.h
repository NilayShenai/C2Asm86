// Created by nilay

#ifndef COMPILER_SCOPETABLE_H
#define COMPILER_SCOPETABLE_H

class ScopeTable {
    int size, Id, tableIdTracker;
    int TableID;

    ScopeTable *parentScope;

    SymbolInfo **HashTable;
public:
    ScopeTable() {
        this->size = -1;
        this->tableIdTracker = -1;
        this->Id = this->tableIdTracker;
    }

    explicit ScopeTable(int tableSize,int counter = 0, int p = 0) {
        this->size = tableSize;
        this->tableIdTracker = 0;
        this->Id = p + 1;
        this->TableID = counter;

        this->parentScope = 0;

        HashTable = new SymbolInfo *[tableSize];
        for (int i = 0; i < tableSize; i++) {
            HashTable[i] = new SymbolInfo();
        }
    }

    void setTableIdTracker() {
        tableIdTracker++;
    }

    int getTableIdTracker() {
        return this->tableIdTracker;
    }

    std::string getStringifyID() {
        std::string sID = std::to_string(this->Id);
        ScopeTable *tempParent = this->parentScope;

        while (tempParent != 0) {
            sID += "." + std::to_string(tempParent->getID());
            tempParent = tempParent->getParentScope();
        }
        reverse(sID.begin(), sID.end());
        return sID;
    }

    bool Insert(std::string s, std::string type) {
        int idx = HashFunc(s);

        if (HashTable[idx]->getName() == "") {
            HashTable[idx]->setName(s);
            HashTable[idx]->setType(type);

            return true;
        }
        else {
            SymbolInfo *root = HashTable[idx];
            while (root->getNextPointer() != 0) {
                if (root->getName() == s) {
                    if(root->getType()=="ID"){
                        std::string foundMsg = s + " already exists in current ScopeTable\n";
                    }
                    return false;
                }
                root = root->getNextPointer();
            }
            if (root->getNextPointer() == 0 && root->getName() == s) {
                if(root->getType()=="ID"){
                    std::string foundMsg = s + " already exists in current ScopeTable\n";
                }
                return false;
            }

            root = HashTable[idx];
            int positionTracker = 0;

            SymbolInfo *newSymbolInfo = new SymbolInfo(s, type, 0);


            while (root->getNextPointer() != 0) {
                root = root->getNextPointer();
                positionTracker++;
            }
            root->setNextPointer(newSymbolInfo);
            return true;
        }
 
        return false;
    }

    bool InsertModified(SymbolInfo* s)
    {
        std::string key = s->getName();
        std::string value  = s->getType();
        int index = HashFunc(key);

        if(HashTable[index]->getName() == "" ){

            HashTable[index] = s;
            return true;
        }else 
        {

            SymbolInfo* head = HashTable[index];

            if(head->getNextPointer() == 0 && head->getName() == key){
                return false;
            }else{
                
                while(head!=0){
                    if(head->getName() == key){
                        return false;
                    }
                    head = head->getNextPointer();
                }
            }


            int j = 0;
            head = HashTable[index];

            while(head->getNextPointer() != 0){
                head = head->getNextPointer();
                j++;
            }

            s->setNextPointer(0);
            head->setNextPointer(s);
            return true;
        }
    }

    int getID() {
        return this->TableID;
    }

    ScopeTable *getParentScope() {
        return this->parentScope;
    }

    void setParentScope(ScopeTable *parent) {
        this->parentScope = parent;
    }

    int HashFunc(std::string s) const {
        int sumOfAsciiValue = 0;
        for (auto si:s) {
            sumOfAsciiValue += si;
        }
        return abs(sumOfAsciiValue % size);
    }


    SymbolInfo *LookUP(std::string s) {
        int index = HashFunc(s);
        SymbolInfo *head = HashTable[index];
        int positionTracker = 0;

       
        if (head == 0) {
            return 0;
        }
        while (head != 0) {
            if (head->getName() == s) {
                return head;
            }
            positionTracker++;
            head = head->getNextPointer();
        }
        return head;
    }

    bool Delete(std::string s) {

        int index = HashFunc(s);


        SymbolInfo *root = HashTable[index];
        SymbolInfo *temp, *p, *q;

        if (root == 0) {
            return false;
        }

        if (root->getName() != s && root->getNextPointer() == 0) {
            return false;
        }

        else if (root->getName() == s && root->getNextPointer() == 0) {
            root->setName("");
            root->setType("");

            return true;
        }

        else if (HashTable[index]->getName() == s && HashTable[index]->getNextPointer() != 0) {
            temp = HashTable[index];
            HashTable[index] = HashTable[index]->getNextPointer();

 
            temp->setNextPointer(0);
            delete temp->getNextPointer();
            delete temp;


            return true;
        }

        else {

            p = root;
            q = root->getNextPointer();
            int positionTracker = 0;

            while (q != 0 && q->getName() != s) {
                p = q;
                q = q->getNextPointer();
                positionTracker++;
            }


            if (q != 0) {
                p->setNextPointer(q->getNextPointer());
                q->setNextPointer(0);
                delete q->getNextPointer();
                delete q;

 
                return true;
            }

            return false;
        }
    }

    void print() {
        std::cout << std::endl << "ScopeTable # " << this->getStringifyID() << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << i << " --> ";
            if (HashTable[i]->getNextPointer() == 0) {
                if (HashTable[i]->getName() != "")
                    std::cout << " < " << HashTable[i]->getName() << " : " << HashTable[i]->getType() << "> ";
            } else {
                SymbolInfo *temp = HashTable[i];
                while (temp != 0) {
                    std::cout << " < " << temp->getName() << " : " << temp->getType() << "> ";
                    temp = temp->getNextPointer();
                }
            }
            std::cout << " " << std::endl;
        }
        std::cout << std::endl;
    }
    void printModified(FILE *logs) {
        fprintf(logs,"ScopeTable # %s\n",this->getStringifyID().c_str());
        for (int i = 0; i < size; i++) {
            if (HashTable[i]->getNextPointer() == 0) {
                if (HashTable[i]->getName() != ""){
                    fprintf(logs," %d --> ",i);
                    fprintf(logs,"< %s : %s> ",HashTable[i]->getName().c_str(),HashTable[i]->getType().c_str());
                    fprintf(logs, "\n");
                }
            } else {
                SymbolInfo *temp = HashTable[i];
                fprintf(logs, " %d --> ", i);
                while (temp != 0) {
                    fprintf(logs,"< %s : %s> ",temp->getName().c_str(),temp->getType().c_str());
                    temp = temp->getNextPointer();
                }
                fprintf(logs,"\n");
            }
        }
        fprintf(logs,"\n");
    }

    bool copyOfDeleteFunction(std::string s) {
        int index = HashFunc(s);
        SymbolInfo *root = HashTable[index];
        SymbolInfo *temp, *p, *q;
        if (root == 0) {
            return false;
        }
        if (root->getName() != s && root->getNextPointer() == 0) {
            return false;
        }
        else if (root->getName() == s && root->getNextPointer() == 0) {
            root->setName("");
            root->setType("");
            return true;
        }
        else if (HashTable[index]->getName() == s && HashTable[index]->getNextPointer() != 0) {
            temp = HashTable[index];
            HashTable[index] = HashTable[index]->getNextPointer();

            temp->setNextPointer(0);
            delete temp->getNextPointer();
            delete temp;


            return true;
        }
 
        else {

            p = root;
            q = root->getNextPointer();
            int positionTracker = 0;

            
            while (q != 0 && q->getName() != s) {
                p = q;
                q = q->getNextPointer();
                positionTracker++;
            }


            if (q != 0) {
                p->setNextPointer(q->getNextPointer());
                q->setNextPointer(0);
                delete q->getNextPointer();
                delete q;

                
                return true;
            }
            
            return false;
        }
    }

    void OutOfScope() {
        for (int i = 0; i < size; i++) {
            SymbolInfo *temp = HashTable[i];

            while (temp->getName() != "") {
                copyOfDeleteFunction(temp->getName());
                temp = HashTable[i];
            }
        }
    }

    ~ScopeTable() {
        this->OutOfScope();
        for (int i = 0; i < size; i++) {
            delete HashTable[i]->getNextPointer();
            delete HashTable[i];
        }
        delete[] HashTable;
    }
};

#endif 
