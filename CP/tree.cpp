// tree.cpp
// compile with: g++ -std=c++11 tree.cpp -o tree

#include <iostream>
#include <future>

using namespace std;

int valtab[127]; // used for integer values of variables

class Tree; // forward declare

class Node {
protected:
    Node() { use = 1; }
    virtual void print(ostream &os) = 0;
    virtual ~Node() { }
    virtual int eval() = 0;
private:
   friend class Tree;
   friend ostream& operator<<(ostream&, const Tree&);
   int use; // reference count
};

class Tree {
public:
    Tree(int n); // constant
    Tree(char id); // variable
    Tree(char op, Tree t); // unary operator
    Tree(char op, Tree left, Tree right); // binary operator
    Tree(const Tree &t) { p = t.p; ++p->use; }
    ~Tree() { if (--p->use == 0) delete p; }
    void operator=(const Tree &t);
    int eval() { return p->eval(); }
private:
    friend class Node;
    friend ostream& operator<<(ostream &os, const Tree &t);
    Node *p; // polymorphic hierarchy
};

void Tree::operator=(const Tree &t)
{
    ++t.p->use;
    if (--p->use == 0) 
        delete p;
    p = t.p;
}

ostream& operator<<(ostream &os, const Tree &t)
{
    t.p->print(os);
    return os;
}

class LeafNode: public Node {
private:
    friend class Tree;
    void print(ostream &os) = 0;
    virtual int eval() = 0;
};

class IntNode: public LeafNode {
public:
    int eval() { return n; }
private:
    friend class Tree;
    int n;
    void print(ostream &os) { os << n ;}
    IntNode(int k): n(k) { }
};

class IdNode: public LeafNode {
public:
    int eval() { return valtab[name]; }
private:
    friend class Tree;
    char name;
    void print(ostream& o) { o << name; }
    IdNode(char id): name(id) { }
};

class UnaryNode: public Node {
public:
    int eval();
private:
    friend class Tree;
    const char op;
    Tree opnd;
    UnaryNode(char a, Tree b): op(a), opnd(b) { }
    void print(ostream& o) { o << "(" << op << opnd << ")"; }
};

int UnaryNode::eval()
{
    std::future<int> f = std::async(&Tree::eval, opnd);

    switch (op) {
        case '-': return (-f.get());
        case '+': return (+f.get());
        default: cerr << "no operand" << endl;
            return 0;
    }
}

class BinaryNode: public Node {
public:
    int eval();
private:
    friend class Tree;
    const char op;
    Tree left;
    Tree right;
    BinaryNode(char a, Tree b, Tree c): op(a), left(b), right(c) { }
    void print(ostream &os) { os << "(" << left << op << right << ")"; }
};

int BinaryNode::eval()
{
    std::future<int> fl = std::async(&Tree::eval, left);
    std::future<int> fr = std::async(&Tree::eval, right);
    switch (op) {
        case '-':
            return (fl.get() - fr.get());
        case '+':
            return (fl.get() + fr.get());
        case '*':
            return (fl.get() * fr.get());
        default: cerr << "no operand" << endl;
            return 0;
    }
}

Tree::Tree(int n) { p = new IntNode(n); }
Tree::Tree(char id) { p = new IdNode(id); }
Tree::Tree(char op, Tree t) { p = new UnaryNode(op, t); }
Tree::Tree(char op, Tree left, Tree right) { p = new BinaryNode(op, left, right); }

int main()
{   
    valtab['A'] = 3; valtab['B'] = 4;
    cout << "A = 3, B = 4" << endl;
    Tree t1 = Tree('*', Tree('-', 5), Tree('+', 'A', 4));
    Tree t2 = Tree('+', Tree('-', 'A', 1), Tree('+', t1, 'B'));
    cout << "t1 = " << t1 << ", t2 = " << t2 << endl;
    cout << "t1 = " << t1.eval() << ", t2 = " << t2.eval() << endl;

    return 0;
}

