#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Room {
    Position position;
    struct Room* connected_rooms[4];
} Room;

typedef struct Room_QueueNode {
    Room* room;
    struct Room_QueueNode* next;
} QueueNode;

typedef struct Room_Queue {
    int length;
    QueueNode* start;
    QueueNode* end;
} RoomQueue;

typedef struct DynamicArray {
    Room** values;
    int length;
    int allocated_length;
} RoomArray;

Position NEIGHBOUR_COORDINATES[4] = {
    {0, 1},  // up
    {1, 0},  // right
    {0, -1}, // down
    {-1, 0}  // left 
};

RoomQueue room_queue;
RoomArray generated_rooms;

void enqueue(RoomQueue *queue, Room *room){

    QueueNode* new_node=malloc(sizeof(QueueNode));

    new_node->room=room;
    new_node->next = NULL;

    if (queue->end==NULL) {

        queue->start=new_node;
        queue->end=new_node;
   
    }else {        
        queue->end->next=new_node;
        queue->end = new_node;    
    }
    queue->length++;
}


Room *dequeue(RoomQueue *queue){

    QueueNode *new_Dnode= queue->start;
    Room *new_room=new_Dnode->room;
    queue->start = new_Dnode->next;

    if (queue->start==NULL) {
        queue->end =NULL;
    }
    
    free(new_Dnode);

    queue->length--;

    return new_room;
}

// inicializa a room
Room new_room(int x, int y){
    
    Room *room=malloc(sizeof(Room));
    room->position.x=x;
    room->position.y=y;
    for (int i =0; i<4 ; i++) {
        room->connected_rooms[i]=NULL;
    }

    return *room;
} 
// de maneira "random" adiciona a conexão nas salas com base na posiçao das salas 
void add_connection_to_room(Room *base_room, int base_door_index, Room *room_to_connect ){
    base_room->connected_rooms[base_door_index]=room_to_connect;
    room_to_connect->connected_rooms[(base_door_index+2) %4]=base_room;
}

// cria a posiçao da salas 
Room *create_room(int x , int y,int index){
    Room *room=NULL;
    switch (index) {
        case 0: *room=new_room(x,y+1);
            break;
        case 1: *room=new_room(x+1, y);
            break;
        case 2: *room=new_room(x,y-1);
            break;
        case 3: *room=new_room(x-1, y);
    
    }

    return room;

}

Room *get_neighbour(int x , int y , int index){
    x = x + NEIGHBOUR_COORDINATES[index].x;
    y = y + NEIGHBOUR_COORDINATES[index].y;

    for (int i =0; i<generated_rooms.length; i++) {
        if (generated_rooms.values[i]->position.x==x && generated_rooms.values[i]->position.y==y) {
            
            return generated_rooms.values[i];
        }
    }
    return NULL ;
}




void create_map(){

    Room spawn_room = new_room(0,0) ;
    room_queue.length=0;
    room_queue.start=NULL;
    room_queue.end=NULL;
    
    generated_rooms.length=1 ;
    generated_rooms.allocated_length=10;
    generated_rooms.values=malloc(sizeof(Room**)*10);
    generated_rooms.values[0]= &spawn_room;


    room_queue.start = malloc(sizeof(QueueNode));
    room_queue.start->room = &spawn_room;
    room_queue.start->next = NULL;
    room_queue.end = room_queue.start;
    room_queue.length=1;

    while (room_queue.length>0) {
        
        QueueNode* current_node = room_queue.start;
        Room* current_room = current_node->room;

        for (int j=0; j<4; j++) {
            
            int target_x= current_room->position.x + NEIGHBOUR_COORDINATES[j].x;
            int target_y= current_room->position.y + NEIGHBOUR_COORDINATES[j].y;

            Room* neighbour_room=get_neighbour(target_x, target_y, j);
        
            if (neighbour_room==NULL) {
                Room* new_room = create_room(target_x, target_y, j);
                add_connection_to_room(current_room, j , new_room);
                
                if (generated_rooms.length==generated_rooms.allocated_length) {
                    generated_rooms.values=realloc( generated_rooms.values,sizeof(Room*) *(generated_rooms.allocated_length *2));
                }

                generated_rooms.values[generated_rooms.allocated_length++]=new_room;

                QueueNode*new_node= malloc(sizeof(QueueNode));
                new_node->room=new_room;
                new_node->next=NULL;
                
                if (room_queue.end==NULL) {
                    
                    room_queue.start=new_node;
                    room_queue.end = new_node;
                }else {
                    room_queue.end->next=new_node;
                    room_queue.end = new_node;
                }
                room_queue.length++;

                //enqueue(room_queue,new_room );
            }else{    
                   add_connection_to_room(current_room, j, neighbour_room);
            }
        }

        room_queue.start = current_node->next;
        free(current_node);
        room_queue.length--;
    }
}




