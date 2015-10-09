#include <iostream>
#include <string>
using namespace std;

/****************************************************************
 * Quick and Dirty Data Structures
 ****************************************************************/

struct Node
{
  Node* next = NULL;
  //not needed for this example but a
  //link list that doesn't hold data is silly
  int data;

  //deconstructing a circular list is hard...don't worry about this
  bool isBeingDeleted = false;
  ~Node()
  {
    isBeingDeleted = true;
    if (next != NULL && !next->isBeingDeleted)
    {
      delete next;//
    }
  }
};

struct BTNode
{
  BTNode* p = NULL; //parent
  BTNode* l = NULL; //left child
  BTNode* r = NULL; //right child

  int data;

  BTNode(int data)
  {
    this->data = data;
  }

  ~BTNode()
  {
    if (l != NULL)
    {
      delete l;
    }
    if (r != NULL)
    {
      delete r;
    }
  }

  void insert(int num)
  {
    if (num < data)
    {
      if (l == NULL)
      {
        l = new BTNode(num);
        l->p = this;
      }
      else
      {
        l->insert(num);
      }
    }
    else
    {
      if (r == NULL)
      {
        r = new BTNode(num);
        r->p = this;
      }
      else
      {
        r->insert(num);
      }
    }
  }
};

/* Question 1
 * Print the numbers 0 to 100.  If the number is divisible by three print
 * “Fizz” instead of the number. If the number is divisible by 5 print “Buzz”
 * instead of the number. If the number is divisible by both 3 and 5 print
 * “FizzBuzz” instead of the number.
 */
void FizzBuzz()
{
  for (int i = 0; i <= 100; i++)
  {
    if (i % 3 == 0)
    {
      cout << "Fizz";
    }
    if (i % 5 == 0)
    {
      cout << "Buzz";
    }
    if (i % 3 != 0 && i % 5 != 0)
    {
      cout << i;
    }
    cout << endl;
  }
}

/* Question 2
 *Implement a function that will return the nth number in the Fibonacci sequence.
 */

int RecursiveFibonacci(unsigned int n)
{
  if (n <= 1)
  {
    return n;
  }
  return RecursiveFibonacci(n - 1) + RecursiveFibonacci(n - 2);
}

/* Question 3
 * Implement the previous questions both iteratively and recursively.
 */
int IterativeFibonacci(unsigned int n)
{
  if (n == 0)
    return 0;
  int a = 0, b = 1, c;
  for (int i = 1; i < n; i++)
  {
    c = a + b;
    a = b;
    b = c;
  }
  return b;
}

/* Question 4
 * Reverse the letters of a string in place
 */
string reverseString(string &myString)
{
  for (int i = 0; i < myString.length() / 2; i++)
  {
    swap(myString[i], myString[myString.length() - 1 - i]);
  }
  return myString;
}

/* Question 5
 * Reverse the words of a string
 */
void addWordToFront(string &base, string addition)
{
  if (!base.empty())
  {
    addition.push_back(' ');
  }
  base.insert(0, addition);
}

string reverseWordsofString(string myString)
{
  string newString = "", temp = "";
  for (int i = 0; i < myString.length(); i++)
  {
    if (myString[i] != ' ')
    {
      temp.push_back(myString[i]);
    }
    else
    {
      addWordToFront(newString, temp);
      temp = "";
    }
  }
  addWordToFront(newString, temp);
  return newString;
}

/* Question 6
 * Write a function that determines if a linked list is circular.
 *   The function will take a reference to a node in the list as its only argument.
 *     (hint: you only need 2 pointers)
 */

// returns true if circular
bool tortoiseAndHare(Node first)
{
  if (first.next != NULL)
  {
    Node* tortoise = &first;
    Node* hare = first.next;
    while (hare->next != NULL)
    {
      if (tortoise == hare)
      {
        return true;
      }
      hare = hare->next;
      if (hare->next != NULL)
      {
        hare = hare->next;
      }
      tortoise = tortoise->next;
    }
  }
  return false;
}

/* Question 7
 * Find the second largest number in a Binary Search Tree.
 */
int secondLargestBST(BTNode root)
{
  BTNode* cur = &root;//current
  while (cur->r != NULL)
  {
    cur = cur->r;
  }
  if (cur->l != NULL)
  {
    cur = cur->l;
  }
  else
  {
    return cur->p->data;
  }
  while (cur->r != NULL)
  {
    cur = cur->r;
  }
  return cur->data;
}

/* Question 8
 * Implement a function that determines if an integer is a power of 2 with bitwise operations.
 */
bool isPow2(int x)
{
  return 0 == (x & (x - 1));
}


/****************************************************************
 * Testing and Execution
 ****************************************************************/

Node buildList()
{
  Node node;
  for (int i = 0; i < 10; i++)
  {
    node.next = new Node;
  }
  return node;
}

Node buildCircularList()
{
  Node node;
  Node* last;
  for (int i = 0; i < 11; i++)
  {
    node.next = new Node;
    last = node.next;
  }
  last->next = &node;
  return node;
}

BTNode buildTestTree()
{
  BTNode root(5);
  root.insert(4);
  root.insert(7);
  root.insert(10);
  root.insert(20);
  root.insert(15);
  root.insert(14);
  root.insert(17);
  root.insert(16);
  root.insert(18);
  root.insert(21);
  return root;
}

void executeProblem(unsigned int problem)
{
  switch (problem)
  {
  case 0: // RUN ALL OF THEM
    for (int i = 1; i <= 8; i++)
    {
      executeProblem(i);
    }
    break;
  case 1:
    FizzBuzz();
    break;
  case 2:
    cout << "First 10 Fibonacci numbers" << endl;
    for (int i = 0; i < 10; i++)
    {
      cout << RecursiveFibonacci(i) << endl;
    }
    break;
  case 3:
    cout << "First 10 Fibonacci numbers" << endl;
    for (int i = 0; i < 10; i++)
    {
      cout << IterativeFibonacci(i) << endl;
    }
    break;
  case 4:
  {
    string myString = "Hello World!";
    reverseString(myString);
    cout << myString << endl;
  }
  break;
  case 5:
    cout << reverseWordsofString("FreeCodingClass from World Hello") << endl;
    break;
  case 6:
    cout << (tortoiseAndHare(buildList()) ? "Circular" : "Not Circular") << endl;
    cout << (tortoiseAndHare(buildCircularList()) ? "Circular" : "Not Circular") << endl;
    break;
  case 7:
    cout << secondLargestBST(buildTestTree()) << endl;
    break;
  case 8:

    cout << "X is " << (isPow2(512) ? "" : "not ") << "a power of 2" << endl;
    break;
  }
}

int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    executeProblem(atoi(argv[1]));
  }
  else
  {
    cout << "PLEASE INPUT THE PROBLEM NUMBER YOU WOULD LIKE TO RUN AS A COMMAND LINE ARGUMENT";
  }
  cout << endl;
  return 0;
}
