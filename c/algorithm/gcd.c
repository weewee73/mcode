int gcd(int a,int b){
    int temp;

    if(a<b){/*交换两个数，使大数放在a上*/
        temp = a;
        a = b;
        b = temp;
    }

    while(b! = 0){/*利用辗除法，直到b为0为止*/
        temp = a%b;
        a = b;
        b = temp;
    }

    return a;
}


// greatest common divisor (GCD) or greatest common factor (GCF) or Highest common factor (HCF)
int gcd(int x, int y) {
    if (x == 0) {
        return y;
    }

    while (y != 0) {
        if (x > y) {
            x = x - y;
        }
        else {
            y = y - x;
        }
    }

    return x;
}

// least common multiple
int lcm(int x, int y) {
    return (x * y) / gcd(x, y);
}

/* Recursive Function: Greatest Common Divisor */
int gcdr(int a, int b)
{
    if (a == 0)
        return b;

    return gcdr(b%a, a);
}


unsigned int gcd(unsigned int a, unsigned int b)
{
    int r;
    while(b>0)
    {
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}

unsigned int gcd(unsigned int a, unsigned int b)
{
    while(b^=a^=b^=a%=b);

    return a;
}

unsigned int gcd(unsigned int a,unsigned int b)
{
    return (b>0)?gcd(b,a%b):a;
}
