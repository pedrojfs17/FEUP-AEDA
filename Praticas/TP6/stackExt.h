# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> s;
    stack<T> min;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
    return this->s.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    return s.top();
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    if (!this->empty()) {
        if (s.top() == min.top()) {
            min.pop();
        }
        s.pop();
    }
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    if (this->empty()) {
        s.push(val);
        min.push(val);
    }
    else {
        if (val <= min.top()) {
            min.push(val);
        }
        s.push(val);
    }
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    return min.top();
}

