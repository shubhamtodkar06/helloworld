#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char value) : data(value), left(nullptr), right(nullptr) {}
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

TreeNode* constructExpressionTreeFromPrefix(const string& prefix) {
    stack<TreeNode*> st;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        char current = prefix[i];

        if (!isOperator(current)) {
            TreeNode* newNode = new TreeNode(current);
            st.push(newNode);
        } else {
            TreeNode* operatorNode = new TreeNode(current);

            TreeNode* operand1 = st.top();
            st.pop();
            TreeNode* operand2 = st.top();
            st.pop();

            operatorNode->left = operand1;
            operatorNode->right = operand2;

            st.push(operatorNode);
        }
    }

    return st.top();
}

void recursiveInorder(TreeNode* root) {
    if (root != nullptr) {
        recursiveInorder(root->left);
        cout << root->data << " ";
        recursiveInorder(root->right);
    }
}

void recursivePostorder(TreeNode* root) {
    if (root != nullptr) {
        recursivePostorder(root->left);
        recursivePostorder(root->right);
        cout << root->data << " ";
    }
}

void nonRecursiveInorder(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* current = root;

    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        cout << current->data << " ";

        current = current->right;
    }
}

void nonRecursivePostorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    stack<TreeNode*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        TreeNode* current = st1.top();
        st1.pop();
        st2.push(current);

        if (current->left) {
            st1.push(current->left);
        }

        if (current->right) {
            st1.push(current->right);
        }
    }

    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

int main() {
    string prefixExpression;

    cout << "Enter the prefix expression: ";
    cin >> prefixExpression;

    TreeNode* root = constructExpressionTreeFromPrefix(prefixExpression);

    cout << "Recursive Inorder Traversal: ";
    recursiveInorder(root);
    cout << endl;

    cout << "Recursive Postorder Traversal: ";
    recursivePostorder(root);
    cout << endl;

    cout << "Non-Recursive Inorder Traversal: ";
    nonRecursiveInorder(root);
    cout << endl;

    cout << "Non-Recursive Postorder Traversal: ";
    nonRecursivePostorder(root);
    cout << endl;

    return 0;
}
