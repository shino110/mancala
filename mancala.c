#include<stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* next;
} Node;

Node* append_node(Node* head, int data);
int count_node(Node* head);
void print_nodes(Node* head);
int conv_pocketcher_idx(char input);
void free_all_nodes(Node * head);

void init_values();
void display_holes();
int get_plyer_input();
int check_game_end();
void calc_move(int pocket_idx);
void calc_points(int *point_players);

Node *list_choose_pockets();
int check_input_in_list(int in_num, Node *head);

// variables for one game
int point_pockets[14]; // number of points in each pockets
const int player1_goal_idx = 0;
const int player2_goal_idx = 7;
int player_turn;
int game_end;

int main() {
    int chosen_poecket;
    int points[2];

    init_values();
    while (game_end == 0) {
        display_holes();
        chosen_poecket = get_plyer_input();
        calc_move(chosen_poecket);
        game_end = check_game_end();
        if (player_turn == 1) {
            player_turn = 2;
        } else {
            player_turn = 1;
        }
    }
    calc_points(&(points[0]));
    display_holes();

    // 24 points each is draw
    if (points[0] == 24) {
        printf("This game is draw!")
    } else {
        printf("Winner is Player%d!", game_end);
    }
    printf("Player1: %2d points, Player2: %2d points", points[0], points[1]);
    return 0;
}

void init_values() {
    int i;
    for (i = 0; i < 14; i++) {
        point_pockets[i] = 4;
    }
    point_pockets[player1_goal_idx] = 0;
    point_pockets[player2_goal_idx] = 0;
    player_turn = 1;
    game_end = 0;
    return;
}

void display_holes() {
    // pockets’ idx     0     1     2     3     4     5     6
    printf("");
    printf("Player1:  GOAL |  A  |  B  |  C  |  D  |  E  |  F  |  -        \n");
    printf("           %2d  | %2d  | %2d  | %2d  | %2d  | %2d  | %2d  |  - \n", point_pockets[0], point_pockets[1], point_pockets[2], point_pockets[3], point_pockets[4], point_pockets[5], point_pockets[6]);
    printf("        ------------------------------------------------       \n");
    printf("            -  | %2d  | %2d  | %2d  | %2d  | %2d  | %2d  | %2d\n", point_pockets[13], point_pockets[12], point_pockets[11], point_pockets[10], point_pockets[9], point_pockets[8], point_pockets[7]);
    printf("Player2:    -  |  f  |  e  |  d  |  c  |  b  |  a  | goal      \n");
    // pockets' idx           13    12    11   10     9     8     7
    return;
}


Node *list_choose_pockets() {
    int i;
    int start_idx = 1;
    int end_idx = 7;
    Node *head = NULL;

    if (player_turn != 1) {
        start_idx += 7;
        end_idx += 7;
    }
    for (i = start_idx; i < end_idx; i++) {
        if (point_pockets[i] > 0) {
            head = append_node(head, i);
        }
    }
    return head;
}

// returns pointer of appended node sequence
Node *append_node(Node* head, int data) {
    Node* new;
    Node* next;

    new = malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;

    if (head == NULL) {
        return new;
    } else {
        // lock for the tail to add
        next = head;
        while (next->next != NULL) {
            next = next->next;
        }
        next->next = new;
        return head;
    }
}

int count_node(Node* head) {
    int count = 0;

    while (head != NULL) {
        count += 1;
        head = head->next;
    }
    return count;
}

void free_all_nodes(Node * head) {
    Node* next;
    Node* now;

    now = head;
    while (now != NULL) {
        next = now->next;
        free(now);
        now = next;
    }
return;
}

void print_nodes(Node* head) {
    int i;
    int len_node = count_node(head);
    char choises[3*len_node+1];

    while (head == NULL) {
        return;
    }
    for (i = 0; i < len_node; i++) { // while loop can work as well
        if (player_turn == 1) {
            choises[i*3] = head->data - 1 + 'A'; // idx of 'A' = 1
        } else {
            choises[i*3] = head->data - 8 + 'a'; 
        }
        choises[i*3+1] = ',';
        choises[i*3+2] = ' ';
        head = head->next;
    }
    choises[3*len_node] = '\0';

    printf("%s", choises);
}

int conv_pocketcher_idx(char input) {
    if (player_turn == 1) {
        return input - 'A' + 1; // idx of 'A' = 1
    } else {
        return input - 'a' + 8; // idx of 'a' = 8
    }
}

int check_input_in_list(int in_num, Node *head) {
    while (head != NULL) {
        if (head->data == in_num) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

int get_plyer_input() {
    char input;
    int  input_idx;
    Node *choose_pockets;

    choose_pockets = list_choose_pockets();

    printf("player%d's turn! Choose pocket from:", player_turn);
    print_nodes(choose_pockets);
    scanf(" %c", &input);
    input_idx = conv_pocketcher_idx(input);

    while(check_input_in_list(input_idx, choose_pockets) == 0) {
        printf("try again!\n");
        printf("player%d turn! Choose pocket from:", player_turn);
        print_nodes(choose_pockets);
        scanf(" %c", &input);
        input_idx = conv_pocketcher_idx(input);
    }

    free_all_nodes(choose_pockets);

    return input_idx;
}

void calc_move(int pocket_idx) {
    int i;
    int tmp_idx;
    int point_chosen_pocket;

    point_chosen_pocket = point_pockets[pocket_idx];
    point_pockets[pocket_idx] = 0;

    // distribute points in the chosen pocket to the pockets next to 
    tmp_idx = pocket_idx;
    for (i = 1; i < point_chosen_pocket+1; i++) {
        if (tmp_idx - i < 0) {
            tmp_idx += 14;
        }
        point_pockets[tmp_idx - i] += 1;

        // if the last pocket is empty and not opponent's pocket, (exclude goals)
        // get points from the last pocket and opponent’s pocket that’s next to the last pokect
        if (i == point_chosen_pocket && point_pockets[tmp_idx - i] == 1) {
            if (player_turn == 1) {
                if (tmp_idx - i >= 1 && tmp_idx - i < 7) { // my pocket check
                    point_pockets[player1_goal_idx] += point_pockets[tmp_idx - i];
                    point_pockets[player1_goal_idx] += point_pockets[14 - (tmp_idx - i)];
                    point_pockets[tmp_idx - i] = 0;
                    point_pockets[14 - (tmp_idx - i)] = 0;
                }
            } else {
                if (tmp_idx - i >= 8 && tmp_idx - i < 14) {
                    point_pockets[player2_goal_idx] += point_pockets[tmp_idx - i];
                    point_pockets[player2_goal_idx] += point_pockets[14 - (tmp_idx - i)];
                    point_pockets[tmp_idx - i] = 0;
                    point_pockets[14 - (tmp_idx - i)] = 0;
                }
            }
        }
    }
    return;
}

// return 0: game is not over
// return 1: player1 wins
// return 2: player2 wins
int check_game_end() {
    int i;

    for (i = 1; i < 7; i++) {
        if (point_pockets[i] != 0) {
            break;
        }
        if (i == 6) {
            return 1;
        }
    }
    for (i = 8; i < 14; i++) {
        if (point_pockets[i] != 0) {
            break;
        }
        if (i == 13) {
            return 2;
        }
    }
    return 0;
}

// set points for input array
void calc_points(int *point_players) {
    *point_players = 0;
    *(point_players+1) = 0;
    int i;
    for (i = 0; i < 7; i++) {
        *point_players += point_pockets[i];
    }
    for (i = 7; i < 14; i++) {
        *(point_players+1) += point_pockets[i];
    }
    return;
}