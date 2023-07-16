#include <stdio.h>
#include <stdlib.h>

int main()
{
  int Max[10][10], need[10][10], alloc[10][10], avail[10], completed[10], safeSequence[10];
  int p, r, i, j, process, count = 0;

  printf("Enter the number of processes: ");
  scanf("%d", &p);

  for (i = 0; i < p; i++)
    completed[i] = 0;

  printf("\nEnter the number of resources: ");
  scanf("%d", &r);

  printf("\nEnter the Max Matrix and allocation for each process:\n");
  for (i = 0; i < p; i++)
  {
    printf("For process %d: ", i + 1);
    for (j = 0; j < r; j++)
    {
      scanf("%d", &Max[i][j]);
      alloc[i][j] = 0;
    }
  }

  printf("\nEnter the Available Resources:\n");
  for (i = 0; i < r; i++)
  {
    scanf("%d", &avail[i]);
    need[i][j] = Max[i][j] - alloc[i][j];
  }

  do
  {
    process = -1;
    for (i = 0; i < p; i++)
    {
      if (!completed[i])
      {
        process = i;
        for (j = 0; j < r; j++)
        {
          if (avail[j] < need[i][j])
          {
            process = -1;
            break;
          }
        }
      }
      if (process != -1)
        break;
    }

    if (process != -1)
    {
      safeSequence[count++] = process + 1;
      for (j = 0; j < r; j++)
      {
        avail[j] += alloc[process][j];
        alloc[process][j] = 0;
        completed[process] = 1;
      }
    }

  } while (count != p && process != -1);

  printf("\n%s\n", count == p ? "The system is in a safe state!" : "The system is in an unsafe state!");

  if (count == p)
  {
    printf("Safe Sequence: < ");
    for (i = 0; i < p; i++)
      printf("%d ", safeSequence[i]);
    printf(">\n");
  }

  return 0;
}
