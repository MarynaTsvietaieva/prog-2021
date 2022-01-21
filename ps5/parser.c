#include <string.h>
#include <stdio.h>
#include "parser.h"
#include <stdlib.h>


struct parser* create_parser(){
  struct parser* parser = calloc(1, sizeof(struct parser));  
  
  parser -> commands = create_container(NULL, COMMAND, create_command("KONIEC", "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.", "\\s*[Kk][Oo][Nn][Ii][Ee][Cc]\\s*", 1));
  create_container(parser -> commands, COMMAND, create_command("SEVER","Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.","\\s*[Ss][Ee][Vv][Ee][Rr]\\s*", 1));
  create_container(parser -> commands, COMMAND, create_command("JUH","Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.","\\s*[Jj][Uu][Hh]\\s*", 1));
  create_container(parser -> commands, COMMAND, create_command("VYCHOD","Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.","\\s*[Vv][Yy][Cc][Hh][Oo][Dd]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("ZAPAD","Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.","\\s*[Zz][Aa][Pa][Aa][Dd]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("ROZHLIADNI SA","Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.","\\s*[rR][oO][zZ][hH][lL][iI][aA][dD][nN][iI][ ][sS][aA]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("PRIKAZY","Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.","\\s*[Pp][Rr][Ii][Kk][Aa][Zz][Yy]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("VERZIA","Príkaz zobrazí číslo verzie hry, ľubovoľný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).","\\s*[Vv][Ee][Rr][Zz][Ii][Aa]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("RESTART","Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.","\\s*[Rr][Ee][Ss][Tt][Aa][Rr][Tt]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("O HRE","Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …","\\s*[oO][ ][hH][rR][eE]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("VEZMI","Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.).","\\s*[Vv][Ee][Zz][Mm][Ii]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("POLOZ","Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)","\\s*[Pp][Oo][Ll][Oo][Zz]\\s*",1)); 
  create_container(parser -> commands, COMMAND, create_command("INVENTAR","Zobrazí obsah hráčovho batohu.","\\s*[Ii][Nn][Vv][Ee][Nn][Tt][Aa][Rr]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("POUZI","Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).","\\s*[Pp][Oo][Uu][Zz][Ii]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("ULOZ","Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.","\\s*[Uu][Ll][Oo][Zz]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("PRESKUMAJ","Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).","\\s*[Pp][Rr][Ee][Ss][Kk][Uu][Mm][Aa][Jj]\\s*",1));
  create_container(parser -> commands, COMMAND, create_command("NAHRAJ","Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.","\\s*[Nn][Aa][Hh][Rr][Aa][Jj]\\s*",1));


  parser -> history = create_container(NULL, COMMAND, create_command("O HRE", "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", "\\s*[Oo][ ][Hh][Rr][Ee]\\s*", 1));
  return parser;
}

struct parser* destroy_parser(struct parser* parser){
 if(parser != NULL){
   if(parser -> commands != NULL){
    destroy_containers(parser -> commands);
   }
   if(parser -> history != NULL){
     destroy_containers(parser -> history);
   }
  free(parser);
 }
return NULL;
}

struct command* parse_input(struct parser* parser, char* input){
  if(parser == NULL || input == NULL){
  return NULL;
  }
 
  if(strlen(input) == 0){
   return NULL;
  }
struct parser* p = parser;
  while(p -> commands != NULL){
   if(p -> commands -> command != NULL){
       //printf("%s\n", parser -> commands -> command -> name);
       if(regexec(&p -> commands -> command -> preg, input, 0, NULL, 0) != REG_NOMATCH){
        
        return p -> commands -> command; 
       }
       p -> commands = p -> commands -> next;
    }
   }
 return NULL;
}


