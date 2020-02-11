#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <map>
#include "lex.h"

using namespace std;

int main(int argc, char* argv[])
{
    
    bool v = false;
    bool ids = false;
    bool consts = false;
    int linenumber = 1;
    istream *input = &cin;
    ifstream f;
    f.open(argv[argc-1]);
        
        for (int i = 1; i<argc; i++)
        {
              if (strcmp(argv[i], "-v") == 0)
            {
                v = true;
            }
            else if (strcmp(argv[i], "-consts") == 0)
            {
                consts = true;
            }
            else if (strcmp(argv[i], "-ids") == 0)
            {
                ids = true;
            }
            else if ((argv[i][0] == '-'))
             {
             cout << "UNRECOGNIZED FLAG "<< argv[i] <<endl;
                return 0;
             }
            else if (i == argc - 1)
            {
                if ((!(f.is_open())))
                {
                    cout << "CANNOT OPEN "<< argv[argc-1] <<endl; 
                    return 0;
                } 
                else
                input = &f;
            }
            else 
            {
                cout << "ONLY ONE FILE NAME ALLOWED" <<endl;
                return 0;
            }
            
        }
        
  
    
    Lex chex;
    int counter=0;
   
    list<string> idss;
    list<string> scon;
    list<int> icon;
    
    while((chex = getNextToken(*input, linenumber)) != Token:: ERR && chex != Token::DONE){
        
     
        counter++;
        //cout<<chex.GetLexeme()<<  endl;
        if(v){
           cout<<chex<<endl;
        }
        
        if(chex.GetToken() == ID){
            idss.push_front(chex.GetLexeme());
        }
        
        if(chex.GetToken() == STR){
            scon.push_front(chex.GetLexeme());
        }
        
        if(chex.GetToken() == INT){
            icon.push_front(stoi(chex.GetLexeme()));
        
        }
        
       
    }
    
   
    
    if(chex.GetToken()== Token:: ERR){
        cout<< "Error on line " << linenumber << " (" <<chex.GetLexeme()<< ")"<<endl; 
        return 0;
    }
    
    
    
    
     if(ids){
         if(idss.size() > 0){
             idss.sort();
             idss.unique();
         cout<< "IDENTIFIERS: ";
          for (string n : idss) {
              
           cout << n ;
              
              if(n.compare(idss.back())){
                  cout<<", ";
              }
              }
         cout<<endl;
         }
            
        }
        
        
        if(consts)
        {
            
        if(scon.size() > 0)
        {
            scon.sort();
            scon.unique();
         cout<< "STRINGS:" <<endl;
          for (string n : scon) 
          { 
           cout << n << endl;
          }
        }
            
        if(icon.size() > 0)
        {
            icon.sort();
            icon.unique();
         cout<< "INTEGERS:" <<endl;
          for (int m : icon) 
          { 
           cout << m << endl;
          }
        }
            
        }
    

  
    cout<<"Lines: "<< linenumber-1<<endl;
 
    if(linenumber > 1){
    cout<<"Tokens: " << counter <<endl;
    }

    return 0;
    
}
