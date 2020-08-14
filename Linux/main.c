#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "virtual_inputs.h"

int main(void)
{

    int x = 23, y = ((x-30)*(x-30))-50, fd;
    init_key(&fd);

    sleep(2);

    send_key(&fd,14);
    send_key(&fd,2);
    send_key(&fd,3);

   while (x < 45) {
      send_mice_coord(&fd,x,y);
      x++;
      y = ((x-30)*(x-30))-50;
      usleep(100000);
   }

    destroy_key(&fd);
    
    return 1;
}
