#DEFINE PINMAX 100


typedef struct button
{
	int pin;
	int value;

} Button;

Button buttonList[PINMAX];
int pinCount = 0;
int expireTime = 0;
int oldtime = MAX_INT;

void initButtonList()
{
	int i;
	for(i=0;i<PINMAX;i++)
	{
		buttonList[i].pin = -1;
		buttonList[i].value = -1;
	}

}
/* Funções de registro: */
void button_listen (int pin) 
{
	Button button;
	if(pinCount == PINMAX )
	{
		printf("Not that many pins allowed\n");
		printf("Aborting\n");
		exit(01);
	}
	buttonList[pinCount].pin = pin;
	pinCount++;
 // “pin” passado deve gerar notificações
}
void timer_set (int ms) 
{
	expireTime = ms;
	oldtime = millis();
 // timer deve expirar após “ms” milisegundos
}
/* Callbacks */
void button_changed (int pin, int v); // notifica que “pin” mudou para “v”
void timer_expired (void);

 



/* Programa principal: */
void setup () 
{ 
	initButtonList();
	init();
}

void loop () 
{ 
	int i;
	int val;
	int nowtime;
	for(i=0;i<pinCount;i++)
	{
		val = digitalRead(pins[i]);
		if(val != buttonList[i].val)
		{
			button_changed(buttonList[i].pin,buttonList[i].val);
		}
	}
   nowtime = millis();
   if(nowtime > oldtime + expireTime)
   {
   		oldtime = MAX_INT; // cancel timer;
   		timer_expired(); // timer can be reset here
   }
    
           // notifica que o timer expirou
// inicialização da API
// inicialização do usuário
// detecta novos eventos 
// notifica o usuário 
// detecta novos eventos 
// notifica o usuário
}