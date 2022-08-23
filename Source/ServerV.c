#include "Wrapper.h"
#include "pthread.h" //Gestione tramite MUTEX file .txt

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //Dichiarazione globale Mutex;

void CheckWhereFrom(struct record_gp * gp);

void CheckWhereFrom(struct record_gp * gp){
    if (gp==NULL){
        fprintf(stderr,"Package Green Pass Vuoto, ritorno \n");
        return;
    }
    if (gp->From=="CV") { //Proviene da CentroVaccinale
    printf("[+] Registrazione in Corso Richiesta da Centro Vaccinale \n");

    pthread_mutex_lock(&mutex); //Entra in mutua esclusione


    }
}

int main(int argc, char *argv[]){
    int list_fd, conn_fd;
    struct sockaddr_in server_v;
    socklen_t len;
    pid_t pid;
    FILE *fgp;

    list_fd=wrapped_socket(AF_INET,SOCK_STREAM,0);

    //SockAddr del ServerV
    server_v.sin_family = AF_INET;
    server_v.sin_addr.s_addr = htonl(INADDR_ANY);
    server_v.sin_port= htons(31);

    wrapped_bind(list_fd,(struct sockaddr *)&server_v,sizeof(server_v));

    printf("[+] Bind effettuato \n");
    wrapped_listen(list_fd,1024);

    printf("[+] Listen in corso\n");

    while(1){
        conn_fd = wrapped_accept(list_fd, (struct sockaddr *) NULL,NULL);
        pid=fork();

        if(pid<0){
            perror("Fork Errato");
            close(conn_fd);
            exit(-1);
        }

        //Child
        if (pid==0){
            //Lettura in input packeg
            struct record_gp temp_gp;

            printf("[+] Lettura Package dal Socket \n");

            wrapped_fullread(conn_fd,&temp_gp,sizeof(struct record_gp));
            
            printf("[+] Lettura package fatto \n");

            close(conn_fd);

            //controllo file input
        if((fv=fopen("vector.txt","r"))==NULL){
            fprintf(stderr,"Errore apertura file \n");
             close(list_fd);
             exit(0);
        } 
    


            close(list_fd);

            printf("[-] Chiusura Connesione e Fork in corso \n");

            printgp(&temp_gp);


            exit(0);

        } else {
            close(0);
        }
    }
}