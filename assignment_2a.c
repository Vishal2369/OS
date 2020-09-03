#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void qSORT(int arr[], int low, int high);
int PART(int arr[], int low, int high);
void MERGE_SORT(int arr[], int low, int high);
void MERGE(int arr[], int low, int mid, int high);

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int main() {
  int n;
  scanf("%d", &n);

  int arr[n];
  for (int i = 0; i < n; i++) arr[i] = i + 1;

  int pid = fork();

  if (pid == 0) {
    printf("Executing Child Process with ID: %d", getpid());

    qSORT(arr, 0, n - 1);

    printf("After Sorting: \n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    printf("\n");

  } else {
    printf("Executing Parent Process with ID: %d", getpid());

    MERGE_SORT(arr, 0, n - 1);

    printf("After Sorting: \n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    printf("\n");
  }
}

void qSORT(int arr[], int low, int high) {
  if (low < high) {
    int PIV = PART(arr, low, high);

    qSORT(arr, low, PIV);
    qSORT(arr, PIV + 1, high);
  }
}

int PART(int arr[], int low, int high) {
  int PIV = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] < high) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void MERGE_SORT(int arr[], int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;

    MERGE_SORT(arr, low, mid);
    MERGE_SORT(arr, mid + 1, high);

    MERGE(arr, low, mid, high);
  }
}

void MERGE(int arr[], int low, int mid, int high) {
  int n = mid - low + 1;
  int m = high - low;

  int left[n], right[m];

  for (int i = 0; i < n; i++) left[i] = arr[low + i];
  for (int i = 0; i < m; i++) right[i] = arr[mid + i + 1];

  int i = 0, j = 0, k = low;

  while (i < n && j < m) {
    if (left[i] < right[j]) {
      arr[k] = left[i];
      i++;
    } else {
      arr[k] = right[j];
      j++;
    }
    k++;
  }

  while (i < n) {
    arr[k] = left[i];
    i++;
    k++;
  }

  while (j < m) {
    arr[k] = right[j];
    j++;
    k++;
  }
}