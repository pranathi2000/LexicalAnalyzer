#include "lex.h"
#include <map>

using namespace std;


 map <string, Token > TMap = {
        { "PRINT", PRINT},
        { "LET",LET},
        { "IF",IF},
        { "LOOP",LOOP},
        { "BEGIN",BEGIN},
        { "END", END},
        { "ID",ID},
        { "INT",INT},
        { "STR", STR},
        { "PLUS", PLUS},
        { "MINUS", MINUS},
        { "STAR", STAR},
        { "SLASH", SLASH},
        { "LPAREN", LPAREN},
        { "RPAREN", RPAREN},
        {"BANG", BANG},
        { "SC", SC},
        { "ERR", ERR},
        { "DONE", DONE}
        
    
    };

map < Token,string > TMap2 = {
        {  PRINT, "PRINT"},
        {  LET, "LET"},
        {  IF, "IF"},
        {  LOOP, "LOOP"},
        {  BEGIN, "BEGIN"},
        {  END, "END"},
        {  ID, "ID"},
        {  INT, "INT"},
        {  STR, "STR"},
        {  PLUS, "PLUS"},
        {  MINUS, "MINUS"},
        {  STAR, "STAR"},
        {  SLASH, "SLASH"},
        {  LPAREN, "LPAREN"},
        {  RPAREN, "RPAREN"},
        {BANG, "BANG"},
        {  SC, "SC"},
        {  ERR, "ERR"},
        {  DONE, "DONE"}
        
    
    };


    
ostream& operator <<(ostream& out, const Lex& lex){

    Token t = lex.GetToken();
      out<< TMap2[t];
    if(t== Token::ID || t==Token::INT || t==Token::STR || t== Token::ERR){
      out<< "(" << lex.GetLexeme() <<")";
    }
    
    return out;
}
 
Lex getNextToken(istream& in, int& linenumber){
   
    
    char ch;
    string lexeme;
    
    enum  LexState  {BEGIN, IN_IDENTIFIER, IN_STRING, ERROR, DONE, IN_INTEGER, COMMENT} 
    lexState = BEGIN; 
    
    while(in.get(ch)){ 
        
     switch(lexState){
             
         case BEGIN:
             
             if(isalpha(ch)){
                 lexeme += ch;
                 lexState = IN_IDENTIFIER;
             
             }
              
             if(isdigit(ch)){
                 lexeme += ch;
                 lexState = IN_INTEGER;
                 
             }
             
             if(ch == '"'){
                 lexState = IN_STRING;
              
             }
              
            if(ch == '+' ){ 
                lexeme += ch;
               return Lex(Token::PLUS, lexeme, linenumber);
                
            }
             
            if(ch == '-'){
                lexeme += ch;
                return Lex(Token::MINUS, lexeme, linenumber);
                
            
            }
             
            if(ch == '*'){
                lexeme += ch;
              return Lex(Token::STAR, lexeme, linenumber);
            
            }
             
            if(ch == '/'){  
                
                if (in.peek() == '/')
                {
                 lexState = COMMENT;
                }
                else
                {
                    lexeme += ch;
                    return Lex(Token::SLASH, lexeme, linenumber);
                }
            
            }
             
            if(ch == '('){
                lexeme += ch;
                return Lex(Token::LPAREN, lexeme, linenumber);
                lexeme.clear();
            
            }
             
            if(ch == ')'){
            lexeme += ch;
               return Lex(Token::RPAREN, lexeme, linenumber);
                lexeme.clear();
            }
             
             if(ch == '.'){
               lexeme+= ch;
               return Lex(Token::ERR, lexeme, linenumber);
                 lexeme.clear();

            }
            
            
               
            if(ch == ';'){
                lexeme += ch;
                return Lex(Token::SC, lexeme, linenumber);
                lexeme.clear();
            }
             
            
             
             if(ch == '!'){
                
                lexeme +=ch;
                return Lex(Token::BANG, lexeme, linenumber);
                 lexeme.clear();
             }
             
             if(ch == '\n'){
                lexeme += ch;
                linenumber++;
                lexeme.clear();
            }
             
            if (ch == '$')
            {
                lexeme += ch;
                return Lex(Token::ERR, lexeme, linenumber);
            }
             
            if (ch == '_')
            {
                 lexeme += ch;
                return Lex(Token::ERR, lexeme, linenumber);
            }

            break;
             
          
             
         case IN_IDENTIFIER:

             if(isalpha(ch) || isdigit(ch)){
                 lexeme +=ch;
                 if(!isalnum(in.peek())) {
                     if (lexeme[0] == '/' && lexeme[1] == '/')
                     {
                         lexState = BEGIN;
                     }
                     else
                     {
                         string upperLex = "";
                     for (int i = 0 ; i<lexeme.length();i++)
                      {
                      upperLex += toupper(lexeme[i]);
                      }
                     if (TMap.count(upperLex)>0)
                     {
                     return Lex(TMap[upperLex], lexeme, linenumber);
                         }
                    return Lex(Token::ID, lexeme, linenumber);
                     }
                 }
                 
             }
             
            
             
             else {
                
                 if(ch == '.'){
                    lexeme.clear();
                    lexeme +=ch;
                
                    return Lex(Token::ERR, lexeme, linenumber);
                     lexeme.clear();
                 }
                 in.putback(ch);
                 
                 if (ch == '/')
                 {
                     lexeme+=ch;
                     lexState = COMMENT;
                     
                 }
              
             
                 

               return Lex(Token::ID, lexeme, linenumber);
             }
             
             
            break;
             
         
         case IN_INTEGER:
             if(isdigit(ch)){
                 lexeme += ch; 
             }
             
             else if(isalpha(ch)){
                 lexeme +=ch;
               
                return Lex(Token::ERR, lexeme, linenumber);
             }
             else{ 
                in.putback(ch);
          return Lex(Token:: INT, lexeme, linenumber);

                
             
             }
            
            break;
             
             
         case IN_STRING:

             if(ch == '"'){
             
           return Lex(Token::STR, lexeme, linenumber);
        
             }
             
             else if(ch == '\\'){
                 if(isalpha(in.peek()) || isspace(in.peek()) || ispunct(in.peek())){
                     if(in.peek() == 'n'){
                         in.get(ch);
                         lexeme += '\n';
                     }
                     
                     else{
                         in.get(ch);
                         lexeme +=ch;
                     }
                 
                 }

                 
                 else{
                 lexeme += "\\";
                 
                 }
                 
             
             }
             
             else if(ch == '\n'){
                 lexeme +=ch;
                 lexeme.insert(0, 1, '"');
              return Lex(Token::ERR, lexeme, linenumber);
             }
            
           else {
             lexeme += ch;
                 
             } 
             
             
            break;
             
        case COMMENT:
             if (ch == '/')
                 {
                     if(isalpha(ch) || isdigit(ch)||isspace(ch)){
                         in.get();
                     }   
                             
                 }
             if(ch == '\n'){
                 linenumber++;
                lexState = BEGIN;
                
             }
              if(isalpha(ch) || isdigit(ch)){
                 
                 if(ch == '\n') {
                     linenumber++;
                    lexState = BEGIN;
                 }
                 
             }
                 
             
            break;
         

         case DONE:
            break;
             
         case ERROR:
             break;
             
     }
    
    }
    
   
   if(in.eof())
   {
       return Lex(Token::DONE, lexeme, linenumber);
    }
		

    return Lex();
    
    
}
