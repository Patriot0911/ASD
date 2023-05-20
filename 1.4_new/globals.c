char ProgName[] = "Лабораторна робота 4";

#define group_num       21
#define num_in_group    17
#define startx          500
#define starty          500
#define sradius         30

HWND Button_matrix_dir, 
    Button_matrix_undir, 
    Button_matrix_modif,
    Button_pathes,
    Button_access,
    Button_strong;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const int MATRIX_MAX = (int)(num_in_group/10)+10, 
    SEED = group_num*100+num_in_group;

/* For components of Strongly Connection (bad realization)*/
int* d_visited;
int* stack;
int* components;