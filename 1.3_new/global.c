#define group_num       21
#define num_in_group    17
#define startx          500
#define starty          500

char ProgName[] = "Лабораторна робота 3";
char *Anames[12] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};

const int MATRIX_MAX = (int)(num_in_group/10)+10,
    SEED = group_num*100+num_in_group;
int lastbutton = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND Button_matrix_dir, 
    Button_matrix_undir;