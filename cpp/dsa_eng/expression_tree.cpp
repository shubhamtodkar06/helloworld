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

TreeNode* constructExpressionTreeFromPostfix(const string& postfix) {
    stack<TreeNode*> st;

    for (char current : postfix) {
        if (!isOperator(current)) {
            TreeNode* newNode = new TreeNode(current);
            st.push(newNode);
        } else {
            TreeNode* operatorNode = new TreeNode(current);

            TreeNode* operand2 = st.top();
            st.pop();
            TreeNode* operand1 = st.top();
            st.pop();

            operatorNode->right = operand2;
            operatorNode->left = operand1;

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

void recursivePreorder(TreeNode* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        recursivePreorder(root->left);
        recursivePreorder(root->right);
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

void nonRecursivePreorder(TreeNode* root) {
    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* current = st.top();
        st.pop();

        cout << current->data << " ";

        if (current->right != nullptr) {
            st.push(current->right);
        }

        if (current->left != nullptr) {
            st.push(current->left);
        }
    }
}

int main() {
    string postfixExpression;

    cout << "Enter the postfix expression: ";
    cin >> postfixExpression;

    TreeNode* root = constructExpressionTreeFromPostfix(postfixExpression);

    cout << "Recursive Inorder Traversal: ";
    recursiveInorder(root);
    cout << endl;

    cout << "Recursive Preorder Traversal: ";
    recursivePreorder(root);
    cout << endl;

    cout << "Non-Recursive Inorder Traversal: ";
    nonRecursiveInorder(root);
    cout << endl;

    cout << "Non-Recursive Preorder Traversal: ";
    nonRecursivePreorder(root);
    cout << endl;

    return 0;
}
