#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swapstrings (char **str, int first, int second)
{
    char *tmp = str[first];
    str[first] = str[second];
    str[second] = tmp;
}

void bubbleSort (char ** str, int size)
{
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (strcmp(str[j], str[j+1]) > 0)
                swapstrings(str, j, j+1);
}

void insertionSort (char ** str, int size)
{
    int i, j;
    char *temp;
    for (i = 1; i < size; i++)
        {
            temp = str[i];
            for (j = i - 1; j >= 0; j--)
                {
                    if (strcmp(temp, str[j]) > 0) break;
                    str[j + 1] = str[j];
                    str[j] = temp;
                }
        }
}


void mergeSort(char **str, int l, int r)
{
  if (l == r - 1) return;
  int mid = (l + r) / 2;
  mergeSort(str, l, mid);
  mergeSort(str, mid, r);

  char **tmparray = (char **) malloc((r-l) * sizeof(char *));
  if (tmparray == NULL)
  {
    printf("no memory");
    return;
  }
  int firstpath = l;
  int secondpath = mid;
  int i=0, end;
  while (firstpath<mid && secondpath<r)
  {
      if (strcmp(str[secondpath], str[firstpath]) > 0)
      {
        tmparray[i] = str[firstpath];
        i++;
        firstpath++;
        end = firstpath;
      }
      else
      {
        tmparray[i] = str[secondpath];
        i++;
        secondpath++;
        end = secondpath;
      }
  }

  if (end == firstpath)
  {
    while (secondpath<r)
    {
        tmparray[i] = str[secondpath];
        i++;
        secondpath++;
    }
  }
  else
  {
    while (firstpath<mid)
    {
        tmparray[i] = str[firstpath];
        i++;
        firstpath++;
    }
  }

  for (i = 0; i < r - l; i++)
  {
    str[l+i] = tmparray[i];
  }

  free (tmparray);
}

void quickSort(char **str, int left, int right)
{
    if (left < right)
    {
        int leftptr = left, rightptr = right;
        char *middle = str[(leftptr + rightptr) / 2];
        do
        {
            while (strcmp(middle, str[leftptr]) > 0) leftptr++;
            while (strcmp(str[rightptr], middle) > 0) rightptr--;
            if (leftptr <= rightptr)
            {
                swapstrings (str, leftptr, rightptr);
                leftptr++;
                rightptr--;
            }
        } while (leftptr <= rightptr);
        quickSort(str, left, rightptr);
        quickSort(str, leftptr, right);
    }
}

void formheap(char **str, int root, int bottom)
{
  int maxChild;
  int done = 0;

  while ((root * 2 <= bottom) && (!done))
  {
    if (root * 2 == bottom)
      maxChild = root * 2;
    else if (strcmp(str[root*2], str[root*2+1]) > 0)
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
    if (strcmp(str[maxChild], str[root]) > 0)
    {
      swapstrings(str, root, maxChild);
      root = maxChild;
    }
    else
      done = 1;
  }
}

void heapSort(char **str, int size)
{
  int i;
  for (i = (size / 2) - 1; i >= 0; i--)
    formheap(str, i, size - 1);
  for (i = size - 1; i >= 1; i--)
  {
    swapstrings(str, 0, i);
    formheap(str, 0, i - 1);
  }
}

int main (int argc, char *argv[])
{
  FILE *file;
  if ((file = fopen(argv[2], "r")) == NULL)
    {
      printf("file is not open");
      return 0;
    }
  int number_str = atoi (argv[1]);
  char **str = (char **) malloc (number_str*sizeof(char *));
  if (str == NULL)
    {
      printf("no memory");
      return 0;
    }

  int i;
  for (i=0; i<number_str; i++)
  {
      int size=32, len=0;
      str[i] = (char *) malloc (size*sizeof(char));
      if (str[i] == NULL)
      {
        printf("no memory");
        return 0;
      }
      str[i][len] = fgetc(file);
      while (str[i][len] != '\n' )
      {
          if ( str[i][len] == EOF){
            str[i][len] = '\n';
            break;
          }

          len++;
          if (len==size)
          {
              size=size*2;
              str[i]=(char *) realloc (str[i], size*sizeof(char));
              if (str[i] == NULL)
              {
                printf("no memory");
                return 0;
              }
          }
          str[i][len] = fgetc(file);
      }
  }

  char algorithm = argv[3][0];

    switch (algorithm){
        case 'b':
            bubbleSort(str, number_str);
            break;
        case 'i':
            insertionSort(str, number_str);
            break;
        case 'm':
            mergeSort(str, 0, number_str);
            break;
        case 'q':
            quickSort(str, 0, number_str-1);
            break;
        case 'h':
            heapSort(str, number_str);
            break;
        default:
            printf ("wrong algorithm name\n");
            break;
    }

  for (i=0; i<number_str; i++)
    {
        printf("%s", str[i]);
        free(str[i]);
    }
  free(str);
  fclose(file);
  return 0;
}
