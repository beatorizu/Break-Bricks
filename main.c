#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Anota��o:
#include <allegro.h>
//dimens�o da tela
#define MAX_X 800
#define MAX_Y 600
//dimens�o da tela virtual, no caso para o uso de scroll
#define V_MAX_X 0
#define V_MAX_Y 0
//define a intensidade de cores
#define COLOR_BITS 8

#define PASSO 2
//define o n�mero de imagens de vetor
#define s 6

void init();
void deinit();
void drawStone();               //fun��o para desenhar os blocos
void drawTelaInicial();         //fun��o para desenhar tela inicial
void drawTelaJogo();            //fun��o para desenhar tela jogo
void drawTelaCred();            //fun��o para desenhar tela cr�ditos
void destroyStone();            //fun��o para liberar a mem�ria usada pelo desenho dos blocos
void closeGame();               //fun��o para finalizar o jogo
void incrementa_temporizador(); //incrementa o temporizador
void incrementa_x();
void incrementa_y();
void addPont(int p); //adiciona pontos as variaveis globais
void addLife();      //adiciona uma vida
void subLife();      //retira uma vida
//Os par�metros de paleta do draw_sprite est�o como NULL
//estrutura de pontos, com as cordenadas X e Y
struct pont
{
     int x, y;
} p1, p2;

volatile int exit_program = FALSE; //vari�vel global para controlar a sa�da do programa
volatile int temporizador;         //vari�vle global para controlar o tempo
volatile int xx;
volatile int yy;
int cs, vidas = 3, pont = 0, pontV = 0;
//cs = contador para a fun��o drawStone;
//vidas = vidas do jogo
//pont = pontua��o geral do jogo
//pontV = pontua��o para ganhar vidas
//sJogo = se for verdadeiro mant�m o jogo, sen�o pausa ou sai para o menu inicial

BITMAP *prato, *tela, *ametista[s], *lapislazuli[s], *esmeralda[s], *ouro[s], *citrino[s], *rubi[s], *ball, *play[2], *cred[2], *sair[2], *logo, *cursor, *bola;
//ponteiros para as imagens utilizadas no jogo

SAMPLE *breakBlockGlass, *ring;

enum
{
     telaInicial,
     telaJogo,
     telaCred
};
//enums para cada tela de jogo que ser� controlado pelo INT statusTela que ser� iniciado com telaInicial
int statusTela;
int main()
{
     init();
     while (!exit_program)
     { //enquanto a vari�vel exit_program�vel for n�o falso, executa os comandos
          if (statusTela == telaInicial)
          {
               drawTelaInicial();
          }
          else if (statusTela == telaJogo)
          {
               drawTelaJogo();
          }
          else
          {
               drawTelaCred();
          }
     }
     deinit();
     return 0;
}
END_OF_MAIN()

void init()
{
     int depth, res;
     allegro_init();
     depth = desktop_color_depth();
     if (depth == 0)
          depth = 32;
     set_color_depth(depth);
     res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, MAX_X, MAX_Y, V_MAX_X, V_MAX_Y);
     set_window_title("Break Bricks"); //muda o t�tulo no topo da janela
     if (res != 0)
     {
          allegro_message(allegro_error);
          exit(-1);
     }
     install_timer();
     install_keyboard();
     install_mouse();
     install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
     tela = create_bitmap(MAX_X, MAX_Y);                         //cria tela auxiliar
     breakBlockGlass = load_sample("sounds/ice-block-drop.wav"); //inicia o som do bloco
     ring = load_sample("sounds/ringsSonic.wav");                //inicia o som do bloco
     statusTela = telaInicial;
     set_close_button_callback(closeGame); //habilita o bot�o 'fechar(X)', tem como par�metro uma fun��o para finalaza��o do game
}

void incrementa_temporizador()
{
     temporizador++;
}
END_OF_FUNCTION(incrementa_temporizador)

