#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class SplayTree
{
public:
    typedef struct tagNode
    {
        tagNode * ch[2];
        tagNode * fa;
        T key;
        int siz;
        //bool is_snt;
    }NODE, *PNODE;
    typedef const NODE *CPNODE;
private:
    const static int INF = 0x7FFFFFFF;
    PNODE tree;
    PNODE root, NIL, ncnt;

    inline bool XOR(bool exp1, bool exp2)
    {
        if(exp1 == exp2)
            return false;
        return true;
    }

    inline PNODE NewNode(T val, bool is_snt = false)
    {
        PNODE p = ++ncnt;
        p->ch[0] = p->ch[1] = p->fa = NIL;
        p->key = val;
        p->siz = 1;
        //p->is_snt = is_snt;
        return p;
    }

    void update(PNODE x)
    {
        if(!x)
            return;
        x->siz = 1;
        x->siz += x->ch[0]->siz;
        x->siz += x->ch[1]->siz;
    }

    void rotate(PNODE x)
    {
        PNODE y = x->fa;
        int d = (x == y->ch[0]);
        x->fa = y->fa;

        if(y->fa != NIL)
            y->fa->ch[y->fa->ch[1] == y] = x;

        y->ch[!d] = x->ch[d];
        if(x->ch[d] != NIL)
            x->ch[d]->fa = y;

        x->ch[d] = y;   y->fa = x;

        if(root == y)
            root = x;

        update(y);
        update(x);
    }

    /** @b Splay the tree so that x become a child of rt
        @p x target node
        @p rt designated root
    **/
    void splay(PNODE x, PNODE rt)
    {
        PNODE y, z;

        while(x->fa != rt)
        {
            y = x->fa, z = y->fa;
            if(z == rt)
                rotate(x);
            else
            {
                if(XOR(y == z->ch[0], x == y->ch[0]))
                    rotate(x);
                else
                    rotate(y);
                rotate(x);
            }
        }
    }

    PNODE insert(PNODE & rt, PNODE p, T val)
    {
        if(rt == NIL)
        {
            rt = NewNode(val);
            rt->fa = p;
            splay(rt, NIL);
            return rt;
        }
        rt->siz ++;
        return insert(rt->ch[(val > rt->key)], rt, val);
    }

    PNODE find(PNODE rt, T val)
    {
        PNODE p;
        if(rt == NIL)
            return NIL;
        if(val == rt->key)
        {
            p = rt->ch[0];
            // If there are multiple nodes with identical value
            // return the first one
            while(p != NIL && p->key == val)
            {
                rt = p;
                p = p->ch[0];
            }
            splay(rt, NIL);
            return rt;
        }
        if(val < rt->key)
            p = find(rt->ch[0], val);
        else
            p = find(rt->ch[1], val);
        if(p == NIL)
        {
            p = rt;
            splay(rt, NIL);
        }
        return p;
    }
    PNODE upper_bound(PNODE rt,T val)
    {
        if(rt == NIL)
            return NIL;
        PNODE p;
        if(val >= rt->key)
            p = upper_bound(rt->ch[1], val);
        else
        {
            p = upper_bound(rt->ch[0], val);
            if(p == NIL)
                p = rt;
        }
        return p;
    }
    PNODE lower_bound(PNODE rt,T val)
    {
        if(rt == NIL)
            return NIL;
        PNODE p;
        if(val < rt->key)
            p = lower_bound(rt->ch[0], val);
        else
        {
            p = lower_bound(rt->ch[1], val);
            if(p == NIL)
                p = rt;
        }
        return p;
    }
    PNODE lower_bound_exclusive(PNODE rt, T val)
    {
        if(rt == NIL)
            return NIL;
        PNODE p;
        if(val <= rt->key)
            p = lower_bound_exclusive(rt->ch[0], val);
        else
        {
            p = lower_bound_exclusive(rt->ch[1], val);
            if(p == NIL)
                p = rt;
        }
        return p;
    }

public:
#undef _DEBUG
#ifdef _DEBUG
    const PNODE getRoot()
    {
        return this->root;
    }

    void DEBUG(CPNODE cur)
    {
        if(cur == NIL)
            return ;
        DEBUG(cur->ch[0]);
        cerr << "Key:"<< cur->key << " Father:" << cur->fa->key << " ChildL:";
        cerr << cur->ch[0]->key << " ChildR:" << cur->ch[1]->key << " Size:" << cur->siz ;
        cerr << endl ;
        DEBUG(cur->ch[1]);
    }

    void DEBUG()
    {
        DEBUG(root);
        //cerr << endl ;
    }

    CPNODE findNotSplay(PNODE rt, T val)
    {
        if(rt == NIL)
            return NIL;

        if(rt->key == val)
            return rt;
        else if(rt->key > val)
            return findNotSplay(rt->ch[0], val);
        else
            return findNotSplay(rt->ch[1], val);
    }
#else
    void DEBUG()
    {   }
#endif // DEBUG

    SplayTree(PNODE TreeSpace, pair<T,T> sentinel)
    {
        if(TreeSpace == NULL)
            throw 0;
        tree = TreeSpace;
        NIL = ncnt = &tree[0];
        NIL -> key = -INF;
        NIL -> ch[0] = NIL -> ch[1] = NIL -> fa = NIL;
        root = NIL;

        this->insert(sentinel.first);
        this->insert(sentinel.second);
    }

    CPNODE insert(T val)
    {
        return this->insert(root, NIL, val);
    }

    CPNODE find(T val)
    {
        return this->find(root, val);
    }

    int getRank(T val)
    {
        int ans = 0; PNODE cur = root;

        while(true)
        {
            if(cur == NIL)
                return -1;

            if(val < cur->key)
                cur = cur->ch[0];
            else
            {
                ans += (cur->ch[0]->siz + 1);
                if(cur->key == val)
                    break;
                cur = cur->ch[1];
            }
        }
        splay(cur, NIL);
        return ans;
    }

    PNODE select(int k, PNODE nwrt)
    {
        PNODE p = root;
        int lsz;

        while(true)
        {
            lsz = p->ch[0]->siz;
            if(k == lsz + 1)
                break;
            if(k <= lsz)
                p = p->ch[0];
            else
                p = p->ch[1], k = k - lsz - 1;
        }

        splay(p, nwrt);
        return p;
    }

    PNODE operator [](int index)
    {
        return select(index, root);
    }

    /// @note This function does not splay the selected node
    CPNODE upper_bound(T val)
    {
        return upper_bound(root, val);
    }
    /// @note This function does not splay the selected node
    CPNODE lower_bound(T val)
    {
        return lower_bound(root, val);
    }

    void erase(T val)
    {
        int k = getRank(val);
        if(k <= 0)
            return;
        PNODE p(select(k-1, NIL)), q(select(k+1, p));
        q->ch[0] = NIL;
        splay(q, NIL);
    }

    void erase(T intStart, T intEnd)
    {
        if(intEnd < intStart)
            return;
        PNODE p = lower_bound_exclusive(root, intStart);
        PNODE q = upper_bound(root, intEnd);
        if(p == NIL || q == NIL)
            return;
        cerr << "Erasing" << endl ;
        splay(p, NIL);
        splay(q, p);
        q->ch[0] = NIL;
        //splay(q, NIL);
    }
};

