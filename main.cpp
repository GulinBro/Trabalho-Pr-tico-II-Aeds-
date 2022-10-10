#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <stack>
#include <fstream>
#include "funcoes.hpp"




using namespace std;
 
int main() {
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);

      
    
    
    inicializarlista(&L1);
    inicializarpilha(&TP1);
    menu();

    
    

    
  
  cout << endl;
  return 0;
}
  
