/* Funções de registro: */
void button_listen (int pin); // “pin” passado deve gerar notificações

void timer_set (int ms); // timer deve expirar após “ms” milisegundos


// dever da aplicação usuária implementar
/* Callbacks */
void button_changed (int pin, int v); // notifica que “pin” mudou para “v”

// Uma vez expirado, o timer morre.
void timer_expired (void);

