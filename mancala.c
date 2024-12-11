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
    return;
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
    return;
}

// not done
struct Node *list_choose_pockets() {
    int i;
    int start_idx = 0;
    int end_idx = 6;
    struct Node *head;

    if player_turn != 1 {
        start_idx += 6;
        end_idx += 6;
    }
    for (i = start_idx; i < end_idx; i++) {
        if (points_pockets[i] > 0) {
            head = append_node(head, i);
        }
    }
    return head;
}

// returns pointer of appended node sequence
Node *append_node(struct Node* head, int data) {
    struct Node* new;
    struct Node* next;

    new = malloc(sizeof(struct Node));
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

int count_node(struct Node* head) {
    int count = 0;

    while (head != NULL) {
        count += 1;
        head = head->next;
    }
    return count;
}

void free_all_nodes(struct Node * head) {
    struct Node* next;
    struct Node* now;

    if (head == NULL) {
        return;
    } else {
        now = head;
        while (next->next != NULL) {
            next = now->next;
            free(now);
            now = next;
        }
    }
    return;
}

void print_nodes(struct Node* head) {
    int i;
    int len_node = count_node(head);
    char choises[3*len_node];

    while (head == NULL) {
        return;
    }
    for (i = 0; i < len_node; i++) { // while loop can work as well
        if (player_turn == 1) {
            choises[i*3] = head->data + 'A';
        } else {
            choises[i*3] = head->data - 6 + 'a'; ///watch out!
        } 
        choises[i*3+1] = ','
        choises[i*3+2] = ' '
        head = head->next;
    }

    printf("%s", choises);
}

int conv_pocketcher_idx(char input) {
    if (player_turn == 1) {
        return input - 'A';
    } else {
        return input - 'a' + 6; ///watch out!
    } 
}

bool check_input_in_list(int in_num, struct Node *head) {
    while (head != NULL) {
        if (head->data == in_num) {
            return true;
        }
        head = head->next;
    }
    return false;
}

int get_plyer_input() {
    char input;
    int  input_idx;
    struct Node *choose_pockets;

    choose_pockets = list_choose_pockets()

    printf("")
    printf("player%d's turn! Choose pocket from:", player_turn);
    print_nodes(choose_pockets)
    scanf("%c", &input);
    input_idx = conv_pocketcher_idx(input)

    while(!check_input_in_list(input_idx, choose_pockets)) {
        printf("try again!");
        printf("")
        printf("player%d's turn! Choose pocket from:", player_turn);
        print_nodes(choose_pockets)
        scanf("%c", &input);
        input_idx = conv_pocketcher_idx(input)
    }

    free_all_nodes(choose_pockets);

    return pocket_idx;
}

void calc_move(int pocket_idx) {
    int i;
    int tmp_idx;
    int point_chosen_pocket;

    point_chosen_pocket = points_pockets[pocket_idx];
    points_pockets[pocket_idx] = 0;

    // distribute points in the chosen pocket to one another
    tmp_idx = pocket_idx;
    for (i = 0; i < point_chosen_pocket; i++) {
        if (tmp_idx + i+1 > 11) {
            tmp_idx -= 12;
        }
        points_pockets[tmp_idx + i+1] += 1;

        // if the last pocket is empty, 
        // get points from the last pocket and opponent's pocket that's next to the last pokect
        if (i == point_chosen_pocket-1 and points_pockets[tmp_idx + i+1] == 1) {
            if (player_turn == 1) {
                point_GOAL += points_pockets[tmp_idx + i+1];
                point_GOAL += points_pockets[11 - (tmp_idx + i+1)];
            } else {
                point_goal += points_pockets[tmp_idx + i+1];
                point_goal += points_pockets[11 - (tmp_idx + i+1)];
            }
            points_pockets[tmp_idx + i+1] = 0;
            points_pockets[11 - (tmp_idx + i+1)] = 0;
        }
    }
    return;
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
            return 1;
        }
    }
    for (i = 6; i < 12; i++) {
        if point_pockets[i] != 0 {
            break;
        }
        if i == 11 {
            return 2;
        }
    }
    return 0;
}

// set points for input array
void calc_points(int *point_players) {
    int i;
    *point_plaers = point_GOAL;
    *(point_plaers+1) = point_goal;
    for (i = 0; i < 6; i++) {
        *point_plaers += point_pockets[i]
    }
    for (i = 6; i < 12; i++) {
        *(point_plaers+1) += point_pockets[i]
    }
    return;
}

void main() {
    int points[2];
    int chosen_poecket;

    init_values();
    if (check_game_end == 0) {
        display_holes();
        get_plyer_input();
        calc_move(chosen_poecket);
    }
    calc_points(&(points[0]));
    display_holes();
    
    printf("")
    printf("winner is Player%d!", check_game_end);
    printf("Player1: %2d points, Player2: %2d points", points[0], points[1]);
    return;
}