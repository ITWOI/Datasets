extern void double_free_003 (){
    char *ptr = (char *)malloc(sizeof(char));
    int flag = 0;
    if (flag >= 0)
        free(ptr);
    free(ptr);
}


