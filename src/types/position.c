#include "../../includes/types/position.h"
#include <stdio.h>

Position create_position(int x, int y) {
    Position position = {x, y};
    return position;
}

Position position_get_up(Position position) {
    Position up = {position.x, position.y - 1};
    return up;
}

Position position_get_down(Position position) {
    Position down = {position.x, position.y + 1};
    return down;
}

Position position_get_left(Position position) {
    Position left = {position.x - 1, position.y};
    return left;
}

Position position_get_right(Position position) {
    Position right = {position.x + 1, position.y};
    return right;
}

String position_to_string(Position position) {
    char *buffer = malloc(sizeof(char) * 16);
    snprintf(buffer, sizeof(buffer), "(%d, %d)", position.x, position.y);
    String string = create_string(buffer);
    free(buffer);
    return string;
}
