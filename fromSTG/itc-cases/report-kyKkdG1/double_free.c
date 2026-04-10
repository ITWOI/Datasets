extern void double_free_001 (){
    char *ptr = (char *)malloc(sizeof(char));
    free(ptr);
    free(ptr);
}


