void função(int n){
    if(n>0){
        return funçao(n-1) + funçao(n-1);
    }
    faz_algo;
    return n;
}

verifica_algo(int n){
    int x, y;
    for (x=0 ; x<log(n) ; x++) {
        for(y=0; y < n;y++){
            faz_algo;
        }
    }

}

verifica_algo(int n){
    int x;
    for (x=0 ; x<n ; x++) {
        faz_algo;
 
    }
    if(n > 0){
        return 2* funçao(n-1);
    }

}