void bubble_sort(int nums[], int n);
void selection_sort(int nums[], int n);
void insertion_sort(int nums[], int n);
void quick_sort(int nums[], int n);
void merge_sort(int nums[], int n);
void heap_sort(int nums[], int n);
void shell_sort(int nums[], int n);
void counting_sort(int nums[], int n);
void radix_sort(int nums[], int n);
void shaker_sort(int nums[], int n);
void flash_sort(int nums[], int n);

extern void (*typeOfSort[])(int nums[], int n);
extern const char* typeOfSortName[];
extern const int nOfSort;