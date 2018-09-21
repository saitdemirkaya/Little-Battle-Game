#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct players/*monsters and heros*/
{
    char *type;
    char *name;
    int HP;
    int damage;
    int number;
    int row;
    int column;
    int XP;
    int count;
};
/*Count: How many monsters or heroes are there
Number: all monsters start to attack in the order of: 1.MINDFLAYER, 2.TROLL, 3.GOBLIN*/
struct players *ptr_monster;
struct players *ptr_hero;
struct dynammic_array{/*dynammic array for map*/
	char **arr;
	int row;
	int column;
	int count;
};
struct dynammic_array *matris;
/*Map Command control */
void show_map(char *token,FILE *f){
	int i,j;
					if(!strcmp(token,"MAP\n")||!strcmp(token,"MAP")){
					fprintf(f,"\nMAP STATUS\n");
							for (i = 0; i < matris->row; i++){
								for (j = 0; j < matris->column; j++){
									fprintf(f, "%c ", matris->arr[i][j]);
								}		
						fprintf(f,"\n");	
					}
					
					}else if(!strcmp(token,"HERO\n")||!strcmp(token,"HERO")){
						fprintf(f,"\nHERO STATUS\n");
						for(i=0;i<ptr_hero->count;i++){
							fprintf(f,"%s HP:%d XP:%d\n",(ptr_hero+i)->name,(ptr_hero+i)->HP,(ptr_hero+i)->XP);
						}
					}else {
						fprintf(f,"\nMONSTER STATUS\n");
						for(i=0;i<ptr_monster->count;i++){
							fprintf(f,"%s HP:%d\n",(ptr_monster+i)->name,(ptr_monster+i)->HP);
						}
					}
}
/*game finish control.If all monsters or heroes died, game over*/
void game_finish(FILE *f){
	int i;
	int hero_count=0,monster_count=0;
	for(i=0;i<ptr_hero->count;i++){
		if((ptr_hero+i)->HP==0){
			hero_count++;
		}
	}
	if(hero_count==ptr_hero->count){
		fprintf(f,"ALL HEROES DEAD!");
		exit(1);
	}
	for(i=0;i<ptr_monster->count;i++){
		if((ptr_monster+i)->HP==0){
			monster_count++;
		}
	}
	if(monster_count==ptr_monster->count){
		fprintf(f,"\nALL MONSTER ARE DEAD!");
		exit(1);
	}
}
/*copy string*/
void copy1( char *s1, const char *s2 ){
	int i;
	for ( i = 0; s2[ i ] != '\0'; i++ )
	s1[ i ] = s2[ i ];
	s1[ i ] = 0;
}

