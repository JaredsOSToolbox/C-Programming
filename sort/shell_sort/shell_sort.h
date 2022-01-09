void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shell_sort_(int container[], int size) {
    int i, j, distance, temp;
    distance = 3;
    while (distance > 0) {
        for (i = 0; i < size; ++i) {
            j = i;
            temp = container[i];
            while ((j >= distance) && (container[j - distance] > temp)) {
                container[j] = container[j - distance];
                j -= distance;
            }
            container[j] = temp;
        }
        if (distance / 2 != 0) {
            distance /= 2;
        } else if (distance == 1) {
            distance = 0;
        } else {
            distance = 1;
        }
    }
}
