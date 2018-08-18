#include <string>
#include <iostream>

using std::string; using std::cout;
using std::endl; using std::cin;
using std::cerr;

struct Products
{
  Products()
    : prod_name(), brand_name(), nChildren(0), children(NULL)
  {}

  string prod_name;
  string brand_name;
  unsigned int nChildren;
  Products *children;
};

bool inputprod(unsigned int val, Products* newProd);

int main(int argc, char* argv[])
{
	Products *newProd = NULL;
	if(!inputprod(3, newProd))
		{
		cerr << "Error!!!" << endl;
		}

  return 0;
}

bool inputprod(unsigned int val, Products* newProd)
{
  if (newProd)
    return false;

  newProd = new Products[val]; // dynalloc array of Products of size val

  for (unsigned int i = 0; i < val; ++i)
      {
      cout << "Product" << i+1 << ": ";
      cin >> newProd[i].prod_name;
      cout << "How many child products for " << newProd[i].prod_name << "? ";
      cin >> newProd[i].nChildren;

      newProd[i].children = new Products[newProd[i].nChildren]; // dynalloc array nchildren Products' of current Products
      for(unsigned int j = 0; j < newProd[i].nChildren; ++j)
        {
          cout << newProd[i].prod_name << "[" << j+1 << "]: ";
          newProd[i].children[j].prod_name = newProd[i].prod_name;
          cin >> newProd[i].children[j].brand_name;
        }
    }

  for(unsigned int i = 0; i < val; ++i)
    {
      cout << "Product#" << i << ": " << newProd[i].prod_name << endl;
      for (unsigned int j = 0; j < newProd[i].nChildren; ++j)
          cout << "Child Product#" << j << ": " << newProd[i].children[j].brand_name << endl;
    }

  // tidy up
  for(unsigned int i = 0; i < val; ++i)
	  delete [] newProd[i].children;
  delete [] newProd;
  newProd = NULL;

  return true;
}
