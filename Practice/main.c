#include<stdio.h>

void permute(char *s, int l, int r){
    int i;
    if(l==r)
    printf("\n%s ", s);

    else{
        for(i=0; i<= r; i++){
            swap(&s[l], &s[i]);
            permute (s, l+1, r);
            swap(&s[l], &s[i]);
        }
    }
}

int main(){
    permute("CAT", 0, 2);
}