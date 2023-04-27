#include "dynamic_string.h"

typedef struct _Position {
    int x;
    int y;
} Position;

Position *create_position(int x, int y);

Position *position_get_up(Position *position);
Position *position_get_down(Position *position);
Position *position_get_left(Position *position);
Position *position_get_right(Position *position);

String *position_to_string(Position *position);
