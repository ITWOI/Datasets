extern void double_free_005 (){
    char *ptr = (char *)malloc(sizeof(char));
    int flag = 0;
    while (flag == 0)
        {
            free(ptr);
            flag++;
        }
    free(ptr);
}


