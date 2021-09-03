int 
bitcount(STYPE value)
{
    int count = 0;
    UTYPE value1 = value;
    while(value1 > 0){
        count += value1 & 1;
        value1 >>= 1;
    }
    return count;
}
