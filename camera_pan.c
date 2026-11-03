#include <stdio.h>

typedef enum {
    CAMERA_PAN_LEFT_POSITION,
    CAMERA_PAN_RIGHT_POSITION,
    CAMERA_PAN_FORWARD_POSITION,
    CAMERA_PAN_LEFT_FORWARD_POSITION,
    CAMERA_PAN_RIGHT_FORWARD_POSITION
} CameraPanState;

typedef enum {
    CAMERA_PAN_PIVOT_RIGHT,
    CAMERA_PAN_PIVOT_LEFT
} CameraPanCommand;

void next_state(CameraPanState *state, CameraPanCommand command) {
    switch (*state) {
        case CAMERA_PAN_LEFT_POSITION: {
            if (command == CAMERA_PAN_PIVOT_LEFT) {
                printf("Servo already in CAMERA_PAN_LEFT_POSITION. Can't go further left.\n");
            } else if (command == CAMERA_PAN_PIVOT_RIGHT) {
                // servo command function
                *state = CAMERA_PAN_LEFT_FORWARD_POSITION;
            }
            break;
        }
        case CAMERA_PAN_LEFT_FORWARD_POSITION: {
            if (command == CAMERA_PAN_PIVOT_LEFT) {
                // servo command function
                *state = CAMERA_PAN_LEFT_POSITION;
            } else if (command == CAMERA_PAN_PIVOT_RIGHT) {
                // servo command function
                *state = CAMERA_PAN_FORWARD_POSITION;
            }
            break;
        }
        case CAMERA_PAN_FORWARD_POSITION: {
            if (command == CAMERA_PAN_PIVOT_LEFT) {
                // servo command function
                *state = CAMERA_PAN_LEFT_FORWARD_POSITION;
            } else if (command == CAMERA_PAN_PIVOT_RIGHT) {
                // servo command function
                *state = CAMERA_PAN_RIGHT_FORWARD_POSITION;
            }
            break;
        }
        case CAMERA_PAN_RIGHT_FORWARD_POSITION: {
            if (command == CAMERA_PAN_PIVOT_LEFT) {
                // servo command function
                *state = CAMERA_PAN_FORWARD_POSITION;
            } else if (command == CAMERA_PAN_PIVOT_RIGHT) {
                // servo command function
                *state = CAMERA_PAN_RIGHT_POSITION;
            }
            break;
        }
        case CAMERA_PAN_RIGHT_POSITION: {
            if (command == CAMERA_PAN_PIVOT_LEFT) {
                // servo command function
                *state = CAMERA_PAN_RIGHT_FORWARD_POSITION;
            } else if (command == CAMERA_PAN_PIVOT_RIGHT) {
                printf("Servo already in CAMERA_PAN_RIGHT_POSITION. Can't go further right.\n");
            }
            break;
        }
    }
}

const char *get_command_name(CameraPanCommand c) {
    switch (c) {
        case CAMERA_PAN_PIVOT_LEFT: return "CAMERA_PAN_PIVOT_LEFT";
        case CAMERA_PAN_PIVOT_RIGHT: return "CAMERA_PAN_PIVOT_RIGHT";
    }
    return "UNKNOWN";
}

const char *get_state_name(CameraPanState s) {
    switch (s) {
        case CAMERA_PAN_LEFT_POSITION: return "CAMERA_PAN_LEFT_POSITION";
        case CAMERA_PAN_LEFT_FORWARD_POSITION: return "CAMERA_PAN_LEFT_FORWARD_POSITION";
        case CAMERA_PAN_FORWARD_POSITION: return "CAMERA_PAN_FORWARD_POSITION";
        case CAMERA_PAN_RIGHT_FORWARD_POSITION: return "RIGHT_FORWORD_POSITION";
        case CAMERA_PAN_RIGHT_POSITION: return "CAMERA_PAN_RIGHT_POSITION";
    }
    return "UNKNOWN";
}

void run_camera_pan(void) {
    CameraPanState state;
    CameraPanCommand command;
    int n;
    int initial_state = CAMERA_PAN_FORWARD_POSITION;

    state = initial_state;
    while (1) {
        printf("Current State: %s\n\n", get_state_name(state));
        printf("Enter 0 or 1: ");
        scanf("%d", &n);
        command = (CameraPanCommand)n;

        printf("Attempting %s command...\n", get_command_name(command));
        next_state(&state, command);
    }
}