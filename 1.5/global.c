#define group_num       21
#define num_in_group    17
#define startx          500
#define starty          500

char ProgName[] = "Лабораторна робота 5";

const int MATRIX_MAX = (int)(num_in_group/10)+10,
    SEED = group_num*100+num_in_group;
int lastbutton = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND Button_matrix_dir;