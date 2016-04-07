typedef enum {FALSE,TRUE} Boolean;

Boolean verificaAlpha(char caracter){
    return ( caracter >= 'A' && caracter <= 'Z' ) ? TRUE : FALSE;
}

Boolean verificaNumero(char *num, int min, int max){
    int n;
    n=atoi(num);
    return ( n >=min && n <=max ) ? TRUE : FALSE;  
}


