/* pmsun.c -- PortMidi os-dependent code */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/audioio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "portmidi.h"
#include "pmutil.h"
#include "pminternal.h"


#define AUDIODEV "/dev/audio"


PmDeviceID pm_default_input_device_id = -1;
PmDeviceID pm_default_output_device_id = -1;

extern pm_fns_node pm_sun_in_dictionary;
extern pm_fns_node pm_sun_out_dictionary;

/* pm_strdup -- copy a string to the heap. Use this rather than strdup so 
 *    that we call pm_alloc, not malloc. This allows portmidi to avoid 
 *    malloc which might cause priority inversion.
 */
char *pm_strdup(const char *s)
{
    int len = strlen(s);
    char *dup = (char *) pm_alloc(len + 1);
    strcpy(dup, s);
    return dup;
}


void pm_init()
{
    audio_info_t auinfo;
    char *audio_dev = NULL, *tmp_audio;

    if ((tmp_audio = getenv("AUDIODEV")) != NULL) {
       struct stat s;

       if (stat(tmp_audio, &s) == 0) {
           audio_dev = pm_strdup(tmp_audio);
       } 
    }
    
    if (audio_dev == NULL) {
        audio_dev=pm_strdup(AUDIODEV);
    }

    // Add output devices
    pm_add_device("SUN_AUDIO",
      audio_dev,
      FALSE,
      (void *)0,
      &pm_sun_out_dictionary);

    // this is set when we return to Pm_Initialize, but we need it
    // now in order to (successfully) call Pm_CountDevices()
    pm_initialized = TRUE;
    pm_default_output_device_id = 0;
}

void pm_term(void)
{
}

PmDeviceID Pm_GetDefaultInputDeviceID() {
    Pm_Initialize();
    return pm_default_input_device_id; 
}

PmDeviceID Pm_GetDefaultOutputDeviceID() {
    Pm_Initialize();
    return pm_default_output_device_id;
}

void *pm_alloc(size_t s) { return malloc(s); }

void pm_free(void *ptr) { free(ptr); }

/* midi_message_length -- how many bytes in a message? */
static int midi_message_length(PmMessage message)
{
    message &= 0xff;
    if (message < 0x80) {
        return 0;
    } else if (message < 0xf0) {
        static const int length[] = {3, 3, 3, 3, 2, 2, 3};
        return length[(message - 0x80) >> 4];
    } else {
        static const int length[] = {
            -1, 2, 3, 2, 0, 0, 1, -1, 1, 0, 1, 1, 1, 0, 1, 1};
        return length[message - 0xf0];
    }
}

static PmError sun_out_open(PmInternal *midi, void *driverInfo)
{
    const char *device = descriptors[midi->device_id].pub.name;
    int *fd;

    fd = pm_alloc(sizeof(int));
    if (fd == NULL) {
        fprintf(stderr, "failed to alloc memory\n");
        return pmHostError;
    }
    fd[0] = open(device, O_WRONLY);
    if (fd[0] < 0) {
        fprintf(stderr, "failed to open devive %s\n", device);
        return pmHostError;
    }
    
    midi->descriptor = fd;

    return pmNoError;
}
static PmError sun_out_close(PmInternal *midi)
{
    int *fd = midi->descriptor;
    if (fd) {
    	close(fd[0]);
    	free(fd);
    }
    return pmNoError;
}
static PmError sun_abort(PmInternal *midi)
{
    int *fd = midi->descriptor;
    if (fd) {
    	close(fd[0]);
    	free(fd);
    }
    return pmNoError;
}
static PmTimestamp sun_synchronize(PmInternal *midi)
{
    return 0;
}
static PmError sun_write_byte(PmInternal *midi, unsigned char byte,
                        PmTimestamp timestamp)
{
    int *fd = midi->descriptor;
    size_t w = write(fd[0], &byte, 1);
    if (w != 1) {
        fprintf(stderr, "device write failed\n");
        return pmHostError;
    }
    return pmNoError;
}
static PmError sun_write_short(PmInternal *midi, PmEvent *event)
{
    int bytes = midi_message_length(event->message);
    PmMessage msg = event->message;
    int i;
    for (i = 0; i < bytes; i++) {
        unsigned char byte = msg;
        sun_write_byte(midi, byte, event->timestamp);
        msg >>= 8;
    }

    return pmNoError;
}
static PmError sun_write_flush(PmInternal *midi, PmTimestamp timestamp)
{
    return pmNoError;
}
PmError sun_sysex(PmInternal *midi, PmTimestamp timestamp)
{
    return pmNoError;
}
static unsigned int sun_has_host_error(PmInternal *midi)
{
    return 0;
}
static void sun_get_host_error(PmInternal *midi, char *msg, unsigned int len)
{
}

/*
pm_fns_node pm_sun_in_dictionary = {
    none_write_short,
    none_sysex,
    none_sysex,
    none_write_byte,
    none_write_short,
    none_write_flush,
    sun_synchronize,
    sun_in_open,
    sun_abort,
    sun_in_close,
    sun_poll,
    sun_has_host_error,
    sun_get_host_error
};
*/

pm_fns_node pm_sun_out_dictionary = {
    sun_write_short,
    sun_sysex,
    sun_sysex,
    sun_write_byte,
    sun_write_short,
    sun_write_flush,
    sun_synchronize,
    sun_out_open,
    sun_abort,
    sun_out_close,
    none_poll,
    sun_has_host_error,
    sun_get_host_error
};

