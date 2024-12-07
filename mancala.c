#include<studio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* next;
} Node;

// variables for one game
int point_pockets[12]; // number of points in each pockets
int point_GOAL; // number of points in player1's goal
int point_goal; // number of points in player2's goal
int player_turn;

void init_values() {
    int i;
    for (i = 0; i < 12; i++) {
        point_pockets[i] = 4;
    }
    point_GOAL = 0;
    point_goal = 0;
    player_turn = 1;
    return
}

void display_holes() {
    // pockets' idx           0     1     2     3     4     5
    printf("")
    printf("Player1:  GOAL |  A  |  B  |  C  |  D  |  E  |  F  |  -");
    printf("           %2d  |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d |  -");
    printf("        ------------------------------------------------");
    printf("            -  |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d");
    printf("Player2:    -  |  f  |  e  |  d  |  c  |  b  |  a  | goal");
    // pockets' idx           11    10    9     8     7     6
    return
}

// not done
int *list_choose_pockets() {
    int i;
    int start_idx = 0;
    int end_idx = 6;

    if player_turn != 1 {
        start_idx += 6;
        end_idx += 6;
    }
    for(i = start_idx; i < end_idx; i++) {
        if (points_pockets[i] > 0) {
            choose_pockets[next_idx] = i;
            next_idx += 1;
        }
    }
}



void print_node()

bool check_input_in_list() {

}

int get_plyer_input() {
    char input;

    printf("")
    printf("player%d's turn! Choose pocket from:%s", player_turn, XXXX)
    scanf("%c", &input);

    while(!check_input_in_list()) {
        printf("try again!");
        printf("Choose pocket from:%s", XXX)
        scanf("%c", &input);
    }

    if (player_turn == 1) {
        return input - 'A'
    } else {
        return input - 'a' + 6 ///watch out!
    } 
}

// return 0: game is not over
// return 1: player1 wins
// return 2: player2 wins
int check_game_end() {
    int i;
    for (i = 0; i < 6; i++) {
        if point_pockets[i] != 0 {
            break;
        }
        if i == 5 {
            return 1
        }
    }
    for (i = 6; i < 12; i++) {
        if point_pockets[i] != 0 {
            break;
        }
        if i == 11 {
            return 2
        }
    }
}

// returns pointer of [player1's point, player2's point]
int *calc_points() {
    int i;
    int *point_players = malloc(sizeof(int) * 2);
    point_plaers[0] = point_GOAL;
    point_plaers[1] = point_goal;
    for (i = 0; i < 6; i++) {
        point_plaers[0] += point_pockets[i]
    }
    for (i = 6; i < 12; i++) {
        point_plaers[1] += point_pockets[i]
    }
    return point_players;
}


void main() {
    int *points;
    int *choose_pockets;
    int chosen_poecket;

    init_values();
    if (check_game_end == 0) {
        display_holes();
        choose_pockets = list_choose_pockets();
        chosen_poecket = get_plyer_input(choose_pockets);
        calc_move(chosen_poecket);

        free(choose_pockets);
        free(chosen_poecket);
    }
    points = calc_points();
    display_holes();
    
    printf("")
    printf("winner is Player%d!", check_game_end);
    printf("Player1: %2d points, Player2: %2d points", points[0], points[1]);

    free(points);
    return
}