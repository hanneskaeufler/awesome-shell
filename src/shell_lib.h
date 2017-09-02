int ash_execute_command(char **args);
void ash_input_loop();
char *ash_read_line(int (*getchar_fn)(void));
char **ash_split_line(char *line);
