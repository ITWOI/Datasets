extern void zero_division_004_func_001 (){
    zero_division_004_s_gbl.divisor = 0;
}


extern void zero_division_004 (){
    int dividend = 1000;
    int ret;
    zero_division_004_func_001();
    ret = dividend / zero_division_004_s_gbl.divisor;
}


