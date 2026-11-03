#include <stdio.h>

typedef enum {
    CAMERA_TILT_UP_POSITION,
    CAMERA_TILT_STRAIGHT_POSITION,
    CAMERA_TILT_DOWN_POSITION
} CameraTiltState;

typedef enum {
    CAMERA_TILT_PIVOT_UP,
    CAMERA_TILT_PIVOT_DOWN
} CameraTiltCommand;

void next_state(CameraTiltState *state, CameraTiltCommand command) {
    switch (*state) {
        case CAMERA_TILT_DOWN_POSITION: {
            if (command == CAMERA_TILT_PIVOT_DOWN) {
                printf("Servo already in Down Position. Can't pivot down.\n");
            } else if (command == CAMERA_TILT_PIVOT_UP) {
                // servo moves up
                *state = CAMERA_TILT_STRAIGHT_POSITION;
            }
            break;
        }
        case CAMERA_TILT_STRAIGHT_POSITION: {
            if (command == CAMERA_TILT_PIVOT_DOWN) {
                *state = CAMERA_TILT_DOWN_POSITION;
            } else if (command == CAMERA_TILT_PIVOT_UP) {
                *state = CAMERA_TILT_UP_POSITION;
            }
            break;
        }
        case CAMERA_TILT_UP_POSITION: {
            if (command == CAMERA_TILT_PIVOT_DOWN) {
                *state = CAMERA_TILT_STRAIGHT_POSITION;
            } else if (command == CAMERA_TILT_PIVOT_UP) {
                printf("Servo already in Up Position. Can't pivot up.\n");
            }
            break;
        }
    }
}

const char *get_state_name(CameraTiltState s) {
    switch (s) {
        case CAMERA_TILT_DOWN_POSITION: return "CAMERA_TILT_DOWN_POSITION";
        case CAMERA_TILT_STRAIGHT_POSITION: return "CAMERA_TILT_STRAIGHT_POSITION";
        case CAMERA_TILT_UP_POSITION: return "CAMERA_TILT_PIVOT_UP";
    }
    return "UNKNOWN";
}

const char *get_command_name(CameraTiltCommand c) {
    switch (c) {
        case CAMERA_TILT_PIVOT_DOWN: return "CAMERA_TILT_PIVOT_DOWN";
        case CAMERA_TILT_PIVOT_UP: return "CAMERA_TILT_PIVOT_UP";
    }
    return "UNKNOWN";
}

void run_camera_tilt(void) {
    CameraTiltState state;
    CameraTiltCommand command;
    int n;
    int initial_state = CAMERA_TILT_STRAIGHT_POSITION;

    state = initial_state;
    while (1) {
        printf("Current State: %s\n\n", get_state_name(state));
        printf("Enter 0 or 1: ");
        scanf("%d", &n);
        command = (CameraTiltCommand)n;

        printf("Attempting %s command...\n", get_command_name(command));
        next_state(&state, command);
    }
}