SplayTree<int>::NODE Tree[250000];
SplayTree<int>::CPNODE tmpNode;

int main()
{
    int opcnt;
    SplayTree<int> spl(Tree, make_pair(0x80000000, 0x7fffffff));
    cin >> opcnt;
    /*
    while(opcnt--)
    {
        int op, x, y;
        cin >> op ;
        switch(op)
        {
        case 1:
            cin >> x ;
            spl.insert(x);
            spl.DEBUG();
            break;
        case 2:
            cin >> x ;
            if(x >= 0)
                tmpNode = spl.find(x);
            else
                tmpNode = spl.findNotSplay(spl.getRoot(), -x);
            cout << tmpNode->fa->key << " "
                << tmpNode->ch[0]->key << " "
                << tmpNode->ch[1]->key << " "
                << tmpNode->siz << endl ;
            break;
        case 3:
            cin >> x ;
            cout << spl.getRank(x) << endl;
            spl.DEBUG();
            break;
        case 4:
            cin >> x ;
            cout << (spl.select(spl.getRank(x), spl.getRoot()->fa))->key << endl ;
            spl.DEBUG();
            break;
        case 5:
            cin >> x;
            spl.erase(x);
            spl.DEBUG();
            break;
        case 6:
            cin >> x >> y;
            spl.erase(x, y);
            spl.DEBUG();
            break;
        case 7:
            cin >> x ;
            cout << spl.lower_bound(x)->key << " " << spl.upper_bound(x)->key << endl ;
            break;
        }
    }
    */

    while(opcnt--)
    {
        char opt; int x, y;
        cin >> opt;

        switch(opt)
        {
        case 'I':
        case 'i':
            cin >> x;
            spl.insert(x);
            spl.DEBUG();
            break;
        case 'Q':
        case 'q':
            cin >> x;
            cout << spl.lower_bound(x)->key << endl ;
            spl.DEBUG();
            break;
        case 'D':
        case 'd':
            cin >> x >> y;
            spl.erase(x, y);
            spl.DEBUG();
            break;
        }
    }
}

