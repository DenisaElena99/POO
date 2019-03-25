#include<iostream>

using namespace std;

class node
{

    int data;
    node* left;
    node* right;
public:
    node* getleft()
    {
        return left;
    }
    node* getright()
    {
        return right;
    }
    int getdata()
    {
        return data;
    }
    friend class BST;

};


class BST
{

private:
    node* root;
public:
    void Setroot(node *t)
    {
        root=t;
    }
    node* makeEmpty(node* t)
    {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {

        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }


    node* remove(int x, node* t)
    {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
    void inorder2(BST *new_bst,node* t)
    {
        if(t == NULL)
            return;
        inorder2(new_bst,t->left);
        (*new_bst).insert(t->data);
        inorder2(new_bst,t->right);
    }

    node* find(node* t, int x)
    {
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
            return find(t->right, x);
        else
            return t;
    }

    BST()
    {
        root = NULL;
    }

    ~BST()
    {
        root = makeEmpty(root);
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void display()
    {
        inorder(root);
        cout << endl;
    }

    void search(int x)
    {
        root = find(root, x);
    }
    /*  BST operator<<(const BST& b)
    /*  BST operator<<(const BST& b)
      {
           inorder(root);
          cout << endl;
      }
    */
    node* getroot()
    {
        return root;
    }
    friend ostream& operator<<(ostream& out, BST &t)
    {
        t.inorder(t.getroot());
        return out;
    }

    friend istream& operator>>(istream& in,BST &t)
    {

        t.Setroot(t.makeEmpty(t.getroot()));

        int n,val;
        in>>n;
        for(int i=1; i<=n; i++)
        {
            in>>val;
            t.insert(val);

        }
        return in;
    }

    BST& operator+(BST &t)///daca bagam fara referinta erau obiecte temporare
    {
        BST *q=new BST;
        (*this).inorder2(q,root);
        t.inorder2(q,t.getroot());

        return *q;

    }
    int  height(node *t)
    {
        if(t==NULL) return 0;
        else if(t->getleft()==0 && t->getright()==0) return 1;
        else return 1+max((*this).height(t->getleft()), (*this).height(t->getright()));
    }
    void leaf(node *t)
    {
        if(t==NULL) return;
        if(t->getleft()==NULL && t->getright() == NULL)
        {
            cout<<t->getdata()<<" ";
            return;
        }
        leaf(t->left);
        leaf(t->right);
    }
};



int main()
{
    BST t,q;

    t.insert(20);
    t.insert(25);
    t.insert(15);
    t.insert(10);
    t.insert(30);
    t.display();
    t.remove(20);
    t.display();
    t.display();
    cout<<t;
    q.insert(10);
    cin>>q;
    cout<<(t+q);
    cout<<t.height(t.getroot());
    cout<<endl;
    t.leaf(t.getroot());
    BST a[100];
    int n;
    for(int i=1; i<=n; i++)
        cin>>a[i];
    for(int i=1; i<=n; i++)
        a[i].display();

}