void incrementa_x()
{
     xx++;
}
END_OF_FUNCTION(incrementa_x)
void incrementa_y()
{
     yy++;
}
END_OF_FUNCTION(incrementa_y)
void loadStone()
{
     for (cs = 0; cs < 6; cs++)
     {
          lapislazuli[cs] = load_bitmap("draw/lapislazuli.bmp", NULL);
     }
     for (cs = 0; cs < 6; cs++)
     {
          esmeralda[cs] = load_bitmap("draw/esmeralda.bmp", NULL);
     }
     for (cs = 0; cs < 6; cs++)
     {
          rubi[cs] = load_bitmap("draw/rubi.bmp", NULL);
     }
     for (cs = 0; cs < 6; cs++)
     {
          citrino[cs] = load_bitmap("draw/citrino.bmp", NULL);
     }
     for (cs = 0; cs < 6; cs++)
     {
          ouro[cs] = load_bitmap("draw/ouro.bmp", NULL);
     }
     for (cs = 0; cs < 6; cs++)
     {
          ametista[cs] = load_bitmap("draw/ametista.bmp", NULL);
     }
     //cada la�o de for ir� carregar um vetor de ret�ngulos
}
END_OF_FUNCTION(loadStone)

void drawStone()
{
     p1.x = MAX_X / 2 - 240;
     p1.y = MAX_Y / 10;
     for (cs = 0; cs < 6; cs++)
     {
          draw_sprite(tela, lapislazuli[cs], p1.x, p1.y);
          p1.x += 80;
     }
     p1.x = 160;
     p1.y += 30;
     for (cs = 0; cs < 6; cs++)
     {
          draw_sprite(tela, esmeralda[cs], p1.x, p1.y);
          p1.x += 80;
     }
     p1.x = 160;
     p1.y += 30;
     for (cs = 0; cs < 6; cs++)
     {
          draw_sprite(tela, rubi[cs], p1.x, p1.y);
          p1.x += 80;
     }
     p1.x = 160;
     p1.y += 30;
     for (cs = 0; cs < 6; cs++)
     {
          draw_sprite(tela, citrino[cs], p1.x, p1.y);
          p1.x += 80;
     }
     p1.x = 160;
     p1.y += 30;
     for (cs = 0; cs < 6; cs++)
     {
          draw_sprite(tela, ouro[cs], p1.x, p1.y);
          p1.x += 80;
     }
     p1.x = 160;
     p1.y += 30;
     for (cs = 0; cs < 6; cs++)
     {
          draw_sprite(tela, ametista[cs], p1.x, p1.y);
          p1.x += 80;
     }
     //cada la�o de for ir� desenhar um vetor de ret�ngulos
}
END_OF_FUNCTION(drawStone)

//FUN�AO DA CLISAO DA BOLINHA
int colli(int x, int y, int w1, int h1, int x2, int y2, int w2, int h2)
{
     if ((x > x2 + w2) || (y > y2 + h2) || (x2 > x + w1) || (y2 > y + h1))
          return FALSE;
     else
          return TRUE;
}
END_OF_FUNCTION(colli)
//FIM DA FUN��Oda bolinha

void destroyStone()
{
     for (cs = 0; cs < 6; cs++)
     {
          destroy_bitmap(lapislazuli[cs]);
     }
     for (cs = 0; cs < 6; cs++)
     {
          destroy_bitmap(esmeralda[cs]);
     }
     for (cs = 0; cs < 6; cs++)
     {
          destroy_bitmap(rubi[cs]);
     }
     for (cs = 0; cs < 6; cs++)
     {
          destroy_bitmap(citrino[cs]);
     }
     for (cs = 0; cs < 6; cs++)
     {
          destroy_bitmap(ouro[cs]);
     }
     for (cs = 0; cs < 6; cs++)
     {
          destroy_bitmap(ametista[cs]);
     }
     //cada la�o de for ir� apagar um vetor de ret�ngulos
}
END_OF_FUNCTION(destroyStone)

