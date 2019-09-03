#include <stdio.h>
#include <string.h>

/*int fun(char *p) {
    if (p == NULL || *p == '\0') return 0;
    int current = 1, i = 1;

    while (*(p+current)) {
        if (p[current] != p[current-1]) {
            p[i] = p[current];
            i++;
        }

        current++;
    }

    *(p+i)='\0';
    printf("%s",p);
    return i;
}*/
/*void fun(char *str1, char *str2){

    char *temp = str1;

    str1 = str2;

    str2 = temp;

    printf("str1 is %s, str2 is %s \n", str1, str2);

}

void fun1(char *str1, char *str2){

    fun(str1,str2);

    printf("str1 is %s, str2 is %s \n", str1, str2);

}*/
/*void fun(char *s){
    char p[20];
    int length = strlen(s);
    int i;

    for (i = 0; i < length; i++) {
        p[i] = s[length  - i];
    }

    printf("%s", p);
}*/

void fun(char *a, char *b)

{

    int m = strlen(a);

    int n = strlen(b);

    int i;

    for (i = 0; i <= n; i++)

        a[m+i]  = b[i];

}



int main()

{

    char * str1 = "ECE ";

    char str2[10] = "463 ";

    fun(str1, str2);

    printf("%s ", str1);

    return 0;

}

/*int main() {
    //int x = fun("Internet");
    //fun("EEEEE");
    //fun("Internet");
    fun1("IP", "Protocol");
    //fun("ECE will provide answers to all questions in the universe");
    //char arr[] = "ECE463";
    //printf("%c", *(arr+3));
    //printf("%s", arr+3);

    return 0;
}*/