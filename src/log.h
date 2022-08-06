/*
 * Curse of DND - nCurses DND Character Sheet
 * log.h
 */

/* 
 * Initialize logging functionality
 * Must be run for logging to work!
 */
int log_init();

/*
 * print function for writing to the log
 * only prints to the log if the log has been initialized
 *
 * @fmt: format string
 * @...: variables for passing to format string
 */
void log_print(const char *fmt, ...) 
  __attribute__((format (printf, 1, 2)));
