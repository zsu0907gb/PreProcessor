
// Editor(s) used: Xcode
// Compiler(s) used: Xcode

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

#include <cassert>

int main()
{

  
  stack<char> a;
  int lineIndex = 0;
  bool loopBreaker = false;
  string c;
  int p = 0;
  ifstream fin;
  char filename[1000];
  cout << "Enter filename (H, CPP, JAVA, HTML, or JS):" << endl;
  cin >> filename;
  fin.open(filename);
  if (!fin.good()) throw "File Not found Error";
  
  while (fin.good()&& loopBreaker == false)
  {
    lineIndex++;
    string line;
    getline(fin,line);
    
    for (int i=0;i<line.length();i++)
    {
      if(loopBreaker){break;}
      if(line[i] == '{' || line[i] == '(' || line[i] == '[' || (line[i] == '/' && line[i + 1] == '*'))
      {
        a.push(line[i]);
        p = lineIndex;
      }
      
      if(line[i] == '}' || line[i] == ')' || line[i] == ']' || (line[i] == '/' && line[i - 1] == '*'))
      {
      switch(line[i])
      {
        case '}':
          if(a.size()>0 && a.top() == '{')
            a.pop();
          else
          {
          cout << "closing curly braces found in line "<< lineIndex << " of " << filename << endl;
          cout << "But no matching opening curly braces found" << endl;
          loopBreaker = true;
          cout << endl;
          }
          break;
        case ')':
          if(a.size()>0 && a.top() == '(')
            a.pop();
          else
          {
          cout << "closing parentheses found in line "<< lineIndex << " of " << filename << endl;
          cout << "But no matching opening parentheses found" << endl;
          loopBreaker = true;
          cout << endl;
          }
          break;
        case ']':
          if(a.size()>0 && a.top() == '[')
            a.pop();
          else
          {
          cout << "closing square brackets found in line "<< lineIndex << " of " << filename << endl;
          cout << "But no matching opening square brackets found" << endl;
          loopBreaker = true;
          cout << endl;
          }
          break;
        case '/':
          if(line[i] == '/' && line[i - 1] == '*')
          {
            if(a.size()>0 && a.top() == '/')
              a.pop();
          
          else
          {
          cout << "closing comment offsets found in line "<<lineIndex << " of " << filename << endl;
          cout << "But no matching opening comment offsets found" << endl;
          loopBreaker = true;
          cout << endl;
          }
          break;
          }
          }//switch end
      }//second if end

    }//for loop end
  }//while loop end
  fin.close();
   
  if (a.size() == 0 && loopBreaker == false)
    cout << "No mismatches found by my preprocessor in " << filename << endl;
  if(a.size()>0&&loopBreaker == false)
  {
  if(a.top() == '(')
  {
    c = "Parenthesis";
  }
  else if(a.top() == '{')
  {
    c = "Curly braces";
  }
  else if(a.top() == '[')
  {
    c = "Square brackets";
  }
  else if(a.top() == '/')
  {
    c = "Comment offsets";
  }
  cout << "Opening " << c << " found in line " << p << " of "
  << filename << endl;
  cout << "But no matching closing " << c << " found" << endl;
    
  }
}
