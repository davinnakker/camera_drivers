#ifndef RUN_CAMERA_TILT_H
#define RUN_CAMERA_TILT_H

typedef enum {
    CAMERA_TILT_UP_POSITION,
    CAMERA_TILT_STRAIGHT_POSITION,
    CAMERA_TILT_DOWN_POSITION
} CameraTiltState;

typedef enum {
    CAMERA_TILT_PIVOT_UP,
    CAMERA_TILT_PIVOT_DOWN
} CameraTiltCommand;

void run_camera_tilt(void);

#endif