#include "dining.h"


int main(void) {

  for (int i = 0; i < count; i++)
      pthread_create (&philos[i], NULL, philosopher, (void *)i);
  for (int i = 0; i < count; i++)
      pthread_join (philos[i], NULL);
  return 0;
}
