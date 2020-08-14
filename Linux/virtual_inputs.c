#include "virtual_inputs.h"

// fd - File Description
void init_key(int* fd)
{

   // File description for uinput
   *fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

   /*
    * The ioctls below will enable the device that is about to be
    * created, to pass key events.
    */
   ioctl(*fd, UI_SET_EVBIT, EV_REL);
   ioctl(*fd, UI_SET_RELBIT, REL_X);
   ioctl(*fd, UI_SET_RELBIT, REL_Y);

   ioctl(*fd, UI_SET_EVBIT, EV_KEY);
  // for(int index = 1; index < 0x73; index++)
  // 	ioctl(fd, UI_SET_KEYBIT, virtual_keycode[index]);

   memset(&usetup, 0, sizeof(usetup));
   usetup.id.bustype = BUS_USB;
   usetup.id.vendor = 0x1234; /* sample vendor */
   usetup.id.product = 0x5678; /* sample product */
   strcpy(usetup.name, "Example device");

   ioctl(*fd, UI_DEV_SETUP, &usetup);
   ioctl(*fd, UI_DEV_CREATE);

   sleep(1);
}

void emit(int*fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   /* timestamp values below are ignored */
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(*fd, &ie, sizeof(ie));
}

void send_key(int* fd, int index)
{
   ioctl(*fd, UI_SET_KEYBIT, virtual_keycode[index]);
   emit(fd, EV_KEY, virtual_keycode[index], 1);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, virtual_keycode[index], 0);
   emit(fd, EV_SYN, SYN_REPORT, 0);
}

void send_mice_coord(int* fd, int x, int y)
{
   emit(fd, EV_REL, REL_X, x);
   emit(fd, EV_REL, REL_Y, y);
   emit(fd, EV_SYN, SYN_REPORT, 0);
}

void destroy_key(int* fd)
{
   sleep(1);
   ioctl(*fd, UI_DEV_DESTROY);
   close(*fd);
}