void attack(char *token1,FILE *f){
	int i,j;
	if(!strcmp(token1,"HERO\n")||!strcmp(token1,"HERO")){
						fprintf(f,"\nHEROES ATTACKED\n");
						for(i=0;i<ptr_hero->count;i++){/*With the first cycle, all heroes control where they can attack in turn.*/
							if((ptr_hero+i)->HP!=0){/*the hero can not attack if dead*/
							/*All squares from 1 to 8 are checked.*/
								if((ptr_hero+i)->row-1>=0){/*Number 1 square*/
								for(j=0;j<ptr_monster->count;j++){/*all monsters are looked at.*/
									if((ptr_monster+j)->HP!=0){/*the hero can not attack if monster dead*/
										if((ptr_monster+j)->row==(ptr_hero+i)->row-1&&(ptr_monster+j)->column==(ptr_hero+i)->column){/*control coordinate*/
										(ptr_monster+j)->HP=(ptr_monster+j)->HP-(ptr_hero+i)->damage;
										if((ptr_monster+j)->HP<=0){/*if the attacked character is killed, thats coordinate point is set and hero's XP increasing*/
											(ptr_monster+j)->HP=0;/*monster health must be zero*/
											(ptr_hero+i)->XP++;
											matris->arr[(ptr_monster+j)->row][(ptr_monster+j)->column]='.';
										}
									}
									}
									
								}
							}
							if((ptr_hero+i)->row-1>=0&&(ptr_hero+i)->column+1<=matris->column-1){/*Number 2 square*/
								for(j=0;j<ptr_monster->count;j++){
									if((ptr_monster+j)->HP!=0){
										if((ptr_monster+j)->row==(ptr_hero+i)->row-1&&(ptr_monster+j)->column==(ptr_hero+i)->column+1){
										(ptr_monster+j)->HP=(ptr_monster+j)->HP-(ptr_hero+i)->damage;
										if((ptr_monster+j)->HP<=0){
											(ptr_monster+j)->HP=0;
											(ptr_hero+i)->XP++;
											matris->arr[(ptr_monster+j)->row][(ptr_monster+j)->column]='.';
										}
									}
									}
								
								}
							}
							
							if((ptr_hero+i)->column+1<=matris->column-1){/*Number 3 square*/
								for(j=0;j<ptr_monster->count;j++){
									if((ptr_monster+j)->HP!=0){
										if((ptr_monster+j)->row==(ptr_hero+i)->row&&(ptr_monster+j)->column==(ptr_hero+i)->column+1){
										(ptr_monster+j)->HP=(ptr_monster+j)->HP-(ptr_hero+i)->damage;
										if((ptr_monster+j)->HP<=0){
											(ptr_monster+j)->HP=0;
											(ptr_hero+i)->XP++;
											matris->arr[(ptr_monster+j)->row][(ptr_monster+j)->column]='.';
										}
									  }	
									}
									
								}
							}
							if((ptr_hero+i)->row+1<=matris->row-1&&(ptr_hero+i)->column+1<=matris->column-1){/*Number 4 square*/
								for(j=0;j<ptr_monster->count;j++){
									if((ptr_monster+j)->HP!=0){
										if((ptr_monster+j)->row==(ptr_hero+i)->row+1&&(ptr_monster+j)->column==(ptr_hero+i)->column+1){
										(ptr_monster+j)->HP=(ptr_monster+j)->HP-(ptr_hero+i)->damage;
										if((ptr_monster+j)->HP<=0){
											(ptr_monster+j)->HP=0;
											(ptr_hero+i)->XP++;
											matris->arr[(ptr_monster+j)->row][(ptr_monster+j)->column]='.';
										}
									}
									}
									
								}
							}
							if((ptr_hero+i)->row+1<=matris->row-1){/*Number 5 square*/
								for(j=0;j<ptr_monster->count;j++){
									if((ptr_monster+j)->HP!=0){
										if((ptr_monster+j)->row==(ptr_hero+i)->row+1&&(ptr_monster+j)->column==(ptr_hero+i)->column){
										(ptr_monster+j)->HP=(ptr_monster+j)->HP-(ptr_hero+i)->damage;
										if((ptr_monster+j)->HP<=0){
											(ptr_monster+j)->HP=0;
											(ptr_hero+i)->XP++;
											matris->arr[(ptr_monster+j)->row][(ptr_monster+j)->column]='.';
										}
									}
									}
									
								}
							}
							if((ptr_hero+i)->row+1<=matris->row-1&&(ptr_hero+i)->column-1>=0){/*Number 6 square*/
								for(j=0;j<ptr_monster->count;j++){
									if((ptr_monster+j)->HP!=0){
										if((ptr_monster+j)->row==(ptr_hero+i)->row+1&&(ptr_monster+j)->column==(ptr_hero+i)->column-1){
										(ptr_monster+j)->HP=(ptr_monster+j)->HP-(ptr_hero+i)->damage;
										if((ptr_monster+j)->HP<=0){
											(ptr_monster+j)->HP=0;
											(ptr_hero+i)->XP++;
											matris->arr[(ptr_monster+j)->row][(ptr_monster+j)->column]='.';
										}
									}
									}
									
								}
							}
							if((ptr_hero+i)->column-1>=0){/*Number 7 square*/
								for(j=0;j<ptr_monster->count;j++){
									if((ptr_monster+j)->HP!=0){
											if((ptr_monster+j)->row==(ptr_hero+i)->row&&(ptr_monster+j)->column==(ptr_hero+i)->column-1){
										(ptr_monster+j)->HP=(ptr_monster+j)->HP-(ptr_hero+i)->damage;
										if((ptr_monster+j)->HP<=0){
											(ptr_monster+j)->HP=0;
											(ptr_hero+i)->XP++;
											matris->arr[(ptr_monster+j)->row][(ptr_monster+j)->column]='.';
										}
									}
									}
								
								}
							}
							if((ptr_hero+i)->row-1>=0&&(ptr_hero+i)->column-1>=0){/*Number 8 square*/
								for(j=0;j<ptr_monster->count;j++){
									if((ptr_monster+j)->HP!=0){
										if((ptr_monster+j)->row==(ptr_hero+i)->row-1&&(ptr_monster+j)->column==(ptr_hero+i)->column-1){
										(ptr_monster+j)->HP=(ptr_monster+j)->HP-(ptr_hero+i)->damage;
										if((ptr_monster+j)->HP<=0){
											(ptr_monster+j)->HP=0;
											(ptr_hero+i)->XP++;
											matris->arr[(ptr_monster+j)->row][(ptr_monster+j)->column]='.';
										}
									}
									}
									
								}
							}
							}
							
							
						}
						game_finish(f);/*finish control*/
					}else{//MONSTER
						fprintf(f,"\nMONSTERS ATTACKED\n");
						/*With the first cycle, all monsters control where they can attack in turn.Same heroes.*/
						for(i=0;i<ptr_monster->count;i++){
							if((ptr_monster+i)->HP!=0){
								if((ptr_monster+i)->row-1>=0){/*Number 1 square*/
								for(j=0;j<ptr_hero->count;j++){
									if((ptr_hero+j)->HP!=0){
											if((ptr_hero+j)->row==(ptr_monster+i)->row-1&&(ptr_hero+j)->column==(ptr_monster+i)->column){
										(ptr_hero+j)->HP=(ptr_hero+j)->HP-(ptr_monster+i)->damage;
										if((ptr_hero+j)->HP<=0){
											(ptr_hero+j)->HP=0;
											matris->arr[(ptr_hero+j)->row][(ptr_hero+j)->column]='.';
										}
									}
									}
								}
							}
							if((ptr_monster+i)->row-1>=0&&(ptr_monster+i)->column+1<=matris->column-1){/*Number 2 square*/
								for(j=0;j<ptr_hero->count;j++){
									if((ptr_hero+j)->HP!=0){
									if((ptr_hero+j)->row==(ptr_monster+i)->row-1&&(ptr_hero+j)->column==(ptr_monster+i)->column+1){
										(ptr_hero+j)->HP=(ptr_hero+j)->HP-(ptr_monster+i)->damage;
										if((ptr_hero+j)->HP<=0){
											(ptr_hero+j)->HP=0;
											matris->arr[(ptr_hero+j)->row][(ptr_hero+j)->column]='.';
										}
									}	
									}
									
								}
							}
							if((ptr_monster+i)->column+1<=matris->column-1){/*Number 3 square*/
								for(j=0;j<ptr_hero->count;j++){
									if((ptr_hero+j)->HP!=0){
										if((ptr_hero+j)->row==(ptr_monster+i)->row&&(ptr_hero+j)->column==(ptr_monster+i)->column+1){
										(ptr_hero+j)->HP=(ptr_hero+j)->HP-(ptr_monster+i)->damage;
										if((ptr_hero+j)->HP<=0){
											(ptr_hero+j)->HP=0;
											matris->arr[(ptr_hero+j)->row][(ptr_hero+j)->column]='.';
										}
									}
									}
									
								}
							}
							if((ptr_monster+i)->row+1<=matris->row-1&&(ptr_monster+i)->column+1<=matris->column-1){/*Number 4 square*/
								for(j=0;j<ptr_hero->count;j++){
									if((ptr_hero+j)->HP!=0){
										if((ptr_hero+j)->row==(ptr_monster+i)->row+1&&(ptr_hero+j)->column==(ptr_monster+i)->column+1){
										(ptr_hero+j)->HP=(ptr_hero+j)->HP-(ptr_monster+i)->damage;
										if((ptr_hero+j)->HP<=0){
											(ptr_hero+j)->HP=0;
											matris->arr[(ptr_hero+j)->row][(ptr_hero+j)->column]='.';
										}
									}
									}
									
								}
							}
							if((ptr_monster+i)->row+1<=matris->row-1){/*Number 5 square*/
								for(j=0;j<ptr_hero->count;j++){
									if((ptr_hero+j)->HP!=0){
									if((ptr_hero+j)->row==(ptr_monster+i)->row+1&&(ptr_hero+j)->column==(ptr_monster+i)->column){
										(ptr_hero+j)->HP=(ptr_hero+j)->HP-(ptr_monster+i)->damage;
										if((ptr_hero+j)->HP<=0){
											(ptr_hero+j)->HP=0;
											matris->arr[(ptr_hero+j)->row][(ptr_hero+j)->column]='.';
										}
									}	
									}
									
								}
							}
							if((ptr_monster+i)->row+1<=matris->row-1&&(ptr_monster+i)->column-1>=0){/*Number 6 square*/
								for(j=0;j<ptr_hero->count;j++){
									if((ptr_hero+j)->HP!=0){
									if((ptr_hero+j)->row==(ptr_monster+i)->row+1&&(ptr_hero+j)->column==(ptr_monster+i)->column-1){
										(ptr_hero+j)->HP=(ptr_hero+j)->HP-(ptr_monster+i)->damage;
										if((ptr_hero+j)->HP<=0){
											(ptr_hero+j)->HP=0;
											matris->arr[(ptr_hero+j)->row][(ptr_hero+j)->column]='.';
										}
									}	
									}
									
								}
							}
							if((ptr_monster+i)->column-1>=0){/*Number 7 square*/
								for(j=0;j<ptr_hero->count;j++){
									if((ptr_hero+j)->HP!=0){
									if((ptr_hero+j)->row==(ptr_monster+i)->row&&(ptr_hero+j)->column==(ptr_monster+i)->column-1){
										(ptr_hero+j)->HP=(ptr_hero+j)->HP-(ptr_monster+i)->damage;
										if((ptr_hero+j)->HP<=0){
											(ptr_hero+j)->HP=0;
											matris->arr[(ptr_hero+j)->row][(ptr_hero+j)->column]='.';
										}
									}	
									}
									
								}
							}
							if((ptr_monster+i)->row-1>=0&&(ptr_monster+i)->column-1>=0){/*Number 8 square*/
								for(j=0;j<ptr_hero->count;j++){
									if((ptr_hero+j)->HP!=0){
										if((ptr_hero+j)->row==(ptr_monster+i)->row-1&&(ptr_hero+j)->column==(ptr_monster+i)->column-1){
										(ptr_hero+j)->HP=(ptr_hero+j)->HP-(ptr_monster+i)->damage;
										if((ptr_hero+j)->HP<=0){
											(ptr_hero+j)->HP=0;
											matris->arr[(ptr_hero+j)->row][(ptr_hero+j)->column]='.';
										}
									}
									}
									
								}
							}
							}	
						}
						game_finish(f);
					}
}
void input1_processing(char *line){
	char *token;
	int i;
	token = strtok(line,",");          
        if(!strcmp(token,"HERO")){          		
            		for(i=0;i<4;i++){/*Character has 4 features*/
            			if(i==0){/*ptr_hero->count: Karakterin kaçýncý sýrada olduðunu tutar.*/
            				(ptr_hero+ptr_hero->count)->type= (char*)malloc(sizeof(char));
            				copy1((ptr_hero+ptr_hero->count)->type,token);
						}
						if(i==1){
            				(ptr_hero+ptr_hero->count)->name= (char*)malloc(sizeof(char));
            				copy1((ptr_hero+ptr_hero->count)->name,token);
						}
						if(i==2){
            				(ptr_hero+ptr_hero->count)->HP= atoi(token);
						}
						if(i==3){
            				(ptr_hero+ptr_hero->count)->damage= atoi(token);
						}
                    token = strtok(NULL,",");
					}
						(ptr_hero+ptr_hero->count)->number=ptr_hero->count+1;
						(ptr_hero+ptr_hero->count)->XP=0;/*The XP value is set to 0 as a start.*/
						ptr_hero->count++;
		}else{
            			for(i=0;i<4;i++){/*same hereos.*/
            			if(i==0){
            				(ptr_monster+ptr_monster->count)->type= (char*)malloc(sizeof(char));
            				copy1((ptr_monster+ptr_monster->count)->type,token);
						}
						if(i==1){
            				(ptr_monster+ptr_monster->count)->name= (char*)malloc(sizeof(char));
            				copy1((ptr_monster+ptr_monster->count)->name,token);
            				
						}
						if(i==2){
            				(ptr_monster+ptr_monster->count)->HP= atoi(token);
						 }
						if(i==3){
            				(ptr_monster+ptr_monster->count)->damage= atoi(token);
            				
						 }
				    token = strtok(NULL,",");
					}
					(ptr_monster+ptr_monster->count)->number=ptr_monster->count;
					ptr_monster->count++;
		}
}
void move(char *token1, FILE *f){
	int i,j,k;
	int new_row;
	int new_column;
	fprintf(f,"\nHEROES MOVED\n");
	while(token1!=NULL){
        			if(!strcmp(token1,"HERO")){
						token1 = strtok(NULL," ");	
							while(token1!='\0'){
								for(i=0;i<ptr_hero->count;i++){/*The name given is compared to all heroes's names.*/
									if(!strcmp(token1,(ptr_hero+i)->name)){
										token1 = strtok(NULL," ");
										new_row = atoi(token1);
										token1 = strtok(NULL," ");
										new_column = atoi(token1);
											if((ptr_hero+i)->HP==0){// if dead, don't move.
											fprintf(f,"\n %s can't move.Is DEAD!.\n",(ptr_hero+i)->name);
											}else{
												if(new_row<=matris->row-1&&new_column<=matris->column-1){
													if('.'==matris->arr[new_row][new_column]){/*wall control*/
													matris->arr[(ptr_hero+i)->row][(ptr_hero+i)->column]='.';
													(ptr_hero+i)->row=new_row;
													(ptr_hero+i)->column=new_column;
													char first_char;
													first_char = (ptr_hero+i)->name[0];
													matris->arr[new_row][new_column]=first_char;	
												}else{/*Place is occupied.*/
												fprintf(f,"\n %s can't move. Place is occupied.\n",(ptr_hero+i)->name);
												}
											}else{/*There is a wall.*/
											fprintf(f,"\n %s can't move.There is a wall.\n",(ptr_hero+i)->name);
											}
										
										}
									}
								}
								token1 = strtok(NULL," ");
							}	
							}
					token1 = strtok(NULL," ");
				}
}
void input2_processing(char *line, FILE *f){
	char *token1;
	int i,j;
	token1 = strtok(line," ");
           	if(!strcmp(token1,"LOADMAP")){
           		for(i=0;i<3;i++){
        				if(i!=0){
        					if(i==1){
        						matris->row=atoi(token1);
							}else{
								matris->column=atoi(token1);
							}	
						}
        					token1 = strtok(NULL," ");
        				}
        				matris->arr = (char **)malloc(sizeof(char *) * matris->row);/*malloc for load*/
						matris->arr[0] = (char *)malloc(sizeof(char) * matris->column * matris->row);
						for(i = 0; i < matris->row; i++)
							matris->arr[i] = (*matris->arr + matris->column * i);
							for (i = 0; i < matris->row; i++)
								for (j = 0; j < matris->column; j++)
									matris->arr[i][j] = '.'; // OR *(*(arr+i)+j) = ++count
			   }else if(!strcmp(token1,"PUT")){
					while(token1!=NULL){
        					if(!strcmp(token1,"HERO")){
							token1 = strtok(NULL," ");	
							while(token1!='\0'){/*reading end of line*/
								for(i=0;i<ptr_hero->count;i++){
									if(!strcmp(token1,(ptr_hero+i)->name)){
										char first_char;
										first_char = (ptr_hero+i)->name[0];/*first char*/
										token1 = strtok(NULL," ");/*reading another tokens*/
										(ptr_hero+i)->row=atoi(token1);
										token1 = strtok(NULL," ");
										(ptr_hero+i)->column=atoi(token1);
										matris->arr[(ptr_hero+i)->row][(ptr_hero+i)->column]=first_char;
										
									}
								}
								token1 = strtok(NULL," ");
							}	
							}else if(!strcmp(token1,"MONSTER")){
							
							token1 = strtok(NULL," ");	
							while(token1!='\0'){
								for(i=0;i<ptr_monster->count;i++){
									if(!strcmp(token1,(ptr_monster+i)->name)){
										char first_char;
										first_char = (ptr_monster+i)->name[0];
										token1 = strtok(NULL," ");
										(ptr_monster+i)->row=atoi(token1);
										token1 = strtok(NULL," ");
										(ptr_monster+i)->column=atoi(token1);
										matris->arr[(ptr_monster+i)->row][(ptr_monster+i)->column]=first_char;
										
									}
								}
								token1 = strtok(NULL," ");
							}
					}
					token1 = strtok(NULL," ");
				}
			}else if(!strcmp(token1,"SHOW")){
				token1 = strtok(NULL," ");
				show_map(token1,f);
			}else if(!strcmp(token1,"ATTACK")){
				token1 = strtok(NULL," ");
				attack(token1,f);
			}else if(!strcmp(token1,"MOVE")){
				token1 = strtok(NULL," ");
				move(token1,f);
			}
			   
}
int main(int argc,char *argv[])
{
	char line[100];/*for line*/
	const char* file = NULL;
	file = argv[1];/*chars*/
	const char* file1 = NULL;
	file1 = argv[2];/*commands*/
	const char* file2 = NULL;
	file2 = argv[3];/*output*/


    FILE *fp = fopen(file, "r");
    FILE *f = fopen(file2, "w");
    char line1[100];/*for line*/
    ptr_hero = (struct players*) malloc(10*sizeof(struct players));/* space for monsters and heros*/
    ptr_monster = (struct players*) malloc(10*sizeof(struct players));
    matris = (struct dynammic_array*) malloc(sizeof(struct dynammic_array)); /*space for dynammic array*/
    ptr_hero->count=0;
    ptr_monster->count=0;
     if(fp != NULL){  
        while(fgets(line, sizeof line, fp) != NULL){
        	input1_processing(line);/*for chars_1.txt*/
		}
	}
	fclose(fp);
	FILE *fp1 = fopen(file1, "r");
	while(fgets(line1, sizeof line1, fp1) != NULL){
			input2_processing(line1,f);/*for commands_1.txt*/
	}
	fclose(fp1);
	fclose(f);
	return 0;
}