BITMAP *t, *fim;
int rands = 0;
void drawTelaJogo()
{
     BITMAP *win;
     win = load_bitmap("draw/win.bmp", NULL);
     loadStone();
     int sJogo = FALSE, exit_screen = FALSE, statusJogo = FALSE;
     temporizador = 0;
     pont = 0;
     pontV = 0;
     statusJogo = FALSE;
     LOCK_FUNCTION(incrementa_temporizador);
     LOCK_VARIABLE(temporizador);
     install_int_ex(incrementa_temporizador, SECS_TO_TIMER(1));
     //timers bolinha
     xx = 0;
     yy = 0;
     LOCK_FUNCTION(incrementa_x);
     LOCK_VARIABLE(xx);
     install_int_ex(incrementa_x, SECS_TO_TIMER(1));

     LOCK_FUNCTION(incrementa_y);
     LOCK_VARIABLE(yy);
     install_int_ex(incrementa_y, SECS_TO_TIMER(1));
     //fim timers bolinha
     bola = load_bitmap("draw/bolinha.bmp", NULL);
     prato = load_bitmap("draw/prato.bmp", NULL);
     t = load_bitmap("draw/teste2.bmp", NULL);
     fim = load_bitmap("draw/gameover.bmp", NULL);

     int x = 400, y = 400, x2 = 300, y2 = 558, area = 0;
     cs = 0;
     int temp = 0, ganha = 1000;

     int topo = 0, esq = 0, di = 0, baixo = 0;
     while (!exit_program && !exit_screen)
     {
          if (key[KEY_BACKSPACE])
          {
               vidas = 3;
               exit_screen = TRUE;
               statusTela = telaInicial;
          }
          if (pontV == 1200)
          { //se a variavel pontV acumular mais 3600 pontos, ir� adicionar uma vida e ir� zerar pontV
               addLife();
               pontV = 0;
          }
          p1.x = MAX_X / 2 - 240;
          p1.y = MAX_Y / 10;
          textprintf_ex(tela, font, MAX_X / 2, MAX_Y / 60, makecol(255, 255, 255), -1, "Tempo: %d", temporizador);
          textprintf_ex(tela, font, MAX_X / 80, MAX_Y / 60, makecol(255, 255, 255), -1, "Vidas: %d", vidas);
          textprintf_ex(tela, font, MAX_X / 80, MAX_Y / 60 + 15, makecol(255, 255, 255), -1, "Pontos: %d", pont);
          drawStone();
          draw_sprite(tela, prato, x2, y2);
          draw_sprite(tela, bola, x, y);
          if (x2 >= 3)
          {
               if ((key[KEY_LEFT]) && (!key[KEY_RIGHT]))
               {
                    x2--;
               }
          }
          if (x2 <= 600)
          {
               if ((key[KEY_RIGHT]) && (!key[KEY_LEFT]))
               {
                    x2++;
               }
          }

          if (esq == 1)
          {

               x++;
               if (x == 800)
               {
                    esq = 0;
               }
          }
          if (esq == 0)
          {

               x--;
               if (x == 5)
               {
                    esq = 1;
               }
          }
          if (topo == 0)
          {
               y--;
               if (y == 35)
               {
                    topo = 1;
               }
          }
          if (pont >= 4200)
          {
               //mensagem de vitoria
               draw_sprite(tela, win, MAX_X / 2 - 157, MAX_Y / 2 - 45);
               readkey();
               vidas = 3;
          }

          //COLISAO PRATO BOLINHA
          if (colli(x, y, bola->w, bola->h, x2, y2, prato->w, prato->h) == TRUE)
          {

               rands = rand() % 2;
               if (rands == 1)
               {
                    esq = 1;
               }
               else
               {
                    esq = 0;
               }
               if (topo == 0)
               {
                    topo = 1;
               }
               if (topo == 1)
               {
                    topo = 0;
               }
          }
          //ACABA COLISAO PRATO BOLINHA
          if (topo == 1)
          {
               y++;
               if (y == 600)
               {
                    if (vidas > 0)
                         subLife();
                    topo = 0;
               }
          }
          if (vidas == 0)
          {
               draw_sprite(tela, fim, MAX_X / 2 - 160, MAX_Y / 2 - 17);
               readkey();
               pont = 0;
          }
          if (y <= 233 && x >= 160 && x <= 630 && y >= 30)
          {
               if (y <= 233 && y >= 30 && x >= 572 && x <= 642)
               {
                    if (y <= 240 && y >= 210)
                    {
                         if (ametista[5] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ametista[5] = t;
                    }
                    if (y <= 210 && y >= 180)
                    {
                         if (ouro[5] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ouro[5] = t;
                    }
                    if (y <= 180 && y >= 150)
                    {
                         if (citrino[5] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         citrino[5] = t;
                    }
                    if (y <= 150 && y >= 120)
                    {

                         if (rubi[5] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         rubi[5] = t;
                    }
                    if (y <= 120 && y >= 90)
                    {

                         if (esmeralda[5] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         esmeralda[5] = t;
                    }
                    if (y <= 90 && y >= 30)
                    {

                         if (lapislazuli[5] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         lapislazuli[5] = t;
                    }
               }
               if (y <= 231 && y >= 37 && x >= 485 && x <= 555)
               {

                    if (y <= 240 && y >= 210)
                    {

                         if (ametista[4] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ametista[4] = t;
                    }
                    if (y <= 210 && y >= 180)
                    {

                         if (ouro[4] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ouro[4] = t;
                    }
                    if (y <= 180 && y >= 150)
                    {

                         if (citrino[4] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         citrino[4] = t;
                    }
                    if (y <= 150 && y >= 120)
                    {

                         if (rubi[4] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         rubi[4] = t;
                    }
                    if (y <= 120 && y >= 90)
                    {

                         if (esmeralda[4] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         esmeralda[4] = t;
                    }
                    if (y <= 90 && y >= 30)
                    {

                         if (lapislazuli[4] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         lapislazuli[4] = t;
                    }
               }
               if (y <= 231 && y >= 37 && x >= 398 && x <= 468)
               {

                    if (y <= 240 && y >= 210)
                    {

                         if (ametista[3] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ametista[3] = t;
                    }
                    if (y <= 210 && y >= 180)
                    {

                         if (ouro[3] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ouro[3] = t;
                    }
                    if (y <= 180 && y >= 150)
                    {

                         if (citrino[3] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         citrino[3] = t;
                    }
                    if (y <= 150 && y >= 120)
                    {

                         if (rubi[3] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         rubi[3] = t;
                    }
                    if (y <= 120 && y >= 90)
                    {

                         if (esmeralda[3] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         esmeralda[3] = t;
                    }
                    if (y <= 90 && y >= 30)
                    {

                         if (lapislazuli[3] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         lapislazuli[3] = t;
                    }
               }
               if (y <= 231 && y >= 37 && x >= 311 && x <= 381)
               {

                    if (y <= 240 && y >= 210)
                    {

                         if (ametista[2] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ametista[2] = t;
                    }
                    if (y <= 210 && y >= 180)
                    {

                         if (ouro[2] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ouro[2] = t;
                    }
                    if (y <= 180 && y >= 150)
                    {

                         if (citrino[2] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         citrino[2] = t;
                    }
                    if (y <= 150 && y >= 120)
                    {

                         if (rubi[2] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         rubi[2] = t;
                    }
                    if (y <= 120 && y >= 90)
                    {

                         if (esmeralda[2] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         esmeralda[2] = t;
                    }
                    if (y <= 90 && y >= 30)
                    {

                         if (lapislazuli[2] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         lapislazuli[2] = t;
                    }
               }
               if (y <= 231 && y >= 37 && x >= 224 && x <= 294)
               {

                    if (y <= 240 && y >= 210)
                    {

                         if (ametista[1] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ametista[1] = t;
                    }
                    if (y <= 210 && y >= 180)
                    {

                         if (ouro[1] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         ouro[1] = t;
                    }
                    if (y <= 180 && y >= 150)
                    {

                         if (citrino[1] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         citrino[1] = t;
                    }
                    if (y <= 150 && y >= 120)
                    {

                         if (rubi[1] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         rubi[1] = t;
                    }
                    if (y <= 120 && y >= 90)
                    {

                         if (esmeralda[1] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                         }
                         esmeralda[1] = t;
                    }
                    if (y <= 90 && y >= 30)
                    {

                         if (lapislazuli[1] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                              pont += 100;
                         }
                         lapislazuli[1] = t;
                    }
               }
               if (y <= 231 && y >= 37 && x >= 137 && x <= 217)
               {

                    if (y <= 240 && y >= 210)
                    {

                         if (ametista[0] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              pont += 100;
                         }
                         ametista[0] = t;
                    }
                    if (y <= 210 && y >= 180)
                    {

                         if (ouro[0] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                              pont += 100;
                         }
                         ouro[0] = t;
                    }
                    if (y <= 180 && y >= 150)
                    {

                         if (citrino[0] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                              pont += 100;
                         }
                         citrino[0] = t;
                    }
                    if (y <= 150 && y >= 120)
                    {

                         if (rubi[0] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                              pont += 100;
                         }
                         rubi[0] = t;
                    }
                    if (y <= 120 && y >= 90)
                    {
                         if (esmeralda[0] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                              pont += 100;
                         }
                         esmeralda[0] = t;
                    }
                    if (y <= 90 && y >= 30)
                    {
                         if (lapislazuli[0] != t)
                         {
                              pont += 100;
                              pontV += 100;
                              play_sample(breakBlockGlass, 255, 128, 1000, 0);
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 1)
                              {
                                   esq = 0;
                              }
                              if (esq == 0)
                              {
                                   esq = 1;
                              }
                              if (topo == 1)
                              {
                                   topo = 0;
                              }
                              if (topo == 0)
                              {
                                   topo = 1;
                              }
                              pont += 100;
                         }
                         lapislazuli[0] = t;
                    }
               }
          }
          draw_sprite(screen, tela, 0, 0);
          clear(tela);
     }
     destroyStone();
}
END_OF_FUNCTION(drawTelaJogo)

void drawTelaCred()
{
     BITMAP *cred;
     cred = load_bitmap("draw/creditos.bmp", NULL);
     int sJogo = FALSE, exit_screen = FALSE;
     while (!exit_program && !exit_screen)
     {
          if (key[KEY_BACKSPACE])
          {
               exit_screen = TRUE;
               statusTela = telaInicial;
          }
          draw_sprite(tela, cred, 0, 0);
          draw_sprite(screen, tela, 0, 0);
          clear(tela);
     }
}

void drawTelaInicial()
{
     play[0] = load_bitmap("draw/play.bmp", NULL);
     play[1] = load_bitmap("draw/playSelecionado.bmp", NULL);
     cred[0] = load_bitmap("draw/credits.bmp", NULL);
     cred[1] = load_bitmap("draw/creditsSelecionado.bmp", NULL);
     sair[0] = load_bitmap("draw/exit.bmp", NULL);
     sair[1] = load_bitmap("draw/exitSelecionado.bmp", NULL);
     logo = load_bitmap("draw/BreakBricks.bmp", NULL);
     cursor = load_bitmap("draw/cursor.bmp", NULL);
     set_mouse_sprite(cursor);
     int sJogo = FALSE, exit_screen = FALSE;
     while (!exit_program && !exit_screen)
     {
          if (key[KEY_ESC])
          { //se a tecla esc for precionada, a vari�vel exit_program recebe TRUE, com isso, o looping principal � interrompido
               exit_program = TRUE;
          }
          if (mouse_x > MAX_X / 2 - 77 && mouse_x < MAX_X / 2 + 77 && mouse_y > MAX_Y / 2 - 62 && mouse_y < MAX_Y / 2)
          {
               draw_sprite(tela, play[1], MAX_X / 2 - 77, MAX_Y / 2 - 62);
               if (mouse_b == 1)
               {
                    mouse_b = 0;
                    play_sample(ring, 255, 128, 1000, 0);
                    exit_screen = TRUE;
                    statusTela = telaJogo;
               }
          }
          if (mouse_x > MAX_X / 2 - 140 && mouse_x < MAX_X / 2 + 140 && mouse_y > MAX_Y / 2 + 34 && mouse_y < MAX_Y / 2 + 130)
          {
               draw_sprite(tela, cred[1], MAX_X / 2 - 140, MAX_Y / 2 + 34);
               if (mouse_b == 1)
               {
                    mouse_b = 0;
                    play_sample(ring, 255, 128, 1000, 0);
                    exit_screen = TRUE;
                    statusTela = telaCred;
               }
          }
          if (mouse_x > MAX_X / 2 - 55 && mouse_x < MAX_X / 2 + 55 && mouse_y > MAX_Y / 2 + 175 && mouse_y < MAX_Y / 2 + 225)
          {
               draw_sprite(tela, sair[1], MAX_X / 2 - 55, MAX_Y / 2 + 175);
               if (mouse_b == 1)
               {
                    exit_program = TRUE;
                    exit_screen = TRUE;
               }
          }
          draw_sprite(tela, logo, MAX_X / 2 - 127, 0);
          draw_sprite(tela, play[0], MAX_X / 2 - 77, MAX_Y / 2 - 62);
          draw_sprite(tela, cred[0], MAX_X / 2 - 140, MAX_Y / 2 + 34);
          draw_sprite(tela, sair[0], MAX_X / 2 - 55, MAX_Y / 2 + 175);
          show_mouse(tela);
          draw_sprite(screen, tela, 0, 0);
          clear(tela);
     }
     destroy_bitmap(play[0]);
     destroy_bitmap(play[1]);
     destroy_bitmap(cred[0]);
     destroy_bitmap(cred[1]);
     destroy_bitmap(sair[0]);
     destroy_bitmap(sair[1]);
     destroy_bitmap(logo);
     destroy_bitmap(cursor);
}
END_OF_FUNCTION(drawTelaInicial)

void addPont(int p)
{ //dependendo da cordenada(o valor de y), p ter� um valor que ser� adicionado a pont e pontV
     pont += p;
     pontV += p;
}

void addLife()
{
     vidas += 1;
}

void subLife()
{
     vidas -= 1;
}

void closeGame()
{
     exit_program = TRUE;
}
END_OF_FUNCTION(closeGame)

void deinit()
{
     clear_keybuf();
}
