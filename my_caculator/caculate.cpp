#include <iostream>
#include <stack>
#include <cctype>
#include <stdexcept>
#include <string>

using namespace std;

bool isValidChar(char c) {
    return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || isdigit(c);
}

int priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int calculate(const string& expression) {
    stack<int> values;
    stack<char> ops;

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;
        if (expression[i] == '(') {
            ops.push(expression[i]);
        } else if (isdigit(expression[i])) {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = val * 10 + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        } else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty())
                ops.pop();
        } else {
            while (!ops.empty() && priority(ops.top()) >= priority(expression[i])) {
                int val2 = values.top();
                values.pop();
                int val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();
        int val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

bool isValidExpression(const string& expression) {
    stack<char> parentheses;

    for (char c : expression) {
        if (!isValidChar(c))
            return false;
        if (c == '(')
            parentheses.push(c);
        else if (c == ')') {
            if (parentheses.empty() || parentheses.top() != '(')
                return false;
            parentheses.pop();
        }
    }

    return parentheses.empty();
}

void run() {
    while (true) {
        cout << "請輸入算式，以 '=' 結束：" << endl;
        cout << "輸入 \"==\" 來結束程式" << endl;
        string input;
        string finalInput;
        while (true) {
            getline(cin, input);
            if(input == "==") return; // 結束程式
            if (!input.empty()) {
                finalInput += input;
                char lastChar = input[input.size() - 1];
                if (lastChar == '=') {
                    cout << "最後一個元素是: " << lastChar << endl;
                    break;
                }
            }
        }

        // Delete the last character '='
        if (!finalInput.empty()) {
            finalInput.pop_back();
        }

        if (!isValidExpression(finalInput)) {
            cout << "輸入的表達式不合法" << endl;
            continue; // 回到輸入算式的循環
        }

        try {
            int res = calculate(finalInput);
            cout << "計算結果: " << res << endl;
        }
        catch (const invalid_argument& e) {
            cerr << "錯誤: " << e.what() << endl;
        }
    }
}

int main() {
    run();
    cout << "程式結束" << endl;
    return 0;
}
