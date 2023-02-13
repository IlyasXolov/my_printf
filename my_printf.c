#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define hexNums "0123456789abcdef"

void putchar7(char c){
    write(1, &c, 1);
}

int putstr7(char *s){
    int i;
    for(i = 0; s[i] != '\0'; i++){
        putchar7(s[i]);
    }
    return i;
}

char * int_to_char(int number, char ch){
    if(number == 0){
        return "0";
    }
    char flag;
    char *res = (char*)malloc(10 * sizeof(char));
    *res = '\0';
    if(ch == 'u'){
        if(number < 0){
            number = number * -1;
        }
    }
    if(ch == 'd'){
        if(number < 0){
            number = number * -1;
            flag = '-';
            
        }
    }

    while(number){
        res--;
        *res = number % 10 + '0';
        number /= 10;
    }
    if(flag){
        res--;
        *res = '-';
    }
    return res;
}

int utoa_in_c(long long val, int base){
    if(val == 0) {
        putstr7("0");
        return 1;
    }
    
            int ret = 0;
            int nega = 0;
            if(val < 0) {

                nega = 1;
                val*=-1;
            }



            char buf[32];
            buf[31] = 0;
            int i = 30;
            for(; val && i ; --i, val /= base)
                buf[i] = hexNums[val % base];
            if(nega) {
                putstr7("-");
                ret++;
            }




    putstr7(&buf[i+1]);
    ret += strlen(&buf[i+1]);
    return ret;
}

int my_size(char *str){
    int i;
    for(i = 0; str[i] != '\0'; i++){
    
    }
    return i;
}
char* i_octal(int o){

    char *res = (char*)malloc(10 * sizeof(char));
    while(o){
         res--;
        *res = o % 8 + '0';
        o /= 8; 

    }
    return res;
}

int my_printf(char *format, ...){
    va_list my_list;
    va_start(my_list, format);
    int j = 0;
    int x;
    char c;
    char *string;
     unsigned long a;
    for(int i = 0; format[i] != '\0'; i++){
        if(format[i] == '%'){
            i++;
            switch(format[i]){
                case 'd':
                    x = va_arg(my_list, int);
                    string = int_to_char(x ,'d');
                    j+= my_size(string);
                    putstr7(string);

                break;

                case 'u':
                    x = va_arg(my_list, int);

                    string = int_to_char(x, 'u');
                        
                    putstr7(string);

                    j+= my_size(string);
                
                    break;

                case 'x':
                    x = va_arg(my_list, int);
                    int q;
                    char decimal[100];
                    int l = 0;
                    while(x != 0){
                        q = x % 16;
                        if( q < 10)
                            decimal[l++] = 48 + q;
                        else
                            decimal[l++] = 55 + q;
                        x = x / 16;                    
                    }
                    l--;
                    while(l >= 0){
                        putchar7(decimal[l]);
                        l--;
                        j++;
                    }
                    break;
                    
                case 's':
                    string = va_arg(my_list, char*);
                    if(string == (char*)NULL)
                        string = "(null)";
                    j += putstr7(string);
                    
                break;
                
                case 'c':
                c = (char)va_arg(my_list,int);
                    putchar7(c);
                    j++;
                    break;
                case 'o':
                    x = va_arg(my_list, int);
                    string = i_octal(x);
                    j += putstr7(string);
                break;
                case 'p':
                     a = (unsigned long) va_arg(my_list, void*);
                    putstr7("0x");
                    j += 2;
                    j += utoa_in_c(a, 16);
                break;
                
            }
        }else{
            
            putchar7(format[i]);
            j++;
        }
    }
    
    return j;
}

int main() {
    void* t = malloc(10);
    int d = my_printf("%p\n",t);
    my_printf("%d\n",d);
    free(t); t = "hello";
    d=0;d = my_printf("%s world!\n",t);
    my_printf("%d\n",d);
    
    return 0;
}
