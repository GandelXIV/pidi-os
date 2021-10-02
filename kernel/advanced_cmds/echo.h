void ksh_echo()
{
    char* str = (char*) kmalloc(255);
    kprints("Enter string: ");
    kinputs(str);
    kprints(str);
    kprintc('\n');
}