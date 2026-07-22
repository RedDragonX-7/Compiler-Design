#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULES 20
#define MAX_PROD 10
#define MAX_SYMBOLS 20

// Structure for grammar rule
typedef struct {
    char head;
    char body[MAX_PROD][MAX_SYMBOLS];
    int prod_count;
} GrammarRule;

GrammarRule grammar[MAX_RULES];
int rule_count = 0;

char first_sets[26][50];
char follow_sets[26][50];

// Check if symbol is a non-terminal
bool is_non_terminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

// Add symbol to set uniquely
bool add_to_set(char set[], char c) {
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == c)
            return false;
    }

    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
    return true;
}

// Merge one set into another
bool merge_sets(char dest[], char src[], bool ignore_epsilon) {
    bool changed = false;

    for (int i = 0; src[i] != '\0'; i++) {

        if (ignore_epsilon && src[i] == 'e')
            continue;

        if (add_to_set(dest, src[i]))
            changed = true;
    }

    return changed;
}

// Check if FIRST contains epsilon
bool has_epsilon(char set[]) {

    for (int i = 0; set[i] != '\0'; i++)
        if (set[i] == 'e')
            return true;

    return false;
}

// FIRST computation
void compute_first() {

    bool changed = true;

    while (changed) {

        changed = false;

        for (int i = 0; i < rule_count; i++) {

            int head = grammar[i].head - 'A';

            for (int j = 0; j < grammar[i].prod_count; j++) {

                char *prod = grammar[i].body[j];

                if (prod[0] == 'e') {

                    if (add_to_set(first_sets[head], 'e'))
                        changed = true;

                } else {

                    bool nullable = true;

                    for (int k = 0; prod[k] != '\0' && nullable; k++) {

                        char sym = prod[k];

                        if (!is_non_terminal(sym)) {

                            if (add_to_set(first_sets[head], sym))
                                changed = true;

                            nullable = false;

                        } else {

                            int idx = sym - 'A';

                            if (merge_sets(first_sets[head],
                                           first_sets[idx], true))
                                changed = true;

                            if (!has_epsilon(first_sets[idx]))
                                nullable = false;
                        }
                    }

                    if (nullable) {
                        if (add_to_set(first_sets[head], 'e'))
                            changed = true;
                    }
                }
            }
        }
    }
}

// FOLLOW computation
void compute_follow(char start) {

    add_to_set(follow_sets[start - 'A'], '$');

    bool changed = true;

    while (changed) {

        changed = false;

        for (int i = 0; i < rule_count; i++) {

            int head = grammar[i].head - 'A';

            for (int j = 0; j < grammar[i].prod_count; j++) {

                char *prod = grammar[i].body[j];

                for (int k = 0; prod[k] != '\0'; k++) {

                    char cur = prod[k];

                    if (!is_non_terminal(cur))
                        continue;

                    int cur_idx = cur - 'A';

                    bool nullable = true;

                    for (int n = k + 1; prod[n] != '\0' && nullable; n++) {

                        char next = prod[n];

                        if (!is_non_terminal(next)) {

                            if (add_to_set(follow_sets[cur_idx], next))
                                changed = true;

                            nullable = false;

                        } else {

                            int next_idx = next - 'A';

                            if (merge_sets(follow_sets[cur_idx],
                                           first_sets[next_idx], true))
                                changed = true;

                            if (!has_epsilon(first_sets[next_idx]))
                                nullable = false;
                        }
                    }

                    if (nullable) {

                        if (merge_sets(follow_sets[cur_idx],
                                       follow_sets[head], false))
                            changed = true;
                    }
                }
            }
        }
    }
}

int main() {

    // Initialize FIRST and FOLLOW sets
    for (int i = 0; i < 26; i++) {
        first_sets[i][0] = '\0';
        follow_sets[i][0] = '\0';
    }

    // Grammar:
    // E -> TA
    grammar[rule_count].head = 'E';
    strcpy(grammar[rule_count].body[0], "TA");
    grammar[rule_count].prod_count = 1;
    rule_count++;

    // A -> +TA | e
    grammar[rule_count].head = 'A';
    strcpy(grammar[rule_count].body[0], "+TA");
    strcpy(grammar[rule_count].body[1], "e");
    grammar[rule_count].prod_count = 2;
    rule_count++;

    // T -> FB
    grammar[rule_count].head = 'T';
    strcpy(grammar[rule_count].body[0], "FB");
    grammar[rule_count].prod_count = 1;
    rule_count++;

    // B -> *FB | e
    grammar[rule_count].head = 'B';
    strcpy(grammar[rule_count].body[0], "*FB");
    strcpy(grammar[rule_count].body[1], "e");
    grammar[rule_count].prod_count = 2;
    rule_count++;

    // F -> (E) | i
    grammar[rule_count].head = 'F';
    strcpy(grammar[rule_count].body[0], "(E)");
    strcpy(grammar[rule_count].body[1], "i");
    grammar[rule_count].prod_count = 2;
    rule_count++;

    compute_first();
    compute_follow('E');

    printf("========== FIRST SETS ==========\n");

    for (int i = 0; i < rule_count; i++) {

        char head = grammar[i].head;

        printf("FIRST(%c) = { ", head);

        char *s = first_sets[head - 'A'];

        for (int j = 0; s[j] != '\0'; j++) {

            printf("%c", s[j]);

            if (s[j + 1] != '\0')
                printf(", ");
        }

        printf(" }\n");
    }

    printf("\n========== FOLLOW SETS ==========\n");

    for (int i = 0; i < rule_count; i++) {

        char head = grammar[i].head;

        printf("FOLLOW(%c) = { ", head);

        char *s = follow_sets[head - 'A'];

        for (int j = 0; s[j] != '\0'; j++) {

            printf("%c", s[j]);

            if (s[j + 1] != '\0')
                printf(", ");
        }

        printf(" }\n");
    }

    return 0;
}