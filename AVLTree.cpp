#include <iostream>
using namespace std;
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    int height;
    TreeNode (int v){
        val = v;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};
void PreOrder (TreeNode *root, bool &first){
    if (!root) return;
    if (root != nullptr){
        if (!first){
            cout << " ";
        }
        cout << root -> val;
        PreOrder(root -> left, first);
        PreOrder(root -> right, first);
    }
}
int height (TreeNode *node){
    if (!node) return 0;
    return node -> height;
}
void updateheight (TreeNode *node){
    if (!node) return;
    node -> height = max (height(node -> left), height(node -> right)) + 1;
}
int getBalance (TreeNode *root){
    if (!root) return 0;
    return height(root -> left) - height(root -> right);
}
void fix (TreeNode *&root){
    //L
    if (getBalance(root) > 1){
        if (getBalance(root -> left) < 0) root -> left = RightRotate(root -> left);
        root = LeftRotate(root);
    }
    //R
    if (getBalance(root) < -1){
        if (getBalance(root -> right) > 0) root -> right = LeftRotate(root -> right);
        root = RightRotate(root);
    }
}
TreeNode *RightRotate (TreeNode *x){
    if (x -> left == nullptr) return x;
    TreeNode *L = x -> left;
    TreeNode *rL = L -> right;

    L -> right = x;
    x -> left = rL;
    updateheight(x);
    updateheight(L);
    return L;
}

TreeNode *LeftRotate (TreeNode *y){
    if (y -> right == nullptr) return y;
    TreeNode *R = y -> right;
    TreeNode *lR = R -> left;

    R -> left = y;
    y -> right = lR;
    updateheight(y);
    updateheight(R);
    return R;
}

TreeNode *insert (TreeNode *&root, int val){
    if (!root) return new TreeNode (val);
    if (val < root -> val) root -> left = insert(root -> left, val);
    else if (val > root -> val) root -> right = insert(root -> right, val);
    updateheight(root);
    fix(root);
    return root;
} 
TreeNode *deleteNode (TreeNode *&root, int val){
    if (!root) return nullptr;
    if (val < root -> val) root -> left = deleteNode(root -> left, val);
    else if (val > root -> val) root -> right = deleteNode(root -> right, val);
    else{
        if (root -> left && root -> right){
            TreeNode *tmp = root -> right;
            while(tmp -> left) tmp = tmp -> left;
            root -> val = tmp -> val;
            root -> right = deleteNode(root -> right, tmp -> val);
            updateheight(root);
            fix(root);
            return root;
        }
        else if (root -> left){
            TreeNode *tmp = root -> left;
            delete root;
            root = nullptr;
            return tmp;
        }
        else if (root -> right){
            TreeNode *tmp = root -> right;
            delete root;
            root = nullptr;
            return tmp;
        }
        else{
            delete root;
            root = nullptr;
            return nullptr;
        }
    }
    
}  
int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);




    return 0;
}